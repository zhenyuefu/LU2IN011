#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void eval_Horner_1(double a, double* coeff_f, int n, double* f_a) {
  *f_a = coeff_f[n];
  for (int i = n - 1; i >= 0; i--) {
    *f_a = a * *f_a + coeff_f[i];
  }
}

void eval_Horner_2(double a, double* coeff_f, int n, double* f_a,
                   double* f_minus_a) {
  double yi, yp, x_2;
  int i;
  x_2 = a * a;
  if (n / 2) {
    yi = coeff_f[n];
    yp = coeff_f[n - 1];
    i = n - 2;
  } else {
    yi = 0;
    yp = coeff_f[n];
    i = n - 1;
  }
  for (; i >= 0; i -= 2) {
    yi = yi * x_2 + coeff_f[i];
    yp = yp * x_2 + coeff_f[i - 1];
  }
  *f_a = yp + a * yi;
  *f_minus_a = yp - a * yi;
}

void gauss(double* a, double* b, int n) {
  int i, j, k, il;
  double aux, aux2;
  for (i = 0; i < n - 1; i++) {
    aux = *(a + i * n + i);
    for (k = i + 1; k < n; k++) *(a + i * n + k) /= aux;
    *(b + i) /= aux;
    for (k = i + 1; k < n; k++) {
      aux2 = *(a + k * n + i);
      for (j = i + 1; j < n; j++) *(a + k * n + j) -= aux2 * *(a + i * n + j);
      *(b + k) -= aux2 * *(b + i);
    }
  }
  *(b + n - 1) /= *(a + n * n - 1);
  for (i = n - 2; i >= 0; i--) {
    aux = *(b + i);
    for (k = i + 1; k < n; k++) aux -= *(a + i * n + k) * *(b + k);
    *(b + i) = aux;
  }
}

void interpol_linalg(double* a, double* f_a, int n, double* coeff_f) {
  double c[n * n];
  for (int i = 0; i < n; i++) {
    *(c + i * n) = 1;
    coeff_f[i] = f_a[i];
    for (int j = 1; j < n; j++) {
      *(c + i * n + j) = *(c + i * n + j - 1) * a[i];
    }
  }
  gauss(c, coeff_f, n);
}

double sum(double* t, int index_fin, int num) {
  double r = 0;
  for (int i = 0; i < num; i++) {
    r += t[index_fin - i];
  }
  return r;
}

void interpol_Lagrange(double* a, double* f_a, int n, double* coeff_f) {
  double l[n][n];
  double c;
  double d[n];
  double t[n], t_temp[n];
  int t_index = 0;
  for (int i = 0; i < n; i++) {
    c = f_a[i];
    d[0] = 1;
    t_index = 0;
    for (int j = 0; j < n; j++) {
      if (i != j) {
        c /= (a[i] - a[j]);
        t[t_index] = -a[j];
        t_temp[t_index] = -a[j];
        t_index++;
      }
    }
    d[1] = sum(t, n - 2, n - 1);
    for (int k = 2; k < n; k++) {
      d[k] = 0;
      for (int l = 0; l < n - k; l++) {
        t_temp[l] = t[l] * sum(t_temp, n - k, n - k - l);

        d[k] += t_temp[l];
      }
    }
    for (int m = 0; m < n; m++) {
      l[i][n - m - 1] = d[m] * c;
      // printf("l[%d][%d] = %f,d[%d]=%f,c=%f\n", i, n - m - 1, l[i][n - m -
      // 1],m,d[m], c);
    }
  }
  for (int i = 0; i < n; i++) {
    coeff_f[n - i - 1] = 0;
    for (int j = 0; j < n; j++) {
      coeff_f[n - i - 1] += l[j][n - i - 1];
    }
  }
}

int main(void) {
  /* test function Lagrange */
  // double x[3] = {-1, 2, 3};
  // double y[3] = {4, 4, 8};
  // int n = 3;
  // double coeff[3];
  // double ans[3];
  // interpol_Lagrange(x, y, 3, coeff);
  // eval_Horner_1(-1, coeff, 3, &ans[0]);
  // eval_Horner_1(2, coeff, 3, &ans[1]);
  // eval_Horner_1(3, coeff, 3, &ans[2]);
  // for (int i = 0; i < 3; i++) printf("%f\t", ans[i]);
  // printf("\n");
  int n = pow(2, 9);
  double x[n];
  double y[n];
  double coeff_function[n];
  srand((unsigned)time(NULL));
  for (int i = 0; i < n; i++) {
    x[i] = i;
    y[i] = rand() % 2 - 1;
  }
  clock_t start_t, end_t;
  double total_t;
  start_t = clock();
  interpol_linalg(x, y, n, coeff_function);
  end_t = clock();
  total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
  printf("Time interpol_linalg:%f\n", total_t);

  start_t = clock();
  interpol_Lagrange(x, y, n, coeff_function);
  end_t = clock();
  total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
  printf("Time interpol_Lagrange:%f\n", total_t);

  return 0;
}