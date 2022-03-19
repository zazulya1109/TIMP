#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

typedef struct Graph {   //структура графа 
	int number_of_vertices;
	int** matrix;
} Graph;

// Нахождение кратчайших путей алгоритмом Флойда-Уоршелла
void FloydWarshall(Graph* p)
{
	int inf = 10000000;
	int n = p->number_of_vertices;

	// Устанавливаем в вершины где нет путей inf
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (p->matrix[i][j] == 0 && i != j)
				p->matrix[i][j] = inf;
		}
	}

	// Собственно реализация алгоритма Флойда-Уоршелла
	for (int k = 0; k < n; k++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (p->matrix[i][k] + p->matrix[k][j] < p->matrix[i][j])
					p->matrix[i][j] = p->matrix[i][k] + p->matrix[k][j];
			}
		}
	}

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (p->matrix[i][j] == inf)
				p->matrix[i][j] = 0;

}

typedef struct node {
	int value;          // значение, которое хранит узел 
	struct node *next;  // ссылка на следующий элемент списка
} node;

typedef struct list {
	struct node *head;  // начало списка
} list;

// инициализация пустого списка
void init(list *l)
{
	l->head = NULL;
};

// удалить все элементы из списка
void clean(list *l)
{
	node *temp1, *temp2;
	temp1 = l->head;
	l->head = NULL;

	while (temp1 != NULL)
	{
		temp2 = temp1;
		temp1 = temp1->next;
		free(temp2);
	}
};

void pushBack(list* l, int val) {
	node* tmp = (node*)malloc(sizeof(node));
	tmp->next = NULL;
	tmp->value = val;


	if (l->head == NULL)
		l->head = tmp;
	else {
		node* n = l->head;
		while (n->next != NULL)
			n = n->next;
		n->next = tmp;
	}
}

int pop(list* l) {
	if (l->head == NULL)
		return 0;

	int tmp = l->head->value;
	node* n = l->head;
	l->head = n->next;
	free(n);
	return tmp;
}

int top(list* l) {
	return l->head->value;
}

int at(list* l, int v) {
	node* n = l->head;
	for (int i = 0; i < v; i++)
		n = n->next;
	return n->value;
}

void swap(list* l, int v) {
	node* n = l->head;
	for (int i = 0; i < v - 1; i++)
		n = n->next;
	node* tmp = n->next;
	n->next = l->head->next;
	l->head->next = tmp;
}

void findHamiltonianCycle(int **G, int num, list* l) {
	list queue;
	init(&queue);
	for (int i = 0; i < num; i++)
		pushBack(&queue, i);

	for (int k = 0; k < num * (num - 1); k++) {
		if (G[at(&queue, 0)][at(&queue, 1)] == 0) {
			int i = 2;
			while (G[at(&queue, 0)][at(&queue, i)] == 0 ||
				G[at(&queue, 1)][at(&queue, i + 1)] == 0)
				i++;
			swap(&queue, i);
		}
		pushBack(&queue, top(&queue));
		if (l->head != NULL && l->head->value == top(&queue))
		{
			return;
		}
		pushBack(l, pop(&queue));
	}
}

int main() {

	setlocale(LC_ALL, "Rus");

	int num_verts;
	int num_ribs;
	int tmp;

	// получаем кол-во ребер и вершин графа
	printf("Введите кол-во вершин: ");
	scanf("%d", &num_verts);
	printf("Введите кол-во ребер: ");
	scanf("%d", &num_ribs);


	if (num_ribs < 2 || num_verts < 2) {
		printf("Неккоректные значения!\n");
		return 0;
	}

	// создание графов и буфера
	Graph MatrixA;
	Graph MatrixP;
	MatrixA.matrix = (int**)malloc(num_verts * sizeof(int*));
	MatrixP.matrix = (int**)malloc(num_verts * sizeof(int*));

	MatrixA.number_of_vertices = num_verts;
	MatrixP.number_of_vertices = num_verts;

	for (int i = 0; i < num_verts; i++) {
		MatrixA.matrix[i] = (int*)malloc(num_verts * sizeof(int));
		MatrixP.matrix[i] = (int*)malloc(num_verts * sizeof(int));
		for (int j = 0; j < num_verts; j++) {
			MatrixA.matrix[i][j] = 0;
			MatrixP.matrix[i][j] = 0;
		}
	}

	//заполнение графов
	printf("\nВведите данные ребра в формате:\n");
	printf("<from> <to> <rank>\n");
	for (int i = 0; i < num_ribs; i++) {
		int from, to, rank;
		// Получаем номера вершин и их вес
		scanf("%d", &from);
		scanf("%d", &to);
		scanf("%d", &rank);
		// заполняем матрицу смежности и расстояний
		MatrixA.matrix[from][to] = rank;
		MatrixP.matrix[from][to] = rank;
	}

	// вывод матрицы расстояний
	printf("Mатрица графа:\n");
	for (int i = 0; i < num_verts; i++)
	{
		for (int j = 0; j < num_verts; j++)
			printf("%d ", MatrixA.matrix[i][j]);
		printf("\n");
	}

	FloydWarshall(&MatrixP);
	printf("\nMатрица минимальных путей:\n");
	for (int i = 0; i < num_verts; i++)
	{
		for (int j = 0; j < num_verts; j++)
			printf("%d ", MatrixP.matrix[i][j]);
		printf("\n");
	}

	printf("Введите номер вершины: ");
	scanf("%d", &tmp);
	for (int i = 0; i < num_verts; i++) {
		if (tmp == i)
			continue;
		printf("\nОт вершины #%d до #%d: ", tmp, i);
		if (MatrixP.matrix[tmp][i] == 0)
			printf("нет пути");
		else
			printf("%d", MatrixP.matrix[tmp][i]);
	}

	printf("\nНахождение контура\n\n");

	for (int i = 0; i < num_verts; i++) {
		for (int j = 0; j < num_verts; j++) {
			if (i == j)
				continue;
			if (MatrixP.matrix[i][j] == 0) {
				printf("Цикла нет\n");
				return 0;
			}
		}
	}

	list l;
	init(&l);
	findHamiltonianCycle(MatrixA.matrix, MatrixA.number_of_vertices, &l);

	int sum = 0;
	int v1, v2, first;

	v2 = pop(&l);
	first = v2;
	printf("%d", v2);

	for (int i = 1; i < num_verts; i++) {
		v1 = v2;
		v2 = pop(&l);
		printf("->%d", v2);

		sum += MatrixA.matrix[v1][v2];
	}
	printf("->%d", first);
	sum += MatrixA.matrix[v2][first];

	printf("\n%d\n", sum);

	return 0;
}