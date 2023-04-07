// Ej4_permutacion_pi.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <vector>
using namespace std;

const int N = 4;
void prinftVector(vector<int> v);
void inicializar_vector_con_Ceros(vector<int>& pi, int n);
void inicializar_vector(vector<int> &pi, int n);
int sumaMinParcial(int m[N][N], int n, vector <int> pi);
vector<int> minimiceSuma(int m[N][N], int n, int i, vector<int> repetidos, int& sumaMin, vector<int> pi_permutado, vector<int> pi_Final);

int main()
{
    int n = N;
    int matriz[N][N] = { {0, 1, 10, 10},
                         {10, 0, 3, 15},
                         {21, 17, 0, 2},
                         {3, 22, 30, 0} };
    vector<int> pi_vacio;
    vector<int> repetidos;
    inicializar_vector(repetidos, n);
    inicializar_vector_con_Ceros(pi_vacio, n);
    prinftVector(repetidos);
    prinftVector(pi_vacio);
    system("pause");
    //voy a guardar como la primer suma_Min la perm {1,2,3,4,...,n} y cuando lo compare con este mismo va a ser igual y guarda ese, o otro menor
    int suma = sumaMinParcial(matriz, n, repetidos); //ahora repetidos esta completo 
    cout << suma << endl;
    system("pause");
    //pi_vacio = minimiceSuma(matriz, n, 0, repetidos, suma, pi_vacio, pi_vacio); //el ultimo return
    prinftVector( minimiceSuma(matriz, n, 0, repetidos, suma, pi_vacio, pi_vacio) );
}
//pruebo todas las permutaciones de pi ={1,2,..n} posibles y voy podando cada vez 
//q la suma parcial sea mas grande...
//ya tengo la primer permutacion que es la normal,con eso encuentro la suma parcial y comparo

vector <int> minimiceSuma(int m[N][N], int n, int i, vector<int> repetidos, int& sumaMin, vector<int> pi_permutado, vector<int> pi_Final) {
    for (int k = 1; k < n+1; k++) {

        if (repetidos[k-1] != 0) { //aun no use ese num en la combinacion
            repetidos[k - 1] = 0;//marco que ya use este valor en la combinacion
            pi_permutado[i] = k;
           
            if (sumaMin < sumaMinParcial(m, n, pi_permutado)) { //poda, entra aca aun que no este completamente permutado, ej:{4,2,0,0,0..} 
                                                             //asi voy descartando antes de seguir con las sig combi de {4,2,0,0..}
                //pi_Final = minimiceSuma(m, n, i+1, repetidos, sumaMin, pi_permutado, pi_Final);
                
                if (i == n - 1) { 
                    pi_Final = minimiceSuma(m, n, 0, repetidos, sumaMin, pi_permutado, pi_Final);
                }
                else {
                    pi_Final = minimiceSuma(m, n, i + 1, repetidos, sumaMin, pi_permutado, pi_Final);
                }
            }
            else {
                
                if (i == n-1) { //encontre una nueva sumaMin y llegue al final de pi_permutado
                    
                    sumaMin = sumaMinParcial(m, n, pi_permutado);
                    pi_Final = pi_permutado;                 
                    pi_Final = minimiceSuma(m, n, 0, repetidos, sumaMin, pi_permutado, pi_Final);
                }
                else {
                    pi_Final = minimiceSuma(m, n, i+1, repetidos, sumaMin, pi_permutado, pi_Final);
                }
            }
            repetidos[k - 1] = k;
            pi_permutado[i] = 0;
        }
        
    }
    return pi_Final; //devuelve el que quiero
}
int sumaMinParcial(int m[N][N], int n, vector <int> pi) {
    //sumo todo, ya que si no tengo una permutacion completa los demas deberian ser ceros
    int pi_i = 0, D_n1 = 0;
    int pi_i1 = 0;
    int sumatoria = 0;
    for (int i = 0; i < n-1; i++) {
        pi_i = pi[i]-1;         //pi(i)
        pi_i1 = pi[i + 1] - 1; // pi(i+1)
        sumatoria += m[pi_i][pi_i1];
    }
    pi_i = pi[n - 1]-1; //como pi y m se majan desd 0 pero logicamente son desde uno osea en pi[i]
    //debo siempre correrlos pi[(n-1)=3](ulti incide de pi) = 4 = ult elem en pi pero en realidad es 3 en indice en m
    pi_i1 = pi[0]-1;
    D_n1 = m[ pi_i ][ pi_i1 ]; //pos D_n_1

    return D_n1+sumatoria;
}
void inicializar_vector(vector<int>& pi, int n) {
    for (int i = 0; i < n; i++){
        //pi[i] = i+1; //tengo que definir dimensiones para usarlo
        pi.push_back(i+1);
    }
}
void inicializar_vector_con_Ceros(vector<int>& pi, int n) {
    for (int i = 0; i < n; i++) {
        //pi[i] = 0;
        pi.push_back(0);
    }
}
void prinftVector(vector<int> v) {
    for (int i : v) {
        cout << i << " ";
    }
    cout << endl;
}


