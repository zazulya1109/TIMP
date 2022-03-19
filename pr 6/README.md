# Практическая работа №6

#### Введение: необходимо реализовать обход бинарных деревьев на языке C. 
#### Задание:
##### Реализовать обход дерева в ширину:
1. считать с входного потока 7 чисел и занести их в дерево;
2. вывести все значения вершин дерева через пробел в порядке их посещения.
##### Реализовать прямой обход дерева:
1. считать с входного потока 7 чисел и занести их в дерево;
2. вывести все значения вершин дерева через пробел в порядке их посещения.
##### Реализовать обратный обход дерева:
1. считать с входного потока 7 чисел и занести их в дерево;
2. вывести все значения вершин дерева через пробел в порядке их посещения.
### Ход работы
#### Таблица 1
                    
Программа  | Название на gitlabe
--- | -------------
Обход дерева в ширину  |  01.c
Прямой обход дерева  |  02.c
Обратный обход дерева |  03.c


##### Код программы обхода дерева в ширину: 
```C
#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "list.h"

void print(Tree* t) {
    if (t->head == NULL){
        printf("-\n");
        return;
    }

    List l1, l2;
    init_list(&l1);
    init_list(&l2);

    bool have_child = false;

    node* temp_node = t->head;
    app_back(&l2, temp_node);

    do {
        coppy(&l1, &l2);
        have_child = false;

        while(l1.head != NULL) {
            
            temp_node = del_front(&l1);
            if (temp_node == NULL)
                continue;
        
            if (temp_node->left != NULL) {
                app_back(&l2, temp_node->left);
                have_child = true;
            }
            if (temp_node->right != NULL) {
                app_back(&l2, temp_node->right);
                have_child = true;
            }
            printf("%d ", temp_node->root);
        } 
    } while (have_child);
    printf("\n");
}

int main(){
    int tmp;

    Tree tree;
    init_tree(&tree);

    for (int i = 0; i < 7; i++) {
        scanf("%d", &tmp);
        insert(&tree, tmp);
    }

    print(&tree);

    return 0;
}

```


##### Код программы прямого обхода дерева:
```C
#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "list.h"

void print(Tree* t) {
    node* root = t->head;
    List list;
    init_list(&list);

    while (list.count != 0 || root != NULL) {
        if (root != NULL) {
            printf("%d ", root->root);
            if (root->right) 
                app_front(&list, root->right);
            
            root = root->left;
        }
        else {
            root = del_front(&list);
        }
    } 
    printf("\n");
}

int main(){
    int tmp;

    Tree tree;
    init_tree(&tree);

    for (int i = 0; i < 7; i++) {
        scanf("%d", &tmp);
        insert(&tree, tmp);
    }

    print(&tree);

    return 0;
}
```

##### Код программы обратного обхода дерева 
```C
#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

void print(node* n) {
    if (n->left != NULL)
        print(n->left);
    if (n->right != NULL) 
        print(n->right);
    printf("%d ", n->root);
}

int main(){
    int tmp;

    Tree tree;
    init_tree(&tree);

    for (int i = 0; i < 7; i++) {
        scanf("%d", &tmp);
        insert(&tree, tmp);
    }

    print(tree.head);
    printf("\n");

    return 0;
}
```

### Заключение : программы прекрасно работают и прошли проверки. 
