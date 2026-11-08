// Esperado: TRUE. O valor é copiado antes do free e não há acesso depois dele.
#include <stdlib.h>

int __VERIFIER_nondet_int(void);

int main(void) {
    int *p = malloc(sizeof(int));
    if (p == NULL) return 1;
    *p = __VERIFIER_nondet_int();
    int valor = *p;
    free(p);
    return valor;
}
