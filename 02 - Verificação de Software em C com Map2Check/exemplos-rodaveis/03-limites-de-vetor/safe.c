// Esperado: TRUE. O índice é verificado antes da escrita.
#include <stdlib.h>

int __VERIFIER_nondet_int(void);

int main(void) {
    int n = __VERIFIER_nondet_int();
    int *v = malloc(10 * sizeof(int));
    if (v == NULL) return 1;
    if (n >= 0 && n < 10) {
        v[n] = 1;
    }
    free(v);
    return 0;
}
