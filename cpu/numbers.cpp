#include <variant>
#include <unistd.h>
#include <stdint.h>
#include <iostream>
#include <cstring>

#include "numbers.h"

variantnum parse_num(uint8_t * p1, uint8_t num_mode) {
    uint8_t size;
    anynumber m1;
    bool is_signed = (num_mode >> 3) & 1;
    if ((num_mode >> 2) & 1) {
        // float32
        uint32_t data1 = (*p1 << 24) | (*(p1+1) << 16) | (*(p1+2) << 8) | *(p1+3);
        _Float32 f1;
        std::memcpy(&f1, &data1, sizeof(_Float32));
        m1 = f1;
        size = 32;
    }
    else if ((num_mode >> 1) & 1) {
        // uint32
        uint32_t data1 = (*p1 << 24) | (*(p1+1) << 16) | (*(p1+2) << 8) | *(p1+3);
        if (is_signed) {
            int32_t f1;
            std::memcpy(&f1, &data1, sizeof(int32_t));
            m1 = f1;
        }
        else {
            m1 = data1;
        }
        size = 32;
    }
    else if (num_mode & 1) {
        // int16
        uint16_t data1 = (*(p1) << 8) | *(p1+1);
        if (is_signed) {
            int16_t f1;
            std::memcpy(&f1, &data1, sizeof(int16_t));
            m1 = f1;
        }
        else {
            m1 = data1;
        }
        size = 16;
    }
    else {
        // int8
        uint8_t data1 = *(p1);
        if (is_signed) {
            int8_t f1;
            std::memcpy(&f1, &data1, sizeof(int8_t));
            m1 = f1;
        }
        else {
            m1 = data1;
        }
        size = 8;
    }
    return {.size = size, .num = m1};
}

uint8_t do_cmp(uint8_t * p1, uint8_t * p2, uint8_t compare_mode, uint8_t num_mode) {
    anynumber m1, m2;
    m1 = parse_num(p1, num_mode).num;
    m2 = parse_num(p2, num_mode).num;

    if ((compare_mode >> 3) & 1) {
        return m1 >= m2;
    }
    else if ((compare_mode >> 2) & 1) {
        return m1 <= m2;
    }
    else if ((compare_mode >> 1) & 1) {
        return m1 > m2;
    }
    else if (compare_mode & 1) {
        return m1 < m2;
    }
    else {
        return m1 == m2;
    }
}

// Create op functions
OP_FUNC(do_add, +)
OP_FUNC(do_sub, -)
OP_FUNC(do_mul, *)
OP_FUNC(do_div, /)