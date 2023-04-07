// SUDOKU_BT.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
using namespace std;

void printSudoku(int sudoku[9][9]);
void completarSudoku(int s[9][9], int f, int c);
bool esApto(int op, int s[9][9], int f, int c);    
bool estaEnFila(int op, int s[9][9], int f);
bool estaEnColumna(int op, int s[9][9], int c);
bool estaEnCuadrante(int op, int s[9][9], int f, int c);
bool estavacio(int e);

int main() {
    int sudoku1[9][9] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };
    
    int sudoku2[9][9] = {
        {0, 0, 9, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 3, 7, 0, 0, 0, 0},
        {0, 8, 1, 9, 0, 6, 0, 0, 0},
        {0, 4, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 7, 0, 0, 0, 0, 9},
        {8, 0, 0, 0, 0, 2, 0, 7, 0},
        {0, 0, 0, 0, 5, 9, 4, 0, 0},
        {6, 0, 0, 0, 0, 0, 0, 5, 0},
        {0, 9, 5, 0, 2, 8, 0, 0, 0}
        };



    int sudoku3[9][9] = {
        {8, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 3, 6, 0, 0, 0, 0, 0},
        {0, 7, 0, 0, 9, 0, 2, 0, 0},
        {0, 5, 0, 0, 0, 7, 0, 0, 0},
        {0, 0, 0, 0, 4, 5, 7, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 3, 0},
        {0, 0, 1, 0, 0, 0, 0, 6, 8},
        {0, 0, 8, 5, 0, 0, 0, 1, 0},
        {0, 9, 0, 0, 0, 0, 4, 0, 0}
    };

    int sudoku4[9][9] = {
        {0, 0, 0, 2, 6, 0, 7, 0, 1},
        {6, 8, 0, 0, 7, 0, 0, 9, 0},
        {1, 9, 0, 0, 0, 4, 5, 0, 0},
        {8, 2, 0, 1, 0, 0, 0, 4, 0},
        {0, 0, 4, 6, 0, 2, 9, 0, 0},
        {0, 5, 0, 0, 0, 3, 0, 2, 8},
        {0, 0, 9, 3, 0, 0, 0, 7, 4},
        {0, 4, 0, 0, 5, 0, 0, 3, 6},
        {7, 0, 3, 0, 1, 8, 0, 0, 0}
    };

    cout << "sudoku 1:\n";
    printSudoku(sudoku1);
    completarSudoku(sudoku1, 0, 0);
    
    cout << "sudoku 2:\n";
    printSudoku(sudoku2);
    completarSudoku(sudoku2, 0, 0);
    
    cout << "sudoku 3:\n";
    printSudoku(sudoku3);
    completarSudoku(sudoku3, 0, 0);
    
    cout << "sudoku 4:\n";
    printSudoku(sudoku4);
    completarSudoku(sudoku4, 0, 0);

    return 0;
}

void completarSudoku(int s[9][9], int f, int c) {
   
    //planteo todas las soluciones posible del sudoku y se me genera un arbol
    for (int k = 1; k < 10; k++) {
        if (s[f][c] == 0) { //estavacio

            if (esApto(k, s, f, c)) {

                s[f][c] = k;
                if (c < 8) {
                    completarSudoku(s, f, c + 1);
                    //cada vez que vuelva tengo que poner en cero la casilla, ya que si volvi, i.e que fui por la rama equivocada sea cual sea el numero
                    s[f][c] = 0;
                }
                else if (f < 8) {
                    completarSudoku(s, f + 1, 0);
                    s[f][c] = 0;
                }

            } //la poda se hace automaticamente si llego al 9 y ningun num es apto
            else if (k == 9) {
                s[f][c] = 0;
            }
        }
        else { //voy al sig, lo hago asi para no saltar al paso recursivo cuando la casilla es fija
            if (c < 8) {
                c++; k = 0;
            }
            else if (f < 8) {
                f++; c = 0; k = 0;
            }
        }

    }
    //sudokuResuelto
    if (f == 8 && c ==8) {
        cout << "\nsudoku resuelto:\n"<<endl;
        printSudoku(s);
    }

}
bool esApto(int op, int s[9][9], int f, int c) {
    if (estaEnFila(op, s, f) || estaEnColumna(op, s, c) || estaEnCuadrante(op, s, f, c)) 
        return false;
    else return true;
}
bool estaEnFila(int op, int s[9][9], int f) {
    for (int i = 0; i < 9; i++){
        if (s[f][i] == op) return true;
        //res =& s[f][i] != op; no anda
    }
    return false;
}

bool estaEnColumna(int op, int s[9][9], int c) {
    for (int i = 0; i < 9; i++) {
        if (s[i][c] == op) return true;
    }
    return false;
}
bool estaEnCuadrante(int op, int s[9][9], int f, int c) {
    //me fijo en que cuadrante del sudoku estoy del 0 al 8
    /*  0 | 1 | 2
        ---------
        3 | 4 | 5
        ---------
        6 | 7 | 8  */

    //int cuadrante = (f / 3) * 3 + (c / 3); //formula que optiene el cuadrante, calculando fila y col respecto a cuadrantes
    int row = f / 3;   // fila del cuadrante
    int col = c / 3;   // columna del cuadrante
    int cuadrante = row * 3 + col;
    //recorro con fors solo ese cuadrante
    int f_i = 0; //inicializado para los que empiezan en 0
    int c_i = 0;

    if (cuadrante >= 3 && cuadrante <= 5) {
        f_i = 3; //fila empieza en 0   
    }
    else if (cuadrante >= 6 ) {
        f_i = 6;
    }

    if (cuadrante == 1 || cuadrante == 4 || cuadrante == 7) {
        c_i = 3; //col empieza en 3   
    }
    else if (cuadrante == 2 || cuadrante == 5 || cuadrante == 8) {
        c_i = 6;
    }
  
    //todas terminan en f_i + 3
    //recorro
    for (int i = f_i; i < f_i + 3; i++) {
        for (int j = c_i; j < c_i+3; j++){
            //evaluo que no este en el cuadrante
            if (op == s[i][j]) return true;
        }
    }
    return false;
}
bool estavacio(int e) {
    if (e == 0) return true;
    else false;
}

void printSudoku(int sudoku[9][9]) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cout << sudoku[i][j] << " ";
            if (j == 2 || j == 5) {
                cout << "| ";
            }
        }
        cout << std::endl;
        if (i == 2 || i == 5) {
            cout << "------+-------+------" << std::endl;
        }
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
