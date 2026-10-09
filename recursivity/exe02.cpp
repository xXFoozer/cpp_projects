#include <iostream>
using namespace std;

int main()
{
    int user_input = 0;

    do
    {
        cout << "Digite quantos termos da sequencia deseja (maior que 0): ";
        cin >> user_input;

        if (cin.fail())     
        {
            cin.clear();
            cin.ignore(10000, '\n');
            user_input = 0;
        }
    } while (user_input <= 0);

    long previous = 0;
    long actual = 1;

    for (int i = 1; i <= user_input; i++)
    {
        cout << actual << " ";

        long long next = previous + actual;
        previous = actual;
        actual = next;
    }

    cout << endl;

    return 0;
}