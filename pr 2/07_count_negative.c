#include <stdio.h>

int main()
{
    int n, i = 0, vtoroi_ras, x, skolko = 0;

    vtoroi_ras = scanf("%d", &n);

   for(i; i < n; i++) {
       vtoroi_ras = scanf("%d", &x);
       if(x < 0)
       {
          skolko++;
       }

   }
    printf("%d", skolko);
    return 0;
}