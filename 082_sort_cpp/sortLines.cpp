#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main(int argc, char * argv[]) {
  if (argc == 1) {
    vector<string> lines;
    string curr;
    // read from standard input
    while (getline(cin, curr)) {
      lines.push_back(curr);
      // push_back will make a copy of curr, so int the next round, curr won't be covered.
    }
    sort(lines.begin(), lines.end());
    for (auto s : lines) {
      cout << s << endl;
    }
  }
  else {
    for (int i = 1; i < argc; ++i) {
      vector<string> lines;
      ifstream f(argv[i]);  // open input file as a ifstream
      string curr;
      while (getline(f, curr)) {
        lines.push_back(curr);
      }
      sort(lines.begin(), lines.end());
      for (auto s : lines) {
        cout << s << endl;
      }
      f.close();
    }
  }
  return 0;
}
