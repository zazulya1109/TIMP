#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

void Write(FILE* file, int* array, int size)
{
	for (int i = 0; i < size; i++)
		fprintf(file, "%d ", array[i]);
	fprintf(file, "\n");
}

void quickSort(int* a, int first, int last, int size, FILE* file)
{
	if (first < last)
	{
		int left = first, right = last, middle = a[(left + right) / 2];
		do
		{
			while (a[left] < middle) left++;
			while (a[right] > middle) right--;
			if (left <= right)
			{
				int tmp = a[left];
				a[left] = a[right];
				a[right] = tmp;
				left++;
				right--;
			}
		} while (left <= right);
		Write(file, a, size);

		quickSort(a, first, right, size, file);
		quickSort(a, left, last, size, file);
	}
}

void pyramidSort(int* a, int size, FILE* file)
{
	int tmp, sh = 0, b = 0;
	while (1)
	{
		b = 0;
		for (int i = 0; i < size; ++i)
		{
			if (2 * i + 2 + sh < size)
			{
				if (a[i + sh] > a[2 * i + 1 + sh] || a[i + sh] > a[2 * i + 2 + sh])
				{
					if (a[2 * i + 1 + sh] < a[2 * i + 2 + sh])
					{
						tmp = a[i + sh];
						a[i + sh] = a[2 * i + 1 + sh];
						a[2 * i + 1 + sh] = tmp;
						b = 1;
					}
					else
					{
						if (a[2 * i + 2 + sh] < a[2 * i + 1 + sh])
						{
							tmp = a[i + sh];
							a[i + sh] = a[2 * i + 2 + sh];
							a[2 * i + 2 + sh] = tmp;
							b = 1;
						}
					}
				}
			}
			else if (2 * i + 1 + sh < size)
			{
				if (a[i + sh] > a[2 * i + 1 + sh])
				{
					tmp = a[i + sh];
					a[i + sh] = a[2 * i + 1 + sh];
					a[2 * i + 1 + sh] = tmp;
					b = 1;
				}
			}

		}
		if (!b) sh++;
		if (sh + 2 >= size) break;
		Write(file, a, size);
	}
}

int main()
{
	int num;
	int* array1;
	int* array2;
	FILE* quick = fopen("./quickfile.log", "w");
	FILE* heap = fopen("./heapsort.log", "w");

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

	quickSort(array1, 0, num - 1, num, quick);
	pyramidSort(array2, num, heap);

	for (int i = 0; i < num; i++)
		printf("%d ", array1[i]);
	printf("\n");
}