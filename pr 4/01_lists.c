#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct node {
	int value;          // значение, которое хранит узел 
	struct node *next;  // ссылка на следующий элемент списка
	struct node *prev;  // ссылка на предыдущий элемент списка
} node;

typedef struct list {
	struct node *head;  // начало списка
	struct node *tail;  // конец списка
} list;


// инициализация пустого списка
void init(list *l) {
	l->head = NULL;
	l->tail = l->head;
}

// удалить все элементы из списка
void clean(list *l) {
	node* temp = l->head;
	while (temp->next != NULL){
		node* temp1 = temp;
		temp = temp->next;
		free(temp1);
	}
	l->head = NULL;
	l->tail = NULL;
}


// проверка на пустоту списка
bool is_empty(list *l) {
	return l->head == NULL;
}

// поиск элемента по значению. вернуть NULL если элемент не найден
int find(list *l, int value) {
	node *temp = l -> head;
    while(temp != NULL) {
        if((temp -> value) == value) {
            return 1;
        }
        temp = temp -> next;
    }
    return 0;

}

// вставка значения в конец списка, вернуть 0 если успешно
int push_back(list *l, int value){
	if (l->head == NULL){
		l->head = malloc(sizeof(node));
		l->head->value = value;
		l->head->next = NULL;
		l->head->prev = NULL;
		l->tail = l->head;
		return 0;
	}
	node* n = malloc(sizeof(node));
	n->value = value;
	node* temp = l->tail;
	l->tail = n;
	temp->next = l->tail;
	l->tail->prev = temp;
	n->next = NULL;
	n->prev = temp;
	return 0;
}

// вставка значения в начало списка, вернуть 0 если успешно
int push_front(list *l, int value) {
	node* n = malloc(sizeof(node));
	n->value = value;
	node* tmp = l->head;
	l->head = n;
	n->next = tmp;
	tmp->prev = n;
	n->prev = NULL;
	return 0;
}

// вставка значения после указанного узла, вернуть 0 если успешно
int insert_after(list *l, int value, int x){
    node* tmp = l->head;
	for (int i = 1; i <=x; ++i){
		tmp = tmp->next;
		if (tmp == NULL) { return 1; }
	}
	if (tmp->next == NULL){
	    node *gospod = malloc(sizeof(node));
	    gospod -> value = value;
		gospod -> next = NULL;
        gospod -> prev = l -> tail;
        if (l->tail) {
            l->tail->next = gospod;
        }
        l->tail = gospod;
        return 0;

	}
	node *gospod = malloc(sizeof(node));
	gospod->next = tmp->next;
	tmp->next = gospod;
	gospod->next->prev = gospod;
	gospod->prev = tmp;
	gospod->value = value;
	return 0;
    
}

// вставка значения перед указанным узлом, вернуть 0 если успешно
int insert_before(list *l, int x, int value){
	if(x==2){
	    insert_after(l, value, 0);
	    return 0;
	}
	
	x = x - 1;
	node* tmp = l->head;
	for (int i = 1; i < x; ++i){
		tmp = tmp->next;
		if (tmp == NULL) { return 1; }
	}
		if (tmp->prev == NULL){
		push_front(l, value);
		return 0;
	}
	if (tmp->next == NULL){
		node *gospod = malloc(sizeof(node));
		gospod->value = value;
		tmp->next = gospod;
		gospod->next = NULL;
		return 0;
	}
	node *gospod = malloc(sizeof(node));
	gospod->next = tmp->next;
	tmp->next = gospod;
	gospod->next->prev = gospod;
	gospod->prev = tmp;
	gospod->value = value;
	return 0;
}

// удалить первый элемент из списка с указанным значением, 
// вернуть 0 если успешно
int remove_first(list *l, int value) {
	node *temp;
    node *temp1;
    node *temp2 = l -> head;

    if(temp2  -> value == value) {
        temp = temp2;
        l -> head = temp2 -> next;
        temp2 = temp2 -> next;
        temp2 -> prev = NULL;
    	free(temp);
    	return 0;   
    }
    else {
        while (temp2 -> value != value) {
            temp2 = temp2 -> next;
        }
        if(temp2 -> next == NULL)
    	{
    	    temp = temp2;
    	    temp2 = temp2 -> prev;
    	    l -> tail = temp2;
    	    temp2 -> next = NULL;
    	    free(temp);   
        	return 0;
    	}
    	else {
        	temp2 = temp2 -> prev;
            temp = temp2 -> next;
            temp1 = temp -> next;
            temp1 -> prev = temp2;
            temp2 -> next = temp1;
        	free(temp);
        	return 0;
    	}
    }

}

// удалить последний элемент из списка с указанным значением, 
// вернуть 0 если успешно
int remove_last(list *l, int value) {
    node *temp;
    node *temp1;
    node *temp2 = l -> tail;
    
    if(temp2  -> value == value) {
        temp = temp2;
        l -> tail = temp2 -> prev;
        temp2 = temp2 -> prev;
        temp2 -> next = NULL;
    	free(temp);
    	return 0;   
    }
    else {
        while(temp2 -> prev -> value !=value) {
           temp2 = temp2 -> prev;
        }
        temp = temp2 -> prev;
        if(temp -> prev ==NULL){
            l -> head = temp2;
            temp2 -> prev = NULL;
            free(temp);
    	    return 0;
        }
        else{
        temp1 = temp -> prev;
        temp1 -> next = temp2;
        temp2 -> prev = temp1;
    	free(temp);
    	return 0;
        }
    }
    
}

// вывести все значения из списка в прямом порядке через пробел,
// после окончания вывода перейти на новую строку
void print(list *l) {
	node* temp = l->head;
	while (temp != NULL){
		printf("%d ", temp->value);
		temp = temp->next;
	}
	printf("\n");
}

// вывести все значения из списка в обратном порядке через пробел,
// после окончания вывода перейти на новую строку
void print_invers(list *l){
	node* temp = l->tail;
	while (temp != NULL){
		printf("%d ", temp->value);
		temp = temp->prev;
	}
	printf("\n");
}


int main() {
	int n, a, x, y;
	scanf("%d", &n);
	list * l = malloc(sizeof(list));
	init(l);
	for (int i = 0; i < n; ++i){
		scanf("%d", &a);
		push_back(l, a);
	}
	print(l);

	scanf("%d%d%d", &a, &x, &y);
	printf("%d ", find(l, a));
    printf("%d ", find(l, x));
    printf("%d ", find(l, y));


	scanf("%d", &a);
	push_back(l, a);
	print_invers(l);

	scanf("%d", &a);
	push_front(l, a);
	print(l);

	scanf("%d%d", &x, &a); //вставка после указаного значения
	if (x >= 1){
		insert_after(l, a, x-1);
	}
	print_invers(l);

	scanf("%d%d", &x, &a);
	if (x >= 1){
	insert_before(l, x, a);}
	print(l);

	scanf("%d", &a);
    x = find(l,a);
	if(x){remove_first(l, a);}
	print_invers(l);

	scanf("%d", &a);
	x=find(l,a);
	if(x){remove_last(l, a);}
	print(l);
	return 0;
}

