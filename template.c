/**
 * \file            template.c
 * \brief           Template source file
 */

/*
 * Copyright (c) 2023 Tilen MAJERLE
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
 * AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * This file is part of my_library.
 *
 * Author:          Tilen MAJERLE <tilen@majerle.eu>
 * Version:         v1.y.z
 */
#include "template.h"

/**
 * \brief           Sum `2` numbers
 * \param[in]       par_a: First value
 * \param[in]       par_b: Second value
 * \return          Sum of input values
 */
int32_t
sum(int32_t par_a, int32_t par_b) {
    return par_a + par_b;
}

/**
 * \brief           Sum `2` numbers together
 * \note            This is a strictly module-private function, hence the `prv_` prefix and `static` keyword
 * \param[in]       par_a: First parameter
 * \param[in]       par_b: Second parameter
 * \return          Sum of input values
 */
static int32_t
prv_sum(int32_t par_a, int32_t par_b) {
    return par_a + par_b;
}
