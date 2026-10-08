#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Pessoa {
    string nome;
    int idade;
    string email;
    Pessoa *contatoEmergencia; 
};

void lerDadosBasicos(Pessoa *p) {
    cin.ignore(); 
    cout << "Nome: ";
    getline(cin, p->nome);

    cout << "Idade: ";
    cin >> p->idade;
    cin.ignore();

    cout << "Email: ";
    getline(cin, p->email);
}

Pessoa* cadastrarPessoa() {
    Pessoa *p = new Pessoa();
    p->contatoEmergencia = nullptr;

    lerDadosBasicos(p);

    char resposta;
    cout << "Deseja cadastrar um contato de emergencia? (s/n): ";
    cin >> resposta;

    if (resposta == 's' || resposta == 'S') {
        cout << "\n-- Dados do contato de emergencia --" << endl;
        p->contatoEmergencia = cadastrarPessoa(); 
    }

    return p;
}

void exibirPessoa(Pessoa *p) {
    cout << "Nome: " << p->nome << endl;
    cout << "Idade: " << p->idade << endl;
    cout << "Email: " << p->email << endl;

    if (p->contatoEmergencia != nullptr) {
        cout << "Contato de emergencia:" << endl;
        cout << "  Nome: " << p->contatoEmergencia->nome << endl;
        cout << "  Idade: " << p->contatoEmergencia->idade << endl;
        cout << "  Email: " << p->contatoEmergencia->email << endl;
    } else {
        cout << "Contato de emergencia: nao informado" << endl;
    }
}

void liberarPessoa(Pessoa *p) {
    if (p == nullptr) return;

    if (p->contatoEmergencia != nullptr) {
        liberarPessoa(p->contatoEmergencia);
    }

    delete p;
}

int main() {
    vector<Pessoa*> cadastros;
    char continuar = 's';

    do {
        cout << "\n-- Novo cadastro --" << endl;
        Pessoa *nova = cadastrarPessoa();
        cadastros.push_back(nova);

        cout << "\nDeseja cadastrar outra pessoa? (s/n): ";
        cin >> continuar;

    } while (continuar == 's' || continuar == 'S');

    cout << "\n===== Pessoas cadastradas =====" << endl;
    for (size_t i = 0; i < cadastros.size(); i++) {
        cout << "\nCadastro " << (i + 1) << ":" << endl;
        exibirPessoa(cadastros[i]);
    }

    for (size_t i = 0; i < cadastros.size(); i++) {
        liberarPessoa(cadastros[i]);
    }

    cout << "\nPrograma encerrado." << endl;
    return 0;
}