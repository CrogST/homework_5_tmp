#pragma once

#include <type_traits>
#include <iostream>
#include <vector>
#include <list>
#include <tuple>

class print_ip {

    template <typename T>
    struct is_stl_cont : std::false_type {};

    template <typename T>
    struct is_stl_cont<std::vector<T>> : std::true_type {};

    template <typename T>
    struct is_stl_cont<std::list<T>> : std::true_type {};

    template <typename T>
    static const auto is_stl_cont_v = is_stl_cont<T>::value;

    template<typename T, typename ... Args> struct is_equal;
    template<typename T> struct is_equal<T> : std::true_type {};

    template<typename T, typename ... Args>
    struct is_equal<T, T, Args...> : is_equal<T, Args...> {};

    template<typename T, typename U, typename ... Args>
    struct is_equal<T, U, Args...> : std::false_type {};

    template<int T, typename ... U>
    static void tuple_out(std::tuple<U...> val) {
        std::cout << std::get<T>(val);
        if constexpr(T < std::tuple_size_v<decltype(val)> - 1) {
            std::cout << ".";
            tuple_out<T+1, U...>(val);
        }
    }

public:

    template <typename T>
    static std::enable_if_t<std::is_integral_v<T>, void> print(T val) {
        auto size = sizeof(T);
        std::string str;
        for(size_t i = 0; i < size; i++) {
            auto b = (val >> 8*(size - i - 1)) & 0xFF;
            str += std::to_string(b);
            if(i != size - 1) str += ".";
        }
        std::cout << str << std::endl;
    }

    template <typename T>
    static std::enable_if_t<is_stl_cont_v<T>, void> print(T val) {
        std::string str;
        unsigned int cnt = 0;
        for(const auto & el : val) {
            cnt++;
            str += std::to_string(el);
            if(cnt != val.size()) str += ".";
        }
        std::cout << str << std::endl;
    }

    //template<typename T>
    //std::enable_if_t<std::is_same_v<T, std::string>, void> print(T val) {
    static void print(std::string val) {
        std::cout << val << std::endl;
    }

    template<typename ... T>
    std::enable_if_t<is_equal<T...>::value, void>
    static print(std::tuple<T...> val) {
        tuple_out<0>(val);
        std::cout << std::endl;
    }
};