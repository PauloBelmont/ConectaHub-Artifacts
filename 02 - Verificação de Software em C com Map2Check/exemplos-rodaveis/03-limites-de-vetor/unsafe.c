// Esperado: FALSE. O índice n pode ser qualquer inteiro, inclusive fora de [0, 9].
#include <stdlib.h>

int __VERIFIER_nondet_int(void);

int main(void) {
    int n = __VERIFIER_nondet_int();
    int *v = malloc(10 * sizeof(int));
    if (v == NULL) return 1;
    v[n] = 1;
    free(v);
    return 0;
}
