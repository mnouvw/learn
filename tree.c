#include<stdlib.h>
#include<stdio.h>
#include<time.h>

typedef struct Node{
    int data;
    struct Node *left;
    struct Node *right;
} Node;


void pre_order_traversal(Node*);
void in_order_traversal(Node*);
void post_order_traversal(Node*);

Node* insertBST(Node*, int);
Node* buildBST(int*, int, int);

Node* search_BST(Node*, int);

// base
Node* makeNode(int);
void freeNode(Node *root);


// ############### order traversal ###############
void order_traversal(Node *root){
    pre_order_traversal(root);
    printf("\n");
    in_order_traversal(root);
    printf("\n");
    post_order_traversal(root);
    printf("\n");
}
void handle(Node *root){
    printf("%d ", root->data);
}
// Pre-Order Traversal
void pre_order_traversal(Node *root){
    if(root == NULL){
        return;
    }
    handle(root);
    pre_order_traversal(root->left);
    pre_order_traversal(root->right);
}

// In-Order Traversal
void in_order_traversal(Node *root){
    if(root == NULL){
        return;
    }
    in_order_traversal(root->left);
    handle(root);
    in_order_traversal(root->right);
}

// Post-Order Traversal
void post_order_traversal(Node *root){
    if(root == NULL){
        return;
    }
    post_order_traversal(root->left);
    post_order_traversal(root->right);
    handle(root);
}
// ############### order traversal ###############

// ############### Binary Search Tree ###############
Node* insertBST(Node *root, int data){
    if(root == NULL){
        return makeNode(data);
    }
    Node *p = root;
    while(p != NULL){
        if(p->data == data){
            break;
        }
        if(p->data < data){
            if(p->left == NULL){
                p->left = makeNode(data);
                break;
            }
            p = p->left;
        }else{
            if(p->right == NULL){
                p->right = makeNode(data);
                break;
            }
            p = p->right;
        }
    }
    return root;
}

Node* buildBST(int *a, int m, int n){
    Node *root = NULL;
    int i = m;
    for(; i <= n; i++){
        root = insertBST(root, a[i]);
    }
    printf("\n");
    return root;
}

Node* search_BST(Node *root, int key){
    Node *p = root;
    while(p != NULL && p->data != key){
        if(p->data < key){
            p = p->left;
        }else{
            p = p->right;
        }
    }
    return p;
}

// ############### Binary Search Tree ###############

// ############### Union-Find Set ###############
#define set_len 13
int set[set_len + 1];
int rank[set_len + 1];

void make_set(){
    int i = 0;
    for(; i < set_len; i++){
        set[i] = i;
        rank[i] = 1;
    }
}

int find_set(int p){
    if(set[p] != p){
        set[p] = find_set(set[p]);
    }
    return set[p];
}

int is_same_set(int x, int y){
    int x_p = find_set(x);
    int y_p = find_set(y);
    return x_p == y_p;
}

void union_set(int x, int y){
    int x_p = find_set(x);
    int y_p = find_set(y);

    if(is_same_set(x_p, y_p)){
        return;
    }
    if(rank[x_p] == rank[y_p]){
        set[y_p] = x_p;
        rank[x_p]++;
    }

    if(rank[x_p] > rank[y_p]){
        set[y_p] = x_p;
    } else{
        set[x_p] = y_p;
    }
}

// ############### Union-Find Set ###############

// ############### main ###############
int main(){
    printf("order traversal\n");
    // order traversal
    Node *root = makeNode(4);
    Node *l = makeNode(1);
    Node *r = makeNode(8);
    Node *lr = makeNode(0);
    Node *rl = makeNode(3);
    l->right = lr;
    r->left = rl;
    root->left = l;
    root->right = r;
    order_traversal(root);
    freeNode(root);

    printf("--------------------\nbst\n");

    // bst
    int n = 10;
    int a[n];
    int i = 0;
    srand(time(0));
    for(; i < n; i++){
        a[i] = rand() % n;
        printf("%d ", a[i]);
    }
    root = buildBST(a, 0, n - 1);
    order_traversal(root);
    Node *k = search_BST(root, a[n - 1]);
    printf("%d %d\n", a[n - 1], k->data);
    freeNode(root);

    printf("--------------------\nunion-find set\n");

    // union-find set
    make_set();
    union_set(1, 3);
    union_set(1, 5);
    union_set(3, 5);
    union_set(5, 8);
    printf("%d\n", is_same_set(8, 3));
    printf("%d\n", is_same_set(1, 7));
    printf("%d\n", is_same_set(2, 7));

    return 0;
}
// ############### main ###############

// ############### base ###############

Node* makeNode(int data){
    Node *root = (Node*)malloc(sizeof(Node));
    root->data = data;
    root->left = NULL;
    root->right = NULL;
    return root;
}

void freeNode(Node *root){
    if(root == NULL){
        return;
    }
    freeNode(root->left);
    freeNode(root->right);
    free(root);
}
// ############### base ###############