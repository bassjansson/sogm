// guitarfx.cpp

#include <iostream>
#include "amplifier.h"

using namespace std;

int main() {
	Amplifier amp;

	amp.level = 0.5;
	amp.process();
}

