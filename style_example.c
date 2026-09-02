/*
 * 文件：style_example.c
 * 用途：覆盖代码风格规则的示例源文件
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
#include "style_example.h"

#include <stdlib.h>

style_status_t style_status;

static style_point_t default_point;      /* 模块初始化后的默认点，生命周期覆盖整个模块 */
static uint32_t event_count;             /* 成功处理的数据次数 */
static style_callback_fn style_callback; /* 可选的数据处理回调 */

/*
 * 根据构建配置决定是否保留跟踪值；
 * 未启用跟踪时，传入参数不会被求值。
 */
#if defined(STYLE_EXAMPLE_ENABLE_TRACE)
#define STYLE_EXAMPLE_TRACE(value) ((void)(value))
#else /* defined(STYLE_EXAMPLE_ENABLE_TRACE) */
#define STYLE_EXAMPLE_TRACE(value) ((void)(STYLE_EXAMPLE_EMPTY_LENGTH))
#endif /* !defined(STYLE_EXAMPLE_ENABLE_TRACE) */

static uint8_t prv_is_valid_buffer(const void* data, size_t length);
static uint32_t prv_accumulate_bytes(const void* data, size_t length);
static size_t prv_find_first_byte(const void* data, size_t length);
static style_status_t prv_get_status_for_length(size_t length);
static void prv_set_point(style_point_t* point, int32_t coord_x, int32_t coord_y);

/**
 * brief           检查输入缓冲区是否满足长度边界
 * param[in]       data: 待检查的数据
 * param[in]       length: 数据长度，单位为字节
 * return          有效时返回 `1`，否则返回 `0`
 */
static uint8_t prv_is_valid_buffer(const void* data, size_t length)
{
    uint8_t is_valid;

    is_valid = 1U;
    if (data == NULL || length == STYLE_EXAMPLE_EMPTY_LENGTH || length > STYLE_EXAMPLE_BUFFER_CAPACITY) {
        is_valid = 0U;
    }
    return is_valid;
}

/**
 * brief           使用 `do-while` 累加输入数据
 * param[in]       data: 待累加的数据
 * param[in]       length: 数据长度，单位为字节
 * return          数据累加结果
 */
static uint32_t prv_accumulate_bytes(const void* data, size_t length)
{
    const uint8_t* bytes;
    size_t index;
    uint32_t total;

    if (data == NULL || length == STYLE_EXAMPLE_EMPTY_LENGTH) {
        return STYLE_EXAMPLE_EMPTY_LENGTH;
    }

    bytes = data;
    index = STYLE_EXAMPLE_EMPTY_LENGTH;
    total = STYLE_EXAMPLE_EMPTY_LENGTH;
    do {
        total += bytes[index];
        ++index;
    } while (index < length);
    return total;
}

/**
 * brief           查找第一个非空字节
 * param[in]       data: 待查找的数据
 * param[in]       length: 数据长度，单位为字节
 * return          第一个非空字节的索引；未找到时返回 `length`
 */
static size_t prv_find_first_byte(const void* data, size_t length)
{
    const uint8_t* bytes;
    size_t index;

    if (data == NULL || length == STYLE_EXAMPLE_EMPTY_LENGTH) {
        return length;
    }

    bytes = data;
    index = STYLE_EXAMPLE_EMPTY_LENGTH;
    while (index < length && bytes[index] == STYLE_EXAMPLE_EMPTY_BYTE) {
        ++index;
    }
    return index;
}

/**
 * brief           根据数据长度选择模块状态
 * param[in]       length: 数据长度，单位为字节
 * return          选择后的模块状态
 */
static style_status_t prv_get_status_for_length(size_t length)
{
    style_status_t next_status;

    next_status = STYLE_STATUS_ERROR;
    switch (length) {
        case STYLE_EXAMPLE_EMPTY_LENGTH:
            next_status = STYLE_STATUS_ERROR;
            STYLE_EXAMPLE_TRACE(length);
            break;
        case STYLE_EXAMPLE_SINGLE_LENGTH: {
            uint8_t is_ready;

            is_ready = 1U;
            if (is_ready) {
                next_status = STYLE_STATUS_READY;
            } else {
                next_status = STYLE_STATUS_IDLE;
            }
            break;
        }
        default:
            next_status = STYLE_STATUS_READY;
            STYLE_EXAMPLE_TRACE(length);
            break;
    }
    return next_status;
}

/**
 * brief           在确认指针有效后设置点坐标
 * param[out]      point: 待写入的点
 * param[in]       coord_x: 新的横坐标
 * param[in]       coord_y: 新的纵坐标
 */
static void prv_set_point(style_point_t* point, int32_t coord_x, int32_t coord_y)
{
    if (point == NULL) {
        return;
    }

    STYLE_EXAMPLE_SET_POINT(point, coord_x, coord_y);
}

void style_example_init(void)
{
    STYLE_EXAMPLE_SET_POINT(&default_point, STYLE_EXAMPLE_INITIAL_COORDINATE, STYLE_EXAMPLE_INITIAL_COORDINATE);
    style_status = STYLE_STATUS_IDLE;
    event_count = STYLE_EXAMPLE_EMPTY_LENGTH;
    style_callback = NULL;
}

int32_t style_example_sum(int32_t par_a, int32_t par_b)
{
    return par_a + par_b;
}

style_status_t style_example_get_status(void)
{
    return style_status;
}

int32_t style_example_process(const void* data, size_t length, style_point_t* point)
{
    style_buffer_t buffer = {
        .data = NULL,
        .length = STYLE_EXAMPLE_EMPTY_LENGTH,
    };
    style_status_t next_status;
    const uint8_t* bytes;
    size_t first_index;
    uint32_t checksum;
    int32_t copy_result, result;
    uint8_t is_valid;
    char marker;
    double scaled_value;
    float average_value;

    if (data == NULL || point == NULL || length == STYLE_EXAMPLE_EMPTY_LENGTH) {
        return STYLE_EXAMPLE_RESULT_INVALID;
    }

    result = STYLE_EXAMPLE_RESULT_FAILED;
    is_valid = prv_is_valid_buffer(data, length);
    if (!is_valid) {
        /* 输入不满足模块边界条件时，保持失败状态并跳过后续处理。 */
    } else {
        bytes = data;
        checksum = prv_accumulate_bytes(bytes, length);
        first_index = prv_find_first_byte(bytes, length);
        first_index = STYLE_EXAMPLE_MIN(first_index, length);
        average_value = (float)checksum / (float)length;
        scaled_value = (double)average_value * STYLE_EXAMPLE_SCALE_FACTOR;
        marker = (scaled_value >= STYLE_EXAMPLE_MARK_THRESHOLD) ? STYLE_EXAMPLE_HIGH_MARK : STYLE_EXAMPLE_LOW_MARK;
        next_status = prv_get_status_for_length(length);
        style_status = next_status;
        ++event_count;
        STYLE_EXAMPLE_TRACE(checksum);

        if (marker == STYLE_EXAMPLE_HIGH_MARK) {
            prv_set_point(point, STYLE_EXAMPLE_HIGH_COORDINATE, (int32_t)first_index);
        } else {
            prv_set_point(point, STYLE_EXAMPLE_LOW_COORDINATE, (int32_t)first_index);
        }

        copy_result = style_example_copy(data, length, &buffer);
        if (copy_result == STYLE_EXAMPLE_RESULT_OK) {
            style_example_release(&buffer);
            if (style_callback != NULL) {
                style_callback(data, length);
            }
            result = STYLE_EXAMPLE_RESULT_OK;
        }
    }
    return result;
}

int32_t style_example_copy(const void* source, size_t length, style_buffer_t* output)
{
    const uint8_t* source_bytes;
    uint8_t* copy_data;
    size_t index;
    int32_t result;

    if (source == NULL || output == NULL || length == STYLE_EXAMPLE_EMPTY_LENGTH) {
        return STYLE_EXAMPLE_RESULT_INVALID;
    }

    result = STYLE_EXAMPLE_RESULT_FAILED;
    copy_data = NULL;
    if (output->data == NULL && output->length == STYLE_EXAMPLE_EMPTY_LENGTH
        && length <= (SIZE_MAX / sizeof(*copy_data))) {
        copy_data = malloc(sizeof(*copy_data) * length);
        if (copy_data != NULL) {
            source_bytes = source;
            for (index = STYLE_EXAMPLE_EMPTY_LENGTH; index < length; ++index) {
                copy_data[index] = source_bytes[index];
            }
            output->data = copy_data;
            output->length = length;
            result = STYLE_EXAMPLE_RESULT_OK;
        }
    }
    return result;
}

int32_t style_example_fill(void* const data, size_t length, uint8_t value)
{
    uint8_t* bytes;
    size_t index;

    if (data == NULL || length == STYLE_EXAMPLE_EMPTY_LENGTH) {
        return STYLE_EXAMPLE_RESULT_INVALID;
    }

    bytes = data;
    for (index = STYLE_EXAMPLE_EMPTY_LENGTH; index < length; ++index) {
        bytes[index] = value;
    }
    return STYLE_EXAMPLE_RESULT_OK;
}

void style_example_release(style_buffer_t* buffer)
{
    if (buffer == NULL) {
        return;
    }

    if (buffer->data != NULL) {
        free(buffer->data);
        buffer->data = NULL;
    }
    buffer->length = STYLE_EXAMPLE_EMPTY_LENGTH;
}

const void* style_example_get_data(const style_buffer_t* const buffer)
{
    const void* data;

    if (buffer == NULL) {
        return NULL;
    }

    data = buffer->data;
    return data;
}

void style_example_register_callback(style_callback_fn callback)
{
    style_callback = callback;
}
