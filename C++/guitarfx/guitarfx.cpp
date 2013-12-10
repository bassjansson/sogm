#include <iostream>

#define BUFFERSIZE 10

using namespace std;

// Class
class Amplifier {

public:
	Amplifier();
	void showLevel();

private:
	long level;

};

// Constructor
Amplifier::Amplifier() {
	level = 5;
}

// Function
void Amplifier::showLevel() {
	cout << "Amplifier level: " << level << endl;
}

// Main
int main() {
	Amplifier amp;
 	amp.showLevel();
}

