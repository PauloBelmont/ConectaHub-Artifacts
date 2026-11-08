// Esperado: FALSE. O valor é lido depois do free.
#include <stdlib.h>

int __VERIFIER_nondet_int(void);

int main(void) {
    int *p = malloc(sizeof(int));
    if (p == NULL) return 1;
    *p = __VERIFIER_nondet_int();
    free(p);
    return *p;
}
