#include<stdio.h>
#include<stdlib.h>
#include<math.h>
// sort
void insertionSort(int*, int, int);
void bubbleSort(int*, int, int);
void mergeSort(int*, int, int);
void selectionSort(int*, int, int);
void quickSort(int*, int, int);
void heapSort(int*, int, int);

// select

int randomized_select(int*, int, int, int);

// base
void swap(int*, int*);
void printarray(int*, int);

//############### Sort ###############
void sort(int *a, int m, int n){
    heapSort(a, m, n);
    //quickSort(a, m, n);
    //mergeSort(a, m, n);
    //bubbleSort(a, m, n);
}

// Insertion Srot
void insertionSort_before(int *a, int m, int k){
    int t = a[k];
    int i = k - 1;
    for(; i >= m && a[i] > t; i--){
        a[i + 1] = a[i];
    }
    a[i + 1] = t;
}
void insertionSort(int *a, int m, int n){
    int i = m + 1;
    for(; i <= n; i++){
        insertionSort_before(a, m, i);
    }
}

// Bubble Sort
void bubbleSort_before(int *a, int m, int k){
    int i = m;
    for(; i < k; i++){
        if(a[i] > a[i+1]){
            swap(a + i, a + i + 1);
        }
    }
}
void bubbleSort(int *a, int m, int n) {
    int i = n;
    for(; i > m; i--){
        bubbleSort_before(a, m, i);
    }
}

// Selection Sort
void selectionSort_before(int *a, int m, int n, int i){
    int min = i;
    int j = i + 1;
    for(; j <= n; j++){
        if(a[j] < a[min]){
            min = j;
        }
    }
    swap(a + min, a + i);
}
void selectionSort(int *a, int m, int n){
    int i = m;
    for(; i <= n - 1; i++){
        selectionSort_before(a, m, n, i);
    }
}

// Merge Sort
void mergeSort_recursive(int *a, int *reg, int m, int n){
    //base sort
    if(m >= n){
        return ;
    }
    int middle = (m + n)/2;
    int start1 = m, end1 = middle;
    int start2 = middle + 1, end2 = n;
    mergeSort_recursive(a, reg, start1, end1);
    mergeSort_recursive(a, reg, start2, end2);
    int k = m;
    while(start1 <= end1 && start2 <= end2){
        reg[k++] = a[start1] <= a[start2] ? a[start1++] : a[start2++];
    }
    while(start1 <= end1){
        reg[k++] = a[start1++];
    }
    while(start2 <= end2){
        reg[k++] = a[start2++];
    }
    for(k = m; k <= n; k++){
        a[k] = reg[k];
    }
}
void mergeSort(int *a, int m, int n){
    int *reg = (int*)malloc(sizeof(int) * (n-m+1));
    mergeSort_recursive(a, reg, m, n);
    free(reg);
}

// Quick Sort
int pivot(int *a, int m, int n){
    return (rand() % (n - m + 1)) + m;
}
int patition(int *a, int m, int n){
    int p = pivot(a, m, n);
    int pivotvalue = a[p];
    swap(a + p, a + n);
    int stroeindex = m;
    int i = m;
    for(; i <= n - 1; i++){
        if(a[i] < pivotvalue){
            swap(a + stroeindex++, a + i);
        }
    }
    swap(a + stroeindex, a + n);
    return stroeindex;
}
void quickSort(int *a, int m, int n){
    if(m >= n){
        return;
    }
    int p = patition(a, m, n);
    quickSort(a, m, p - 1);
    quickSort(a, p + 1, n);
}

// Heap Sort
// 若 a[k] < a[p] (k >= m and p <= n), 则交换 a[k] a[p] 的值
// 返回值为是否调整，无调整：0, 调整：1
int first_lt_second(int *a, int m, int n, int k, int p){
    if(k < m || p > n){
        return 0;
    }
    if(a[k] < a[p]){
        swap(a + k, a + p);
        return 1;
    }
    return 0;
}
void max_heapify(int *a, int m, int n, int start){
    int len = n - m;
    int i = start - m;
    while(i < len){
        int left_child = 2 * i + 1;
        int right_child = 2 * i + 2;
        int max = a[left_child + m] > a[right_child + m] ? left_child : right_child;
        int b = first_lt_second(a, m, n, i + m, max + m);
        // 是否需要向下调整
        i = b ? max : len;
    }
}
void build_max_heap(int *a, int m, int n){
    int len = n - m;
    int i = (len - 1)/ 2;
    for(; i >= 0; i--){
        max_heapify(a,  m, n, i + m);
    }
}
void heapSort(int *a, int m, int n){
    build_max_heap(a, m, n);
    int i = n;
    for(; i > m; i--){
        swap(a + m, a + i);
        max_heapify(a, m, i - 1, 0);
    }
}
//############### Sort ###############

//############### Select ###############



// Order Statistics
// select ith in array from m to n
int randomized_select(int *a, int m, int n, int i){
    if(m == n){
        return a[m];
    }
    int k = patition(a, m, n);
    if(i + m == k){
        return a[k];
    }
    if(i + m < k){
        return randomized_select(a, m, k - 1, i);
    }
    return randomized_select(a, k + 1, n, i - k - 1);
}
//############### Select ###############

int main(){
    const int n = 11;
    int a[11] = {1,2,3,4,5,9,7,8,-1,6,0};
    sort(a, 0, n - 1);
    printarray(a, n);
    return 0;
}

void swap(int *a, int *b){
    int t = *a;
    *a = *b;
    *b = t;
}

void printarray(int *a, int len){
    int i = 0;
    for(; i < len - 1; i++){
        printf("%d ", *(a + i));
    }
    printf("%d\n", *(a + i));
}