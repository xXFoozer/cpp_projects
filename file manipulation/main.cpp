#include <cstdio>
#include <iostream>
using namespace std;

int main()
{
    FILE *arquivo = fopen("pessoas.csv", "r");

    if (arquivo == NULL)
    {
        cout << "Arquivo nao encontrado !!";
        return 1;
    }

    char linha[250];

    while (fgets(linha, sizeof(linha), arquivo) != NULL)
    {
        char nome[70];
        int idade;
        if (sscanf(linha, "%70[^;]; %d", nome, &idade) == 2)
        {
            printf("\n %s tem %d anos de idade;", nome, idade);
        }
    }

    fclose(arquivo);

    return 0;
}