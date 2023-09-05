#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <locale.h>

using namespace std;

// Variáveis e constantes globais

const int NUM_PISTAS = 3; // Quantidade de pistas e competidores
const int TAM_PISTA = 50; // Tamanho do percurso

     
atomic<bool> jogoIniciado(false);
atomic<bool> jogoRodando(true);
atomic<int> jogadorPosicao[NUM_PISTAS];

mutex mtx;

condition_variable cv;

// Funções 

// Implementa a lógica do jogo
void gameLogica(){
    while(!jogoIniciado){
        this_thread::yield();
    }

    while(jogoRodando){
        for(int i = 0; i < NUM_PISTAS; i++){
            jogadorPosicao[i] += rand() % 3 + 1;
        if(jogadorPosicao[i] >= TAM_PISTA){
            jogoRodando = false;
            break;
        }
        }
        
        unique_lock<mutex> lock(mtx);
        cv.notify_all();
        lock.unlock();

        this_thread::sleep_for(chrono::milliseconds(500));
    }
}

// Renderiza o jogo na tela
void desenhaGame(){
    while(!jogoIniciado){
        this_thread::yield();
    }

    while(jogoRodando){
        unique_lock<mutex> lock(mtx);
        cv.wait(lock);

        for(int i = 0; i < NUM_PISTAS; i++){
            cout << "Pista " << i+1 << ": ";
            for(int j = 0; j < TAM_PISTA; j++){
                if(j == jogadorPosicao[i]){
                    cout << "X";
                }
                else{
                    cout << "-";
                }
            }
            cout << endl;
        }
        lock.unlock();
    }
}

// Captura dados do usuário

void entradaUsuario(){
    while(!jogoIniciado){
        int pista;
        cout << "Escolha um competidor (1 - " << NUM_PISTAS << "): ";
        cin >> pista;

        // Validação de dados

        if(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Valor inválido. Tente novamente." << endl;
            continue;
        }

        if(pista < 1 || pista > NUM_PISTAS){
            cout << "Competidor inválido. Escolha um número entre 1 e " <<  NUM_PISTAS << "." << endl;
            continue;
        }

        jogadorPosicao[pista - 1] += NUM_PISTAS;
        jogoIniciado = true;
    }
}

// Executa o jogo e cria as threads

int main(){
    setlocale(LC_ALL, "Portuguese");

    thread t1(gameLogica);
    thread t2(desenhaGame);
    thread t3(entradaUsuario);

    t1.join();
    t2.join();
    t3.join();

    return 0;
}