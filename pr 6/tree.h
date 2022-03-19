#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct node {       // элемент дерева
    int root;               
    struct node* left;
    struct node* right;
    struct node* parent;
}node;

typedef struct Tree {       // структура дерева
    struct node* head;      // главный узел дерева
}Tree;

void init_tree(Tree* t) {        // инициализация дерева
    t->head = NULL;
}

void clean_node(node* n) {      //рекурсивная очиста ветки
    if (n->left != NULL)
        clean_node(n->left);    // очистка левой части ветки
    if (n->right != NULL)
        clean_node(n->right);   // очистка правой части ветки
    free(n);                    // удаление узла узла
}

void clean_tree(Tree* t) {           // очистка дерева
    if (t->head == NULL)
        return;
    clean_node(t->head);
    t->head = NULL;
}

int insert(Tree* t, int value) {                // вставка элемента
    node* new = (node*)malloc(sizeof(node));    // выделение памяти
    if (new == NULL)                            // если не выделилась память
        return 2;                               // то вернуть 2
    
    new->root = value;
    new->left = NULL;
    new->right = NULL;

    if (t->head == NULL) {      // если дерево пустое
        t->head = new;
        new->parent = NULL;
        return 0;
    }

    node* tmp = t->head;

    while (true) {
        if (tmp->root == value){
            free(new);
            return 1;
        }
        else if (value > tmp->root) {
            if (tmp->right == NULL){
                new->parent = tmp;
                tmp->right = new;
                return 0;
            }
            else 
                tmp = tmp->right;
        }
        else if (value < tmp->root){
            if (tmp->left == NULL){
                new->parent = tmp;
                tmp->left = new;
                return 0;
            }
            else 
                tmp = tmp->left;
        }
    }
}
int calculat(node* n) {         // подсчет кол-во эл. в ветке
    int sum = 0;

    if (n == NULL)
        return 0;

    if (n->left != NULL)
        sum += calculat(n->left);
    if (n->right != NULL)
        sum += calculat(n->right);
    return sum + 1;
}