#include <iostream>
#include <string>
using namespace std;

bool ehPalindromo(char *inicio, char *fim);


int main()
{
    char *palavra = new char[50];

    cout << "Digite a palavra: " << endl;
    cin >> palavra;

    char *fim = palavra;
    while (*fim != '\0')
    {
        fim++;
    }
    fim--;

    if (ehPalindromo(palavra, fim))
    {
        cout << "A palavra E um palindromo!" << endl;
    }
    else
    {
        cout << "A palavra NAO e um palindromo." << endl;
    }
    delete[] palavra;

    return 0;
}

bool ehPalindromo(char *inicio, char *fim)
{
    if (inicio >= fim)
    {
        return true;
    }

    if (*inicio != *fim)
    {
        return false;
    }

    return ehPalindromo(inicio + 1, fim - 1);
}
