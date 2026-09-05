---
name: c-code-style
description: Write, edit, or review C (and C-compatible header) code according to C coding style rules, then check and run clang-format to enforce formatting. Trigger on "write C code", "edit a .c/.h file", "review C code style", "format C code", "run clang-format", "check clang-format", "apply the C style guide".
---

# C code style

This skill applies whenever you are writing, editing, or reviewing `.c` or `.h`
files in a project that adopts this style guide. The full rule set lives in
[`CODING_RULES.md`](../../../CODING_RULES.md) at the repository root — that
file is the single source of truth (this repository's `README.md` is just a
symlink to it, so it renders on the GitHub front page). This skill exists to
make the rules operational: what to self-apply while writing code, and how to
run the formatter afterward.

## 1. Read the rules first

Before writing or editing C code, read `CODING_RULES.md` in this repository
(or wherever this skill was installed alongside it — if it's not there, the
checklist in step 3 below is a self-contained fallback). Do not rely on
memory of "typical" C style — several of this guide's rules are deliberately
non-default (e.g. `(void)` on zero-parameter functions, at most 2 `return`
points per function, no `stdbool.h`).

## 2. What `clang-format` fixes for you

Don't hand-format these — write reasonably and let the formatter normalize
them in step 4: indentation and spacing, brace placement, pointer-asterisk
alignment, function-prototype alignment, trailing commas in struct
initializers, blank-line and parenthesis spacing.

## 3. What `clang-format` will NOT fix — apply these yourself while writing

These are semantic or naming rules; a formatter cannot infer them. Apply them
as you write, not after:

- Names (variables, parameters, struct/enum members) are lowercase with
  underscores and **at least 3 characters**. Never a bare `__`/`_` prefix.
  `static` module-private functions use a `prv_` prefix.
- Use `stdint.h` types (`uint8_t`, `int32_t`, ...) except `char`/`float`/`double`.
  Avoid `stdbool.h`; use `1`/`0`.
- Don't rely on static initializers for `global`/`static` variables that need
  a real startup value in embedded contexts — give the module an `init()`
  function instead.
- Declare all locals at the top of a block, grouped by type, in order:
  custom structs/enums (and their pointers) → integers (widest unsigned
  first) → floating point.
- `const`-correct pointers and parameters; generic pointers are `void*`, cast
  internally, never cast a `void*` return value.
- Every function with zero parameters uses `(void)`, never empty `()`.
- Function definitions keep the return type, storage-class and qualifier
  keywords, and the function name on the same line; the opening curly bracket
  goes on the following line.
- A function has **at most 2 `return` points**: one early return for
  parameter/argument validation, one at the end. No `return` in the middle —
  use a return-value variable to accumulate the result instead.
- Check a pointer against `NULL` before dereferencing it (unless the
  surrounding code guarantees it can't be `NULL`). After `free(ptr)`,
  immediately set `ptr = NULL`.
- Boolean-treated variables are compared with `if (x)` / `if (!x)`, never
  `== 1` / `== 0`; counter/value variables use `> 0` / `== 0`, never bare
  `if (x)`.
- Comments default to Chinese. Add comments when the code alone does not make
  the intent, invariant, boundary, unit, ownership, lifetime, hardware or
  protocol constraint, or design reason clear. Apply this to functions,
  variables, macros, types, and members when needed; do not comment every
  declaration by default. Keep comments focused on that information instead
  of repeating the code.
- Structure and enumeration members need comments only when their meaning,
  unit, range, ownership, lifetime, hardware relation, protocol value, or
  other constraint is not obvious from the name and type. Align member
  comments visually when comments are present.
- Functions (including `static`) use Doxygen `/** ... */` comments with
  `@brief`, `@note`, `@param[in]`, `@param[out]`, `@param[in,out]`, and
  `@return` as applicable; descriptions remain Chinese. Use `@` commands,
  not backslash commands. Put public API comments near declarations in
  headers and private implementation comments near definitions in source
  files. Keep one canonical function contract and do not duplicate it.
- For variables, macros, types, members, and local declarations, use the
  shortest comment form that preserves the needed information: omit comments
  when the name and type are already clear, use a trailing single-line comment
  for a short explanation, use a preceding single-line comment for module
  state, and use a preceding multi-line comment only for multiple constraints,
  boundaries, ownership, lifetime, side effects, or design reasons.

## 4. Format the code

After writing or editing any `.c`/`.h` file, resolve the plugin root from this
`SKILL.md` location (three directories above it), then run the bundled formatter
script by absolute path:

```sh
<plugin-root>/scripts/check-format.sh <changed-file.c> [<changed-file.h> ...]
```

The script explicitly passes `<plugin-root>/.clang-format` to `clang-format`,
so it applies this plugin's rules even when the changed files live in another
repository. If Bash is unavailable, perform the same operation directly with
`clang-format --style=file:<plugin-root>/.clang-format` after confirming the
installed version is `20` or newer.

This script:

1. Checks `clang-format` is on `PATH` and is version `20` or newer (this
   repo's minimum — see `CODING_RULES.md`, General rules).
2. If missing or too old, prints the install command for the current OS
   (`brew install llvm` on macOS, distro package or LLVM apt repo on Linux,
   the LLVM installer on Windows) and exits non-zero — install it, then
   re-run.
3. Otherwise runs `clang-format -i` on the given files.

To verify compliance without writing changes (e.g. before reporting a task
done), use `--check` instead:

```sh
<plugin-root>/scripts/check-format.sh --check <file.c> [<file.h> ...]
```

Exits `0` if already compliant, non-zero (with the specific violations) if
not.

## 5. Verified behavior

This flow was tested directly in this repository: `check-format.sh` correctly
refuses to run when `clang-format` is absent (prints the right install
command per OS and exits 1), and — once `clang-format` is installed —
correctly detects a deliberately mis-formatted file with `--check`, fixes it
with the default (in-place) mode, and re-verifies clean afterward.
`template.c` and `template.h` in this repository both pass `--check` as-is —
use them as formatting and comment-placement references.
