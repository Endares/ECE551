#include "target.h"

double pos_to_angle(double x, double y);

launch_result_t compute_launch_by_info(const launch_input_t * this_launch,
                                       const planet_list_t * planets) {
  //STEP 3: Write this
  planet_t *srcPlanet, *destPlanet;
  srcPlanet = find_planet(planets, this_launch->src);
  destPlanet = find_planet(planets, this_launch->dest);
  point_t srcCoordinate, destCoordinate;
  srcCoordinate = get_location_at(srcPlanet, this_launch->time);
  destCoordinate = get_location_at(destPlanet, this_launch->time);
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
  if (angle < 0)
    angle += 2 * M_PI;
  //angle = fmod((angle + 2 * M_PI), 2 * M_PI);

  launch_result_t res;
  res.duration = time;
  res.theta = angle;
  return res;
}

double when_does_planet_return_to(const planet_t * planet,
                                  point_t pos,
                                  double start_time) {
  //STEP 3: Write this
  // posistion of the planet at start_time
  point_t pos_start = get_location_at(planet, start_time);
  double ang_start = pos_to_angle(pos_start.x, pos_start.y);
  double ang_end = pos_to_angle(pos.x, pos.y);
  double duration =
      fmod(ang_end - ang_start + 2 * M_PI, 2 * M_PI) / (2 * M_PI) * planet->year_len;
  return start_time + duration;
}

double pos_to_angle(double x, double y) {
  double angle = atan(y / x);
  if (x < 0)
    angle += M_PI;
  if (angle < 0)
    angle += 2 * M_PI;
  return angle;
}
