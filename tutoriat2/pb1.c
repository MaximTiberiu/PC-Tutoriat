#include <stdio.h>
#include <assert.h>
#include <stdlib.h>


int cautare_binara(int* a, int x, int st, int dr)
{
    // 1 2 3 4 5 6 7
    // x = 2

    if(st > dr) return -1;
    if(a[st] == x) return st;
    if(a[dr] == x) return dr;

    int mijloc = (st + dr) / 2;
    if(a[mijloc] == x) 
        return mijloc;
    else if(a[mijloc] < x) 
        return cautare_binara(a, x, mijloc + 1, dr);
    else
        return cautare_binara(a, x, st, mijloc - 1);
}

int main()
{
    int n, x, y;
    int* a;
    int i;

    scanf("%d %d %d", &n, &x, &y);

    a = (int*)malloc(n * sizeof(int));
    assert(a != NULL);

    for(i = 0 ; i < n ; i++)
        scanf("%d", &(a[i]));

    int pozX, pozY;
    pozX = cautare_binara(a, x, a[0], a[n - 1]);
    pozY = cautare_binara(a, y, a[0], a[n - 1]);

    if(pozX != -1 && pozY != -1)
    {
        printf("[%d, %d]\n", pozX, pozY);

        for(i = pozX ; i <= pozY ; i++)
            printf("%d ", a[i]);
        printf("\n");
    }
    else printf("O pozitie nu este in vector!\n");

    free(a);

    return 0;
}
