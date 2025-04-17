#include <iostream>
int main(){
    std::int64_t n, m, a;
    std::cin >> n >> m >> a;
    std::int64_t flagstones_needed = ((n + a - 1) / a) * ((m + a - 1) / a);
    std::cout << "" << flagstones_needed << std::endl;
    return 0;
}