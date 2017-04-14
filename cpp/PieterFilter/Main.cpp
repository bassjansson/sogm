
#include <iostream>
#include "Filter.h"

using namespace std;


int main (int argc, const char* argv[])
{
    int sampleRate = 48000;

	Filter filter(sampleRate);

    filter.addZero(3000,  1);
    filter.addZero(6000,  1);
    filter.addZero(12000, 0.3);
    filter.addZero(24000, 0.15);

    filter.addPole(0,    0.72);
    filter.addPole(4500, 0.93);

    int window = 1024;
    float* response;

    if (argc < 2)
        response = filter.getFrequencyResponse(window);
    else
        response = filter.testFrequencyResponse(window);

    for (int i = 0; i < window; i++)
    {
        float frequency = (float)i / window * sampleRate / 2;
        cout << frequency << "\t" << response[i] << "\n";
    }

    /*
    cout << "\n";

    float* zeros = filter.getZeroCoefficients();

    for (int i = 0; i < filter.getZeroSize(); i++)
    {
        clog << i << ":\t" << zeros[i] << "\n";
    }

    clog << endl;

    float* poles = filter.getPoleCoefficients();

    for (int i = 0; i < filter.getPoleSize(); i++)
    {
        clog << i << ":\t" << poles[i] << "\n";
    }
     */
}
