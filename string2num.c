#include<stdio.h>

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

int main(){
    char *s = "-1234.1452";
    double a = stod(s);
    printf("%f\n", 2 * a);
    return 0;
}