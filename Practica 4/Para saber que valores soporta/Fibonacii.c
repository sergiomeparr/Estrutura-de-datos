#include <stdio.h>
/* Devuelve el t�rmino n-�simo de la sucesi�n de Fibonacci */
double fibonacci (double n) {
  double s1, s2, s3;
  unsigned i = 2;

  if (n == 0) return 0; /* fibo (0) = 0 */
  if (n == 1) return 1; /* fibo (1) = 1 */
  s1 = 0;
  s2 = 1;
  while (i <= n) {
     s3 = s1 + s2;
     s1 = s2;
     s2 = s3;
     i++;
  };
  return s3;
}
/***** Funci�n Principal *****/
int main () {
  double x;
  while(1){
  printf ("Introducir n�mero: ");
  scanf ("%lf", &x); 
  printf ("Fibonacci (%.lf) = %.lf \n\n", x, fibonacci(x) );                 
 }
  return 0;
}
 


