#include <math.h>
#include <stdint.h>
#include <stdio.h>

// int bitcommun(double x, double y) {
//   return -log10(fabs(2 * (x - y) / (x + y)));
// }

// int bitcommun_opt(double x, double y) {
//   uint64_t mask = 0;
//   uint64_t a = (*(uint64_t*)&x) & mask;
//   uint64_t b = (*(uint64_t*)&y) & mask;
//   printf("%d %d", x, y);
//   return 0;
// }
void p(double a, double x0, double delta, double xs) {
  double x1, x2 = x0;
  double v, rapport;
  int i = 0;
  printf("x0=%.1f,a=%.1f\n", x0, a);
  do {
    x1 = x2;
    x2 = (((4 * x1 - (3 * a - 2)) * x1 - a) * x1 - 2 * a) /
         ((5 * x1 - (4 * a - 3)) * x1 - 2 * a - 2);
    i++;
    rapport = fabs(x2 - xs) / fabs(x1 - xs);
    v = -log10(fabs((x2 - xs) / xs));
    printf("x%d=%f\tv=%f\trapport=%f\n", i, x2, v, rapport);
  } while (fabs(x1 - x2) > delta);
  printf("\n\n\n");
}

int main(void) {
  double delta = pow(10, -14);
  p(0.3, 2, delta, 1);      // linéaire
  p(3.5, 5, delta, 3.5);    // exponentielle.
  p(3.5, 0.5, delta, 1);    // linéaire
  p(1.0, -3.0, delta, -2);  // linéaire
  p(1.0, 2.0, delta, 1);    // linéaire

  return 0;
}
