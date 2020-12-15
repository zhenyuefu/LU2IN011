#include <math.h>
#include <stdio.h>
#include <time.h>

double f1(double x) { return cos(x); }
double f2(double x) { return sin(x); }
double f3(double x) { return exp(x); }
double f4(double x) { return pow(x, 10); }

double rectangle(double (*f)(double), double a, double b, long n) {
  double aux1, x1, h;
  h = (b - a) / n;
  aux1 = 0;
  for (x1 = a; x1 < b + h / 2; x1 += h) aux1 += f(x1);
  return h * aux1;
}

double trapeze(double (*f)(double), double a, double b, long n) {
  double aux1, x1, h;
  h = (b - a) / n;
  aux1 = 0;
  for (x1 = a + h; x1 < b - h / 2; x1 += h) aux1 += f(x1);
  return (h / 2) * (f(a) + 2 * aux1 + f(b));
}

double simpson(double (*f)(double), double a, double b, long n) {
  double aux1, aux2, x1, x2, h, h2;
  h = (b - a) / n;
  h2 = 2 * h;
  aux1 = f(a + h);
  aux2 = 0;
  for (x1 = a + 3 * h, x2 = a + h2; x1 < b; x1 += h2, x2 += h2) {
    aux1 += f(x1);
    aux2 += f(x2);
  }
  return (h / 3) * (f(a) + 4 * aux1 + 2 * aux2 + f(b));
}

int main(void) {
  const double pi = acos(-1);
  long n;
  double ans[8];
  double realans[8] = {
      sin(1) - sin(0), 1 - cos(1),      exp(1) - 1, 1 / 11, 0, 2,
      exp(pi) - 1,     pow(pi, 11) / 11};
  double err;
  struct timespec start, end;

  /* methode rectangle */
  timespec_get(&start, TIME_UTC);
  for (int k = 4; k <= 10; k++) {
    n = pow(2, k);
    ans[0] = rectangle(f1, 0, 1, n);
    ans[1] = rectangle(f2, 0, 1, n);
    ans[2] = rectangle(f3, 0, 1, n);
    ans[3] = rectangle(f4, 0, 1, n);
    ans[4] = rectangle(f1, 0, pi, n);
    ans[5] = rectangle(f2, 0, pi, n);
    ans[6] = rectangle(f3, 0, pi, n);
    ans[7] = rectangle(f4, 0, pi, n);
    err = 0;
    for (int i = 0; i < 8; i++) {
      err += ans[i] - realans[i];
    }
    printf("n:%d->err:%f\n", n, err / 8);
  }
  timespec_get(&end, TIME_UTC);

  time_t d_sec = end.tv_sec - start.tv_sec;
  long d_nsec = end.tv_nsec - start.tv_nsec;
  long duration = d_sec * 1E9 + d_nsec;
  printf("Time rectangle: %ld nanosecond\n", duration);

  /* methode trapeze */
  timespec_get(&start, TIME_UTC);
  for (int k = 4; k <= 10; k++) {
    n = pow(2, k);
    ans[0] = trapeze(f1, 0, 1, n);
    ans[1] = trapeze(f2, 0, 1, n);
    ans[2] = trapeze(f3, 0, 1, n);
    ans[3] = trapeze(f4, 0, 1, n);
    ans[4] = trapeze(f1, 0, pi, n);
    ans[5] = trapeze(f2, 0, pi, n);
    ans[6] = trapeze(f3, 0, pi, n);
    ans[7] = trapeze(f4, 0, pi, n);
    err = 0;
    for (int i = 0; i < 8; i++) {
      err += ans[i] - realans[i];
    }
    printf("n:%d->err:%f\n", n, err / 8);
  }
  timespec_get(&end, TIME_UTC);
  d_sec = end.tv_sec - start.tv_sec;
  d_nsec = end.tv_nsec - start.tv_nsec;
  duration = d_sec * 1E9 + d_nsec;
  printf("Time trapeze: %ld nanosecond\n", duration);

  /* methode simpson */
  timespec_get(&start, TIME_UTC);
  for (int k = 4; k <= 10; k++) {
    n = pow(2, k);
    ans[0] = simpson(f1, 0, 1, n);
    ans[1] = simpson(f2, 0, 1, n);
    ans[2] = simpson(f3, 0, 1, n);
    ans[3] = simpson(f4, 0, 1, n);
    ans[4] = simpson(f1, 0, pi, n);
    ans[5] = simpson(f2, 0, pi, n);
    ans[6] = simpson(f3, 0, pi, n);
    ans[7] = simpson(f4, 0, pi, n);
    err = 0;
    for (int i = 0; i < 8; i++) {
      err += ans[i] - realans[i];
    }
    printf("n:%d->err:%f\n", n, err / 8);
  }
  timespec_get(&end, TIME_UTC);
  d_sec = end.tv_sec - start.tv_sec;
  d_nsec = end.tv_nsec - start.tv_nsec;
  duration = d_sec * 1E9 + d_nsec;
  printf("Time simpson: %ld nanosecond\n", duration);
  return 0;
}