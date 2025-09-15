#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Constante dos valores do sorteio de ataque
#define DADO_MAX 6

// Constantes do menu
#define MENU_EXIBIR 1
#define MENU_ATACAR 2
#define MENU_SAIR 3

// Definição da struct Territorio usando typedef
typedef struct
{
    char nome[30]; // Nome do território
    char cor[10];  // Cor do exército
    int tropas;    // Quantidade de tropas
} Territorio;

// Função para cadastrar territórios dinamicamente
Territorio *cadastrarTerritorios(int numTerritorios)
{
    Territorio *mapa = (Territorio *)calloc(numTerritorios, sizeof(Territorio));
    if (mapa == NULL)
    {
        printf("Erro ao alocar memória.\n");
        exit(1);
    }

    for (int i = 0; i < numTerritorios; i++)
    {
        printf("Cadastro do territorio %d:\n", i + 1);

        printf("Digite o nome do territorio: ");
        fgets(mapa[i].nome, sizeof(mapa[i].nome), stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0';

        printf("Digite a cor do exercito: ");
        fgets(mapa[i].cor, sizeof(mapa[i].cor), stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0';

        printf("Digite a quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
        getchar();

        printf("\n");
    }

    return mapa;
}

// Função para exibir os territórios
void exibirTerritorios(Territorio *mapa, int numTerritorios)
{
    printf("\n=== Territorios cadastrados ===\n");
    for (int i = 0; i < numTerritorios; i++)
    {
        printf("Territorio %d:\n", i + 1);
        printf("  Nome: %s\n", mapa[i].nome);
        printf("  Cor do exercito: %s\n", mapa[i].cor);
        printf("  Tropas: %d\n\n", mapa[i].tropas);
    }
}

// Função para simular ataque entre territórios
void atacar(Territorio *atacante, Territorio *defensor)
{
    int dadoAtacante = rand() % DADO_MAX + 1;
    int dadoDefensor = rand() % DADO_MAX + 1;

    printf("%s (atacante) rola %d\n", atacante->nome, dadoAtacante);
    printf("%s (defensor) rola %d\n", defensor->nome, dadoDefensor);

    if (atacante->tropas <= 0)
    {
        printf("O território %s não tem tropas suficientes para atacar!\n", atacante->nome);
        return;
    }
    else if (dadoAtacante > dadoDefensor)
    {
        printf("Atacante vence!\n");
        defensor->tropas--; // Menos 1 tropa

        if (defensor->tropas <= 0)
        {
            printf("O território %s foi dominado por %s!\nNova cor: %s\n", defensor->nome, atacante->nome, atacante->cor);
            strcpy(defensor->cor, atacante->cor); // Mudança de dono
        }
    }
    else
    {
        printf("Defensor resiste!\n");
        printf("Atacante perdeu uma tropa durante o ataque !\n");
        atacante->tropas--; // Atacante perde uma tropa
    }

    printf("Status após ataque:\n");
    printf("%s - Cor: %s, Tropas: %d\n", atacante->nome, atacante->cor, atacante->tropas);
    printf("%s - Cor: %s, Tropas: %d\n\n", defensor->nome, defensor->cor, defensor->tropas);
}

// Função para liberar memória
void liberarMemoria(Territorio *mapa)
{
    free(mapa);
}

int menu()
{
    printf("\n==============");
    printf("\n==== Menu ====");
    printf("\n==============\n");
    printf("\nO que deseja fazer no momento?\n");
    printf("\n1 - Exibir mapa");
    printf("\n2 - Realizar ataque");
    printf("\n3 - Sair\n");

    int itemMenu;
    do
    {
        printf("\nDigite sua escolha: ");
        scanf("%d", &itemMenu);
        getchar();
        if (itemMenu < 1 || itemMenu > 3)
            printf("\nOpção inválida!\n");
    } while (itemMenu < 1 || itemMenu > 3);

    return itemMenu;
}

int main()
{
    srand(time(NULL)); // Inicializa random para ataques

    printf("Bem Vindo ao jogo War!\n");

    int numTerritorios;
    printf("Quantos territorios deseja cadastrar? ");
    scanf("%d", &numTerritorios);
    getchar();

    Territorio *mapa = cadastrarTerritorios(numTerritorios);

    int itemMenu, terAtacante, terDefensor;

    do
    {
        itemMenu = menu();
        switch (itemMenu)
        {
        case MENU_EXIBIR: // Mostrar Mapa
            exibirTerritorios(mapa, numTerritorios);
            break;
        case MENU_ATACAR: // Ataque
            printf("Escolha o numero do territorio atacante: ");
            scanf("%d", &terAtacante);
            printf("Escolha o numero do territorio defensor: ");
            scanf("%d", &terDefensor);
            getchar(); // limpa buffer

            if (terAtacante < 1 || terAtacante > numTerritorios || terDefensor < 1 || terDefensor > numTerritorios)
            {
                printf("Territorios inválidos!\n");
            }
            else if (strcmp(mapa[terAtacante - 1].cor, mapa[terDefensor - 1].cor) == 0)
            {
                printf("Não é possível atacar um território da própria cor!\n");
            }
            else if ((terAtacante - 1) == (terDefensor - 1))
            {
                printf("Não é possível um território atacar a si mesmo!\n");
            }
            else
            {
                atacar(&mapa[terAtacante - 1], &mapa[terDefensor - 1]);
            }
            break;
        case MENU_SAIR: // Sair
            printf("\n===================");
            printf("\nOBRIGADO POR JOGAR!");
            printf("\n===================\n");
            printf("\nFinalizando o Jogo!");
            liberarMemoria(mapa);
            break;
        default:
            break;
        }
    } while (itemMenu != 3);
    return 0;
}