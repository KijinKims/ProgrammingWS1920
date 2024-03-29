#include <iostream>
#include <vector>

int main() {
  std::vector<int> v;
  v.reserve(50);

  for (auto i = 104; i < 154; ++i) {
      v.push_back(i);
  }

  // auto to int can fix the problem
  for (int i = v.size() - 1; i >= 0; --i) {
      std::cout << i << ": " << v[i] << std::endl;
  }

  return 0;
}
