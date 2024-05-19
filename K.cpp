#include <iostream>
#include <vector>

void PrintResult(int number, int resource,
                 const std::vector<std::vector<int>>& dp,
                 std::vector<int> resources) {
  if (dp[number][resource] == 0) {
    return;
  }
  if (dp[number - 1][resource] == dp[number][resource]) {
    PrintResult(number - 1, resource, dp, resources);
  } else {
    PrintResult(number - 1, resource - resources[number], dp, resources);
    std::cout << number << '\n';
  }
}

int main() {
  // input
  int number;
  int resource;
  std::cin >> number >> resource;
  std::vector<int> resources(number + 1);
  std::vector<int> costs(number + 1);
  for (int i = 1; i < number + 1; ++i) {
    std::cin >> resources[i];
  }
  for (int i = 1; i < number + 1; ++i) {
    std::cin >> costs[i];
  }

  // algorithm
  std::vector<std::vector<int>> dp(number + 1,
                                   std::vector<int>(resource + 1, 0));
  for (int i = 1; i < number + 1; ++i) {
    for (int j = 1; j < resource + 1; ++j) {
      if (j >= resources[i]) {
        dp[i][j] =
            std::max(dp[i - 1][j], dp[i - 1][j - resources[i]] + costs[i]);
      } else {
        dp[i][j] = dp[i - 1][j];
      }
    }
  }

  // output
  PrintResult(number, resource, dp, resources);
}
