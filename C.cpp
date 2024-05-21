#include <iostream>
#include <vector>

const int kBinSearchBorder = 17;
const int kBorder = 1e9;

long long Solve(int number, int airplane) {
  std::vector<std::vector<long long>> dp(
      number + 1, std::vector<long long>(airplane + 1, 0));

  // base cases
  if (number == 0) {
    return 0;
  }
  if (number >= 1 && airplane == 0) {
    return -1;
  }

  // base of dynamic
  for (int i = 1; i <= number; ++i) {
    dp[i][0] = kBorder;
    dp[i][1] = i;
  }
  for (int i = 1; i <= airplane; ++i) {
    dp[1][i] = 1;
  }

  // updating dp with the help of binary search by floors (number)
  for (int i = 2; i <= airplane; ++i) {
    for (int j = 2; j <= number; ++j) {
      int left = 1;
      int right = j;

      while (right - left > 1) {
        int middle = left + (right - left) / 2;

        if (dp[j - middle][i] > dp[middle - 1][i - 1]) {
          left = middle;
        } else {
          right = middle;
        }
      }

      dp[j][i] = 1 + std::max(dp[right - 1][i - 1], dp[j - right][i]);
    }
  }

  return dp[number][airplane];
}

int main() {
  // input
  int number;
  int airplane;
  std::cin >> number >> airplane;
  
  // the airplane is no more than 100k so >16 airplanes are enough to solve the
  // problem by binary search
  airplane = std::min(airplane, kBinSearchBorder);
  
  // reduce the number by 1 to make it easier to handle loops and basic dp-cases
  --number;

  std::cout << Solve(number, airplane);
}
