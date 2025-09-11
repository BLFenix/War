#include <stdio.h>
#include <string.h>
#include <locale.h>

// Definição da struct Territorio
typedef struct
{
    char nome[30]; // Nome do território
    char cor[10];  // Cor do exército
    int tropas;    // Quantidade de tropas
} Territorio;

int main()
{
    setlocale(LC_ALL, "Portuguese");

    // Vetor de 5 territórios
    Territorio territorios[5];

    printf("=== Cadastro de Territórios (War - Nível Novato) ===\n\n");

    // Entrada de dados dos 5 territórios
    for (int i = 0; i < 5; i++)
    {
        printf("Cadastro do territorio %d:\n", i + 1);

        printf("Digite o nome do territorio: ");
        scanf(" %[^\n]", territorios[i].nome); // lê string com espaços

        printf("Digite a cor do exercito: ");
        scanf(" %[^\n]", territorios[i].cor);

        printf("Digite a quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);

        printf("\n");
    }

    // Exibição dos dados cadastrados
    printf("=== Territorios cadastrados ===\n\n");
    for (int i = 0; i < 5; i++)
    {
        printf("Territorio %d:\n", i + 1);
        printf("  Nome: %s\n", territorios[i].nome);
        printf("  Cor do exercito: %s\n", territorios[i].cor);
        printf("  Tropas: %d\n\n", territorios[i].tropas);
    }

    return 0;
}
