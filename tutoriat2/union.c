#include <stdio.h>

union test1 {
    int x;
    int y;
} Test1;

union test2 {
    int x;
    char y;
} Test2;

union test3 {
    int a[10];
    char y;
} Test3;

union test {
    int x;
    char y;
};

struct data {
    unsigned int zi;
    unsigned int luna;
    unsigned int an;
};

struct dataE {
    unsigned int zi : 5;
    unsigned int luna : 4;
    unsigned int an;
};

int main()
{
    /*
    
    printf("test1: %lu; test2: %lu; test3: %lu\n", sizeof(Test1), sizeof(Test2), sizeof(Test3));

    union test p;
    p.x = 65;

    printf("%d %c\n", p.x, p.y);

    */

    struct data d = {2, 11, 2020};
    struct dataE dE = {2, 11, 2020};

    printf("%lu %lu\n", sizeof(d), sizeof(dE));
    return 0;
}