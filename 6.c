
#include <stdio.h>
#define N 5
float invmat(float *a, int n) {
  float aux;
  int i, j, k;
  for (i = 0; i < n; i++) {
    aux = *(a + n * i + i);
    for (j = 0; j < n; j++) *(a + n * i + j) /= aux;
    *(a + n * i + i) = 1.0 / aux;
    for (k = 0; k < n; k++)
      if (k != i) {
        aux = *(a + n * k + i);
        for (j = 0; j < n; j++) *(a + n * k + j) -= aux * *(a + n * i + j);
        *(a + n * k + i) = -aux * *(a + n * i + i);
      }
  }
}

void decomp_LU(float *a, int n) {
  int i, j, k;
  float aux, aux2;
  for (i = 0; i < n - 1; i++) {
    aux = *(a + i * n + i);
    for (k = i + 1; k < n; k++) *(a + i * n + k) /= aux;
    for (k = i + 1; k < n; k++) {
      aux2 = *(a + k * n + i);
      for (j = i + 1; j < n; j++) *(a + k * n + j) -= aux2 * *(a + i * n + j);
    }
  }
}

void get_LU(float *a, float *L, float *U, int n) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j <= i; j++) {
      *(L + i * n + j) = *(a + i * n + j);
    }
    for (int j = i; j <= i; j++) {
      *(U + i * n + j) = 1;
    }
    for (int j = i + 1; j < n; j++) {
      *(U + i * n + j) = *(a + i * n + j);
    }
  }
}

void print_matrix(float *a, int n) {
  for (int i = 0; i < n * n; i++) {
    printf("%.2f\t", a[i]);
    if ((i + 1) % n == 0) printf("\n");
  }
  printf("\n");
}

void prodmatmat(float *a, float *b, float *p, int n) {
  float *p1, *p2, *p3, *pa, *pb;
  for (p1 = a, p3 = p; p1 < a + n * n; p1 += n) {
    for (p2 = b; p2 < b + n; p2++, p3++) {
      *p3 = 0;
      for (pa = p1, pb = p2; pa < p1 + n; pa++, pb += n) {
        *p3 += *pa * *pb;
      }
    }
  }
}

float invlinf(float *l, int n) {
  float aux;
  int i, j, k;
  for (i = 1; i < n; i++) {
    aux = *(l + n * i + i);
    *(l + n * i + i) = 1 / aux;
    for (j = 0; j < i; j++) {
      *(l + n * i + j) /= aux;
      *(l + n * i + j) = -*(l + n * i + j) * *(l + n * j + j);
      for (k = j + 1; k < i; k++)
        *(l + n * i + j) -= *(l + n * i + k) * *(l + n * k + j) / aux;
    }
  }
}

float invusup(float *u, int n) {
  int i, j, k;
  for (i = n - 1; i >= 0; i--) {
    for (j = n - 1; j > i; j--) {
      *(u + n * i + j) = -*(u + n * i + j);
      for (k = j - 1; k > i; k--) {
        *(u + i * n + j) -= *(u + n * k + j) * *(u + i * n + k);
      }
    }
  }
}
int max(int a, int b) {
  if (a > b) return a;
  return b;
}
float invLU(float *a, float *r, int n) {
  int i, j, k;
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      for (k = n - 1; k >= max(i, j); k--) {
        if (i == k)
          *(r + n * i + j) += *(a + n * k + j);
        else
          *(r + n * i + j) += *(a + n * i + k) * *(a + n * k + j);
      }
    }
  }
}

int main(void) {
  /* test inv */
  /* // float test[3 * 3] = {2, 3, -1, 4, 4, -3, -2, 3, -1};
  //   invmat(test, 3); */
  float a[N * N] = {1,  1, 1, 1,  1, 1,  0,  0, 0,  0, 1,   -1, 1,
                    -1, 1, 1, -2, 4, -8, 16, 1, -3, 9, -27, 81};
  decomp_LU(a, N);
  print_matrix(a, N);
  /* test LU */

  // float L[N * N] = {0}, U[N * N] = {0};
  float res[N * N] = {0};
  // get_LU(a, L, U, N);
  // invmat(L, N);
  // invmat(U, N);
  // print_matrix(L, N);
  // print_matrix(U, N);
  // prodmatmat(L, U, res, N);
  // print_matrix(res, N);

  invusup(a, N);
  invlinf(a, N);
  print_matrix(a, N);
  invLU(a, res, N);
  print_matrix(res, N);
  return 0;
}
/* inverse de a
0.00    1.00    -0.00   0.00    -0.00
0.25    0.83    -1.50   0.50    -0.08
0.46    -0.83   0.25    0.17    -0.04
0.25    -0.83   1.00    -0.50   0.08
0.04    -0.17   0.25    -0.17   0.04 */