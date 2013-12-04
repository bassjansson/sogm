
#include <iostream>

using namespace std;

int * myFunction(int input[]) {
	return input;
}

int main() {

	// the array where we are going to point to
	int myarray[] = {5, 6, 7, 8, 9};

	// displaying the array
	cout << "myarray =";
	for(int i = 0; i < 5; i++) cout << " " << myarray[i];
	cout << endl;
	
	// the pointer, initialized using the function
	int * mypointer;
	mypointer = myFunction(myarray);

	// displaying the pointer
	cout << "mypointer =";
	for(int i = 0; i < 5; i++) cout << " " << mypointer[i];
	cout << endl;

}

