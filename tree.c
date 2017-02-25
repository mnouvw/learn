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

// ############### main ###############
int main(){
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

    printf("--------------------\n");

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

    printf("--------------------\n");

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