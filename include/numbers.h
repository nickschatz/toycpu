// This file, and associated .cpp file, store number manipulation functions
#include <stdint.h>
#include <variant>
#include <iostream>
#include <cstring>

#ifndef NUMBERS_H
#define NUMBERS_H

typedef std::variant<uint8_t, uint16_t, uint32_t, _Float32, int8_t, int16_t, int32_t> anynumber;

struct variantnum {
    uint8_t size;
    anynumber num;
};

uint8_t do_cmp(uint8_t * p1, uint8_t * p2, uint8_t compare_mode, uint8_t num_mode);
void do_add(uint8_t * p1, uint8_t * p2, uint8_t * resultp, uint8_t num_mode);
void do_sub(uint8_t * p1, uint8_t * p2, uint8_t * resultp, uint8_t num_mode);
void do_mul(uint8_t * p1, uint8_t * p2, uint8_t * resultp, uint8_t num_mode);
void do_div(uint8_t * p1, uint8_t * p2, uint8_t * resultp, uint8_t num_mode);

// Generic op function
#define OP_FUNC(name, _op_) \
void name(uint8_t * p1, uint8_t * p2, uint8_t * resultp, uint8_t num_mode) { \
    struct variantnum m1, m2; \
    anynumber num1, num2; \
    m1 = parse_num(p1, num_mode); \
    m2 = parse_num(p2, num_mode); \
    num1 = m1.num; \
    num2 = m2.num; \
    uint32_t result; \
    uint8_t size; \
    /* Determine type and operate */ \
    if (std::holds_alternative<_Float32>(num1)) { \
        _Float32 result_ = std::get<_Float32>(num1) _op_ std::get<_Float32>(num2); \
        std::memcpy(&result, &result_, sizeof(result_)); \
        size = m1.size; \
    } \
    else if (std::holds_alternative<uint32_t>(num1)) { \
        uint32_t result_ = std::get<uint32_t>(num1) _op_ std::get<uint32_t>(num2); \
        std::memcpy(&result, &result_, sizeof(result_)); \
        size = m1.size; \
    } \
    else if (std::holds_alternative<uint16_t>(num1)) { \
        uint16_t result_ = std::get<uint16_t>(num1) _op_ std::get<uint16_t>(num2); \
        std::memcpy(&result, &result_, sizeof(result_)); \
        size = m1.size; \
    } \
    else if (std::holds_alternative<uint16_t>(num1)) { \
        uint16_t result_ = std::get<uint16_t>(num1) _op_ std::get<uint16_t>(num2); \
        std::memcpy(&result, &result_, sizeof(result_)); \
        size = m1.size; \
    } \
    /* Store result */ \
    for (int p = 0; p < size/8; p += 1) { \
        *(resultp + p) = (result >> (size - p - 1)) & 0xFF; \
    } \
}

#endif