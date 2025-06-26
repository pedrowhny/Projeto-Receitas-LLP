#include <stdio.h>
#include <stdlib.h>
#include <windows.h> // Para definir a codificação UTF-8 no console
#include <locale.h> // Para definir a codificação UTF-8 no console
#include <string.h>

#define MAX_RECEITAS 50

// Enumeração das categorias de receita
typedef enum
{
    ENTRADA = 1,
    PRATO_PRINCIPAL,
    SOBREMESA,
    BEBIDA,
    LANCHE,
    OUTRO
} CategoriaReceita;

// Estrutura de uma receita
typedef struct
{
    char nome[100];
    char ingredientes[500];
    char instrucoes[1000];
    int tempo_preparo_minutos;
    CategoriaReceita categoria;
} Receita;

// Protótipos das funções
void exibirMenu();
void adicionarReceita(Receita receitas[], int *qtdReceitas);
void listarNomesReceitas(Receita receitas[], int qtdReceitas);
void verDetalhesReceita(Receita receitas[], int qtdReceitas);
CategoriaReceita lerCategoria();
const char *nomeCategoria(CategoriaReceita cat);
void limparBuffer();

// Função principal
int main()
{
    SetConsoleOutputCP(CP_UTF8);
    setlocale(LC_ALL, "pt.br.UTF-8");

    Receita receitas[MAX_RECEITAS];
    int qtdReceitas = 0;
    int opcao;

    do
    {
        exibirMenu();
        printf("Escolha uma opção: ");
        if (scanf("%d", &opcao) != 1) // Verifica se a entrada é um número
        {
            printf("Entrada inválida. Por favor, insira um número.\n"); // Mensagem de erro para entrada inválida
            limparBuffer();
            continue;
        }
        limparBuffer(); // Limpa o \n deixado por scanf

        switch (opcao) // Switch case para as opções do menu
        {
        case 1:
            adicionarReceita(receitas, &qtdReceitas);
            break;
        case 2:
            listarNomesReceitas(receitas, qtdReceitas);
            break;
        case 3:
            verDetalhesReceita(receitas, qtdReceitas);
            break;
        case 4:
            printf("Encerrando o programa...\n");
            break;
        default:
            printf("Opção inválida.\n");
        }
    } while (opcao != 4);

    return 0;
}

// Exibe o menu principal
void exibirMenu()
{
    printf("\n--- LIVRO DE RECEITAS DIGITAL ---\n");
    printf("1. Adicionar Nova Receita\n");
    printf("2. Listar Nomes de Todas as Receitas\n");
    printf("3. Ver Detalhes de uma Receita\n");
    printf("4. Sair\n");
}

// Adiciona uma nova receita
void adicionarReceita(Receita receitas[], int *qtdReceitas)
{
    if (*qtdReceitas >= MAX_RECEITAS) 
    {
        printf("Livro de receitas cheio! Não é possível adicionar mais receitas.\n");
        return;
    }

    Receita nova;

    printf("Digite o nome da receita: ");
    fgets(nova.nome, sizeof(nova.nome), stdin);
    nova.nome[strcspn(nova.nome, "\n")] = '\0'; // Remove \n

    printf("Digite os ingredientes (separe por vírgula ou nova linha):\n");
    fgets(nova.ingredientes, sizeof(nova.ingredientes), stdin);
    nova.ingredientes[strcspn(nova.ingredientes, "\n")] = '\0';

    printf("Digite as instruções de preparo:\n");
    fgets(nova.instrucoes, sizeof(nova.instrucoes), stdin);
    nova.instrucoes[strcspn(nova.instrucoes, "\n")] = '\0';

    printf("Digite o tempo de preparo (em minutos): ");
    scanf("%d", &nova.tempo_preparo_minutos);
    limparBuffer();

    nova.categoria = lerCategoria();

    receitas[*qtdReceitas] = nova;
    (*qtdReceitas)++;

    printf("Receita adicionada com sucesso!\n");
}

// Lista os nomes de todas as receitas
void listarNomesReceitas(Receita receitas[], int qtdReceitas)
{
    if (qtdReceitas == 0)
    {
        printf("Nenhuma receita cadastrada.\n");
        return;
    }

    printf("\n--- LISTA DE RECEITAS ---\n");
    for (int i = 0; i < qtdReceitas; i++)
    {
        printf("%d. %s\n", i + 1, receitas[i].nome);
    }
}

// Mostra os detalhes de uma receita
void verDetalhesReceita(Receita receitas[], int qtdReceitas)
{
    if (qtdReceitas == 0)
    {
        printf("Nenhuma receita cadastrada.\n");
        return;
    }

    printf("Você quer buscar por:\n1. Número\n2. Nome\nEscolha: ");
    int escolha;
    scanf("%d", &escolha);
    limparBuffer();

    if (escolha == 1)
    {
        int numero;
        printf("Digite o número da receita: ");
        scanf("%d", &numero);
        limparBuffer();

        if (numero < 1 || numero > qtdReceitas)
        {
            printf("Número inválido!\n");
            return;
        }

        Receita r = receitas[numero - 1];
        printf("\n--- DETALHES DA RECEITA ---\n");
        printf("Nome: %s\n", r.nome);
        printf("Ingredientes: %s\n", r.ingredientes);
        printf("Instruções: %s\n", r.instrucoes);
        printf("Tempo de preparo: %d minutos\n", r.tempo_preparo_minutos);
        printf("Categoria: %s\n", nomeCategoria(r.categoria));
    }
    else if (escolha == 2)
    {
        char nomeBusca[100];
        printf("Digite o nome da receita: ");
        fgets(nomeBusca, sizeof(nomeBusca), stdin);
        nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

        int encontrado = 0;
        for (int i = 0; i < qtdReceitas; i++)
        {
            if (strcmp(receitas[i].nome, nomeBusca) == 0)
            {
                Receita r = receitas[i];
                printf("\n--- DETALHES DA RECEITA ---\n");
                printf("Nome: %s\n", r.nome);
                printf("Ingredientes: %s\n", r.ingredientes);
                printf("Instruções: %s\n", r.instrucoes);
                printf("Tempo de preparo: %d minutos\n", r.tempo_preparo_minutos);
                printf("Categoria: %s\n", nomeCategoria(r.categoria));
                encontrado = 1;
                break;
            }
        }

        if (!encontrado)
        {
            printf("Receita não encontrada.\n");
        }
    }
    else
    {
        printf("Opção inválida.\n");
    }
}

// Lê a categoria escolhida pelo usuário
CategoriaReceita lerCategoria()
{
    printf("Categorias:\n");
    printf("1. Entrada\n");
    printf("2. Prato Principal\n");
    printf("3. Sobremesa\n");
    printf("4. Bebida\n");
    printf("5. Lanche\n");
    printf("6. Outro\n");
    int cat;
    do
    {
        printf("Escolha a categoria (1 a 6): ");
        scanf("%d", &cat);
        limparBuffer();
    } while (cat < 1 || cat > 6);
    return (CategoriaReceita)cat;
}

// Retorna o nome da categoria como string
const char *nomeCategoria(CategoriaReceita cat)
{
    switch (cat)
    {
    case ENTRADA:
        return "Entrada";
    case PRATO_PRINCIPAL:
        return "Prato Principal";
    case SOBREMESA:
        return "Sobremesa";
    case BEBIDA:
        return "Bebida";
    case LANCHE:
        return "Lanche";
    case OUTRO:
        return "Outro";
    default:
        return "Desconhecida";
    }
}

// Limpa o buffer do teclado
void limparBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}
