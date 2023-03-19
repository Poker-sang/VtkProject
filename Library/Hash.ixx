#include "pch.h"
#pragma once
export module Hash;

typedef std::uint64_t Hash;

constexpr Hash prime = 0x100000001B3ull;
constexpr Hash basis = 0xCBF29CE484222325ull;
export constexpr Hash ToHash(const std::string s)
{
    auto str = s.c_str();
    Hash ret { basis };

    while (*str) {
        ret ^= *str;
        ret *= prime;
        str++;
    }
    return ret;
}

constexpr Hash HashCompileTime(const char* str, const Hash lastValue = basis)
{
    return *str ? HashCompileTime(str + 1, (*str ^ lastValue) * prime) : lastValue;
}

export constexpr Hash operator""_h(const char* p, size_t)
{
    return HashCompileTime(p);
}
