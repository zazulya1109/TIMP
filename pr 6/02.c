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