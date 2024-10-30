#include <algorithm>
#include <fstream>
#include <iostream>
#include <istream>
#include <string>
#include <vector>
using namespace std;

void readSortPrint(istream & is) {
  vector<string> lines;
  string curr;
  // read from standard input
  while (getline(is, curr)) {
    lines.push_back(curr);
    // push_back will make a copy of curr, so int the next round, curr won't be covered.
  }

  if (!is.eof() && !is) {
    cout << "Failed to read." << endl;
    exit(EXIT_FAILURE);
  }

  sort(lines.begin(), lines.end());
  for (auto s : lines) {
    cout << s << endl;
  }
}

int main(int argc, char * argv[]) {
  if (argc == 1) {
    readSortPrint(cin);
  }
  else {
    for (int i = 1; i < argc; ++i) {
      ifstream f(argv[i]);  // open input file as a ifstream
      if (!f) {
        cerr << "Failed to open the file" << argv[i] << endl;
        exit(EXIT_FAILURE);
      }
      readSortPrint(f);
      f.close();
    }
  }
  return 0;
}
