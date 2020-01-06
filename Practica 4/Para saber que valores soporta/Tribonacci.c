#include <stdio.h>
/* Devuelve el término n-ésimo de la sucesión de Tribonacci */
double tribonacci (double n) {
  double s1, s2, s3,s4;
  unsigned i = 3;

  if (n == 0 || n == 1) return 1;
  if (n == 2) return 2; 
  s1 = 1;
  s2 = 1;
  s3 = 2;
  s4 = 0;
  while (i <= n) {
     s4 = s1 + s2 + s3;
     s1 = s2;
     s2 = s3;
     s3 = s4;
     i++;
  };
  return s4;

}
/***** Función Principal *****/
int main () {
  double x;
  while(1){
  printf ("Introducir número: ");
  scanf ("%lf", &x); 
  printf ("Tribonacci (%.lf) = %.lf \n\n", x, tribonacci(x) );                 
 }
  return 0;
}
