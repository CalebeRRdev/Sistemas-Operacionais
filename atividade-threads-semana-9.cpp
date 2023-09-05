#include <iostream>
#include <fstream>
#include <mutex>
#include <thread>
#include <vector>
#include <locale.h>

std::mutex mtx; // mutex para exclusão mútua

void escrever_no_arquivo(const std::string& nome_do_arquivo, int threadId) {
    std::ofstream arquivo(nome_do_arquivo, std::ios_base::app);
    if (arquivo.is_open()) {
        mtx.lock(); // trancamos o mutex antes de escrever no arquivo
        arquivo << "\n\tThread " << threadId << " escreveu no arquivo.\n";
        mtx.unlock(); // destrancamos o mutex após escrever no arquivo
        arquivo.close();
    } else {
        std::cerr << "\n\tNão foi possível abrir o arquivo.\n";
    }
}

int main() {
    setlocale(LC_ALL, "Portuguese");
    const int numThreads = 5;
    const std::string nome_do_arquivo = "\n\tarquivo.txt";
    std::vector<std::thread> threads;
    for (int i = 0; i < numThreads; i++) {
        threads.push_back(std::thread(escrever_no_arquivo, nome_do_arquivo, i));
    }
    for (auto& t : threads) {
        t.join();
    }
    return 0;
}

