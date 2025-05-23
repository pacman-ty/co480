#include <algorithm>
#include <bits/stdc++.h>
#include <iostream>
using namespace std;

void print_frequency(int freq[]) {

  cout << endl << endl << "-----------------" << endl << endl;

  for (int i = 0; i < 26; i++) {
    if (freq[i] != 0) {
      cout << char(i + 'A') << " - " << freq[i] << endl;
    }
  }

  cout << endl << "-----------------" << endl;
}

// Function to calculate the frequencies
// of each character of the string
int find_frequency(const string &str) {
  int freq[26] = {0};

  for (char c : str) {
    if (isalpha(c)) {
      freq[tolower(c) - 'a']++;
    }
  }

  int max_freq = 0;
  char most_frequent = '\0';

  for (int i = 0; i < 26; ++i) {
    if (freq[i] > max_freq) {
      max_freq = freq[i];
      most_frequent = 'a' + i;
    }
  }

  print_frequency(freq);
  return most_frequent;
}

vector<string> get_substrings(const string &cypher, int gcd) {
  vector<string> substrings(gcd);

  for (size_t i = 0; i < cypher.length(); ++i) {
    substrings[i % gcd] += cypher[i];
  }

  return substrings;
}

int find_gcd(const vector<int> &indices) {
  if (indices.size() < 2)
    return 0;

  vector<int> dvals;
  for (size_t i = 0; i < indices.size() - 1; ++i) {
    dvals.push_back(indices[i + 1] - indices[i]);
  }

  int gcd = dvals[0];
  for (size_t i = 1; i < dvals.size(); ++i) {
    gcd = __gcd(gcd, dvals[i]);
  }

  return gcd;
}

vector<int> find_indices(const string &cypher, const string &key) {
  int clen = cypher.length();
  int klen = key.length();
  vector<int> indices;

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

  cout << repeat << endl;

  vector<int> indices = find_indices(cypher, "JXNLAGI");

  int gcd = find_gcd(indices);

  cout << gcd << endl;

  vector<string> substrings = get_substrings(cypher, gcd);

  for (int i = 0; i < substrings.size(); ++i) {
    std::cout << "Substring " << i << ": " << substrings[i] << std::endl;
  }

  vector<char> letters;
  for (int i = 0; i < substrings.size(); ++i) {
    char most_freq = find_frequency(substrings[i]);
    letters.push_back(most_freq);
  }

  for (char c : letters) {
    // Shift 4 letters to the left, wrapping around if needed
    char shifted = ((c - 'a' - 4 + 26) % 26) + 'a';
    std::cout << shifted << " ";
  }
}
