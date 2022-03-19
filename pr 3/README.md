# Практическая работа №3

#### Введение: необходимо реализовать функции для работы с односвязным списком

````C
// инициализация пустого списка
void init(list *l);

// удалить все элементы из списка
void clean(list *l);

// проверка на пустоту списка
bool is_empty(list *l);

// поиск элемента по значению. вернуть NULL если эжемент не найден
node *find(list *l, int value);

// вставка значения в конец списка, вернуть 0 если успешно
int push_back(list *l, int value);

// вставка значения в начало списка, вернуть 0 если успешно
int push_front(list *l, int value);

// вставка значения после указанного узла, вернуть 0 если успешно
int insert_after(node *n, int value);

// удалить первый элемент из списка с указанным значением, 
// вернуть 0 если успешно
int remove_node(list *l, int value);

// вывести все значения из списка в прямом порядке через пробел,
// после окончания вывода перейти на новую строку
void print(list *l);
````
Используя функции реализовать программу, которая:

* считывает количество элементов n, 0 < n <= 2147483647;
* создает пустой список, считывает n элементов a, |a| <= 2147483647 и заносит их в список;
* выводит содержимое списка, используя функцию print;
* считывает k1, k2, k3 (|k| <= 2147483647) и выводит "1", если в списке существует элемент с таким значением и "0", если нет (выводить через пробел, например "1 0 1");
* считывает m, |m| <= 2147483647 и вставляет его в конец списка;
* выводит содержимое списка, используя функцию print;
* считывает t, |t| <= 2147483647 и вставляет его в начало списка;
* выводит содержимое списка, используя функцию print;
* считывает j и x (0 < j <= 2147483647, |x| <= 2147483647) и вставляет значение x после j-ого элемента списка;
* выводит содержимое списка, используя функцию print;
* считывает z, |z| <= 2147483647 и удаляет первый элемент (при его наличии), хранящий значение z из списка;
* выводит содержимое списка, используя функцию print;
* очищает список.
### Ход работы
#### Таблица 1
                    
Программа  | Название на gitlabe
------------- | -------------
Односвязные списки  | 01_lists.c
#### Код программы: 
```
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
	int value; // значение, которое хранит узел
	struct node* next; // ссылка на следующий элемент списка
} node;

typedef struct list {
	struct node* head; // начало списка
} list;

// инициализация пустого списка
void init(list* l)
{
	l->head = NULL;
}

// удалить все элементы из списка
void clean(list* l)
{
	node* temp = l->head;
	while (temp->next != NULL)
	{
		node* temp1 = temp;
		temp = temp->next;
		free(temp1);
	}

	l->head = NULL;
}

// проверка на пустоту списка
bool is_empty(list* l)
{
	return l->head == NULL;
}

// поиск элемента по значению. вернуть NULL если эжемент не найден
node* find(list* l, int value)
{
	node* temp = l->head;

	while (temp != NULL)
	{
		if (temp->value == value)
			return temp;
		temp = temp->next;
	}

	return NULL;
}

// вставка значения в конец списка, вернуть 0 если успешно
int push_back(list* l, int value)
{
	if (l->head == NULL)
	{
		l->head = malloc(sizeof(node));
		l->head->value = value;
		l->head->next = NULL;
		return 0;
	}
	node* n = malloc(sizeof(node));
	n->value = value;

	node* temp = l->head;

	while (temp->next != NULL)
		temp = temp->next;

	temp->next = n;
	n->next = NULL;
}

// вставка значения в начало списка, вернуть 0 если успешно
int push_front(list* l, int value)
{
	node* n = malloc(sizeof(node));
	n->value = value;

	node* tmp = l->head;
	l->head = n;
	n->next = tmp;
}

// вставка значения после указанного узла, вернуть 0 если успешно
int insert_after(list* l, int value, int x)
{
node* tmp= l->head;
for (int i=1; i<x; ++i)
{
tmp = tmp ->next;
if(tmp == NULL){return 1;}
}
if(tmp -> next == NULL)
{
    node *gospod = malloc(sizeof(node));
    gospod -> value = value;
    tmp->next = gospod;
    gospod -> next = NULL;
    return 0;
}
node *gospod = malloc(sizeof(node));
gospod -> next = tmp -> next;
tmp->next = gospod;
gospod -> value = value;
return 0;

}


// удалить первый элемент из списка с указанным значением,
// вернуть 0 если успешно
int remove_node(list* l, int value)
{
node *temp1 = l -> head;
node *temp;
if(temp1 -> value == value)
{
temp = temp1;
l -> head = temp1 -> next;
temp1 = temp1 -> next;
free(temp);
return 0;
}
while(temp1 -> next -> value != value )
{
temp1 = temp1 -> next;
if(temp1 == NULL){return 1;}
}
temp = temp1 -> next;
temp1 -> next = temp -> next;
temp -> next = NULL;
free(temp);
return 0;
}

// вывести все значения из списка в прямом порядке через пробел,
// после окончания вывода перейти на новую строку
void print(list* l)
{
	node* temp = l->head;

	while (temp != NULL)
	{
		printf("%d ", temp->value);
		temp = temp->next;
	}
		printf("\n");
}

// Место для вашего кода
int main()
{
	int n, a , x , y;
	scanf("%d", &n);
	list * l = malloc(sizeof(list));
	init(l);
	for (int i = 0; i < n; ++i)
	{
		scanf("%d", &a);
		push_back(l, a);
	}
	print(l);

	scanf("%d%d%d", &a, &x, &y);
	if (find(l, a) == NULL)
	{
		printf("%d ", 0);
	}
	else
	{
		printf("%d ", 1);
	}
	if (find(l, x) == NULL)
	{
		printf("%d ", 0);
	}
	else
	{
		printf("%d ", 1);
	}
	if (find(l, y) == NULL)
	{
		printf("%d ", 0);
	}
	else
	{
		printf("%d ", 1);
	}


	scanf("%d", &a); //конец списка 
	push_back(l, a);
	print(l);

	scanf("%d", &a); //начало списка 
	push_front(l, a);
	print(l);

    
    scanf("%d%d", &x, &a); //вставка после указаного значения
    if(x >= 1)
    {
	insert_after(l, a, x);
    }
	print(l);

    int h;
	scanf("%d", &h); //удалить элемент указанного значения 
    if (find(l, h) != NULL)
	{
	remove_node(l, h);
	}
	print(l);

	return 0;
}
```

### Заключение : программа  прекрасно работает и прошла проверку. 

