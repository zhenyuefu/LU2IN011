#include <stdio.h>
#include <stdlib.h>

#define N 16
void prodmatmat(double *a, double *b, double *p, int n) {
  // for (int i = 0; i < n; i++) {
  //   for (int j = 0; j < n; j++) {
  //     *(p + i * n + j) = 0;
  //     for (int k = 0; k < n; k++) {
  //       *(p + i * n + j) += *(a + i * n + k) * *(b + k * n + j);
  //     }
  //   }
  // }
  double *p1, *p2, *p3, *pa, *pb;
  for (p1 = a, p3 = p; p1 < a + n * n; p1 += n) {
    for (p2 = b; p2 < b + n; p2++, p3++) {
      *p3 = 0;
      for (pa = p1, pb = p2; pa < p1 + n; pa++, pb += n) {
        *p3 += *pa * *pb;
      }
    }
  }
}

int main(void) {
  double res[N];
  double mat1[N] = {15.0, 34.0, 27.0, 2.0, 8.0, 23,   10.0, 1.0,
                    11.0, 17.0, 9.0,  4.0, 8.0, 65.0, 45.,  7};
  double mat2[N] = {1,   2,   2.5, 2,   0.7, 1,  1.5, 1,
                    0.6, 1.1, 1.2, 0.8, 10,  15, 7,   5};
  prodmatmat(mat1, mat2, res, 4);

  int i;
  for (i = 0; i < N; i++) {
    printf("%lf\t", res[i]);
  }
  return 0;
}