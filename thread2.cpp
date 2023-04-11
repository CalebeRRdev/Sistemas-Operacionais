#include <iostream>
#include <thread>

void funcao1() {
    std::cout << "Thread 1 em execucao" << std::endl;
}

void funcao2() {
    std::cout << "Thread 2 em execucao" << std::endl;
}

int main() {
    // cria as threads
    std::thread t1(funcao1);
    std::thread t2(funcao2);

    // aguarda as threads terminarem
    t1.join();
    t2.join();

    return 0;
}
