# Практическая работа №8

#### Введение: необходимо реализовать алгоритмы сортировок на языке C. 
#### Задание:
##### Написать программу, реализующую следующие алгоритмы сортировки:
- Сортировка «Расческа»
- Сортировка Шелла 
1. Программа принимает на вход количество элементов и на отдельной строке массив элементов.
2. Вывести в stdout отсортированный по возрастанию массив.
3. Записать в файл combsort.log порядок преобразования массива алгоритмом сортировки «Расческа».
4. Записать в файл shellfile.log порядок преобразования массива алгоритмом cортировки Шелла.
### Ход работы
#### Таблица 1
                    
Программа  | Название на gitlabe
--- | -------------
Алгоритм сортировки "Расческа" и Шелла|  01.c
#### Код программы: 
```
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

void Write(FILE* file, int* array, int size) 
{
    for (int i = 0; i < size; i++)
        fprintf(file, "%d ", array[i]);
    fprintf(file, "\n");
}

int combSort( int* a , int sizeArray, FILE* file)
{
    for ( int i = 0; i < sizeArray; i++) 
    {
        for ( int j = 0; j < i + 1; j++) 
        {
            int elementRight = (sizeArray - 1) - (i - j);
            if (a[j] > a[elementRight]) 
            {
                int tmp = a[j];
                a[j] = a[elementRight];
                a[elementRight] = tmp;
                Write(file, a, sizeArray);
            }
        }
    }
}

int shellSort ( int* a, int size, FILE* file)
{
	int step, i, j, tmp, count = 0;	
	for (step = size / 2; step > 0; step /= 2)
		for (i = step; i < size; i++) 
        {
			for (j = i - step; j >= 0 && a[j] > a[j + step]; j -= step)
			{
				tmp = a[j];
				a[j] = a[j + step];
				a[j + step] = tmp;
			}
            Write(file, a, size);
        }
}

int main() 
{
    int num;
    int* array1; 
    int* array2;
    FILE* shell = fopen("./shellfile.log", "w");
    FILE* comb = fopen("./combsort.log", "w");

    scanf("%d", &num);
    array1 = (int*)malloc(num * sizeof(int));
    array2 = (int*)malloc(num * sizeof(int));

    for (int i = 0; i < num; i++) 
    {
        int tmp;
        scanf("%d", &tmp);
        array1[i] = tmp;
        array2[i] = tmp;
    }

    combSort(array1, num, comb);
    shellSort(array2, num, shell);

    for (int i = 0; i < num; i++)
        printf("%d ", array1[i]);
    printf("\n");
}

```

### Заключение 
В ходе выполнение практической работы были изучена сортировка «Расческа» и сортировка Шелла
