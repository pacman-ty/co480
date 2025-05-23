#include <bits/stdc++.h>
#include <iostream>
using namespace std;

int find_gcd() {
  int gcd;
  return gcd;
}

vector<int> find_dvalue(const string &cypher, const string &key) {
  int clen = cypher.length();
  int klen = key.length();
  std::vector<int> indices;

  // Check for all occurrences
  for (size_t i = 0; i <= clen - klen; ++i) {
    if (cypher.substr(i, klen) == key) {
      indices.push_back(i + 1); // +1 for 1-based index
    }
  }

  return indices;
}

string largest_repeat(const string &cypher) {
  int n = cypher.length();
  vector<int> dp(n + 1, 0);

  string ans = "";
  int ansLen = 0;

  // find length of non-overlapping
  // substrings for all pairs (i,j)
  for (int i = n - 1; i >= 0; i--) {

    for (int j = i; j < n; j++) {

      // if characters match, set value
      // and compare with ansLen.
      if (cypher[i] == cypher[j]) {
        dp[j] = 1 + min(dp[j + 1], j - i - 1);

        if (dp[j] >= ansLen) {
          ansLen = dp[j];
          ans = cypher.substr(i, ansLen);
        }
      } else
        dp[j] = 0;
    }
  }

  return ansLen > 0 ? ans : "-1";
}

int main() {
  string cypher =
      "JXNLAGIISPAGPJKTURTMKHIFULVHWETXFQBVNIJTBJBWKSMNHIFQEVTHFXQGXEJEPRBKVZNS"
      "PSCTAUOIJDQGXEJEPRFTFNPBGFVWQRGMKHIFULVPXBDLFQQADVVOCYJXPTBJBWKSMFFEJZVB"
      "GPZRPGJXNLAGIIJPIFPRFQLNSOEPAFJXNLAGIIJAZVOKFQPBQIZEENTXYPEVOXVCWSEIJAIV"
      "SAVSIQFZVCGGIMERJRGSIPCFXIYLLAPXYTVTCIWZZRVWNPERSIRWTTPMERLVSITEBBIIRGMA"
      "XINPZRBPCRWVOKUTZRDXKSMBULVCENZMEDPBSXKSMCFVZZLJBWJZNNSPZVMGIIGCMFFRKAME"
      "JSUEPNUWFXMBGMKDVBJWZPAGBYKSWEJXZPAVOWZDBRESETBFCIZYOEFGVTDREJFCOBPHFCNB"
      "SIMTTVOXYPAHQIIWIGJZVOMTSIVZNPPQGLZVTSEZVYZ";

  string repeat = largest_repeat(cypher);

  cout << repeat;

  find_dvalue(cypher, repeat);
}
