
#include "Complex.h"
#include <cmath>


Complex newComplex (float real, float imag)
{
	Complex result;

	result.real = real;
	result.imag = imag;

	return result;
}


Complex operator+ (Complex left, Complex right)
{
	Complex result;

	result.real = left.real + right.real;
	result.imag = left.imag + right.imag;

	return result;
}

Complex operator- (Complex left, Complex right)
{
	Complex result;

	result.real = left.real - right.real;
	result.imag = left.imag - right.imag;

	return result;
}

Complex operator* (Complex left, Complex right)
{
	Complex result;

	result.real = left.real * right.real - left.imag * right.imag;
	result.imag = left.real * right.imag + left.imag * right.real;

	return result;
}

Complex operator/ (Complex left, Complex right)
{
    Complex result;

    float divider = right.real * right.real + right.imag * right.imag;

	result.real = (left.real * right.real + left.imag * right.imag) / divider;
	result.imag = (left.imag * right.real - left.real * right.imag) / divider;

	return result;
}


Complex carToPol (Complex car)
{
	Complex result;

	result.real = sqrtf(car.real * car.real + car.imag * car.imag);
	result.imag = atan2(car.real, car.imag);

    return result;
}

Complex polToCar (Complex pol)
{
	Complex result;

	result.real = pol.real * cosf(pol.imag);
	result.imag = pol.real * sinf(pol.imag);

    return result;
}


Complex complexPow (Complex input, int power)
{
    Complex result = newComplex(1, 0);

    if (power >= 0)
    {
        for (int i = 0; i < power; ++i)
            result = result * input;
    }
    else
    {
        for (int i = 0; i > power; --i)
            result = result / input;
    }

    return result;
}
