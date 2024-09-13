unsigned power_key(unsigned x, unsigned y, unsigned res);
unsigned power(unsigned x, unsigned y);

// head recursion
//unsigned power(unsigned x, unsigned y) {
//if (y == 0)
//  return 1;
//if (x == 1)
//  return 1;
//return x * power(x, y - 1);
//}

// tail recursion
unsigned power(unsigned x, unsigned y) {
  return power_key(x, y, 1);
}

unsigned power_key(unsigned x, unsigned y, unsigned res) {
  if (y == 0)
    return res;
  if (x == 1)
    return 1;
  return power_key(x, y - 1, x * res);
}
