#include <iostream>
//#include <type_taits>
#include <vector>
#include <list>
#include <map>

template <typename T> struct is_stl_cont                 : std::false_type {};
template <typename U> struct is_stl_cont<std::vector<U>> : std::true_type {};
template <typename U> struct is_stl_cont<std::list<U>>   : std::true_type {};

template <typename T>
void print_ip(T val) {
    if constexpr(std::is_integral_v<T>) {
        auto size = sizeof(T);
        for(size_t i = 0; i < size; i++) {
            auto b = (val >> 8*(size - i - 1)) & 0xFF;
            std::cout << std::to_string(b);
            if(i != size - 1) std::cout << ".";
        }
        std::cout << std::endl;
    } else if constexpr(is_stl_cont<T>::value) {
        for(const auto & el : val) {
            std::cout << el;
            if(el != val[val.size() - 1]) std::cout << ".";
        }
        std::cout << std::endl;
    }
}

template<typename T, typename ... U>
void print_tuple(std::tuple<T, U...> val) {
    //possible ways:
    //auto [a...];
    //std::get<0>(val);
    //do_some(args)...
}

template<> void print_ip<std::string>(std::string val) {
    std::cout << val << std::endl;
}

int main()
{
    char c = -1;
    print_ip(c);
    short s = 0;
    print_ip(s);
    print_ip(21307006433);
    print_ip(8875824491850138409L);
    std::string ip_str = "192.168.0.1";
    print_ip(ip_str);
    std::vector<int> vect = {10,42,0,2};
    print_ip(vect);
//    std::list<int> list = {10,42,0,3};
//    print_ip(list);

//    auto ip_tuple = std::make_tuple(1234,2535,6473);
//    print_ip(ip_tuple);
    return 0;
}
