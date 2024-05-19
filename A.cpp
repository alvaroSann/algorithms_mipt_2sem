#include <algorithm>
#include <iostream>
#include <vector>

const long long kBorder = 1e11;

void ReadInput(int& number, std::vector<long long>& array) {
  std::cin >> number;
  array.resize(number);
  for (int i = 0; i < number; ++i) {
    std::cin >> array[i];
  }
}

int CalculateLDS(const std::vector<long long>& array,
                 std::vector<int>& result) {
  int number = array.size();
  std::vector<long long> dp(number, -kBorder);
  std::vector<int> position(number);
  std::vector<int> previous(number);

  dp[0] = kBorder;
  position[0] = -1;
  int count = 0;

  for (int i = 0; i < number; ++i) {
    int index = static_cast<int>(
        lower_bound(dp.begin(), dp.end(), array[i], std::greater<>()) -
        dp.begin());
    if (array[i] <= dp[index - 1] && dp[index] <= array[i]) {
      dp[index] = array[i];
      position[index] = i;
      previous[i] = position[index - 1];
      count = std::max(count, index);
    }
  }

  result.clear();
  long long current_position = position[count];
  while (current_position != -1) {
    result.push_back(current_position + 1);
    current_position = previous[current_position];
  }

  return count;
}

void PrintResult(int count, const std::vector<int>& result) {
  std::cout << count << '\n';
  for (int i = count - 1; i >= 0; --i) {
    std::cout << result[i] << ' ';
  }
  std::cout << '\n';
}

int main() {
  // input
  int number;
  std::vector<long long> array;
  ReadInput(number, array);

  // algorithm
  std::vector<int> result;
  int count = CalculateLDS(array, result);

  // output
  PrintResult(count, result);
}
