#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include <stdio.h>

#include "provided.h"

//any functions you want your main to use
const char * chooseWord(char * category, catarray_t * cats);
void printWords(catarray_t * cats);

/*substitute the _word_ in file f with rules in cats, print the result to stdout, words can be reused*/
void substituteAndPrint(FILE * f, catarray_t * cats);
// words can't be reused
void substituteAndPrint_2(FILE * f, catarray_t * cats, int reuse);
// ONLY for story-step1
void substituteAndPrint_1(FILE * f);
// make substitution of words according to rules
const char * substituteWord(catarray_t * cats, char * name, category_t * reference);
// make substitution of words according to rules without reusing
const char * substituteWord_2(catarray_t * cats, char * name, category_t * reference);
// remove a word from cats->arr[index]
void removeWord(catarray_t * cats, size_t index, char * word);

// add the most recently used substitution of word into reference
void addToReference(category_t * reference, char * word);
category_t * makeReference();
void freeReference(category_t * reference);

/*read from the file and store the words into a catarray_t*/
catarray_t * readWord(FILE * f);

void freeCats(catarray_t * cats);

/*return the index of specific name in cats->arr, if not found, return -1*/
int findCat(const char * name, catarray_t * cats);

/*find the index pf specific word under a specific name (at cats->arr[index]), if not found, return -1*/
int findWordInName(catarray_t * cats, size_t index, const char * word);

/*add a new word to name, which is at cats->arr[index]*/
void addWordToName(catarray_t * cats, size_t index, char * word);

/*read from the file and store the words into a catarray_t*/
catarray_t * readWord(FILE * f);
#endif
