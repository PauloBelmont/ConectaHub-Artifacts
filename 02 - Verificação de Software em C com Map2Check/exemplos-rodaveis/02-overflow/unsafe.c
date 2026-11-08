// Esperado: FALSE. Com a = INT_MAX e b = 1, a + b estoura o int (comportamento indefinido).

int __VERIFIER_nondet_int(void);

int main(void) {
    int a = __VERIFIER_nondet_int();
    int b = __VERIFIER_nondet_int();
    int soma = a + b;
    return soma == 0;
}
