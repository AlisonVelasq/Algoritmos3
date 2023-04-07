// Ej3_sumaMatriz.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <vector>;
using namespace std;

const int n = 4;

void prinftVector(vector<int> v);
int suma_subMatriz_I(int m[n][n], int n, vector<int> vec_I);
vector<int> maxSuma(int m[n][n], int n, int k, int f, int c, vector<int> vec_I, int& sumaMax, vector<int> I_final);

int main()
{
    int matriz1[n][n] = { { 1, 2, 3, 4 },
                         { 2, 5, 6, 7 },
                         { 3, 6, 8, 9 },
                         { 4, 7, 9, 10 } };
    int matriz2[n][n] = { { 0, 10, 10, 1 },
                          { 10, 0, 5, 2 },
                          { 10, 5, 0, 1 },
                          { 1, 2, 1, 0 } };
    int k = 3;
    int sum = 0;
    vector<int> vec_I = { 0,0,0 };
    vector<int> conj_I = maxSuma(matriz1, n, k, 0, 1, vec_I, sum, vec_I);
    prinftVector(conj_I);

    sum = 0;
    vec_I = { 0,0,0 };
    conj_I = maxSuma(matriz2, n, k, 0, 1, vec_I, sum, vec_I);
    prinftVector(conj_I);

}
/*  pruebo todas las posibilidades de I, empiezo I = {1,2,3}, {1,2,4}, {1,3,4}, etc
    voy a seguir el arbol de todas las combinaciones posibles, pero voy a podar las repetidas ej: (1,2,3) =(2,1,3)
    en si voy a solo fijar la suma en conjuntos con elem distintos (i.e no importa el orden)
    para esot me di cuenta que el arbol se poda cada vez que los hijos de la cabeza padre son menores a este, ya que si esto
    pasa quiere decir que esa combinacion ya esta repetida en otra rama (empiezo con el 1,2,3,..,n) (ver en cuaderno)
    
    (*) no uso que es simetrica, podria hacer una poda con eso
    
    */
vector<int> maxSuma(int m[n][n], int n, int k, int i, int x, vector<int> vec_I, int& sumaMax, vector<int> I_final) {
    //se poda automaticamente ya que solo me fijo en valores ascendente cada vez que vuelvo, ie no nesecito fijarme en nada
    //aunq hace falta una poda mas ooptima para sumas parciales
    int sumaMaxparcial = 0;
    for (int e = x; e < n+1; e++) {
        vec_I[i] = e;
     
        if (i == k - 1) { //mi conj I se completo;
            sumaMaxparcial = suma_subMatriz_I(m, n, vec_I);
            
            cout << " s" << sumaMaxparcial << endl;
            cout << sumaMax<<endl;
            if (sumaMaxparcial > sumaMax) { //encontre una suma mas grande me guado la suma e el conj I correspon a la suma
                cout << "entre" << endl;
                sumaMax = sumaMaxparcial;
                I_final = vec_I;
                I_final = maxSuma(m, n, k, 0, x+1, vec_I, sumaMax, I_final);
            }
            else  I_final = maxSuma(m, n, k, 0, x+1, vec_I, sumaMax, I_final); //voy  a lasig combinacion
        }
        else{
            I_final = maxSuma(m, n, k, i + 1, x + 1, vec_I, sumaMax, I_final); //el x+1 para evitar repetidos
            
        }
        vec_I[i] = 0 ; //volvi
        x++;
    }
    return I_final;
}

int suma_subMatriz_I(int m[n][n], int n, vector<int> vec_I) {
    int suma = 0;

    for (int i: vec_I) {
        for (int j : vec_I)
        {
            suma += m[i - 1][j - 1];
        }
    }
    
    return suma;
}

void prinftVector(vector<int> v) {
    for (int i : v) {
        cout << i << " " ;
    }
}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
