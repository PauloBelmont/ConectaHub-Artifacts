// Esperado: FALSE. Para x == 5, y == 10 e o assert falha.
#include <assert.h>

int __VERIFIER_nondet_int(void);

int main(void) {
    int x = __VERIFIER_nondet_int();
    int y = x * 2;
    assert(y != 10);
    return 0;
}
