/*Desenvolva um programa que carrega uma lista de palavras de um arquivo texto, uma palavra por linha
e indique todas as palavras que são palíndromos, depois gere um novo arquivo só com os palindromos*/

#include <cstdio>
#include <cstring>
#include <cctype>
#include <iostream>
using namespace std;

bool ehPalindromo(char *inicio, char *fim);

int main()
{
    FILE *arquivo = fopen("palavras2.txt", "r");

    if (arquivo == NULL)
    {
        cout << "Arquivo nao encontrado !!";
        return 1;
    }

    FILE *saida = fopen("palindromos.txt", "w");

    if (saida == NULL)
    {
        cout << "Nao foi possivel criar o arquivo de saida !!";
        fclose(arquivo);
        return 1;
    }

    char linha[250];
    int total = 0;
    int encontrados = 0;

    while (fgets(linha, sizeof(linha), arquivo) != NULL)
    {
        int tam = strlen(linha);
        tam --;
        total++;

        char *inicio = linha;
        char *fim = linha;
        fim += tam -2;
   
        cout << "INICIO ->" << inicio << endl;

        if (ehPalindromo(inicio, fim))
        {
            cout << linha << " -> E palindromo" << endl;
            fprintf(saida, "%s\n", linha);
            encontrados++;
        }
        cout<< "FINAL ->" << fim << endl;
    }

    cout << endl;
    cout << "Palavras lidas: " << total << endl;
    cout << "Palindromos encontrados: " << encontrados << endl;
    cout << "Arquivo gerado: palindromos.txt" << endl;

    fclose(arquivo);
    fclose(saida);

    return 0;
}

bool ehPalindromo(char *inicio, char *fim)
{
    if (inicio >= fim)
    {
        return true;
    }

    if (tolower((unsigned char)*inicio) != tolower((unsigned char)*fim))
    {
        return false;
    }

    return ehPalindromo(inicio + 1, fim - 1);
}