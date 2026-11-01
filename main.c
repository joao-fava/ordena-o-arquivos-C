#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10

void gravar(char nome[], int v[]) {
    FILE *f = fopen(nome, "w");
    if (f == NULL) { printf("Erro ao abrir arquivo!\n"); return; }
    for (int i = 0; i < N; i++) fprintf(f, "%d\n", v[i]);
    fclose(f);
}

int ler(char nome[], int v[]) {            
    FILE *f = fopen(nome, "r");
    if (f == NULL) { printf("Crie o arquivo primeiro (opcao 1)!\n"); return 0; }
    int i = 0;
    while (i < N && fscanf(f, "%d", &v[i]) == 1) i++;
    fclose(f);
    if (i < N) { printf("Arquivo incompleto. Crie de novo (opcao 1).\n"); return 0; }
    return 1;
}

void mostrar(int v[]) {
    for (int i = 0; i < N; i++) printf("%d ", v[i]);
    printf("\n");
}

void troca(int *a, int *b) { int t = *a; *a = *b; *b = t; }

void bubble(int v[]) {                     
    for (int i = 0; i < N - 1; i++)
        for (int j = 0; j < N - 1 - i; j++)
            if (v[j] > v[j + 1]) troca(&v[j], &v[j + 1]);
}

void insertion(int v[]) {                 
    for (int i = 1; i < N; i++) {
        int atual = v[i], j = i - 1;
        while (j >= 0 && v[j] > atual) { v[j + 1] = v[j]; j--; }
        v[j + 1] = atual;
    }
}

void selection(int v[]) {                  
    for (int i = 0; i < N - 1; i++) {
        int menor = i;
        for (int j = i + 1; j < N; j++)
            if (v[j] < v[menor]) menor = j;
        troca(&v[i], &v[menor]);
    }
}

void mergeSort(int v[], int ini, int fim) { 
    if (ini >= fim) return;
    int meio = (ini + fim) / 2, temp[N], i = ini, j = meio + 1, k = 0;
    mergeSort(v, ini, meio);
    mergeSort(v, meio + 1, fim);
    while (i <= meio && j <= fim) temp[k++] = (v[i] <= v[j]) ? v[i++] : v[j++];
    while (i <= meio) temp[k++] = v[i++];
    while (j <= fim)  temp[k++] = v[j++];
    for (k = 0; k <= fim - ini; k++) v[ini + k] = temp[k];
}

void quickSort(int v[], int ini, int fim) { 
    if (ini >= fim) return;
    int pivo = v[fim], i = ini - 1;
    for (int j = ini; j < fim; j++)
        if (v[j] <= pivo) troca(&v[++i], &v[j]);
    troca(&v[i + 1], &v[fim]);
    quickSort(v, ini, i);
    quickSort(v, i + 2, fim);
}

void ordenarESalvar(int dados[]) {
    int v[N], op;
    for (int i = 0; i < N; i++) v[i] = dados[i];  
    printf("1-Bubble 2-Insertion 3-Selection 4-Merge 5-Quick: ");
    scanf("%d", &op);
    if      (op == 1) bubble(v);
    else if (op == 2) insertion(v);
    else if (op == 3) selection(v);
    else if (op == 4) mergeSort(v, 0, N - 1);
    else if (op == 5) quickSort(v, 0, N - 1);
    else { printf("Opcao invalida.\n"); return; }

    printf("Antes : "); mostrar(dados);
    printf("Depois: "); mostrar(v);
    gravar("ordenado.txt", v);
    printf("Salvo em ordenado.txt\n");
}

int main(void) {
    int dados[N], op, pos, novo;
    srand(time(NULL));

    do {
        printf("\n1-Criar arquivo  2-Mostrar  3-Ordenar  4-Alterar valor  0-Sair: ");
        if (scanf("%d", &op) != 1) break;   

        if (op == 1) {
            for (int i = 0; i < N; i++) dados[i] = rand() % 100;
            gravar("dados.txt", dados);
            printf("dados.txt criado com %d numeros.\n", N);
        }
        else if (op == 2 && ler("dados.txt", dados)) mostrar(dados);
        else if (op == 3 && ler("dados.txt", dados)) ordenarESalvar(dados);
        else if (op == 4 && ler("dados.txt", dados)) {
            mostrar(dados);
            printf("Posicao (1 a %d): ", N);
            scanf("%d", &pos);
            if (pos < 1 || pos > N) { printf("Posicao invalida.\n"); continue; }
            printf("Novo valor: ");
            scanf("%d", &novo);
            dados[pos - 1] = novo;
            gravar("dados.txt", dados);
            ordenarESalvar(dados);
        }
    } while (op != 0);

    return 0;
}