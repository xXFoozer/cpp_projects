#include <iostream>
using namespace std;

int **create_matrix(int matrix_size);
void showMatrix(int **matrix, int matrix_size);
void bomberman(int row, int col, int** matrix, int matrix_size);

int main()
{
    int matrix_size = {};

    cout << "Digite o tamanho da matriz: " << endl;
    cin >> matrix_size;

    int **point = create_matrix(matrix_size);

    int row;
    int col;

    cout << "Digite a coordenada da linha que deseja: " << endl;
    cin >> row;

    cout << "Digite a coordenada da coluna que deseja: " << endl;
    cin >> col;
    
    cout << "\n\n" << endl;

    cout << "ANTES DE ZERAR: " << endl;
    showMatrix(point,matrix_size);
    // mostrar
    

    //bomberman
    bomberman(row, col, point, matrix_size);



    cout << "\n\n" << endl;
    
    cout << "DEPOIS DE ZERAR: " << endl;
    showMatrix(point,matrix_size);
    //mostrar zerada 


    return 0;
}

void bomberman(int row, int col, int** matrix, int matrix_size) {
    if(row < 0  || row >= matrix_size || col < 0 || col >= matrix_size) return;

    if(matrix[row][col] == 0) return;

    matrix[row][col] = 0;

    bomberman(row - 1, col, matrix, matrix_size);
    bomberman(row + 1, col, matrix, matrix_size);
    bomberman(row, col - 1, matrix, matrix_size);
    bomberman(row, col + 1, matrix, matrix_size);
}

void showMatrix(int **matrix, int matrix_size) {
     for (int i = 0; i < matrix_size; i++){
        for (int k = 0; k < matrix_size; k++){
            cout << "\t" << matrix[i][k];
        }
        cout << "\n";
    }
}


int **create_matrix(int matrix_size)
{
    int **matrix = new int *[matrix_size];

    for (int i = 0; i < matrix_size; i++)
    {
        matrix[i] = new int[matrix_size];
    }

    for (int i = 0; i < matrix_size; i++)
    {
        for (int j = 0; j < matrix_size; j++)
        {
            matrix[i][j] = rand() % 2;
        }
    }

    return matrix;
}