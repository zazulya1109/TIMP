#pragma once

#include <stdlib.h>
#include "tree.h"

typedef struct node_l{
    struct node_l* next;
    node* data;
}node_l;

typedef struct List {
    node_l* head;
    int count;
}List;

void init_list(List* l) {
    l->count = 0;
    l->head = 0;
}

void clear_list(List* l) {
    node_l* tmp = l->head;
    node_l* tm;
    
    while(tmp != NULL) {
        tm = tmp;
        tmp = tmp->next;
        free(tm);
    }
    free(tmp);

    l->head = NULL;
    l->count = 0;
}

void app_front(List* l, node* n) {
    node_l* new_n = malloc(sizeof(node_l));
    new_n->data = n;
    new_n->next = l->head;
    l->head = new_n;
    l->count++;
}

void app_back(List* l, node* n) {
    node_l* new_n = malloc(sizeof(node_l));
    new_n->data = n;
    new_n->next = NULL;

    if (l->count == 0) {
        l->count++;
        l->head = new_n;
        return;
    }
    
    node_l* tmp = l->head;  
    while(tmp->next != NULL) 
        tmp = tmp->next;
    tmp->next = new_n;
    l->count++;
}

node* get_front(List* l) {
    if (l->count == 0)
        return NULL;
    return l->head->data;
}

node* get_back(List* l) {
    if (l->count == 0)
        return NULL;
    node_l* tmp = l->head;
    while(tmp->next != NULL)
        tmp = tmp->next;
    return tmp->data;
}

node* del_front(List* l) {
    if (l->count == 0)
        return NULL;
    
    node_l* tmp;
    node* n;
    if (l->count > 1) 
        tmp = l->head->next;
        
    else 
        tmp = NULL;

    n = l->head->data;
    free(l->head);
    l->count--;
    l->head = tmp;

    return n;
}

void coppy(List* to_list, List* from_list) {
    clear_list(to_list);
    node_l* tmp = from_list->head;

    while(tmp != NULL){
        app_back(to_list, tmp->data);
        tmp = tmp->next;
    }
    clear_list(from_list);
}

int del_back(List* l) {
    if (l->count == 0)
        return 0;
    
    node_l* tmp;
    if (l->count == 1) {
        int val = l->head->data->root;
        free(l->head);
        l->count--;
        l->head = NULL;
        return val;
    }
    else {
        while (tmp->next->next != NULL)
            tmp = tmp->next;
        int val = tmp->next->data->root;
        free(tmp->next);
        l->count--;
        tmp->next = NULL;
        return val;
    }
         
}