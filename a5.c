#include <fenv.h>
#include <stdio.h>
#include <stdlib.h>

#define N 11

void gauss_det(double *a, int n, double *det) {
  int i, j, k, il;
  double aux, aux2;
  *det = 1;
  for (i = 0; i < n - 1; i++) {
    aux = *(a + i * n + i);
    *det *= aux;
    for (k = i + 1; k < n; k++)
      *(a + i * n + k) /= aux;
    for (k = i + 1; k < n; k++) {
      aux2 = *(a + k * n + i);
      for (j = i + 1; j < n; j++)
        *(a + k * n + j) -= aux2 * *(a + i * n + j);
    }
  }
  *det *= *(a + n * n - 1);
}

void creat_Hilbert(double *h, int n) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      *(h + n * i + j) = 1.0 / (i + j + 1);
    }
  }
}

double factorial(int n) {
  double r = 1;
  for (int i = 2; i <= n; i++) {
    r *= i;
  }
  return r;
}

double det_Hilbert(int n) {
  double a = 1, b = 1;
  double r;
  for (int i = 1; i < n; i++) {
    a *= factorial(i);
  }
  for (int i = 1; i < 2 * n; i++) {
    b *= factorial(i);
  }

  r = (a * a * a * a) / b;

  return r;
}

int main(void) {
  // float a[N * N] = {10, 0, -5, 15, -2, 7, 3, 0, 8, 14, 1, 2, 0, -21, 1, -1};
  double det;
  double Hilbert[N * N];
  double deth;
  //   int k;
  //   for (k = 0; k < 4; k++) {
  //     switch (k) {
  //     case 0:
  //       fesetround(FE_TOWARDZERO);
  //       break;
  //     case 1:
  //       fesetround(FE_TONEAREST);
  //       break;
  //     case 2:
  //       fesetround(FE_DOWNWARD);
  //       break;
  //     case 3:
  //       fesetround(FE_UPWARD);
  //       break;
  //     };
  //   }
  //   gauss_det(a, N, &det);
  creat_Hilbert(Hilbert, N);
  // for (int i = 0; i < N * N; i++) {
  //   printf("%f ", Hilbert[i]);
  //   if (((i + 1) % N) == 0)
  //     printf("\n");
  // }
  gauss_det(Hilbert, N, &det);
  printf("det 1:%e\n", det);
  deth = det_Hilbert(N);
  printf("det 2:%e\n", deth);
  return 0;
}