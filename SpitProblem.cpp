#include <iostream>
#include <vector>

struct Camel {
    int x, d;
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    if (!(std::cin >> n)) return 0;

    std::vector<Camel> camels(n);
    for (int i = 0; i < n; i++) {
        std::cin >> camels[i].x >> camels[i].d;
    }

    bool ok = false;
    Camel* data_ptr = camels.data();

    #pragma acc parallel loop copyin(data_ptr[0:n]) reduction(||:ok)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            if (data_ptr[i].x + data_ptr[i].d == data_ptr[j].x &&
                data_ptr[j].x + data_ptr[j].d == data_ptr[i].x) {
                ok = true;
            }
        }
    }

    std::cout << (ok ? "YES" : "NO") << std::endl;

    return 0;
}