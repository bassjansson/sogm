
#pragma once

#include "Complex.h"


struct FilterBuffer
{
	float* coefficients;
	float* buffer;
    int    size;
	int    position;
};


class Filter
{
public:
	//==================================================================
	 Filter(int sampleRate);
	~Filter();

	//==================================================================
    void addZero (float frequency, float resonance);
    void addPole (float frequency, float resonance);
	void addZero (Complex coordinate);
	void addPole (Complex coordinate);
	void setCoordinates (ComplexVector& zeros, ComplexVector& poles);
	
	//==================================================================
	void setZeroCoefficients (float* coefficients, int size);
	void setPoleCoefficients (float* coefficients, int size);

	//==================================================================
	float* getZeroCoefficients();
	float* getPoleCoefficients();
	int    getZeroSize();
	int    getPoleSize();
	
	//==================================================================
	float* getFrequencyResponse (int windowSize);

	//==================================================================
	float filter (float input);
	void  filter (float* buffer, int size);

protected:
	//==================================================================
	Complex getCoefficient  (Complex* coordinates, int size, int coefficient, int position);
	float*  getCoefficients (ComplexVector& coordinates);

private:
	//==================================================================
    int sampleRate;
    
	ComplexVector* zeros;
	ComplexVector* poles;

	FilterBuffer zeroBuffer;
	FilterBuffer poleBuffer;
};
