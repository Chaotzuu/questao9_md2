#include <stdio.h>


// Função que calcula o MDC usando o Algoritmo de Euclides
int mdc(int a, int b) {

    printf("MDC:\n");
    while (b != 0) {
        int temp = b;
        printf("%d = %d %% %d\n", b, a, temp);
        b = a % b;
        a = temp;
    }
    printf("\n");
    return a;
}

// Verifica se dois números são coprimos
int coprimos(int a, int b) {
    return mdc(a, b) == 1;
}

// Verifica se um número é primo
int primo(int n) {
    if (n <= 1) return 0;
    for (int i = 2; i*i <= n; i++) {
        printf("%d %% %d\n", n, i);
        if (n % i == 0) return 0;
    }
    return 1;
}

// Algoritmo de Euclides Estendido para calcular o inverso modular
int inverso_modular(int a, int n, int* inv) {
    int t = 0, newt = 1;
    int resto = n, novo_resto = a;
    while (novo_resto != 0) {
        int quociente = resto / novo_resto; // Novo
        int temp = newt;
        newt = t - quociente * newt;
        t = temp;

        temp = novo_resto;
        novo_resto = resto - quociente * novo_resto;
        resto = temp;
    }

    if (resto > 1) return 0; // não há inverso
    if (t < 0) t += n;
    *inv = t;
    return 1;
}

// Função para calcular a^exp mod n usando exponenciação rápida
int exp_mod(int a, int exp, int n) {
    int res = 1;
    a = a % n;
    while (exp > 0) {
        if (exp % 2 == 1)
            res = (res * a) % n;
        a = (a * a) % n;
        exp = exp / 2;
    }
    return res;
}

// Calcula φ(n) com base nos fatores primos
int phi(int n) {
    int result = n;
    for (int i = 2; i * i <= n; i++) {
        printf("Phi %d = %d\n", i, result);
        if (n % i == 0) {
            while (n % i == 0)
                n /= i;
            result -= result / i;
        }
    }
    if (n > 1)
        result -= result / n;
    return result;
}

int main() {
    int H, G, n, x, n1;
    printf("Digite os valores de H, G, n, x e n1: ");
    scanf("%d %d %d %d %d", &H, &G, &n, &x, &n1);

    // Passo 1: Verificar se G e n são primos
    printf("Verificando se G e n sao primos:\n");
    if (!primo(G) || !primo(n)) {
        printf("G ou n nao sao primos. A divisao nao e possivel.\n");
        return 1;
    }
    printf("G e n sao primos.\n\n");

    // Passo 2: Calcular inverso de G mod n
    printf("Calculando o inverso de G em Zn:\n");
    int invG;
    if (!inverso_modular(G, n, &invG)) {
        printf("G nao tem inverso em Z%d.\n", n);
        return 1;
    }

    // Passo 3: Calcular a = H / G = H * G⁻¹ mod n
    printf("a = (%d * %d) %% %d\n",H, invG, n);
    int a = (H * invG) % n;
    printf("Valor de a: %d\n\n", a);

    // Passo 4: Verificar se a e n1 são coprimos
    printf("Verificando se a e n1 sao coprimos:\n");
    if (!coprimos(a, n1)) {
        printf("a e n1 nao sao coprimos. Operacao nao valida.\n");
        return 1;
    }

    // Passo 5: Verificar se n1 é primo
    printf("Verificando se n1 e primo:\n");
    int x1;
    if (primo(n1)) {
        printf("n1 e primo. Aplicando Pequeno Teorema de Fermat.\n");
        x1 = n1 - 1;
    } else {
        printf("n1 nao e primo. Aplicando Teorema de Euler.\n");
        x1 = phi(n1);
    }

    // Passo 8: Decompor x = x1 * q + r
    printf("\nDecompondo o expoente x:\n");
    int q = x / x1;
    int r = x % x1;
    printf("%d = %d * %d + %d\n\n", x, x1, q, r);

    // Passo 10: Calcular os valores intermediários
    printf("Calculando os valores intermediarios:\n");
    printf("%d^%d mod %d = x2\n", a, x1, n1);
    int x2 = exp_mod(a, x1, n1);
    printf("%d^%d mod %d\n",x2, q, n1);
    int x2q = exp_mod(x2, q, n1);
    printf("%d^%d mod %d\n", a, r, n1);
    int ar = exp_mod(a, r, n1);

    // Passo 11: Calcular resultado final
    printf("\nCalculando o resultado final:\n");
    printf("%d^%d mod %d^%d\n", x2, q, a, n1);
    int resultado = (x2q * ar) % n1;
    printf("Resultado final de a^x mod n1: %d\n", resultado);

    return 0;
}