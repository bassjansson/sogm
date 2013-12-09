// Dit is mijn kerstboom programma

#include <iostream>
#include "kerstboom.h"

using namespace std;

void maakBoom(unsigned int grootte, int ballen) {
	for(int i = 1; i <= grootte; i++) {
		string lijn = "";
		for(int r = 0; r < grootte-i; r++) lijn += " ";
		for(int r = 0; r < i*2-1  ; r++) {
			int randnum = random()*ballen/RAND_MAX;
			if(randnum == 0) 	  lijn += "O";
			else if(randnum == 1) lijn += "@";
			else 				  lijn += "*";
		}
		cout << lijn << endl;
	}
	for(int i = 1; i <= grootte/3; i++) {
		string lijn = "";
		for(int r = 0; r < grootte-grootte/3; r++) lijn += " ";
		for(int r = 0; r < grootte/3*2-1; r++) lijn += "|";
		cout << lijn << endl;
	}
}

int main() {
	unsigned int grootte = 0;
	unsigned int hoeveel = 0;
	unsigned int ballen  = 0;
	
	cout << "Hoeveel bomen moeten er zijn? ";
	cin >> hoeveel;
	cout << "Hoe groot moeten de kerstbomen zijn? ";
	cin >> grootte;
	cout << "Hoe groot moet de randomness van de ballen zijn? ";
	cin >> ballen;

	for(int i = 0; i < hoeveel; i++) {
		cout << endl;
		maakBoom(grootte, ballen);
	}

	return 0;
}
