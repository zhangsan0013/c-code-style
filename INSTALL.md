# Installing this skill

This repository is both a C style guide (`CODING_RULES.md`) and a
distributable Claude Code and Codex plugin that teaches an agent to follow it
and enforce formatting with `clang-format`. Pick the path that matches your
setup.

## Option 1: Claude Code plugin (marketplace)

From inside Claude Code, in any project:

```
/plugin marketplace add MaJerle/c-code-style
/plugin install c-code-style
```

This adds the `c-code-style` skill, which auto-loads whenever you ask Claude
to write, edit, or review C code, and it will check for / run `clang-format`
as part of that flow.

> The plugin bundles the whole repository — `CODING_RULES.md`, the
> `template.c`/`template.h` references, and `scripts/check-format.sh` all
> travel with it, so it works the same whether you're inside this repo or in
> your own project. The formatter script explicitly uses the bundled
> `.clang-format`, even when target files live elsewhere. This distribution
> path (`.claude-plugin/marketplace.json`
> + `plugin.json`) was authored against Claude Code's documented plugin
> conventions but not exercised end-to-end with a live `/plugin install` in
> this session — verify the two commands above work before pointing others
> at it, and open an issue on this repo if they don't.

## Option 2: Codex plugin (marketplace)

From a terminal, add this repository as a Codex marketplace and install the
plugin:

```sh
codex plugin marketplace add zhangsan0013/c-code-style
codex plugin add c-code-style@c-code-style-marketplace
```

Start a new Codex task after installation so the `c-code-style` skill is
loaded. It activates when Codex writes, edits, formats, or reviews C source and
header files.

The Codex plugin uses `.codex-plugin/plugin.json`. The existing
`.claude-plugin/marketplace.json` remains the shared marketplace entry, so the
same repository can be installed by both Claude Code and Codex.

## Option 3: Vendor it into your own project (any agent, incl. Codex)

Copy these into your repository:

- `CODING_RULES.md` — the rules (do **not** copy this repo's `README.md`;
  it's just a symlink to `CODING_RULES.md` so it renders on this repo's
  GitHub front page, and copying it would overwrite your own README)
- `.clang-format` — the formatting rules
- `AGENTS.md` — picked up automatically by Codex and other AGENTS.md-aware
  agents; merge it with your existing `AGENTS.md` if you already have one
- `scripts/check-format.sh` — the install-check + format/verify script both
  `AGENTS.md` and the Claude skill call out to
- `template.c` / `template.h` — reference examples for exact formatting and
  doxygen alignment

If you're using Claude Code specifically and don't want the marketplace
plugin, copy `.claude/skills/c-code-style/` into your project instead (or in
addition) for project-scoped auto-discovery.

## Option 4: CI only, no agent

Just want the formatting gate on pull requests, no AI agent involved? Copy
`.github/workflows/clang-format.yml`, `.clang-format`, and
`scripts/check-format.sh`, then follow the branch-protection steps in
`CODING_RULES.md`'s "Continuous integration (GitHub Actions)" section.
