#include <iostream>
using namespace std;

void inverter(char *palavra);

int main()
{

    char *palavra = new char[50];
    cout << "Digite a palavra para ser Invertida: " << endl;
    cin >> palavra;

    inverter(palavra);

    cout << "Invertida: " << "\n"
         << palavra << "!" << endl;

    delete[] palavra;

    return 0;
}

void inverter(char *palavra)
{
    char *fim = palavra;
    while (*fim != '\0')
    {
        fim++;
    }
    fim--;

    char *inicio = palavra;
    char aux;

    while (inicio < fim)
    {
        aux = *inicio;
        *inicio = *fim;
        *fim = aux;
        inicio++;
        fim--;
    }

    // for (int i = 0; i < tamanho / 2; i++)
    // {
    //     char aux = palavra[i];
    //     palavra[i] = palavra[tamanho - 1 - i];
    //     palavra[tamanho - 1 - i] = aux;
    // }
}