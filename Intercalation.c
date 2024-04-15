int* intercala(int* vet, int a, int m, int b) {

    int tamanho_resultado = b - a + 1;
    int* resultado = (int *)malloc(tamanho_resultado * sizeof(*vet));
    int idx = 0;

    int temp_a = a, temp_m = m + 1;

    while (temp_a <= m && temp_m <= b) {
        if (vet[temp_a] < vet[temp_m]) {
            resultado[idx] = vet[temp_a];
            temp_a++;
        } else {
            resultado[idx] = vet[temp_m];
            temp_m++;
        }
        idx++;
    }

    while (temp_a <= m) {
        resultado[idx] = vet[temp_a];
        temp_a++;
        idx++;
    }

    while (temp_m <= b) {
        resultado[idx] = vet[temp_m];
        temp_m++;
        idx++;
    }

    for (int i = 0; i < tamanho_resultado; i++) {
        vet[a + i] = resultado[i];
    }

    free(resultado);

    return vet;
}
