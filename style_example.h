/*
 * 文件：style_example.h
 * 用途：覆盖代码风格规则的示例头文件
 */

/*
 * Copyright (c) 2026 C Style Example
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
 * This file is part of c_code_style.
 *
 * Author:          C Style Example <example@example.com>
 * Version:         v1.y.z
 */
#ifndef STYLE_EXAMPLE_H
#define STYLE_EXAMPLE_H

#include <stddef.h>
#include <stdint.h>

#if defined(__cplusplus)
extern "C" {
#endif /* defined(__cplusplus) */

#define STYLE_EXAMPLE_BUFFER_CAPACITY    (16U)   /* 数据长度上限，单位为字节 */
#define STYLE_EXAMPLE_EMPTY_LENGTH       (0U)    /* 表示空数据长度 */
#define STYLE_EXAMPLE_SINGLE_LENGTH      (1U)    /* 表示单个数据项的长度 */
#define STYLE_EXAMPLE_EMPTY_BYTE         (0U)    /* 表示空字节 */
#define STYLE_EXAMPLE_INITIAL_COORDINATE (0)     /* 初始坐标 */
#define STYLE_EXAMPLE_HIGH_COORDINATE    (10)    /* 高等级结果使用的坐标 */
#define STYLE_EXAMPLE_LOW_COORDINATE     (-10)   /* 低等级结果使用的坐标 */
#define STYLE_EXAMPLE_SCALE_FACTOR       (1.25)  /* 浮点计算使用的缩放因子 */
#define STYLE_EXAMPLE_MARK_THRESHOLD     (128.0) /* 高等级标记阈值 */
#define STYLE_EXAMPLE_HIGH_MARK          ('H')   /* 高等级结果标记 */
#define STYLE_EXAMPLE_LOW_MARK           ('L')   /* 低等级结果标记 */
#define STYLE_EXAMPLE_RESULT_OK          (0)     /* 处理成功 */
#define STYLE_EXAMPLE_RESULT_INVALID     (-1)    /* 参数无效 */
#define STYLE_EXAMPLE_RESULT_FAILED      (-2)    /* 处理失败 */

#define STYLE_EXAMPLE_MIN(val_a, val_b)  (((val_a) < (val_b)) ? (val_a) : (val_b)) /* 返回两个参数中的较小值 */

/*
 * 设置点的两个坐标。
 * `point` 必须指向有效的目标点。
 */
#define STYLE_EXAMPLE_SET_POINT(point, coord_x, coord_y)                                                               \
    do {                                                                                                               \
        (point)->pos_x = (coord_x);                                                                                    \
        (point)->pos_y = (coord_y);                                                                                    \
    } while (0)

/* 示例模块的运行状态。 */
typedef enum {
    STYLE_STATUS_IDLE,  /* 尚未开始处理输入数据 */
    STYLE_STATUS_READY, /* 输入长度已通过边界检查 */
    STYLE_STATUS_ERROR, /* 输入无效或处理失败 */
} style_status_t;

typedef struct style_point {
    int32_t pos_x; /* 结果横坐标，单位为模块坐标 */
    int32_t pos_y; /* 第一个非零字节的索引 */
} style_point_t;

typedef struct {
    uint8_t* data; /* 由 `style_example_copy` 分配，需用 `style_example_release` 释放 */
    size_t length; /* 数据长度，单位为字节 */
} style_buffer_t;

/* 数据处理完成后的回调函数类型，接收数据地址和字节长度。 */
typedef void (*style_callback_fn)(const void* data, size_t length);

/* 当前模块状态，由 `style_example_init` 初始化。 */
extern style_status_t style_status;

/**
 * brief           初始化示例模块的运行状态
 */
void style_example_init(void);

/**
 * brief           计算两个有符号整数的和
 * param[in]       par_a: 第一个输入值
 * param[in]       par_b: 第二个输入值
 * return          两个输入值之和
 */
int32_t style_example_sum(int32_t par_a, int32_t par_b);

/**
 * brief           获取当前模块状态
 * return          当前模块状态
 */
style_status_t style_example_get_status(void);

/**
 * brief           处理一段数据并更新输出点
 * note            成功时更新全局 `style_status`，并同步调用已注册回调
 * param[in]       data: 至少包含 `length` 个字节的数据
 * param[in]       length: 输入数据长度，单位为字节
 * param[out]      point: 用于保存结果的输出点
 * return          成功返回 `STYLE_EXAMPLE_RESULT_OK`；参数无效返回
 *                 `STYLE_EXAMPLE_RESULT_INVALID`；处理失败返回
 *                 `STYLE_EXAMPLE_RESULT_FAILED`
 */
int32_t style_example_process(const void* data, size_t length, style_point_t* point);

/**
 * brief           复制任意类型的数据到动态缓冲区
 * note            成功后由调用者使用 `style_example_release` 释放 `output`
 * param[in]       source: 待复制的数据
 * param[in]       length: 数据长度，单位为字节
 * param[out]      output: 接收动态缓冲区，调用前必须为空
 * return          成功返回 `STYLE_EXAMPLE_RESULT_OK`；参数无效返回
 *                 `STYLE_EXAMPLE_RESULT_INVALID`；输出对象忙或内存不足返回
 *                 `STYLE_EXAMPLE_RESULT_FAILED`
 */
int32_t style_example_copy(const void* source, size_t length, style_buffer_t* output);

/**
 * brief           使用指定字节填充输出缓冲区
 * param[in]       data: 至少包含 `length` 个可写字节的缓冲区
 * param[in]       length: 填充长度，单位为字节
 * param[in]       value: 填充字节
 * return          成功返回 `STYLE_EXAMPLE_RESULT_OK`；参数无效返回
 *                 `STYLE_EXAMPLE_RESULT_INVALID`
 */
int32_t style_example_fill(void* const data, size_t length, uint8_t value);

/**
 * brief           释放动态缓冲区并清除悬空指针
 * param[in,out]   buffer: 待释放的缓冲区；调用后指针和长度清零
 */
void style_example_release(style_buffer_t* buffer);

/**
 * brief           获取动态缓冲区中的通用数据指针
 * param[in]       buffer: 待查询的缓冲区
 * return          缓冲区数据指针；参数无效时返回 `NULL`
 */
const void* style_example_get_data(const style_buffer_t* buffer);

/**
 * brief           注册或清除数据处理回调
 * param[in]       callback: 回调函数；为 `NULL` 时清除当前回调
 */
void style_example_register_callback(style_callback_fn callback);

#if defined(__cplusplus)
}
#endif /* defined(__cplusplus) */

#endif /* STYLE_EXAMPLE_H */
