// Ej2_cuadrado_magico.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
using namespace std;

void vectorConValores(int* vecNums, int tam);
void inicializar_Ceros(int** cm, int n);
void printfCuadrado(int n, int** c);
int supuestoNumMagico(int** cm, int n, int f, int c, int numMag);
int sumoColum(int** cm, int f, int c);
int sumoFila(int** cm, int f, int c);
bool sumaParcialValida(int** cm, int n, int f, int c, int numMag, int k);
void cuadradosMagico(int** cm, int orden, int f, int c, int numMag, int* vecNums, int* cantMagico);
bool comprueboDiagonales(int** cm, int n, int numMag);
void prinfvector(int* v, int n);

int main()
{
	int* cantCuadradosMag = new int();
	*cantCuadradosMag = 0;
	int n = 4;
	int tam = n * n;
	int** cm;
	// asignar memoria dinámica para alojar la matriz
	cm = new int* [n]; // alojar n punteros a entero
	for (int i = 0; i < n; i++) {
		cm[i] = new int[n]; // alojar n enteros en cada fila
	}
	int* vecNums = new int[tam];

	inicializar_Ceros(cm, n	);
	vectorConValores(vecNums, tam);
	cuadradosMagico(cm, n, 0, 0, 0, vecNums, cantCuadradosMag);

	cout << "Hay " << *cantCuadradosMag << " cuadrados magicos" << endl;

	return 0;
}
bool comprueboDiagonales(int** cm, int n, int numMag){
	int sumDiag1 = 0; //suma de las diagonales
	int sumDiag2 = 0;
	for (int i = 0; i < n; i++) {
		//la diagonal son (0,0) (1,1) ..(n,n) la otra es (0,n) (1,n-1) (2, n-2)..(n,0) //en realidad va hasta n= n-1
		sumDiag1 += cm[i][i];
		sumDiag2 += cm[i][(n-1) - i];
	}
	if (numMag == sumDiag1 && numMag == sumDiag2) return true;
	else return false;
}
/*
* debug:
* cout << "p"<<numMag<<f<<c << endl;

				prinfvector(vecNums, tam);
				printfCuadrado(n, cm);
				cout << numMag << endl;
				system("pause");

				if (cm[0][0] == 2 && cm[0][1] == 7 && cm[0][2] ==6) {
					prinfvector(vecNums, tam);
					printfCuadrado(n, cm);
					cout << "N:"<<numMag<<" "<<f<<c <<" v:ki" <<k<<i << endl;
					system("pause");

				}

				cout << "volvi" << endl;
				prinfvector(vecNums, tam);
				if (comprueboDiagonales(cm, n, numMag) && c == 2  && f == 2) {

			printfCuadrado(n, cm);
			system("pause");

	}

*/
void cuadradosMagico(int** cm, int n, int f, int c, int numMag, int* vecNums, int* cantMagico) {
	numMag = (pow(n, 3) + n) / 2;
	int k = 0;
	for (int i = 0; i < n*n; i++) {
		if (vecNums[i] != 0) { //para no repetir, marco con ceros los que ya use
			k = vecNums[i];
			//encuentro el supuesto num magico, osea sumo la primer fila
			// numMag = supuestoNumMagico(cm, n, f, c, numMag);
			//uso la formula;
			if (sumaParcialValida(cm, n, f, c, numMag, k) ) { //poda				
				cm[f][c] = k;
				vecNums[i] = 0;
				
				if (c < n-1) cuadradosMagico(cm, n, f, c + 1, numMag, vecNums,cantMagico);
				else if (f < n-1) cuadradosMagico(cm, n, f + 1, 0, numMag, vecNums,cantMagico);

				//compruebo si termino el cuadrado magico
				if (f == n-1 && c == n-1) { //completo el ult elem con exito
					if (comprueboDiagonales(cm, n, numMag)) {
						//porfin encontre mi cuadrado magico!
						*cantMagico+=1;
						cout << *cantMagico << endl;
						printfCuadrado(n, cm);
						//system("pause");
						//de orden 4 hay 7040 cuadrados (/8 =880
						//abria que fijarse que no cuente las rotaciones para que de 880
					}
					
				}
				//VOLVIO de la recursion
					cm[f][c] = 0; //si volvio es que ese camino no funciono
					vecNums[i] = i + 1; //"saco el cero"
				
			}
		}	
	}
}
bool sumaParcialValida(int** cm, int n, int f, int c, int numMag, int k) {
	if (numMag == 0) return true; //"caso base"
	else {
		cm[f][c] = k; //cuando entro a esta f aun no igual a k, ya que estoy evaluando, por eso lo igualo aca TEMPORALMENTE
		int suma = 0;

		//se supone que ya estoy por la segunda o mas fila
		//estoy parada en el cm[f][c], asi q tengo 2 casos
		// 1) viendo c se si estoy al final de una fila o al final de una columna (me fijo que sea =numMag)
		// 2) o estoy en el medio y me fijo q la sumaParcial sea < numMag
		if (c == n - 1) { //estoy al fina,l de una fila
			suma = sumoFila(cm, f, c); //el c que le paso es hasta donde suma
			cm[f][c] = 0; //aca elimino el temporal
			if (numMag == suma) return true;
			else return false;
		}
		else if (f == n - 1) { //estoy al final de una colum
			suma = sumoColum(cm, f, c); //el f que le paso es hasta donde suma
			cm[f][c] = 0;
			if (numMag == suma) return true;
			else return false;

		}
		else if (c < n - 1) {//suma parcial, hasta donde llegue c en la fila f
			suma = sumoFila(cm, f, c);
			cm[f][c] = 0;
			if (suma < numMag) return true;
			else return false;
		}
		else if (f < n - 1) {
			suma = sumoColum(cm, f, c);
			cm[f][c] = 0;
			if (suma < numMag) return true;
			else return false;

		}
	}
}
int sumoFila(int** cm, int f, int c) {
	int suma = 0;
	for (int i = 0; i <= c; i++) {
		suma += cm[f][i];
	}
	//cout <<"s "<< suma << f << c << endl;
	return suma;
}
int sumoColum(int** cm, int f, int c) {
	int suma = 0;
	for (int i = 0; i <= f; i++) {
		suma += cm[i][c];
	}
	//cout <<"s "<< suma << endl;
	return suma;
}

int supuestoNumMagico(int** cm, int n, int f, int c, int numMag) {
	if (f == 1 && c == 0) { //cuando ya esto en la sig fila
		int m = 0;
		for (int i = 0; i < n; i++) {
			m += cm[0][i];
		}
		//cout << "Nm:"<<numMag << f << c;
		return m;
	}
	else if (f == 0 ) {
		return 0;
	}
	else return numMag; //devuelvo el numMagico que tenia antes
}
void printfCuadrado(int n, int** c) {
	printf("cuadrado magico: \n");

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << c[i][j] << " ";
		}
		cout << "\n";

	}
}

void vectorConValores(int* vecNums, int tam) {
	for (int i = 0; i < tam; i++) {
		vecNums[i] = i + 1;
	}
}
void inicializar_Ceros(int** cm, int n) {

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cm[i][j] = 0;
		}
	}
}
void prinfvector(int* v, int n) {
	for (int i = 0; i < n; i++) {
		cout << v[i] << " ";
	}
	cout << "\n";
}