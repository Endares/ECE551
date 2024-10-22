class Point {
 private:
  double x;
  double y;

 public:
  Point();
  Point(double dx, double dy);
  void move(double dx, double dy);
  double distanceFrom(const Point & p);
  Point & operator=(const Point & rhs);
  ~Point();
};
