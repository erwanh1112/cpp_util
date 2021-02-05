#pragma once

#include <cstdio>
#include <cstdlib>
#include <stdexcept>
#include <string>
#include <string_view>

namespace fmt
{   // Source: https://docs.microsoft.com/en-us/archive/msdn-magazine/2015/march/windows-with-c-using-printf-with-modern-c

    template<typename T>
    T format_arg(T value) noexcept
    {
        static_assert(!std::is_same<std::string_view, T>(), "Arguments of [w]printf() of type std::string_view must be converted to std::[w]string.");
        static_assert(!std::is_same<std::wstring_view, T>(), "Arguments of [w]printf() of type std::wstring_view must be converted to std::[w]string.");
        return value;
    }

    template<typename T>
    const T* format_arg(const std::basic_string<T>& s) noexcept
    {
        return s.data();
    }


    template<typename ...ARGS>
    int printf(const char* format, ARGS ...args) noexcept
    {
        return printf_s(format, format_arg(args)...);
    }

    template<typename ...ARGS>
    int wprintf(const wchar_t* format, ARGS ...args) noexcept
    {
        return wprintf_s(format, format_arg(args)...);
    }
}