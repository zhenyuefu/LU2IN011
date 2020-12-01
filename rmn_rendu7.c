#include <assert.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

double terme_suite(double param, double terme_precedent) {
  double numerateur =
      ((4 * terme_precedent - (3 * param - 2)) * terme_precedent - param) *
          terme_precedent -
      2 * param;
  double denominateur =
      (5 * terme_precedent - (4 * param - 3)) * terme_precedent - 2 * param - 2;

  return numerateur / denominateur;
}

void convergence_suite() {
  double alpha, x0, epsilon;

  printf(
      "Recherche du rang a partir duquel la difference entre la valeur de deux "
      "termes successifs est inferieur a epsilon.\n\n");

  printf("Valeur de α ?\n");
  int verif = scanf("%lf", &alpha);
  assert(verif);

  printf("Valeur de x0 ?\n");
  verif = scanf("%lf", &x0);
  assert(verif);

  printf("Valeur de epsilon ?\n");
  verif = scanf("%lf", &epsilon);
  assert(verif);
  assert(epsilon > 0);

  int rang = 1;

  double x = x0;
  double x_suivant = terme_suite(alpha, x);
  double tmp;

  printf("x0 : %lf\nx1 : %lf\n", x, x_suivant);
  while ((fabs(x_suivant - x) >= epsilon)) {
    x = x_suivant;
    x_suivant = terme_suite(alpha, x);

    rang++;

    printf("x%d : %lf\n", rang, x_suivant);
  }
}

void description_convergence_suite() {
  double a, x0, epsilon, xs;

  printf("Valeur de a ?\n");
  int verif = scanf("%lf", &a);
  assert(verif);

  printf("Valeur de x0 ?\n");
  verif = scanf("%lf", &x0);
  assert(verif);

  printf("Valeur de epsilon ?\n");
  verif = scanf("%lf", &epsilon);
  assert(verif);
  assert(epsilon > 0);

  printf("Valeur de xs ?\n");
  verif = scanf("%lf", &xs);
  assert(verif);

  double x1, x2 = x0;
  double v, rapport;
  int i = 0;

  printf("x0=%.1f,a=%.1f\n", x0, a);
  do {
    x1 = x2;
    x2 = terme_suite(a, x1);
    i++;
    rapport = fabs(x2 - xs) / fabs(x1 - xs);
    v = -log10(fabs((x2 - xs) / xs));
    printf("x%d=%f\tv=%f\trapport=%f\n", i, x2, v, rapport);
  } while (fabs(x1 - x2) > epsilon);
  printf("\n\n\n");
}

int main() {
  printf(
      "On considere la suite suivante :\nx(n+1) = (4*x(n)^3 - (3*α - 2)*x(n)^2 "
      "- α*x(n) - 2*α) / (5*x(n)^2 - (4*α - 3)*x(n) - 2α - 2)\n\n");
  // convergence_suite();
  description_convergence_suite();

  return 0;
}