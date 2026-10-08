#include <iostream>
using namespace std;

void exibirVetor(int vetor[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        cout << vetor[i];
        if (i < tamanho - 1) cout << ", ";
    }
    cout << endl;
}

int main() {
    char continuar = 's';

    do {
        int tamanho;
        cout << "\nQual o tamanho do vetor? ";
        cin >> tamanho;

        int *vetor = new int[tamanho];

        cout << "Digite os " << tamanho << " elementos:" << endl;
        int pares = 0;
        for (int i = 0; i < tamanho; i++) {
            cin >> vetor[i];
            if (vetor[i] % 2 == 0) {
                pares++;
            }
        }

        int *vetorPares = new int[pares];
        int atual = 0;
        for (int i = 0; i < tamanho; i++) {
            if (vetor[i] % 2 == 0) {
                vetorPares[atual] = vetor[i];
                atual++;
            }
        }

        cout << "\nVetor original: ";
        exibirVetor(vetor, tamanho);

        cout << "Vetor de pares: ";
        if (pares > 0) {
            exibirVetor(vetorPares, pares);
        } else {
            cout << "(nenhum numero par foi digitado)" << endl;
        }

    
        delete[] vetor;
        delete[] vetorPares;
        vetor = nullptr;
        vetorPares = nullptr;

        cout << "\nDeseja repetir o processo? (s/n): ";
        cin >> continuar;

    } while (continuar == 's' || continuar == 'S');

    cout << "Programa encerrado." << endl;
    return 0;
}