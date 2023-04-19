// Ej6_billetes.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <vector>

using namespace std;

vector<int> billetes_cambio(vector <int> B, int i, int j, int c);
int main()
{
	int c = 14;
	vector <int> B = { 2,3,5,10,20,20 };
	vector <int> b;
	b.push_back(9);
	
		return 0;
}

vector<int> billetes_cambio(vector <int> B, int i, int min, int exceso, int c, vector<int> cambio) {

	if (B[i] <= c) {
		//mido el exceso
		if (suma(cambio) < c){
			cambio.push_back(B[i]);
		}
		else if (suma(cambio) == c) {
			
		}
		else {
			cambio.pop_back();
		}
		
		

	}
}
int suma(vector<int> v) {
	int sum = 0;
	for (int i : v) {
		sum += i;
	}
	return sum;
}