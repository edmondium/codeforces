#include <iostream>
#include <vector>
#include <algorithm>
int main(){
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> grid(n, std::vector<int>(m));
    for (auto i {0}; i < n; ++i)
    for (auto j {0}; j < m; ++j)
std::cin >> grid[i][j];
for (auto j {0}; j < m; ++j){
    std::vector<int> column;
    for (auto i {0}; i < n; ++i)
    column.push_back(grid[i][j]);
sort(column.begin(), column.end());
for (auto i {0}; i < n; ++i)
grid[i][j] = column[i];
}
long long min_sum {0};
for (auto i {0}; i < n; ++i)
for (auto j {0}; j < m - 1; ++j)
min_sum += abs(grid[i][j] - grid[i][j + 1]);
std::cout << min_sum << std::endl;
return 0;
}