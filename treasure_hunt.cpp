
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <limits>

using namespace std;

const int TAM = 15;

struct Posicao {
    int linha;
    int coluna;
};

void inicializarMatriz(int matriz[TAM][TAM]);
void posicionarJogadorETesouro(int matriz[TAM][TAM], Posicao &jogador, Posicao &tesouro);
void exibirMatriz(const int matriz[TAM][TAM]);
int calcularDistancia(const Posicao &a, const Posicao &b);
bool validarMovimento(const Posicao &atual, char direcao, int passos, Posicao &novaPosicao);
void executarMovimento(int matriz[TAM][TAM], Posicao &jogador, const Posicao &novaPosicao);
void fornecerDicaProximidade(int distanciaAntiga, int distanciaNova);
void lerEntradaUsuario(char &direcao, int &passos);

int main() {
    srand((unsigned int) time(nullptr));

    int matriz[TAM][TAM];
    Posicao jogador, tesouro, novaPosicao;
    int turnos = 0;

    inicializarMatriz(matriz);
    posicionarJogadorETesouro(matriz, jogador, tesouro);

    cout << "=== JOGO DE CACA AO TESOURO ===" << endl;
    cout << "Matriz " << TAM << "x" << TAM << ". Encontre o tesouro escondido!" << endl;
    cout << "Direcoes: W (cima), A (esquerda), S (baixo), D (direita)" << endl << endl;

    while (jogador.linha != tesouro.linha || jogador.coluna != tesouro.coluna) {
        exibirMatriz(matriz);

        char direcao;
        int passos;
        lerEntradaUsuario(direcao, passos);

        if (!validarMovimento(jogador, direcao, passos, novaPosicao)) {
            cout << ">> Movimento invalido! Voce sairia dos limites da matriz." << endl << endl;
            continue;
        }

        int distanciaAntiga = calcularDistancia(jogador, tesouro);

        executarMovimento(matriz, jogador, novaPosicao);
        turnos++;

        if (jogador.linha == tesouro.linha && jogador.coluna == tesouro.coluna) {
            break;
        }

        int distanciaNova = calcularDistancia(jogador, tesouro);
        fornecerDicaProximidade(distanciaAntiga, distanciaNova);
        cout << endl;
    }

    exibirMatriz(matriz);
    cout << endl << "*** PARABENS! Voce encontrou o tesouro em " << turnos << " turno(s)! ***" << endl;

    return 0;
}


void inicializarMatriz(int matriz[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            matriz[i][j] = 0;
        }
    }
}

void posicionarJogadorETesouro(int matriz[TAM][TAM], Posicao &jogador, Posicao &tesouro) {
    jogador.linha = rand() % TAM;
    jogador.coluna = rand() % TAM;

    do {
        tesouro.linha = rand() % TAM;
        tesouro.coluna = rand() % TAM;
    } while (tesouro.linha == jogador.linha && tesouro.coluna == jogador.coluna);

    matriz[jogador.linha][jogador.coluna] = 1;
}

void exibirMatriz(const int matriz[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            cout << (matriz[i][j] == 1 ? "J " : ". ");
        }
        cout << endl;
    }
    cout << endl;
}

int calcularDistancia(const Posicao &a, const Posicao &b) {
    return abs(a.linha - b.linha) + abs(a.coluna - b.coluna);
}

bool validarMovimento(const Posicao &atual, char direcao, int passos, Posicao &novaPosicao) {
    novaPosicao = atual;

    switch (toupper(direcao)) {
        case 'W': novaPosicao.linha -= passos; break; // cima
        case 'S': novaPosicao.linha += passos; break; // baixo
        case 'A': novaPosicao.coluna -= passos; break; // esquerda
        case 'D': novaPosicao.coluna += passos; break; // direita
        default:  return false; // direção inválida
    }

    if (novaPosicao.linha < 0 || novaPosicao.linha >= TAM ||
        novaPosicao.coluna < 0 || novaPosicao.coluna >= TAM) {
        return false;
    }

    return true;
}

void executarMovimento(int matriz[TAM][TAM], Posicao &jogador, const Posicao &novaPosicao) {
    matriz[jogador.linha][jogador.coluna] = 0;
    jogador = novaPosicao;
    matriz[jogador.linha][jogador.coluna] = 1;
}

void fornecerDicaProximidade(int distanciaAntiga, int distanciaNova) {
    if (distanciaNova < distanciaAntiga) {
        cout << "Voce esta mais perto do tesouro." << endl;
    } else if (distanciaNova > distanciaAntiga) {
        cout << "Voce esta mais longe do tesouro." << endl;
    } else {
        cout << "Voce esta na mesma distancia do tesouro." << endl;
    }
}

void lerEntradaUsuario(char &direcao, int &passos) {
    while (true) {
        cout << "Direcao (W/A/S/D): ";
        cin >> direcao;

        cout << "Numero de passos: ";
        cin >> passos;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << ">> Entrada invalida! Digite uma direcao e um numero inteiro." << endl << endl;
            continue;
        }

        char d = toupper(direcao);
        if ((d != 'W' && d != 'A' && d != 'S' && d != 'D') || passos <= 0) {
            cout << ">> Direcao ou numero de passos invalido! Tente novamente." << endl << endl;
            continue;
        }

        break;
    }
}