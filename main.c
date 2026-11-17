// Integrantes do grupo: Igor R Brizola - 10730402 , Calvin Z

#include <stdbool.h>
#include <stdio.h>

#define MAX 1000

// função para carregar dados das unidades do arquivo unidades.csv para o array / variavel.
int carregarUnidades(const char nomeArquivo[], int unidadeIds[], char descricoes[][50], int max);

// função para carregar os dados de consumo do arquivos leituras.txt para os arrays / variaveis
int carregarLeituras(const char nomeArquivo[], int ids[], int unidadeIds[], int meses[], int anos[],
                     float consumos[], int max);

// busca linear: percorre o array de ids e retorna o indice da leitura, ou -1 se nao achar
int buscaLinear(int ids[], int n, int idProcurado);

// busca binaria: exige ids em ordem crescente; retorna o indice da leitura, ou -1 se nao achar
int buscaBinaria(int ids[], int n, int idProcurado);

// ordenacoes por id crescente, sempre movendo todos os arrays paralelos juntos
void bubbleSortLeituraPorId(int ids[], int unidadeIds[], int meses[], int anos[], float consumos[],
                            int n);

void insertionSortLeituraPorId(int ids[], int unidadeIds[], int meses[], int anos[],
                               float consumos[], int n);

void selectionSortLeituraPorId(int ids[], int unidadeIds[], int meses[], int anos[],
                               float consumos[], int n);

void quickSortLeituraPorId(int ids[], int unidadeIds[], int meses[], int anos[], float consumos[],
                           int inicio, int fim);

void mergeSortLeituraPorId(int ids[], int unidadeIds[], int meses[], int anos[], float consumos[],
                           int inicio, int fim);

// soma o consumo de todas as leituras de uma unidade
float calcularConsumoUnidade(int unidadeIds[], float consumos[], int n, int unidadeId);

// soma o consumo das leituras entre mes/ano inicial e mes/ano final
float calcularConsumoPeriodo(int meses[], int anos[], float consumos[], int n, int mesInicial,
                             int anoInicial, int mesFinal, int anoFinal);

// retorna o id da unidade com maior consumo total; no empate, o menor id
int encontrarUnidadeMaiorConsumo(int unidadeIds[], float consumos[], int n);

void trocarItensLeitura(int ids[], int unidadeIds[], int meses[], int anos[], float consumos[],
                        int j);

int carregarUnidades(const char nomeArquivo[], int unidadeIds[], char descricoes[][50], int max) {

    int lidos = 0;

    FILE *arquivo = fopen(nomeArquivo, "r");

    if (arquivo == NULL) {
        return -1;
    }

    while (lidos < max &&
           fscanf(arquivo, "%d ;%49[^\n]", &unidadeIds[lidos], descricoes[lidos]) == 2) {
        lidos++;
    }

    fclose(arquivo);

    printf("== Unidades carregadas com sucesso! == \n");

    return lidos;
}

int carregarLeituras(const char nomeArquivo[], int ids[], int unidadeIds[], int meses[], int anos[],
                     float consumos[], int max) {

    int lidos = 0;

    FILE *arquivo = fopen(nomeArquivo, "r");

    if (arquivo == NULL) {
        return -1;
    }

    while (lidos < max && fscanf(arquivo, "%d %d %d %d %f", &ids[lidos], &unidadeIds[lidos],
                                 &meses[lidos], &anos[lidos], &consumos[lidos]) == 5) {
        lidos++;
    }
    Fsele fclose(arquivo);

    printf("== Leituras carregadas com sucesso! == \n");

    return lidos;
}

int buscaLinear(int ids[], int n, int idProcurado) {
    for (int i = 0; i < n; i++) {
        if (ids[i] == idProcurado) {
            return i;
        }
    }

    return -1;
}

int buscaBinaria(int ids[], int n, int idProcurado) {

    int esq = 0;
    int dir = n - 1;

    while (esq <= dir) {
        int meio = (esq + dir) / 2;

        if (ids[meio] == idProcurado) {
            return meio;
        } else if (ids[meio] < idProcurado) {
            esq = meio + 1;
        } else {
            dir = meio - 1;
        }
    }
    return -1;
}

void bubbleSortLeituraPorId(int ids[], int unidadeIds[], int meses[], int anos[], float consumos[],
                            int n) {

    bool ordenado = true;

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < n - i; j++) {
            if (ids[j] > ids[j + 1]) {
                trocarItensLeitura(ids, unidadeIds, meses, anos, consumos, j);
                ordenado = false;
            }
        }

        if (ordenado) {
            printf("Array já ordenado O(n)");
            return;
        }
    }

    // Usar só para validar que está ordenado.
    /*   for (int k = 0; k < n; k++) {
          printf("| %d | %d | %d | %d | %.2f | \n", ids[k], unidadeIds[k], meses[k], anos[k],
                 consumos[k]);
      }
  } */

    void trocarItensLeitura(int ids[], int unidadeIds[], int meses[], int anos[], float consumos[],
                            int j) {
        int tempId = ids[j];
        int tempUnidadesIds = unidadeIds[j];
        int tempMeses = meses[j];
        int tempAnos = anos[j];
        float tempConsumos = consumos[j];

        ids[j] = ids[j + 1];
        ids[j + 1] = tempId;

        unidadeIds[j] = unidadeIds[j + 1];
        unidadeIds[j + 1] = tempUnidadesIds;

        meses[j] = meses[j + 1];
        meses[j + 1] = tempMeses;

        anos[j] = anos[j + 1];
        anos[j + 1] = tempAnos;

        consumos[j] = consumos[j + 1];
        consumos[j + 1] = tempConsumos;
    }

    int main() {
        char arquivo_leitura[] = "leituras.txt";
        char arquivo_unidades[] = "unidades.csv";

        // dados das unidades, acessar com i
        int unidadeIdsCatalogo[MAX];
        char descricoes[MAX][50];

        // dados de consumo, acessar com j
        int ids[MAX];
        int unidadeIds[MAX];
        int meses[MAX];
        int anos[MAX];
        float consumos[MAX];

        int totalUnidades = carregarUnidades(arquivo_unidades, unidadeIdsCatalogo, descricoes, MAX);

        if (totalUnidades == -1) {
            printf("Erro ao abrir o arquivo unidades.csv.\nEncerrando o programa.\n");
            return 1;
        }

        int totalLeituras =
            carregarLeituras(arquivo_leitura, ids, unidadeIds, meses, anos, consumos, MAX);

        if (totalLeituras == -1) {
            printf("Erro ao abrir o arquivo leituras.txt.\nEncerrando o programa.\n");
            return 1;
        }

        bubbleSortLeituraPorId(ids, unidadeIds, meses, anos, consumos, 50);

        return 0;
    }