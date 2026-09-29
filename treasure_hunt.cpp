#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <cctype>
#include <limits>

using namespace std;

const int TAM_MIN = 2;
const int TAM_MAX = 50;

struct Posicao
{
    int linha;
    int coluna;
};

int lerInteiroNoIntervalo(const char *mensagem, int minimo, int maximo);
void escolherDificuldade(int &linhas, int &colunas);
int **criarMatriz(int linhas, int colunas);
void liberarMatriz(int **matriz, int linhas);
void posicionarJogadorETesouro(int **matriz, int linhas, int colunas, Posicao &jogador, Posicao &tesouro);
void exibirMatriz(int **matriz, int linhas, int colunas);
int calcularDistancia(const Posicao &a, const Posicao &b);
bool validarMovimento(const Posicao &atual, char direcao, int passos, int linhas, int colunas, Posicao &novaPosicao);
void executarMovimento(int **matriz, Posicao &jogador, const Posicao &novaPosicao);
void fornecerDicaProximidade(int distanciaAntiga, int distanciaNova);
void lerEntradaUsuario(char &direcao, int &passos);

int main()
{
    srand((unsigned int)time(nullptr));

    int linhas, colunas;
    Posicao jogador, tesouro, novaPosicao;
    int turnos = 0;

    cout << "=== JOGO DE CACA AO TESOURO ===" << endl
         << endl;
    escolherDificuldade(linhas, colunas);

    int **matriz = criarMatriz(linhas, colunas);
    posicionarJogadorETesouro(matriz, linhas, colunas, jogador, tesouro);

    cout << endl
         << "Matriz " << linhas << "x" << colunas << ". Encontre o tesouro escondido!" << endl;
    cout << "Direcoes: W (cima), A (esquerda), S (baixo), D (direita)" << endl
         << endl;

    while (jogador.linha != tesouro.linha || jogador.coluna != tesouro.coluna)
    {
        exibirMatriz(matriz, linhas, colunas);

        char direcao;
        int passos;
        lerEntradaUsuario(direcao, passos);

        if (!validarMovimento(jogador, direcao, passos, linhas, colunas, novaPosicao))
        {
            cout << ">> Movimento invalido! Voce sairia dos limites da matriz." << endl
                 << endl;
            continue;
        }

        int distanciaAntiga = calcularDistancia(jogador, tesouro);

        executarMovimento(matriz, jogador, novaPosicao);
        turnos++;

        if (jogador.linha == tesouro.linha && jogador.coluna == tesouro.coluna)
        {
            break;
        }

        int distanciaNova = calcularDistancia(jogador, tesouro);
        fornecerDicaProximidade(distanciaAntiga, distanciaNova);
        cout << endl;
    }

    exibirMatriz(matriz, linhas, colunas);
    cout << endl
         << "*** PARABENS! Voce encontrou o tesouro em " << turnos << " turno(s)! ***" << endl;

    liberarMatriz(matriz, linhas);

    cout << endl
         << "Pressione Enter para sair...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
    return 0;
}

int lerInteiroNoIntervalo(const char *mensagem, int minimo, int maximo)
{
    int valor;
    while (true)
    {
        cout << mensagem << " (" << minimo << " a " << maximo << "): ";
        cin >> valor;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << ">> Entrada invalida! Digite um numero inteiro." << endl;
            continue;
        }

        if (valor < minimo || valor > maximo)
        {
            cout << ">> Valor fora do intervalo permitido." << endl;
            continue;
        }

        return valor;
    }
}

void escolherDificuldade(int &linhas, int &colunas)
{
    cout << "Escolha o tamanho da matriz (quanto maior, mais dificil)." << endl;
    linhas = lerInteiroNoIntervalo("Numero de linhas", TAM_MIN, TAM_MAX);
    colunas = lerInteiroNoIntervalo("Numero de colunas", TAM_MIN, TAM_MAX);
}

int **criarMatriz(int linhas, int colunas)
{
    int **matriz = new int *[linhas];
    for (int i = 0; i < linhas; i++)
    {
        matriz[i] = new int[colunas];
        for (int j = 0; j < colunas; j++)
        {
            matriz[i][j] = 0;
        }
    }
    return matriz;
}

void liberarMatriz(int **matriz, int linhas)
{
    for (int i = 0; i < linhas; i++)
    {
        delete[] matriz[i];
    }
    delete[] matriz;
}

void posicionarJogadorETesouro(int **matriz, int linhas, int colunas, Posicao &jogador, Posicao &tesouro)
{
    jogador.linha = rand() % linhas;
    jogador.coluna = rand() % colunas;

    do
    {
        tesouro.linha = rand() % linhas;
        tesouro.coluna = rand() % colunas;
    } while (tesouro.linha == jogador.linha && tesouro.coluna == jogador.coluna);

    matriz[jogador.linha][jogador.coluna] = 1;
}

void exibirMatriz(int **matriz, int linhas, int colunas)
{
    for (int i = 0; i < linhas; i++)
    {
        for (int j = 0; j < colunas; j++)
        {
            cout << (matriz[i][j] == 1 ? "J " : ". ");
        }
        cout << endl;
    }
    cout << endl;
}

int calcularDistancia(const Posicao &a, const Posicao &b)
{
    return abs(a.linha - b.linha) + abs(a.coluna - b.coluna);
}

bool validarMovimento(const Posicao &atual, char direcao, int passos, int linhas, int colunas, Posicao &novaPosicao)
{
    novaPosicao = atual;

    switch (toupper(direcao))
    {
    case 'W':
        novaPosicao.linha -= passos;
        break; // cima
    case 'S':
        novaPosicao.linha += passos;
        break; // baixo
    case 'A':
        novaPosicao.coluna -= passos;
        break; // esquerda
    case 'D':
        novaPosicao.coluna += passos;
        break; // direita
    default:
        return false;
    }

    if (novaPosicao.linha < 0 || novaPosicao.linha >= linhas ||
        novaPosicao.coluna < 0 || novaPosicao.coluna >= colunas)
    {
        return false;
    }

    return true;
}

void executarMovimento(int **matriz, Posicao &jogador, const Posicao &novaPosicao)
{
    matriz[jogador.linha][jogador.coluna] = 0;
    jogador = novaPosicao;
    matriz[jogador.linha][jogador.coluna] = 1;
}

void fornecerDicaProximidade(int distanciaAntiga, int distanciaNova)
{
    if (distanciaNova < distanciaAntiga)
    {
        cout << "Voce esta mais perto do tesouro." << endl;
    }
    else if (distanciaNova > distanciaAntiga)
    {
        cout << "Voce esta mais longe do tesouro." << endl;
    }
    else
    {
        cout << "Voce esta na mesma distancia do tesouro." << endl;
    }
}

void lerEntradaUsuario(char &direcao, int &passos)
{
    while (true)
    {
        cout << "Direcao (W/A/S/D): ";
        cin >> direcao;

        cout << "Numero de passos: ";
        cin >> passos;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << ">> Entrada invalida! Digite uma direcao e um numero inteiro." << endl
                 << endl;
            continue;
        }

        char d = toupper(direcao);
        if ((d != 'W' && d != 'A' && d != 'S' && d != 'D') || passos <= 0)
        {
            cout << ">> Direcao ou numero de passos invalido! Tente novamente." << endl
                 << endl;
            continue;
        }

        break;
    }
}