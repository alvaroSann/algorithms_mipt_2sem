#include <iostream>
#include <string>
#include <vector>

typedef std::vector<std::vector<std::vector<int>>> DpType;

int OutputAnswer(const std::string& word1, const std::string& word2,
                 int transform, const DpType& dp) {
  // if difference between lengths of word1 and word2 is greater than transform
  // then transform is not possible
  if (abs(static_cast<int>(word1.size() - word2.size())) > transform) {
    return -1;
  }
  // general case
  int result = -1;

  for (int added = 0; added < transform + 1; ++added) {
    for (int deleted = 0; deleted < transform + 1; ++deleted) {
      // if the number of operations exceeds the limit or
      // length of the transformed word1 does not match
      // the length of word2, then such a case is degenerate
      if (added + deleted > transform ||
          word1.size() + added - deleted != word2.size()) {
        continue;
      }
      // if all is ok, then result is the maximum
      result = std::max(result, dp[added][deleted][word2.size()] +
                                    (transform - added - deleted));
    }
  }

  // if suddenly, somehow, there are valid positions
  // greater than the length of the final string,
  // then the condition of the task is obviously fulfilled
  if (result > static_cast<int>(word2.size())) {
    return 0;
  }

  return static_cast<int>(word2.size()) - result;
}

int Decoder(const std::string& word1, const std::string& word2, int transform) {
  // dp[added][deleted][length] = all such indices i that word2[i] ==
  // word1_upd[i] when word1_upd is the string word1 with length [length]
  // received as a result of addition [added] and deletion [deleted]
  DpType dp(transform + 1,
            std::vector<std::vector<int>>(
                transform + 1, std::vector<int>(word2.size() + 1, 0)));

  // counting dp
  for (int length = 1; length < static_cast<int>(word2.size()) + 1; ++length) {
    for (int deleted = 0; deleted < transform + 1; ++deleted) {
      for (int added = 0; added < transform + 1; ++added) {
        // if a certain number of deletion operations are applicable
        if (deleted > 0) {
          dp[added][deleted][length] = std::max(dp[added][deleted - 1][length],
                                                dp[added][deleted][length]);
        }
        // if a certain number of addition operations are applicable
        if (added > 0) {
          dp[added][deleted][length] =
              std::max(dp[added - 1][deleted][length - 1] + 1,
                       dp[added][deleted][length]);
        }
        // if a certain number of replace operations are applicable
        int difference = length - added + deleted;
        if (difference > 0 && difference <= static_cast<int>(word1.size())) {
          if (word1[difference - 1] == word2[length - 1]) {
            dp[added][deleted][length] = std::max(
                dp[added][deleted][length], dp[added][deleted][length - 1] + 1);
          } else {
            dp[added][deleted][length] = std::max(
                dp[added][deleted][length], dp[added][deleted][length - 1]);
          }
        }
      }
    }
  }

  return OutputAnswer(word1, word2, transform, dp);
}

int main() {
  // input
  std::string word1;
  std::string word2;
  int transform;
  std::cin >> word1;
  std::cin >> word2;
  std::cin >> transform;

  // algorithm and output
  std::cout << Decoder(word1, word2, transform);
}
