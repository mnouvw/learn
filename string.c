#include<stdio.h>

int stoi(char*);
double stod(char*);

int naiveMatch(char*, char*);
int kmp(char*, char*);

// base
int strlength(char*);
void printString(char*, int, int);


// 字符串转整数
int stoi(char *s){
    if(s == NULL){
        return 0;
    }
    int r = 0;
    int b = 1;
    if(*s == '-'){
        b = -1;
        s++;
    }
    if(*s == '+') {
        s++;
    }
    while(*s != '\0'){
        r = r*10 + (*s - '0');
        s++;
    }
    return r * b;
}

// 字符串转浮点数
double stod(char *s){
    if(s == NULL){
        return 0;
    }
    double r = 0.0;
    double b = 1;
    if(*s == '-'){
        b = -1.0;
        s++;
    }
    if(*s == '+') {
        s++;
    }
    while(*s != '\0' && *s != '.'){
        r = r*10 + (*s - '0');
        s++;
    } if(*s == '.'){
        s++;
        double p = 0.1;
        while(*s != '\0'){
            r = r + p * (*s - '0');
            s++;
            p *= 0.1;
        }
    }
    return r * b;
}

// ############### string match ###############

int match(char *t, char *p){
    //int i = naiveMatch(t, p);
    int i = kmp(t, p);
    return i;
}

// naive string match
int naiveMatch(char *t, char *p){
    int t_len = strlength(t);
    int p_len = strlength(p);
    int i = 0;
    for(; i < t_len - p_len; i++){
        int j = 0;
        for(; j < p_len && *(t+i+j) == *(p+j); j++);
        if(j == p_len){
            return i;
        }
    }
    return -1;
}

// kmp Kunth-Morris-Pratt
int prefix_function(char *s, int m, int n){
    int max = 0;
    int i = 1;
    for(;i <= (n - m + 1) / 2; ){
        int j = 0;
        for(; j <= i && *(s + m + j) == *(s + n - i + 1 + j); j++);
        if(j== i && j > max){
            max = j;
        }
        i++;
    }
    return max;
}

int kmp(char *t, char *p){
    int t_len = strlength(t);
    int p_len = strlength(p);
    int i = 0;
    int pi[p_len];
    for(; i < p_len; i++){
        pi[i] = prefix_function(p, 0, i);
    }

    i = 0;
    for(; i < t_len - p_len;){
        int j = 0;
        for(; j < p_len && *(t+i+j) == *(p+j); j++);
        if(j == p_len){
            return i;
        }
        if(j > 0){
            j--;
            int step = j - pi[j] ;
            i += step;
        }else{
            i++;
        }
    }
    return -1;
}

// ############### string match ###############

// longest palindromic substring
// 返回以 p 位置为中心最长回文字符串的半长度
int palindromic_length(char *s, int p){
    int len = strlength(s);
    int i = 1;
    for(; p - i >= 0 && i + p < len && *(s + p - i) == *(s + p + i); i++);
    return i - 1;
}
void lps(char *str, char *result){
    int len = strlength(str);
    int i = 0;
    int max_i = 0;
    int max_len = 0;
    for(; i < len; i++){
        int p_len = palindromic_length(str, i);
        if(p_len > max_len){
            max_len = p_len;
            max_i = i;
        }
    }
    for(i = 0; i < 2 * max_len + 1; i++){
        result[i] = str[max_i - max_len + i];
    }
    result[i] = '\0';
}


int main(){
    char *s = "-1234.1452";
    double a = stod(s);
    printf("%f\n", 2 * a);

    char *t = "bbc abcdab abcdabcdabde";
    char *p = "abcdabd";
    int i = match(t, p);
    printf("%d\n", i);
    printString(t, i, strlength(p));


    char *pali = "abcdcbcbcba";
    char result[strlength(pali)];
    lps(pali, result);
    printf("%s\n", result);
    return 0;
}

int strlength(char *str){
    int i = 0;
    while(*(str + i++) != '\0');
    return i - 1;
}

void printString(char *s, int index, int len){
    int i = index;
    for(; i < index + len && *(s + i) != '\0'; i++){
        printf("%c", *(s+i));
    }
    printf("\n");
}