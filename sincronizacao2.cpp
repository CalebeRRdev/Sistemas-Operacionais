#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

mutex mtx; // Mutex para garantir exclusão mútua
int contador = 0; // Variável compartilhada

void incrementaContador()
{
    for (int i = 0; i < 1000000; ++i)
    {
        unique_lock<mutex> lock(mtx); // Bloqueia o mutex
        contador++; // Operação crítica
        cout << contador << endl;
        lock.unlock(); // Libera o mutex
    }
}

int main()
{
    thread t1(incrementaContador); // Thread 1
    thread t2(incrementaContador); // Thread 2

    t1.join();
    t2.join();

    cout << "\nContador: " << contador << endl;

    return 0;
}

