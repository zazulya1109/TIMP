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
