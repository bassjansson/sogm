// Dit is mijn kerstboom programma

#include <iostream>
#include "kerstboom.h"

using namespace std;

void maakBoom(unsigned int grote) {
	for(int i = 1; i <= grote; i++) {
		string lijn = "";
		for(int r = 0; r < grote-i; r++) lijn += " ";
		for(int r = 0; r < i*2-1  ; r++) lijn += "*";
		cout << lijn << endl;
	}
	for(int i = 1; i <= grote/3; i++) {
		string lijn = "";
		for(int r = 0; r < grote-grote/3; r++) lijn += " ";
		for(int r = 0; r < grote/3*2-1; r++) lijn += "|";
		cout << lijn << endl;
	}
}

int main() {
	unsigned int grote = 0;
	
	cout << "Hoe groot de kerstboom? " << endl;
	cin >> grote;
	cout << endl;

	maakBoom(grote);

	return 0;
}
