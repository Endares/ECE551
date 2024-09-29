#include <ctype.h>  // islower()
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printRes(int key, FILE * f);

int main(int argc, char * argv[]) {
  if (argc != 2) {
    fprintf(stderr,
            "Error: wrong number of arguments.\n Usage: ./<program> <filename>\n");
    exit(EXIT_FAILURE);
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    fprintf(stderr, "Error opening file: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }

  int c = fgetc(f);
  // empty file
  if (c == EOF) {
    return 0;
  }
  else {
    ungetc(c, f);  // put back that char.
  }

  int cntLetter[26] = {0};
  int mostFrequent = 0;

  while ((c = fgetc(f)) != EOF) {
    char ch = (char)c;  // convert int to char
    if (isalpha(ch)) {
      ch = tolower(ch);
      ++cntLetter[ch - 'a'];
      if (cntLetter[ch - 'a'] >= cntLetter[mostFrequent]) {
        mostFrequent = ch - 'a';
      }
    }
  }
  //  printf("Most frequent letter is %c.\n", (char)(mostFrequent + 'a'));
  int key = (26 + mostFrequent + ('a' - 'e')) % 26;
  if (key < 0 || key >= 26) {
    fprintf(stderr, "Invalid key = %d\n", key);
    exit(EXIT_FAILURE);
  }

  fprintf(stdout, "%d\n", key);
  //printRes(key, f);
  if (fclose(f) != 0) {
    fprintf(stderr, "Error closing file: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }

  return 0;
}

void printRes(int key, FILE * f) {
  printf("%d ", key);
  int c = 0;
  rewind(f);  // return to the start.
  while ((c = fgetc(f)) != EOF) {
    if (isalpha(c)) {
      c = tolower(c);
      c -= 'a';  // if don't do this, then %26 won't work correctly.
      c += key;
      c %= 26;
      c += 'a';
    }
    printf("%c", c);
  }
}
