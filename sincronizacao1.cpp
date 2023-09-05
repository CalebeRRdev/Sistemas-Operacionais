#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

mutex mtx;
condition_variable cv;
bool recursoDisponivel = false;

void produtor()
{
    while (true)
    {
        // Produz um recurso

        {
            unique_lock<mutex> lock(mtx);
            recursoDisponivel = true;
            cout << "Produtor: Recurso produzido!" << endl;
        }

        cv.notify_all(); // Notifica os consumidores

        // Espera um tempo antes de produzir novamente
        this_thread::sleep_for(chrono::milliseconds(1000));
    }
}

void consumidor(int id)
{
    while (true)
    {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, []() { return recursoDisponivel; }); // Espera pelo recurso

        // Consome o recurso
        cout << "Consumidor " << id << ": Recurso consumido!" << endl;
        recursoDisponivel = false;

        // Realiza o processamento do recurso

        // Espera um tempo antes de consumir novamente
        this_thread::sleep_for(chrono::milliseconds(500));
    }
}

int main()
{
    thread t1(produtor); // Thread do produtor
    thread t2(consumidor, 1); // Thread do consumidor 1
    thread t3(consumidor, 2); // Thread do consumidor 2

    t1.join();
    t2.join();
    t3.join();

    return 0;
}
