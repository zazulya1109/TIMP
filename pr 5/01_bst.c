#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

// Структура для хранения узла дерева.
// Необходимо хранить ссылки на потомков, предка и некоторое значение
typedef struct node {       // элемент дерева
    int root;               
    struct node* left;
    struct node* right;
    struct node* parent;
}node;

// Структура для хранения дерева.
// Хранит ссылку на корень дерева и количество элементов в дереве
typedef struct tree {       
    struct node* head;      // главный узел дерева
}tree;

// инициализация дерева
void init(tree* t) {        
    t->head = NULL;
}

void clean_node(node* n) {      //рекурсивная очиста ветки
    if (n->left != NULL)
        clean_node(n->left);    // очистка левой части ветки
    if (n->right != NULL)
        clean_node(n->right);   // очистка правой части ветки
    free(n);                    // удаление узла узла
}

// Удалить все элементы из дерева
void clean(tree* t) {          
    if (t->head == NULL)
        return;
    clean_node(t->head);
    t->head = NULL;
}

// Поиск элемента по значению. Вернуть NULL если элемент не найден
node* find(tree* t, int value) {        
    node* tmp = t->head;                // промежуточный элемент
    while (tmp != NULL) {
        if (tmp->root == value)
            break;
        else if (tmp->root < value)
            tmp = tmp->right;
        else 
            tmp = tmp->left;
    }
    return tmp;
}

// Вставка значения в дерево:
// 0 - вставка выполнена успешно
// 1 - элемент существует
// 2 - не удалось выделить память для нового элемента
int insert(tree* t, int value) {                
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

// Удалить минимальный элемент из поддерева, корнем которого является n
// Вернуть значение удаленного элемента
int remove_min(node* n) {      
    node* tmp = n;
    int min_num;

    while(tmp->left != NULL)    // нахождение мин элемента
        tmp = tmp->left;
    tmp->parent->left = tmp->right;

    if (tmp->right != NULL)
        tmp->right->parent = tmp->parent;

    min_num = tmp->root;
    free(tmp);
    return min_num;
}

// Удалить элемент из дерева:
// 0 - удаление прошло успешно
// 1 - нет элемента с указанным значением
int remove_node (tree* t, int value) {      
    node* tmp = find(t, value);
    if (tmp == NULL)            // если дерево пустое
        return 1;

    if (tmp->left == NULL) {            
        if (tmp->right == NULL) {       // если нет потомков
            if (tmp->parent == NULL)
                t->head = NULL;
            else {
                if (tmp->root > tmp->parent->root)
                    tmp->parent->right = NULL;
                else 
                    tmp->parent->left = NULL;
            }
            free(tmp);
            return 0;
        }
        else {                          // с правым потомком
            if (tmp->parent == NULL)
                t->head = tmp->right;
            else {
                if (tmp->right->root > tmp->parent->root)
                    tmp->parent->right = tmp->right;
                else 
                    tmp->parent->left = tmp->right;
            }
            tmp->right->parent = tmp->parent;
            free(tmp);
            return 0;
        }
    }

    else {
        if (tmp->right == NULL) {       // с левым потомком
            if (tmp->parent == NULL)
                t->head = tmp->left;
            else {
                if (tmp->left->root > tmp->parent->root)
                    tmp->parent->right = tmp->left;
                else 
                    tmp->parent->left = tmp->left;
            }
            tmp->left->parent = tmp->parent;
            free(tmp);
            return 0;
        }
        else {                          // с 2 потомками
            node* min = tmp->right;
            while (min->left != NULL)   //находим минимальный справа
                min = min->left;

            int num = min->root;
            remove_node(t, num);        // удаляем его
            tmp->root = num;            //заменяем значения изначально найденного
            return 0;                   // значения на удаленный мин.
        }
    }
}


void print_vacum(int level) {       // вывод пустых мест в дереве
    int pow_num = 1;
    for (int i = 0; i < (1 << (level-1)); i++)
        printf("_ ");
}

bool print_layer(node* n, int level) {  // вывод целого уровня
    bool next_level = false;
    
    if (level == 0)
    {
        printf("%d ", n->root);
        if (!next_level && (n->right != NULL || n->left != NULL))
            next_level = true;
    }
    else if (level > 0)
    {
        if (n->left != NULL)
            next_level += print_layer(n->left, level - 1);
        else
            print_vacum(level);
        if (n->right != NULL)
            next_level += print_layer(n->right, level - 1);
        else
            print_vacum(level);
        
    }
    

    return next_level;
};

// Вывести все значения из поддерева, корнем которого является n
// по уровням начиная с корня.
// Каждый уровень выводится на своей строке. 
// Элементы в строке разделяются пробелом. Если элемента нет, заменить на _. 
// Если дерево пусто, вывести -
void print(node* n) {           // вывод ветки
    bool next_level = true;
    int level = 0;

    if (n == NULL)
    {
        printf("-\n\n");
        return;
    }

    while (next_level)
    {
        next_level = print_layer(n, level);
        printf("\n");
        level++;
    }
    printf("\n");
};

void print_node(node* n) {       // вывод одного элемента

    if (n == NULL){
        printf("-\n");
        return;
    }

    if (n->parent == NULL)
        printf("_ ");
    else  
        printf("%d ", n->parent->root);

    if (n->left == NULL)
        printf("_ ");
    else  
        printf("%d ", n->left->root);

    if (n->right == NULL)
        printf("_ ");
    else  
        printf("%d ", n->right->root);

    printf("\n");
}

// Вывести все значения дерева t, аналогично функции print
void print_tree(tree* t) {      
    print(t->head);
}

// Выполнить левое вращение поддерева, корнем которого является n:
// 0 - успешно выполненная операция
// 1 - вращение невозможно
void rotate_left(tree* t) {     
    if (t->head == NULL)
        return;

    while (t->head->right != NULL){
        node* temp = t->head->right;
        t->head->right = temp->left;
        temp->left = t->head;
        t->head = temp;
    }
}

// Выполнить правое вращение поддерева, корнем которого является n:
// 0 - успешно выполненная операция
// 1 - вращение невозможно 
void rotate_right(tree* t) {    
    if (t->head == NULL)
        return;
        
    while (t->head->left != NULL) {
        node* temp = t->head->left;
        t->head->left = temp->right;
        temp->right = t->head;
        t->head = temp;
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

int main(){
    tree Tree;
    int val;

    init(&Tree);

    for (int i = 0; i < 4; i++){
        scanf("%d", &val);
        insert(&Tree, val);
    }
    print_tree(&Tree);

    for (int i = 0; i < 3; i++){
        scanf("%d", &val);
        insert(&Tree, val);
    }
    print_tree(&Tree);

    for (int i = 0; i < 2; i++){
        scanf("%d", &val);
        print_node(find(&Tree, val));
        printf("\n");
    }

    scanf("%d", &val);
    remove_node(&Tree, val);
    print_tree(&Tree);

    rotate_left(&Tree);
    print_tree(&Tree);
    scanf("%d", &val);

    rotate_right(&Tree);
    print_tree(&Tree);
    scanf("%d", &val);

    printf("%d\n\n", calculat(Tree.head));
    clean(&Tree);

    print_tree(&Tree);

    return 0;
}