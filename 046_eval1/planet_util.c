#include "planet_util.h"

#include <stdio.h>
#include <string.h>

#include "provided.h"

point_t get_location_at(const planet_t * p, double time) {
  // Step 2: WRITE THIS
  double angle = p->init_pos + time * 2 * M_PI / p->year_len;
  point_t coord;
  coord.x = p->orbital_radius * cos(angle);
  coord.y = p->orbital_radius * sin(angle);
  return coord;
}
planet_t * find_planet(const planet_list_t * lst, const char * name) {
  //Step 2: WRITE THIS
  for (int i = 0; i < lst->num_planets; ++i) {
    if (!strcmp(lst->planets[i]->name, name)) {
      return lst->planets[i];
    }
  }
  fprintf(stderr, "Planet named %s doesn't exit.\n", name);
  exit(EXIT_FAILURE);
}
