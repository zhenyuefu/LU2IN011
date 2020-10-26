#include <stdio.h>
void gauss_jordan(float *a, float *b, int n) {
  int i, j, k, il;
  float aux;
  for (i = 0; i < n; i++) {
    aux = *(a + i * n + i);
    for (j = i + 1; j < n; j++)
      *(a + i * n + j) /= aux;
    for (j = 0; j < n; j++)
      *(b + i * n + j) /= aux;
    for (k = 0; k < n; k++)
      if (k != i) {
        aux = *(a + k * n + i);
        for (j = i + 1; j < n; j++)
          *(a + n * k + j) -= aux * *(a + n * i + j);
        for (j = 0; j < n; j++)
          *(b + n * k + j) -= aux * *(b + n * i + j);
      }
  }
}

int main(void) {
  float a[16] = {15.0, 34.0, 27.0, 2.0, 8.0, 23,   10.0, 1.0,
                 11.0, 17.0, 9.0,  4.0, 8.0, 65.0, 45.,  7};
  float b[16] = {1,   2,   3.5, 2,   0.7, 1.2, 1.5, 1,
                 0.8, 1.1, 1.2, 0.8, 11,  15,  7,   5};
  gauss_jordan(a, b, 4);
  for (int i = 0; i < 16; i++) {
    printf("%f\t", b[i]);
  }
  return 0;
}