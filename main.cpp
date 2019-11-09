#include <iostream>
#include <vector>
#include <list>
#include <map>

template <typename T>
struct is_stl_cont : std::false_type {};

template <typename T>
struct is_stl_cont<std::vector<T>> : std::true_type {};

template <typename T>
struct is_stl_cont<std::list<T>> : std::true_type {};

template <typename T>
static const auto is_stl_cont_v = is_stl_cont<T>::value;

//template <typename T> void print_ip(T val);

template <typename T>
std::enable_if_t<std::is_integral_v<T>, void> print_ip(T val) {
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
std::enable_if_t<is_stl_cont_v<T>, void> print_ip(T val) {
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
//std::enable_if_t<std::is_same_v<T, std::string>, void> print_ip(T val) {
void print_ip(std::string val) {
    std::cout << val << std::endl;
}

template<typename T, typename ... Args> struct is_equal;
template<typename T> struct is_equal<T> : std::true_type {};

template<typename T, typename ... Args>
struct is_equal<T, T, Args...> : is_equal<T, Args...> {};

template<typename T, typename U, typename ... Args>
struct is_equal<T, U, Args...> : std::false_type {};

template<int T, typename ... U>
void tuple_out(std::tuple<U...> val) {
    std::cout << std::get<T>(val);
    if constexpr(T < std::tuple_size_v<decltype(val)> - 1) {
        std::cout << ".";
        tuple_out<T+1, U...>(val);
    }
}

template<typename ... T>
std::enable_if_t<is_equal<T...>::value, void>
print_ip(std::tuple<T...> val) {
    tuple_out<0>(val);
    std::cout << std::endl;
}

int main()
{
    print_ip(char(-1));
    print_ip(short(0));
    print_ip(int(21307006433));
    print_ip(8875824491850138409L);
    print_ip(std::string(    "10.42.0.1"));
    print_ip(std::vector<int>{10,42,0,2});
    print_ip(std::list<int>  {10,42,0,3});
    print_ip(std::make_tuple( 10,42,0,4));
    return 0;
}
