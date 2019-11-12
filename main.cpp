
#include "print_ip.h"

int main()
{
    print_ip::print(char(-1));
    print_ip::print(short(0));
    print_ip::print(int(21307006433));
    print_ip::print(8875824491850138409L);
    print_ip::print(std::string(    "10.42.0.1"));
    print_ip::print(std::vector<int>{10,42,0,2});
    print_ip::print(std::list<int>  {10,42,0,3});
    print_ip::print(std::make_tuple( 10,42,0,4));
    return 0;
}
