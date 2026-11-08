// Esperado: TRUE. Com a e b em [0, 1000], a soma nunca estoura.

int __VERIFIER_nondet_int(void);

int main(void) {
    int a = __VERIFIER_nondet_int();
    int b = __VERIFIER_nondet_int();
    if (a < 0 || a > 1000 || b < 0 || b > 1000) return 0;
    int soma = a + b;
    return soma == 0;
}
