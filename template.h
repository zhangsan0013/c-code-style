/*
 * 文件：template.h
 * 用途：模板头文件
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
 * This file is part of your_library_name.
 *
 * Author:          Tilen MAJERLE <tilen@majerle.eu>
 * Version:         $_version_$
 */
#ifndef TEMPLATE_HDR_H
#define TEMPLATE_HDR_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* 接受 `void*` 参数的自定义函数指针类型。 */
typedef void (*my_func_type_fn)(void* par_a);

/**
 * brief           计算两个数值的和
 * param[in]       par_a: 第一个输入值
 * param[in]       par_b: 第二个输入值
 * return          两个输入值之和
 */
int32_t sum(int32_t par_a, int32_t par_b);

/**
 * brief           计算 `par_a` 除以 `par_b`
 * param[in]       par_a: 被除数
 * param[in]       par_b: 除数，不能为 `0`
 * return          除法结果
 */
int32_t divide(int32_t par_a, int32_t par_b);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* TEMPLATE_HDR_H */
