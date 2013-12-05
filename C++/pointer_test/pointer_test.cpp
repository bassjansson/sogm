
#include <iostream>

using namespace std;

// int   v   =  int
// int  *p   =  int*
// int  *p   =  int[]
// int   a[] =  int[]
// int   a[] = {int   , int  }
// int  *p[] = {int*  , int* }
// int  *p[] = {int[] , int[]}
// int **p   =  int*[]
// int **p   =  int**

int * mypointer[] = {new int[6], new int[6]};

int ** myFunction() {
	for(int i = 0; i < 6; i++) {
		mypointer[0][i] = i;
		mypointer[1][i] = -i;
	}
	return mypointer;
}

int main() {
	
	int ** mainpointer = myFunction();
	
	// displaying the pointer
	cout << "mainpointer[0] =";
	for(int i = 0; i < 6; i++) cout << " " << mainpointer[0][i];
	cout << endl;

	cout << "mainpointer[1] =";
	for(int i = 0; i < 6; i++) cout << " " << mainpointer[1][i];
	cout << endl;
}

