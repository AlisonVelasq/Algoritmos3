// Ejs_basicos_pd.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <ctime> 
using namespace std;

const int N = 100;

long long fibocci(int n);
long long fibo_pd(int n, long long vecMemo[N]);
void inicializar(long long vecMemo[N], int n);
long long factorial(int n);

int main()
{
    unsigned t0,t1;

    t0 = clock();
    int n = N;

    //cout << fibocci(n) << endl;

    //para usar pd, inicializo un vector de tam n donde todos los valores seran -1
    //exepto los primero 2 que son 0 e 1 (casos bases), esto me servira para evitar llamadas recursivas
    long long memorizar[N+1]; //en el lugar cero quiero guardar cero
    inicializar(memorizar, n);
    
    cout << fibo_pd(n, memorizar) << endl;
    
    t1 = clock();

    double time = (double(t1 - t0) / CLOCKS_PER_SEC);
    cout << "Execution Time: " << time << endl;

    return 0;
}
//notemos que haciendolo de esta forma para numeros grandes la complejidad aumenta mucho
//con N = 50  Execution Time: 376.004
long long fibocci(int n) {
    if (n == 0)       return 0;
    else if (n == 1)  return 1;
    else              return fibocci(n - 1) + fibocci(n - 2);
}
//pero si modifico la funcion de forma que me cuarda lo valores, asi en la sig
//llamada recursiva no tengo que calcular lo mismo, notamos que el tiempo de ejecucion 
//baja considerablemente, con N = 50   Execution Time: 0.001
long long fibo_pd(int n, long long vecMemo[N]) {
    if (vecMemo[n] == -1) { //no esta def
        vecMemo[n] = fibo_pd(n - 1, vecMemo) + fibo_pd(n - 2, vecMemo);
        return vecMemo[n];
    }
    else {
        return vecMemo[n];
    }
}
void inicializar(long long v[N], int n) {
    v[0] = 0;
    v[1] = 1;
    for (int i = 2; i <= n; i++) {
        v[i] = -1;
    }
}
long long factorial(int n) { //como aplico pd a esto???
    if (n == 1) {
        return 1;
    }
    else return n * factorial(n - 1);
}