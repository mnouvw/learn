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
        if(p->data > data){
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
        if(p->data > key){
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

// ############### AVL Tree ###############
#define max(x, y) x > y ? x : y

typedef struct AVLNode{
    int data;
    int height;
    struct AVLNode *left;
    struct AVLNode *right;
} AVLNode;

AVLNode* make_AVLNode(int data){
    AVLNode *node = (AVLNode*)malloc(sizeof(AVLNode));
    node->data = data;
    node->height = 1;
    node->left = NULL;
    node->right = NULL;
    return node;
}

AVLNode* ll(AVLNode *root){
    if(root == NULL || root->left == NULL){
        return root;
    }
    AVLNode *p = root->left;
    root->left = p->right;
    p->right = root;
    root->height--;
    return p;
}

AVLNode* rr(AVLNode *root){
    if(root == NULL || root->right == NULL){
        return root;
    }
    AVLNode *p = root->right;
    root->right = p->left;
    p->left = root;
    return p;
}

AVLNode* lr(AVLNode *root){
    root->left = rr(root->left);
    return ll(root);
}
AVLNode* rl(AVLNode *root){
    root->right = ll(root->right);
    return rr(root);
}

AVLNode* rotation(AVLNode *root){
    if(root == NULL || root->left == NULL || root->right == NULL){
        return root;
    }
}

int height_AVL(AVLNode *root){
    if(root == NULL){
        return 0;
    }
    return root->height;
}

AVLNode* insert_AVL(AVLNode *root, int data){
    if(root == NULL){
        return make_AVLNode(data);
    }

    if(root->data == data){
        return root;
    }
    if(data < root->data){
        root->left = insert_AVL(root->left, data);
        if(height_AVL(root->left) - height_AVL(root->right) >= 2){
            if(root->left->data < data){
                root = ll(root);
            }else{
                root = lr(root);
            }
        }
    }else{
        root->right= insert_AVL(root->right, data);
        if(height_AVL(root->right) - height_AVL(root->left) >= 2){
            if(root->right->data < data){
                root = rl(root);
            }else{
                root = rr(root);
            }
        }
    }

    root->height = max(height_AVL(root->left), height_AVL(root->right)) + 1;
    return root;
}

AVLNode* build_AVL(int *a, int m, int n){
    AVLNode *root = NULL;
    int i = m;
    for(; i <= n; i++){
        root = insert_AVL(root, a[i]);
    }
    return root;
}

void in_order_traversal_AVL(AVLNode *root){
    if(root == NULL){
        return;
    }
    in_order_traversal_AVL(root->left);
    printf("%d ", root->data);
    in_order_traversal_AVL(root->right);
}


void order_traversal_AVL(AVLNode *root){
    in_order_traversal_AVL(root);
    printf("\n");
}


// ############### AVL Tree ###############

// ############### main ###############
int main(){
    printf("\norder traversal\n---------------\n");
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

    printf("\nbst\n--------------------\n");

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

    printf("\nunion-find set\n--------------------\n");

    // union-find set
    make_set();
    union_set(1, 3);
    union_set(1, 5);
    union_set(3, 5);
    union_set(5, 8);
    printf("%d\n", is_same_set(8, 3));
    printf("%d\n", is_same_set(1, 7));
    printf("%d\n", is_same_set(2, 7));

    printf("\nAVL\n--------------------\n");

    AVLNode *avlroot = build_AVL(a, 0, n - 1);
    order_traversal_AVL(avlroot);

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