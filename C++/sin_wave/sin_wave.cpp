
#include <iostream>
#include <cmath>

using namespace std;

int main() {
	int window = 1024;

	for(int i = 0; i < window; i++) {
		cout << sin((double)i / window * 2*M_PI) << endl;
	}
}

