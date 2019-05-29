/**
 *	@author Micael Gomes
 *	Trabalho para Disciplina de Sistemas Operacionais
 *	Multithread com PThreads
 */

#include <iostream>
#include <stdlib.h>
#include <thread>
#include <vector>
#include <string.h>

#define a 0
#define b 29999
#define TAM 1000

/*  TAM == 10000 => Quant Primes: 10825260
    Time => ./exe serial: 397,95s user - 0,58s system - 99% cpu - 6:41,73 total */

/*  TAM == 20000 => Quant Primes: 43301112
    Time => ./exe serial: 1526,55s user - 2,30s system - 99% cpu - 25:36,03 total */

using namespace std;

int mat[TAM][TAM];
int quantPrime = 0;

void generateRandomMat();
vector<thread> createThreads(int quantThread);
bool isPrime(int num);
void findPrime(int start, int end);


void printID(){
    cout << "Thread ID : " <<std::this_thread::get_id() << endl;
}

int main(int argc, char *argv[]){       
    int *macroVisited = (int*)calloc(sizeof(int), TAM);
    int quantThread;
    vector<thread> threads;

    if(argv[1]!=NULL) {
        printf("Preenchendo Matriz...\n\n");
        generateRandomMat();
  
        if(!strcmp(argv[1], "serial")){
            printf("Start!\n");
            findPrime(0, TAM);
        } else if(!strcmp(argv[1], "paralelo")){
            if(argv[2]!=NULL){
                quantThread = strtol(argv[2], NULL, 10);
                threads = createThreads(quantThread);

                for(thread & th: threads){
                    if(th.joinable())
                        th.join();
                }
            }
        } else {
            printf("Há Argumentos, mas... não consigo entender\n");
            return 0;    
        }

        printf("Quant Primes: %d\n", quantPrime);
    
    }else{
        printf("Argumentos não encontrado!\n");
    }
    
    return 0;
}

vector<thread> createThreads(int quantThread){
    vector<thread> threads;

    while(quantThread > 0){
        threads.push_back(thread(printID));
        quantThread--;
    }

    return threads;
}

bool isPrime(int num){
    bool flag = true;

    for(int i=2; i<=num/2; i++){
        if(num%i==0){
            flag = false;
            break;
        }
    }

    return flag;
}

void generateRandomMat(){
    srand(time(NULL));
    for(int i=0; i<TAM; i++)
        for(int j=0; j<TAM; j++)
            mat[i][j] = rand() % b + a;
}

void findPrime(int start, int end){
    for(int i=start; i<end; i++)
        for(int j=start; j<end; j++)
            if(isPrime(mat[i][j]))
                quantPrime = quantPrime + 1;
}