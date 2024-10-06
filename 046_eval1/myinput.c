#include "myinput.h"

#include <ctype.h>
#include <float.h>
#include <stdio.h>

void parse_planet_info(planet_t * planet, char * line) {
  //STEP 1: Write this
  char * ptr = line;
  char pname[32];
  double radius = 0, period = 0, initPos = 0;
  int i = 0;
  // 1.name
  if (ptr == NULL) {
    fprintf(stderr, "Error: empty input!\n");
    exit(EXIT_FAILURE);
  }
  while (ptr && *ptr != ':') {
    if (*ptr == '\n' || *ptr == '\0') {
      fprintf(stderr, "Invalid input: name contains %c\n", *ptr);
      exit(EXIT_FAILURE);
    }
    if (i >= 31) {  // need one extra space for '\0'
      fprintf(stderr, "Invalid input: name has more than 32 characters\n");
      exit(EXIT_FAILURE);
    }
    pname[i] = *ptr;
    ++ptr;
    ++i;
  }
  pname[i] = '\0';
  if (!ptr || *ptr != ':') {
    fprintf(stderr, "Invalid input: missing ':' between name and radius.\n");
    exit(EXIT_FAILURE);
  }
  else {
    ++ptr;
  }

  // 2.radius
  if (ptr && *ptr == '+') {
    ++ptr;
  }
  if (!ptr || !isdigit(*ptr)) {
    fprintf(stderr, "Invalid input: missing radius!\n");
    exit(EXIT_FAILURE);
  }
  while (ptr && isdigit(*ptr)) {
    if (radius > DBL_MAX / 10) {
      fprintf(stderr, "Invalid input: radius too big, overflowing double-type.\n");
      exit(EXIT_FAILURE);
    }
    radius = radius * 10 + (*ptr - '0');
    ++ptr;
  }
  // floating point
  if (ptr && *ptr == '.') {
    ++ptr;
    double factor = 10;
    while (ptr && isdigit(*ptr)) {
      if (radius > DBL_MAX - (*ptr - '0') / factor) {
        fprintf(stderr, "Invalid input: radius too big, overflowing double-type.\n");
        exit(EXIT_FAILURE);
      }
      radius += (*ptr - '0') / factor;
      factor *= 10;
      ++ptr;
    }
  }

  if (radius == 0) {
    fprintf(stderr, "Invalid input: radius is 0\n");
    exit(EXIT_FAILURE);
  }

  if (!ptr || *ptr != ':') {
    fprintf(stderr, "Invalid input: missing ':' between radius and period.\n");
    exit(EXIT_FAILURE);
  }
  else {
    ++ptr;
  }

  // 3.period
  if (ptr && *ptr == '+') {
    ++ptr;
  }
  if (!ptr || !isdigit(*ptr)) {
    fprintf(stderr, "Invalid input: missing period!\n");
    exit(EXIT_FAILURE);
  }
  while (ptr && isdigit(*ptr)) {
    if (period > DBL_MAX / 10) {
      fprintf(stderr, "Invalid input: period too big, overflowing double-type.\n");
      exit(EXIT_FAILURE);
    }
    period = period * 10 + (*ptr - '0');
    ++ptr;
  }

  // floating point
  if (ptr && *ptr == '.') {
    ++ptr;
    double factor = 10;
    while (ptr && isdigit(*ptr)) {
      if (period > DBL_MAX - (*ptr - '0') / factor) {
        fprintf(stderr, "Invalid input: period too big, overflowing double-type.\n");
        exit(EXIT_FAILURE);
      }
      period += (*ptr - '0') / factor;
      factor *= 10;
      ++ptr;
    }
  }
  if (period == 0) {
    fprintf(stderr, "Invalid input: period is 0.\n");
    exit(EXIT_FAILURE);
  }

  if (!ptr || *ptr != ':') {
    fprintf(stderr, "Invalid input: missing ':' between period and intial position.\n");
    exit(EXIT_FAILURE);
  }
  else {
    ++ptr;
  }

  // 4.initial position -- angle(deg to radians)
  if (ptr && *ptr == '+') {
    ++ptr;
  }
  if (!ptr || !isdigit(*ptr)) {
    fprintf(stderr, "Invalid input: missing initial position!\n");
    exit(EXIT_FAILURE);
  }
  while (ptr && isdigit(*ptr)) {
    if (initPos > DBL_MAX / 10) {
      fprintf(stderr,
              "Invalid input: initial position too big, overflowing double-type.\n");
      exit(EXIT_FAILURE);
    }
    initPos = initPos * 10 + (*ptr - '0');
    ++ptr;
  }

  // floating point
  if (ptr && *ptr == '.') {
    ++ptr;
    double factor = 10;
    while (ptr && isdigit(*ptr)) {
      if (initPos > DBL_MAX - (*ptr - '0') / factor) {
        fprintf(stderr,
                "Invalid input:initial position too big, overflowing double-type.\n");
        exit(EXIT_FAILURE);
      }
      initPos += (*ptr - '0') / factor;
      factor *= 10;
      ++ptr;
    }
  }

  if (!ptr && *ptr != '\n') {
    fprintf(stderr, "Invalid input: missing newline character.\n");
    exit(EXIT_FAILURE);
  }
  while (initPos > 360) {
    initPos = initPos - 360;
  }
  // degree to radians
  initPos = initPos * M_PI / 180.0;

  // 5.set planet information
  strcpy(planet->name, pname);  // array can't be used as assigned value
  planet->orbital_radius = radius;
  planet->year_len = period;
  planet->init_pos = initPos;
}
