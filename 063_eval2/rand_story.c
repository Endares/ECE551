#include "rand_story.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*return the index of specific name in cats->arr, if not found, return -1*/
int findCat(const char * name, catarray_t * cats) {
  if (cats == NULL) {  // empty cats
    return -1;
  }
  for (size_t i = 0; i < cats->n; ++i) {
    if (strcmp(cats->arr[i].name, name) == 0) {
      return (int)i;
    }
  }
  return -1;
}

/*find the index pf specific word under a specific name (at cats->arr[index]), if not found, return -1*/
int findWordInName(catarray_t * cats, size_t index, const char * word) {
  for (size_t j = 0; j < cats->arr[index].n_words; ++j) {
    if (strcmp(cats->arr[index].words[j], word) == 0) {
      return (int)j;
    }
  }
  return -1;
}

// free catarray_t *
void freeCats(catarray_t * cats) {
  if (cats == NULL) {
    return;
  }
  for (size_t i = 0; i < cats->n; ++i) {
    free(cats->arr[i].name);
    for (size_t j = 0; j < cats->arr[i].n_words; ++j) {
      free(cats->arr[i].words[j]);
    }
    free(cats->arr[i].words);
  }
  free(cats->arr);
  free(cats);
}

/*add a new element to array, which is a new category*/
void addToArr(catarray_t * cats, char * name, char * word) {
  ++(cats->n);
  cats->arr = realloc(cats->arr, cats->n * sizeof(*cats->arr));
  cats->arr[cats->n - 1].n_words = 1;
  cats->arr[cats->n - 1].name = name;
  cats->arr[cats->n - 1].words = malloc(1 * sizeof(char *));
  cats->arr[cats->n - 1].words[0] = word;
}

/*add a new word to name, which is at cats->arr[index]*/
void addWordToName(catarray_t * cats, size_t index, char * word) {
  ++(cats->arr[index].n_words);
  cats->arr[index].words =
      realloc(cats->arr[index].words, cats->arr[index].n_words * sizeof(char *));
  // reallocate failure
  if (cats->arr[index].words == NULL) {
    exit(EXIT_FAILURE);
  }
  cats->arr[index].words[cats->arr[index].n_words - 1] = word;
}

/*read from the file and store the words into a catarray_t*/
catarray_t * readWord(FILE * f) {
  catarray_t * cats = malloc(sizeof(*cats));
  // dynamically allocated memory must be initialized
  cats->n = 0;
  cats->arr = NULL;
  char * curr = NULL;
  size_t linecap = 0;
  while (getline(&curr, &linecap, f) >= 0) {
    char * newLine = strchr(
        curr, '\n');  // '\n' always exits, so even curr isn't a string, it's still safe
    *newLine = '\0';
    char * split = strchr(curr, ':');
    if (split == NULL) {
      fprintf(stderr, "Invalid format of input file, missing : in %s\n", curr);
      exit(EXIT_FAILURE);
    }
    *split = '\0';
    int index;
    if ((index = findCat(curr, cats)) == -1) {  // curr as a name not find in cats
      char * name = strdup(curr);
      char * word = strdup(split + 1);
      addToArr(cats, name, word);
    }
    else {
      if (findWordInName(cats, index, split + 1) ==
          -1) {  // current word is not under name
        char * word = strdup(split + 1);
        addWordToName(cats, index, word);
      }
    }
  }
  free(curr);
  return cats;
}

// make filename of fRes, to print the res in another txt file, not used here.
char * makeResFileName(const char * fname) {
  const char * suffix = "_res.txt";
  unsigned len = strlen(fname) + strlen(suffix) + 1;
  char * res = malloc(len * sizeof(*res));
  snprintf(res, len, "%s%s", fname, suffix);
  return res;
}

// if str is a number. return 1: is a number; 0: isn't a number
int isInteger(const char * str) {
  if (*str == '\0') {  // empty string
    return 0;
  }
  char * endptr = NULL;  // first non-digit char except sign symbol
  strtol(str, &endptr, 10);
  return (*endptr == '\0');
}

/* substitute word according to name: 
   1. name is valid number: backtrack in references
   2. name is in cats: substitude with a word
   3. else: invalid input, exit with failure status
   NOT consider reusing issue: reusing of word is permitted
*/
const char * substituteWord(catarray_t * cats, char * name, category_t * reference) {
  int num = atoi(name);
  // num > 0 must be infront of &&, make sure correctness of int to size_t transform
  if (isInteger(name) && num > 0 && (size_t)num <= reference->n_words) {
    return reference->words[reference->n_words - (size_t)num];
  }
  else if (findCat(name, cats) != -1) {
    return chooseWord(name, cats);
  }
  else {  // invalid input
    fprintf(stderr, "Invalid catagory name: %s!\n", name);
    exit(EXIT_FAILURE);
  }
  return NULL;
}

// remove a word from cats->arr[index]
void removeWord(catarray_t * cats, size_t index, char * word) {
  int index_j = findWordInName(cats, index, word);
  if (index_j == -1) {
    fprintf(stderr, "Error: %s not found in %s\n", word, cats->arr[index].name);
    exit(EXIT_FAILURE);
  }
  char * temp = cats->arr[index].words[(size_t)index_j];
  for (size_t j = (size_t)index_j; j < cats->arr[index].n_words - 1; ++j) {
    cats->arr[index].words[j] = cats->arr[index].words[j + 1];
  }
  cats->arr[index].words[cats->arr[index].n_words - 1] = NULL;
  --(cats->arr[index].n_words);
  cats->arr[index].words =
      realloc(cats->arr[index].words, (cats->arr[index].n_words) * sizeof(char *));
  free(temp);
}

// substitute without reusing
const char * substituteWord_2(catarray_t * cats, char * name, category_t * reference) {
  int num = atoi(name);
  // num > 0 must be infront of &&, make sure correctness of int to size_t transform
  int index = findCat(name, cats);
  if (isInteger(name) && num > 0 && (size_t)num <= reference->n_words) {
    const char * res = strdup(reference->words[reference->n_words - (size_t)num]);
    return res;
  }
  else if (index != -1) {
    const char * choice = strdup(chooseWord(name, cats));
    // remove choice from name
    removeWord(cats, (size_t)index, (char *)choice);
    return choice;
  }
  else {  // invalid input
    fprintf(stderr, "Invalid catagory name: %s!\n", name);
    exit(EXIT_FAILURE);
  }
  return NULL;
}

category_t * makeReference() {
  category_t * ref = malloc(sizeof(*ref));
  if (ref == NULL) {
    exit(EXIT_FAILURE);
  }
  ref->n_words = 0;
  ref->name = NULL;
  ref->words = NULL;
  return ref;
}

void freeReference(category_t * reference) {
  for (size_t i = 0; i < reference->n_words; ++i) {
    free(reference->words[i]);
  }
  free(reference->words);
  free(reference);
}

// add the most recently used substitution of word into reference
void addToReference(category_t * reference, char * word) {
  if (reference->n_words == 0) {  // empty, then make a new word list
    ++reference->n_words;
    reference->words = malloc(sizeof(*(reference->words)));
    if (reference->words == NULL) {
      exit(EXIT_FAILURE);
    }
    reference->words[0] = strdup(word);
    if (reference->words[0] == NULL) {
      exit(EXIT_FAILURE);
    }
  }
  else {
    ++(reference->n_words);
    reference->words =
        realloc(reference->words, reference->n_words * sizeof(*(reference->words)));
    if (reference->words == NULL) {
      exit(EXIT_FAILURE);
    }
    reference->words[reference->n_words - 1] = strdup(word);
    if (reference->words[reference->n_words - 1] == NULL) {
      exit(EXIT_FAILURE);
    }
  }
}

// read file f and substitute each _word_, print res to stdout
void substituteAndPrint(FILE * f, catarray_t * cats) {
  category_t * reference = makeReference();
  int c;         // fgetc returns an int
  int flag = 0;  // 1: encoutering left _ without right _
  while ((c = fgetc(f)) != EOF) {
    if (flag == 0 && c == '_') {
      flag = 1;
      char * word = malloc(sizeof(*word));
      int wordLen = 0;
      while ((c = fgetc(f)) != EOF) {
        if (c == '_') {  // encountering right _
          flag = 0;
          ++wordLen;  // for '\0'
          word = realloc(word, wordLen * sizeof(*word));
          if (word == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
          }
          word[wordLen - 1] = '\0';
          break;
        }
        else {
          wordLen += 1;
          word = realloc(word, wordLen * sizeof(*word));
          if (word == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
          }
          word[wordLen - 1] = c;
        }
      }
      char * newWord = (char *)substituteWord(cats, word, reference);
      addToReference(reference, newWord);
      fprintf(stdout, "%s", newWord);
      free(word);
    }
    else {
      fprintf(stdout, "%c", c);
    }
  }
  freeReference(reference);
}

/* read file f and substitute each _word_, print res to stdout
   words can't be reused*/
void substituteAndPrint_2(FILE * f, catarray_t * cats, int reuse) {
  category_t * reference = makeReference();
  int c;         // fgetc returns an int
  int flag = 0;  // 1: encoutering left _ without right _
  while ((c = fgetc(f)) != EOF) {
    if (flag == 0 && c == '_') {
      flag = 1;
      char * word = malloc(sizeof(*word));
      int wordLen = 0;
      while ((c = fgetc(f)) != EOF) {
        if (c == '_') {  // encountering right _
          flag = 0;
          ++wordLen;  // for '\0'
          word = realloc(word, wordLen * sizeof(*word));
          if (word == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
          }
          word[wordLen - 1] = '\0';
          break;
        }
        else {
          wordLen += 1;
          word = realloc(word, wordLen * sizeof(*word));
          if (word == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
          }
          word[wordLen - 1] = c;
        }
      }
      char * newWord;
      if (reuse) {  // reusing not allowed
        newWord = (char *)substituteWord_2(cats, word, reference);
        addToReference(reference, newWord);
        fprintf(stdout, "%s", newWord);
        free(newWord);
        free(word);
      }
      else {
        newWord = (char *)substituteWord(cats, word, reference);
        addToReference(reference, newWord);
        fprintf(stdout, "%s", newWord);
        free(word);
      }
    }
    else {
      fprintf(stdout, "%c", c);
    }
  }
  freeReference(reference);
}

// ONLY for story-step1! read file f and substitute each _word_, print res to stdout
void substituteAndPrint_1(FILE * f) {
  int c;         // fgetc returns an int
  int flag = 0;  // 1: encoutering left _ without right _
  while ((c = fgetc(f)) != EOF) {
    if (flag == 0 && c == '_') {
      flag = 1;
      char * word = malloc(sizeof(*word));
      int wordLen = 0;
      while ((c = fgetc(f)) != EOF) {
        if (c == '_') {  // encountering right _
          flag = 0;
          ++wordLen;  // for '\0'
          word = realloc(word, wordLen * sizeof(*word));
          if (word == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
          }
          word[wordLen - 1] = '\0';
          break;
        }
        else {
          wordLen += 1;
          word = realloc(word, wordLen * sizeof(*word));
          if (word == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
          }
          word[wordLen - 1] = c;
        }
      }
      char * newWord = (char *)chooseWord(word, NULL);  // no category tested yet.
      fprintf(stdout, "%s", newWord);
      //      free(newWord);
      free(word);
    }
    else {
      fprintf(stdout, "%c", c);
    }
  }
}
