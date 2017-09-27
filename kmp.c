#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int * get_next(const char *p, int n)
{
    int *next = (int *)malloc(sizeof(int) *n);
    next[0] = -1;
    int j, k;
    for (j = 1, k = next[0]; j < n;) {

        if (k == -1 || p[j - 1] == p[k]) {
            next[j] = k + 1;
            k = next[j];
            ++j;
        } else {
            k = next[k];
        }

    }
    return next;
}

const char *kmp(const char *s, const char *p)
{
    int i,j;
    int *next = get_next(p, strlen(p));

    for (i = 0, j = 0; s[i] && p[j]; /* void */) {

        if (s[i] == p[j]) {
            i++;
            j++;
        } else {
            j = next[j];
            if (j == -1) {
                i++;
                j = 0;
            }
        }
    }

    free(next);

    if ( p[j] == 0) {

        return s + (i - j);

    }

    return 0;
}

int main()
{
    char *s1 = "hellon";
    printf("%s\n", kmp(s1, "ell"));
    return 0;
}
