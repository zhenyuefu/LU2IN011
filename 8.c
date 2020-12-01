#include <math.h>
#include <stdio.h>

double f(double x) { return exp(x) - 4; }

double fprime(double x) { return exp(x); }

double g(double x) { return sin(x - 3); }

double gprime(double x) { return cos(x - 3); }

double h(double x) { return (9 * x * x - 1) * 18 * x - 3; }

double hprime(double x) { return 486 * x * x - 18; }

double p(double x) { return x * x * (x - 2) * (x + 1) * (x - 1); }

double pprime(double x) {
  return 4 * x - 3 * x * x - 8 * x * x * x + 5 * x * x * x * x;
}

int bissection(double *z, double (*f)(double), double a, double b, double eps) {
  double a1, b1, m, fa1, fb1, fm;
  if (b < a) {
    a1 = b;
    b1 = a;
  } else {
    a1 = a;
    b1 = b;
  }
  fa1 = f(a1);
  fb1 = f(b1);
  if (fa1 * fb1 > 0) return 0;
  do {
    m = (a1 + b1) / 2;
    fm = f(m);
    if (fa1 * fm < 0) {
      b1 = m;
      fb1 = f(m);
    } else {
      a1 = m;
      fa1 = f(m);
    }
    if (fa1 == 0) break;
  } while ((b1 - a1) > eps);
  *z = a1;
  return 1;
}

int newton(double *z, double (*f)(double), double (*fprime)(double), double a,
           double b, double eps) {
  double x = (a + b) / 2;
  double fx, fpx, x0;
  do {
    x0 = x;
    fx = f(x0);
    fpx = fprime(x0);
    if (fpx == 0) return 0;
    x = x0 - fx / fpx;
  } while (fabs(x - x0) > eps);
  *z = x;
  return 1;
}
int findzero(double *z, double (*f)(double), double (*fprime)(double), double a,
             double b, double eps) {
  if (bissection(z, f, a, b, 0.1) == 0) return 0;
  if (newton(z, f, fprime, a, b, eps) == 0) return 0;
  return 1;
}

int main(void) {
  double eps = pow(10, -8);
  double *res;
  printf("-----------dichotomie----------\n");
  bissection(res, f, 1, 1.5, eps);
  printf("f:%f\n", *res);
  bissection(res, g, -0.5, 0.5, eps);
  printf("g:%f\n", *res);
  bissection(res, h, -1 / 3, 1, eps);
  printf("h:%f\n", *res);
  bissection(res, p, -1.5, 0.5, eps);
  printf("p:%f\n", *res);
  printf("-------------newton------------\n");
  newton(res, f, fprime, 1, 1.5, eps);
  printf("f:%f\n", *res);
  newton(res, g, gprime, -0.5, 0.5, eps);
  printf("g:%f\n", *res);
  newton(res, h, hprime, -1 / 3, 1, eps);
  printf("h:%f\n", *res);
  newton(res, p, pprime, -1.5, 0.5, eps);
  printf("p:%f\n", *res);
  printf("------------findzero-----------\n");
  findzero(res, f, fprime, 1, 1.5, eps);
  printf("f:%f\n", *res);
  findzero(res, g, gprime, -0.5, 0.5, eps);
  printf("g:%f\n", *res);
  findzero(res, h, hprime, -1 / 3, 1, eps);
  printf("h:%f\n", *res);
  findzero(res, p, pprime, -1.5, 0.5, eps);
  printf("p:%f\n", *res);
  return 0;
}