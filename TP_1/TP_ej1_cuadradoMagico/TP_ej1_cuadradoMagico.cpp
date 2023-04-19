// TP_ej1_cuadradoMagico.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <ctime>

using namespace std;

void vectorConValores(int* vecNums, int tam);
void inicializar_Ceros(int** cm, int n);
void printfCuadrado(int n, int** c);

int sumoColum(int** cm, int f, int c);
int sumoFila(int** cm, int f, int c);

bool sumaParcialValida(int** cm, int n, int f, int c, int numMag, int k);
int cuadradoMagico(int**& cm, int orden, int f, int c, int numMag, int* vecNums, int* cantMagico, int k);

void prinfvector(int* v, int n);

bool sumoFilaVal(int** cm, int f, int c, int n , int numM);
bool sumoColumVal(int** cm, int f, int c, int n, int numMag);

bool sumasParciales(int** cm, int f, int c, int n, int numM);

int main()
{
	int n = 0;
	int k = 0;
	//ingreso el orden y el kesimo
	cin >> n;
	cin >> k;

	int* cantCuadradosMag = new int();
	*cantCuadradosMag = 0;
	int tam = n * n;
	int** cm;
	// asignar memoria dinámica para alojar la matriz
	cm = new int* [n]; // alojar n punteros a entero
	for (int i = 0; i < n; i++) {
		cm[i] = new int[n]; // alojar n enteros en cada fila
	}
	//uso un vector con los numeros disponibles para el cuadrado magico
	int* vecNums = new int[tam];

	inicializar_Ceros(cm, n);
	vectorConValores(vecNums, tam);

	clock_t inicio = clock();

	int res = 0;
	int numMag = (pow(n, 3) + n) / 2;

	res = cuadradoMagico(cm, n, 0, 0, numMag, vecNums, cantCuadradosMag, k);

	if (res != 0) cout << "-1" << endl;
	
	clock_t fin = clock(); // tiempo de fin
	double duracion = double(fin - inicio) / CLOCKS_PER_SEC; // duración en segundos

	cout << "tiempo de ejecucion:" << duracion << endl;


	return 0;
}


int cuadradoMagico(int**& cm, int n, int f, int c, int numMag, int* vecNums, int* cantMagico, int k) {
	int x = 0;
	for (int i = 0; i < n * n; i++) {
		if (*cantMagico == k) {		
			return 0;	
		}
		if (*cantMagico < k) {

			if (vecNums[i] != 0) { //para no repetir, marco con ceros los que ya use
				x = vecNums[i];
				if (sumaParcialValida(cm, n, f, c, numMag, x)) { //poda				
					cm[f][c] = x;
					vecNums[i] = 0;

					if (c < n - 1) cuadradoMagico(cm, n, f, c + 1, numMag, vecNums, cantMagico, k);
					else if (f < n - 1) cuadradoMagico(cm, n, f + 1, 0, numMag, vecNums, cantMagico, k);

					//compruebo si termino el cuadrado magico
					if (f == n - 1 && c == n - 1) { //completo el ult elem con exito
						*cantMagico += 1;

						if (*cantMagico == k) { //imprimo adentro, no encontre forma de hacerlo fuera

							printfCuadrado(n, cm);
							return 0;
						}

					}

					cm[f][c] = 0; //si volvio es que ese camino no funciono
					vecNums[i] = i + 1; //"saco el cero"

				}

			}

		}
	}
}

bool sumaParcialValida(int** cm, int n, int f, int c, int numMag, int k) {
	bool res = true;
	
		cm[f][c] = k; //cuando entro a esta f aun no igual a k, ya que estoy evaluando, por eso lo igualo aca TEMPORALMENTE

		if (f == n - 1 && c == 0) {
			res = sumoColumVal(cm, f, c, n, numMag);
		}
		else if (f == n - 1 && c == n - 1) {
			res = sumoFilaVal(cm, f, c, n, numMag);
		}
		else if (c == n - 1) { //estoy al fina,l de una fila
			res = (sumoFila(cm, f, c) == numMag) && (sumoColum(cm, f, c) < numMag);
		}
		else if (f == n - 1) { //estoy al final de una colum
			res = (sumoColum(cm, f, c) == numMag) && (sumoFila(cm, f, c) < numMag);
			
		}
		else if (c < n-1) {//suma parcial, hasta donde llegue c en la fila f

			res = sumasParciales(cm, f, c, n, numMag);
		}
		
		cm[f][c] = 0;
		return res;
}

bool sumoFilaVal(int** cm, int f, int c, int n, int numM) {
	int sumac = 0;
	int suma = 0;
	int diag = 0;
	for (int i = 0; i < n; i++) {
		suma += cm[f][i];
		sumac += cm[i][c];
		diag += cm[i][i];
	}
	return sumac == numM && suma == numM && diag == numM;
	
}
bool sumoColumVal(int** cm, int f, int c, int n, int numM) {
	int suma = 0;
	int diag = 0;
	for (int i = 0; i < n; i++) {
		suma += cm[i][c];
		diag += cm[i][(n - 1) - i];
	}
	return suma == numM && diag == numM;
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

bool sumasParciales(int** cm, int f, int c, int n, int numM) {
	int suma = 0; int suma1 = 0; int suma2 = 0; int sumaf = 0;

	for (int i = 0; i <= c; i++) { //sumo fila
		sumaf += cm[f][i];
	}
	for (int i = 0; i <= f; i++) {//sumo colum y diagonales
		suma += cm[i][c];
		suma1 += cm[i][i];
		suma2 += cm[i][(n - 1) - i];
	}
	return (sumaf < numM) && (suma < numM) && (suma1 < numM) && (suma2 < numM);
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