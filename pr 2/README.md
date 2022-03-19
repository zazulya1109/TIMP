# Практическая работа №2
Ход работы : требуется написать программы в соответствии с вариантом на языке программирования С. 

Программа     | Название на gitlab
-----------  | -------------
Вариант 7. Количество отрицательных чисел.    | **07_count_negative.c**
Вариант 17. Разность сумм чётных и нечётных квадратов    | **17_diff_betw_even_and_odd_squares.c**
##### Программа №1 

##### Исходный код по первой программе 
```
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

``` 

##### Программа №2.

На рисунке 3 предоставлено задание программы номер 2.

![Вариант](pr2/2.PNG)

 Рисунок 3 - Вариант 2 
 
``` 
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
```

### Результат : все работы прекрасно работаю и прошли проверку. 
