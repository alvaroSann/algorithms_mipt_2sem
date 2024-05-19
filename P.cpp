#include <cmath>
#include <iostream>
#include <vector>

const long long kMod = 1e9 + 7;

// Check if the pattern is correct
bool IsCorrect(std::string current, int mask, int number) {
  for (int i = 0; i < number; ++i) {
    if ((current[number - i - 1] == '+' && ((mask >> i) & 1) != 1) ||
        (current[number - i - 1] == '-' && ((mask >> i) & 1) != 0)) {
      return false;
    }
  }
  return true;
}

// the function of transposition
std::vector<std::string> Trans(std::vector<std::string>& array, int length,
                               int width) {
  std::string line;
  for (int i = 0; i < length; ++i) {
    std::cin >> line;
    for (int j = 0; j < width; ++j) {
      array[j] += line[j];
    }
  }
  return array;
}

// counting dynamic for good patterns
long long Solve(int& mask1, int& mask2, std::vector<std::string>& array,
                int length, int width) {
  long long result = 0;
  std::vector<std::vector<long long>> dp((1 << length),
                                         std::vector<long long>(width, 0));

  // base setting of dynamic
  for (int mask = 0; mask < (1 << length); ++mask) {
    if (mask == mask1 || mask == mask2 || !IsCorrect(array[0], mask, length)) {
      continue;
    }

    int current_mask;
    for (int i = 0; i < width; ++i) {
      current_mask = (i % 2 == 0 ? mask : ((1 << length) - mask - 1));
      if (IsCorrect(array[i], current_mask, length)) {
        dp[mask][i] = 1;
      } else {
        break;
      }
    }
  }

  // general setting of dynamic
  dp[mask2][0] = IsCorrect(array[0], mask1, length) ? 1 : 0;
  dp[mask1][0] = IsCorrect(array[0], mask2, length) ? 1 : 0;

  for (int i = 1; i < width; ++i) {
    int lambda = (IsCorrect(array[i], mask1, length) ? 1 : 0) +
                 (IsCorrect(array[i], mask2, length) ? 1 : 0);
    dp[mask2][i] = (dp[mask2][i - 1] * lambda) % kMod;
    dp[mask1][i] = (dp[mask1][i - 1] * lambda) % kMod;
  }

  for (int i = 0; i < (1 << length); ++i) {
    result = (result + dp[i][width - 1]) % kMod;
  }

  return result;
}

int main() {
  // input
  int length;
  int width;
  std::cin >> length >> width;

  // transposition of matrix
  std::vector<std::string> array(width);
  array = Trans(array, length, width);

  // good patterns for matrix
  int alternating_mask1 = 0;
  int alternating_mask2 = 0;
  for (int i = 0; i < length; ++i) {
    (i % 2 == 0) ? alternating_mask1 += (1 << i)
                 : alternating_mask2 += (1 << i);
  }

  // output
  std::cout << Solve(alternating_mask1, alternating_mask2, array, length,
                     width);
}
