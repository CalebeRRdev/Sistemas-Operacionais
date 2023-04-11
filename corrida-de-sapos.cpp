//Elaborar um programa em C++ que simule uma corrida de sapos, onde cada sapo participante da corrida deve ser uma thread.

//Regras:

//O usuário deve informar uma distância máxima em cm (centímetros);
//O usuário deve informar a quantidade de sapos participantes da corrida;
//O usuário deve informar a quantidade máxima de saltos para completar a corrida.


#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <random>
#include <locale.h>

using namespace std;

// Variáveis globais
int distancia_maxima;
int quantidade_sapos;
int max_saltos;
int* posicoes;
mutex mtx;

// Função que simula a corrida do sapo
void corrida(int id) {
    int posicao = 0;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distribuicao(1, max_saltos);

    while (posicao < distancia_maxima) {
        int saltos = distribuicao(gen);
        posicao += saltos;
    // Bloqueia o acesso à variável global posicoes
    mtx.lock();
    
    // Atualiza a posição do sapo na variável global posicoes
    posicoes[id] = posicao;
    
    // Imprime a posição atual do sapo
    cout << "\n\tSapo " << id << " pulou " << saltos << " cm e está na posição " << posicao << " cm" << endl;
    
    // Libera o acesso à variável global posicoes
    mtx.unlock();
    
    // Aguarda um tempo aleatório antes do próximo salto
    this_thread::sleep_for(chrono::milliseconds(distribuicao(gen)*100));
}

// Imprime a mensagem de que o sapo venceu
cout << "\n\tSapo " << id << " venceu a corrida!" << endl;
}

int main() {
setlocale(LC_ALL, "Portuguese");
// Lê os dados informados pelo usuário
cout << "\n\tInforme a distância máxima em centímetros: ";
cin >> distancia_maxima;
cout << "\n\tInforme a quantidade de sapos: ";
cin >> quantidade_sapos;
cout << "\n\tInforme a quantidade máxima de saltos: ";
cin >> max_saltos;
// Cria um array para armazenar as posições dos sapos
posicoes = new int[quantidade_sapos];

// Cria as threads para simular a corrida dos sapos
thread* threads = new thread[quantidade_sapos];
for (int i = 0; i < quantidade_sapos; i++) {
    threads[i] = thread(corrida, i);
}

// Aguarda o término da corrida de todos os sapos
for (int i = 0; i < quantidade_sapos; i++) {
    threads[i].join();
    // Encontra o sapo vencedor
int vencedor = 0;
for (int i = 0; i < quantidade_sapos; i++) {
if (posicoes[i] >= distancia_maxima) {
vencedor = i;
}
}

// Imprime o número do sapo vencedor
cout << "\n\tO sapo vencedor é o número " << vencedor << endl;

// Libera a memória alocada para as variáveis
delete[] posicoes;
delete[] threads;

return 0;
}
}
