#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <locale.h>

using namespace std;

// Variáveis e constantes globais
const int TAM_PISTA = 50; // Tamanho do percurso

atomic<bool> jogoIniciado(false);
atomic<bool> jogoRodando(true);
atomic<int> jogadorPosicao[TAM_PISTA];

mutex mtx;
condition_variable cv;

// Funções 
// Implementa a lógica do jogo
void gameLogica(int numPistas){
    while(!jogoIniciado){
        this_thread::yield();
    }

    while(jogoRodando){
        for(int i = 0; i < numPistas; i++){
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
void desenhaGame(int numPistas){
    while(!jogoIniciado){
        this_thread::yield();
    }

    while(jogoRodando){
        unique_lock<mutex> lock(mtx);
        cv.wait(lock);

        for(int i = 0; i < numPistas; i++){
            cout << "\n\tPista " << i+1 << ": ";
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
void entradaUsuario(int& numPistas){
    while(numPistas <= 0){
        cout << "\n\tQuantos competidores deseja? ";
        cin >> numPistas;

        if(numPistas <= 0){
            cout << "\n\tNúmero inválido. Tente novamente." << endl;
            continue;
        }
    }

    while(!jogoIniciado){
        int pista;
        cout << "\n\tEscolha um competidor (1 - " << numPistas << "): ";
        cin >> pista;

        // Validação de dados
        if(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\n\tValor inválido. Tente novamente." << endl;
            continue;
        }

        if(pista < 1 || pista > numPistas){
            cout << "\n\tCompetidor inválido. Escolha um número entre 1 e " <<  numPistas << "." << endl;
            continue;
        }

        jogadorPosicao[pista - 1] += numPistas;
        jogoIniciado = true;
    }
}

// Executa o jogo e cria as threads
int main(){
    setlocale(LC_ALL, "Portuguese");

    int numPistas = 0;
    entradaUsuario(numPistas);

    thread t1(gameLogica, numPistas);
    thread t2(desenhaGame, numPistas);
    thread t3(entradaUsuario, ref(numPistas));

    t1.join();
    t2.join();
    t3.join();
 
    return 0;   
}

