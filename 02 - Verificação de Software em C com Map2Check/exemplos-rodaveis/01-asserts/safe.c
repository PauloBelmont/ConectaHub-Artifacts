// Esperado: TRUE. Com x limitado a [0, 1000], y é sempre par e não há overflow.
#include <assert.h>

int __VERIFIER_nondet_int(void);

int main(void) {
    int x = __VERIFIER_nondet_int();
    if (x < 0 || x > 1000) return 0;
    int y = x * 2;
    assert(y % 2 == 0);
    return 0;
}
