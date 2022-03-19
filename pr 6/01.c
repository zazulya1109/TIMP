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