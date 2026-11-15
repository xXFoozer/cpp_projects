#include <cstdio>
#include <cstring>
#include <cctype>
#include <iostream>
using namespace std;

const int MAX = 100;

struct Contato
{
    char nome[50];
    char telefone[20];
};

void removeQuebraLinha(char *texto);
void paraMinusculo(char *texto);
void carregar(Contato lista[], int &total);
void listar(Contato lista[], int total);
void buscar(Contato lista[], int total);
void inserir(Contato lista[], int &total);

int main()
{
    Contato lista[MAX];
    int total = 0;
    int opcao;

    carregar(lista, total);

    do
    {
        cout << endl;
        cout << "===== CADASTRO DE CONTATOS =====" << endl;
        cout << "1 - Listar todos" << endl;
        cout << "2 - Buscar contato" << endl;
        cout << "3 - Inserir novo contato" << endl;
        cout << "0 - Sair" << endl;
        cout << "Opcao: ";
        cin >> opcao;
        cin.ignore(); 

        if (opcao == 1)
        {
            listar(lista, total);
        }
        else if (opcao == 2)
        {
            buscar(lista, total);
        }
        else if (opcao == 3)
        {
            inserir(lista, total);
        }
        else if (opcao != 0)
        {
            cout << "Opcao invalida!" << endl;
        }

    } while (opcao != 0);

    cout << "Programa encerrado." << endl;
    return 0;
}

void removeQuebraLinha(char *texto)
{
    texto[strcspn(texto, "\n")] = '\0';
}

void paraMinusculo(char *texto)
{
    for (char *p = texto; *p != '\0'; p++)
    {
        *p = tolower((unsigned char)*p);
    }
}

void carregar(Contato lista[], int &total)
{
    FILE *arquivo = fopen("contatos.txt", "r");

    if (arquivo == NULL)
    {
        cout << "Arquivo nao encontrado. Ele sera criado ao inserir o primeiro contato." << endl;
        return;
    }

    char linha[100];

    while (total < MAX && fgets(linha, sizeof(linha), arquivo) != NULL)
    {
        removeQuebraLinha(linha);

        char *separador = strchr(linha, ';');
        if (separador == NULL)
        {
            continue; // linha fora do formato, ignora
        }

        *separador = '\0'; // separa nome e telefone

        snprintf(lista[total].nome, sizeof(lista[total].nome), "%.49s", linha);
        snprintf(lista[total].telefone, sizeof(lista[total].telefone), "%.19s", separador + 1);
        total++;
    }

    fclose(arquivo);
    cout << total << " contato(s) carregado(s)." << endl;
}

void listar(Contato lista[], int total)
{
    if (total == 0)
    {
        cout << "Nenhum contato cadastrado." << endl;
        return;
    }

    cout << endl << "--- LISTA DE CONTATOS ---" << endl;
    for (int i = 0; i < total; i++)
    {
        cout << i + 1 << ") " << lista[i].nome << " - " << lista[i].telefone << endl;
    }
}

void buscar(Contato lista[], int total)
{
    char busca[50];
    cout << "Digite o nome a buscar: ";
    cin.getline(busca, sizeof(busca));
    paraMinusculo(busca);

    int achou = 0;

    for (int i = 0; i < total; i++)
    {
        char copia[50];
        snprintf(copia, sizeof(copia), "%s", lista[i].nome);
        paraMinusculo(copia);

        if (strstr(copia, busca) != NULL)
        {
            cout << lista[i].nome << " - " << lista[i].telefone << endl;
            achou++;
        }
    }

    if (achou == 0)
    {
        cout << "Contato nao encontrado." << endl;
    }
}

void inserir(Contato lista[], int &total)
{
    if (total >= MAX)
    {
        cout << "Cadastro cheio!" << endl;
        return;
    }

    Contato novo;

    cout << "Nome: ";
    cin.getline(novo.nome, sizeof(novo.nome));

    cout << "Telefone: ";
    cin.getline(novo.telefone, sizeof(novo.telefone));

    FILE *arquivo = fopen("contatos.txt", "a");

    if (arquivo == NULL)
    {
        cout << "Nao foi possivel abrir o arquivo!" << endl;
        return;
    }

    fprintf(arquivo, "%s;%s\n", novo.nome, novo.telefone);
    fclose(arquivo);

    lista[total] = novo;
    total++;

    cout << "Contato cadastrado com sucesso!" << endl;
}