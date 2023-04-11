#include<iostream>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>
#include<locale.h>

using namespace std;

int main(){
setlocale(LC_ALL,"Portuguese");
int fd[2];
pid_t pid;
char buffer[1024];
//criar o pipe
if(pipe(fd)<0){
    cerr<<"\n\tErro ao criar o pipe"<<endl;
    exit(1);
}
//criar o processo filho
pid = fork();
if(pid<0){
    cerr << "\n\tErro ao criar o processo filho"<<endl;
    exit(1);
}
else if (pid==0){
    close(fd[1]);
    //realiza a leitura do pipe
    read(fd[0], buffer, sizeof(buffer));
    cout<<"\n\tProcesso filho: Mensagem recebida do pai:"<<buffer<<endl;
    close(fd[0]);
    exit(0);
}
else{
    //processo pai
    close(fd[0]);
    //escrever no pipe
    string mensagem = "\n\tOlá filho!";
    write(fd[1],mensagem.c_str(),mensagem.length());
    close(fd[1]);
    wait(NULL);
    exit(0);
}
return 0;

}