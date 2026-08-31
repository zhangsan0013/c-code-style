/**
 * \file            template.c
 * \brief           模板源文件
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
 * \brief           模块私有的求和偏移量
 */
static int32_t sum_offset;

/**
 * \brief           使用模块偏移量计算 `2` 个数值的和
 * \param[in]       val_a: 第一个数值
 * \param[in]       val_b: 第二个数值
 * \return          加入模块偏移量后的数值之和
 * \hideinitializer
 */
#define SUM_WITH_OFFSET(val_a, val_b) ((val_a) + (val_b) + sum_offset)

/**
 * \brief           计算 `2` 个数值的和
 * \param[in]       par_a: 第一个数值
 * \param[in]       par_b: 第二个数值
 * \return          输入数值之和
 */
int32_t sum(int32_t par_a, int32_t par_b)
{
    return par_a + par_b;
}

/**
 * \brief           计算 `2` 个数值的和并加入模块偏移量
 * \note            这是严格的模块私有函数，因此使用 `prv_` 前缀和 `static` 关键字
 * \param[in]       par_a: 第一个数值
 * \param[in]       par_b: 第二个数值
 * \return          加入模块偏移量后的数值之和
 */
static int32_t prv_sum(int32_t par_a, int32_t par_b)
{
    int32_t result;

    /* 先保存中间结果，便于在函数末尾统一返回。 */
    result = SUM_WITH_OFFSET(par_a, par_b);
    return result;
}
