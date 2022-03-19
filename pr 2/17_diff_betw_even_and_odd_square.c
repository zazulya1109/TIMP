#include <stdio.h>
#include <math.h>
int main()
{
    int n, vtoroi_ras, i = 1, x, sum = 0;

    vtoroi_ras = scanf("%d", &n);
    
 
   for(i; i <= n; i += 1) 
   {
        if (scanf("%d", &x) > 0)
        {
         sum += pow(-1, (double)i)*x*x;
        }
    
      
   }
    printf("%d", sum);
    return 0;
}