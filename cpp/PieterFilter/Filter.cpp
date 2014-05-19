
#include "Filter.h"
#include <cmath>


//==================================================================
Filter::Filter(int sampleRate)
{
    this->sampleRate = sampleRate;
    
    zeros = new ComplexVector();
    poles = new ComplexVector();
    
    zeroBuffer.position     = 0;
    zeroBuffer.size         = 1;
    zeroBuffer.buffer       = new float[zeroBuffer.size];
    zeroBuffer.coefficients = getCoefficients(*zeros);
    
    poleBuffer.position     = 0;
    poleBuffer.size         = 1;
    poleBuffer.buffer       = new float[poleBuffer.size];
    poleBuffer.coefficients = getCoefficients(*poles);
}

Filter::~Filter()
{
    this->zeros->clear();
    delete this->zeros;
    
    this->poles->clear();
    delete this->poles;
    
    delete[] zeroBuffer.buffer;
    delete[] zeroBuffer.coefficients;
    
    delete[] poleBuffer.buffer;
    delete[] poleBuffer.coefficients;
}

//==================================================================
void Filter::addZero (float frequency, float resonance)
{
    if (frequency <= 0.0f)
    {
        addZero(polToCar(newComplex(resonance, 0.0f)));
    }
    else
    {
        float theta = frequency / sampleRate * 2*M_PI;
        
        addZero(polToCar(newComplex(resonance,  theta)));
        addZero(polToCar(newComplex(resonance, -theta)));
    }
}

void Filter::addPole (float frequency, float resonance)
{
    if (frequency <= 0.0f)
    {
        addPole(polToCar(newComplex(resonance, 0.0f)));
    }
    else
    {
        float theta = frequency / sampleRate * 2*M_PI;
        
        addPole(polToCar(newComplex(resonance,  theta)));
        addPole(polToCar(newComplex(resonance, -theta)));
    }
}

void Filter::addZero (Complex coordinate)
{
    zeros->push_back(coordinate);
    
    delete[] zeroBuffer.buffer;
    delete[] zeroBuffer.coefficients;
    
    zeroBuffer.position     = 0;
    zeroBuffer.size         = (int)zeros->size() + 1;
    zeroBuffer.buffer       = new float[zeroBuffer.size];
    zeroBuffer.coefficients = getCoefficients(*zeros);
}

void Filter::addPole (Complex coordinate)
{
    poles->push_back(coordinate);
    
    delete[] poleBuffer.buffer;
    delete[] poleBuffer.coefficients;
    
    poleBuffer.position     = 0;
    poleBuffer.size         = (int)poles->size() + 1;
    poleBuffer.buffer       = new float[poleBuffer.size];
    poleBuffer.coefficients = getCoefficients(*poles);
}

void Filter::setCoordinates (ComplexVector& zeros, ComplexVector& poles)
{
    this->zeros->clear();
    delete this->zeros;
    
    this->poles->clear();
    delete this->poles;
    
    this->zeros = &zeros;
    this->poles = &poles;
    
    delete[] zeroBuffer.buffer;
    delete[] zeroBuffer.coefficients;
    
    delete[] poleBuffer.buffer;
    delete[] poleBuffer.coefficients;
    
    zeroBuffer.position     = 0;
    zeroBuffer.size         = (int)zeros.size() + 1;
    zeroBuffer.buffer       = new float[zeroBuffer.size];
    zeroBuffer.coefficients = getCoefficients(zeros);
    
    poleBuffer.position     = 0;
    poleBuffer.size         = (int)poles.size() + 1;
    poleBuffer.buffer       = new float[poleBuffer.size];
    poleBuffer.coefficients = getCoefficients(poles);
}

//==================================================================
void Filter::setZeroCoefficients (float* coefficients, int size)
{
    this->zeros->clear();

    delete[] zeroBuffer.buffer;
    delete[] zeroBuffer.coefficients;
    
    zeroBuffer.position     = 0;
    zeroBuffer.size         = size;
    zeroBuffer.buffer       = new float[zeroBuffer.size];
    zeroBuffer.coefficients = coefficients;
}

void Filter::setPoleCoefficients (float* coefficients, int size)
{
    this->poles->clear();
    
    delete[] poleBuffer.buffer;
    delete[] poleBuffer.coefficients;
    
    poleBuffer.position     = 0;
    poleBuffer.size         = size;
    poleBuffer.buffer       = new float[poleBuffer.size];
    poleBuffer.coefficients = coefficients;
}

//==================================================================
float* Filter::getZeroCoefficients()
{
    return zeroBuffer.coefficients;
}

float* Filter::getPoleCoefficients()
{
    return poleBuffer.coefficients;
}

int Filter::getZeroSize()
{
    return zeroBuffer.size;
}

int Filter::getPoleSize()
{
    return poleBuffer.size;
}

//==================================================================
float* Filter::getFrequencyResponse (int windowSize)
{
    int binSize = windowSize;
    windowSize *= 2;
    
    float* signal   = new float[windowSize];
    float* response = new float[binSize];
    
    for (int bin = 0; bin < binSize; bin++)
    {
        for (int i = 0; i < windowSize; i++)
            signal[i] = cosf((float)i / windowSize * 2*M_PI * bin);
        
        filter(signal, windowSize);
        
        float RMS = 0.0f;
        
        for (int i = 0; i < windowSize; i++)
            RMS += signal[i] * signal[i];
        
        RMS = sqrtf(RMS / windowSize);
        
        response[bin] = 20.0f * log10f(RMS);
    }
    
    delete[] signal;
    
    return response;
}

//==================================================================
float Filter::filter (float input)
{
    float output = input * zeroBuffer.coefficients[0];
    
    int size;
    if (zeroBuffer.size > poleBuffer.size) size = zeroBuffer.size;
    else                                   size = poleBuffer.size;
    
    zeroBuffer.buffer[zeroBuffer.position] = input;
    
    for (int i = 1; i < size; i++)
    {
        if (i < zeroBuffer.size)
        {
            int position = (zeroBuffer.position + zeroBuffer.size - i) % zeroBuffer.size;
            output += zeroBuffer.coefficients[i] * zeroBuffer.buffer[position];
        }
        
        if (i < poleBuffer.size)
        {
            int position = (poleBuffer.position + poleBuffer.size - i) % poleBuffer.size;
            output -= poleBuffer.coefficients[i] * poleBuffer.buffer[position];
        }
    }
    
    poleBuffer.buffer[poleBuffer.position] = output;
    
    zeroBuffer.position = (zeroBuffer.position + 1) % zeroBuffer.size;
    poleBuffer.position = (poleBuffer.position + 1) % poleBuffer.size;
    
    return output;
}

void Filter::filter (float* buffer, int size)
{
    for (int i = 0; i < size; i++)
        buffer[i] = filter(buffer[i]);
}

//==================================================================
Complex Filter::getCoefficient (Complex* coordinates, int size, int coefficient, int position)
{
    if (coefficient <= 0)   return newComplex(1, 0);
    if (coefficient > size) return newComplex(0, 0);
	
    return (coordinates[position] * newComplex(-1, 0)
            * getCoefficient(coordinates, size - 1, coefficient - 1, position + 1)
            + getCoefficient(coordinates, size - 1, coefficient    , position + 1));
}

float* Filter::getCoefficients (ComplexVector& coordinates)
{
    int coefficientsSize = (int)coordinates.size() + 1;
    float* coefficients  = new float[coefficientsSize];
    
    for (int i = 0; i < coefficientsSize; i++)
        coefficients[i] = getCoefficient(coordinates.data(), (int)coordinates.size(), i, 0).real;
    
    return coefficients;
}
