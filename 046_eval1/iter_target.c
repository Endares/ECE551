#include "iter_target.h"

#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double calculate_distance(point_t p1, point_t p2);
launch_result_t compute_new_launch_by_info(const launch_input_t * this_launch,
                                           const planet_list_t * planets,
                                           double delta_time);

launch_result_t solve_launch(const launch_input_t * this_launch,
                             const planet_list_t * planets) {
  //STEP 4: write this function
  planet_t * destPlanet;

  destPlanet = find_planet(planets, this_launch->dest);

  double start_time = this_launch->time;

  double min_time = DBL_MAX;
  launch_result_t res;
  double delta_time = 0;

  for (uint64_t i = 0; i < this_launch->max_iterations; ++i) {
    launch_result_t cur_launch_info =
        compute_new_launch_by_info(this_launch, planets, delta_time);
    double cur_dura = cur_launch_info.duration;
    // the precise pos of the destPlanet at ship's arrival
    point_t cur_pos = get_location_at(destPlanet, cur_dura + start_time);
    // the precise pos of the ship at its arrival, aka destPlanet's estimated pos
    point_t dest_pos = get_location_at(destPlanet, delta_time + start_time);

    delta_time = cur_dura;

    if (calculate_distance(cur_pos, dest_pos) <= this_launch->close_enough) {
      // land immediately
      if (cur_dura + 0 <= min_time) {
        min_time = cur_dura;
        res = cur_launch_info;
      }
      return res;
    }
    double cur_meet =
        when_does_planet_return_to(destPlanet, dest_pos, start_time + cur_dura);
    if (cur_meet - start_time < min_time) {
      min_time = cur_meet - start_time;
      res = cur_launch_info;
    }
  }
  return res;
}

launch_result_t compute_new_launch_by_info(const launch_input_t * this_launch,
                                           const planet_list_t * planets,
                                           double delta_time) {
  planet_t *srcPlanet, *destPlanet;
  srcPlanet = find_planet(planets, this_launch->src);
  destPlanet = find_planet(planets, this_launch->dest);
  point_t srcCoordinate, destCoordinate;
  srcCoordinate = get_location_at(srcPlanet, this_launch->time);
  destCoordinate = get_location_at(destPlanet, this_launch->time + delta_time);
  double xs, ys, xd, yd;
  xs = srcCoordinate.x;
  ys = srcCoordinate.y;
  xd = destCoordinate.x;
  yd = destCoordinate.y;

  double distance, time, angle;
  distance = sqrt(pow((xd - xs), 2) + pow((yd - ys), 2));
  time = distance / this_launch->speed;
  angle = atan((yd - ys) / (xd - xs));
  if ((xd - xs) < 0) {
    angle += M_PI;
  }
  if (angle < 0) {
    angle += 2 * M_PI;
  }

  launch_result_t res;
  res.duration = time;
  res.theta = angle;
  return res;
}

double calculate_distance(point_t p1, point_t p2) {
  double distance = sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
  return distance;
}
