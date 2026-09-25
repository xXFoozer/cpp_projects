
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <limits>

using namespace std;

int getNumeroAleatorio(int max);

int main()
{
    srand(time(nullptr));

    int size_vector = 0;

    cout << "Digite um numero para o Vetor: " << endl;
    cin >> size_vector;

    int *vector = new int[size_vector];
    int *pointer_ref = vector;

    for (int i = 0; i < size_vector; i++)
    {
        *pointer_ref = getNumeroAleatorio(100);
        cout << "Endereco: " << pointer_ref << endl;
        cout << "Valor: " << *pointer_ref << endl;
        pointer_ref++;
    }

    delete[] vector;
    vector = nullptr;

    return 0;
}

int getNumeroAleatorio(int max)
{
    return rand() % max + 1;
}
