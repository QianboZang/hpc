#include <iostream>
#include<cmath>
#include "fraction_toolbox.hpp"


void print_fraction(fraction frac)
{
    std::cout << frac.num << '/' << frac.denom << std::endl;
}


void print_fraction_array(fraction frac_array[], int n)
{
    std::cout << "[ " << frac_array[0].num << '/' << frac_array[0].denom << std::endl;
    for (int i = 1; i < n-1; i++)
    {
        std::cout << "  ";
        print_fraction(frac_array[i]);
    }
    std::cout << "  " << frac_array[n-1].num << '/' << frac_array[n-1].denom << " ]" << std::endl;
}


fraction square_fraction(fraction frac)
{
    //TODO: implement function 2
    fraction new_frac = 
    {
        frac.num * frac.num,
        frac.denom * frac.denom
    };

    return new_frac;
}


// TODO: implement function 3
void square_fraction_inplace(fraction & frac) 
{
    frac.num = frac.num * frac.num;
    frac.denom = frac.denom * frac.denom;
}


double fraction2double(fraction frac)
{
    // TODO: implement function 4
    double value = (double)frac.num / (double)frac.denom;

    return value;
}


int gcd(int a, int b)
{
    // TODO: implement function 5
    // recursive
    if (b == 0)
    {
        return a;
    }
    else
    {
        return gcd(b, a % b);
    }
}


// TODO: implement function 6
// iterative
int gcd(fraction frac)
{
    int a = (int)frac.num, b = (int)frac.denom;
    int temp;

    while (b != 0)
    {
        temp = b;
        b = a % b;
        a = temp;
    }

    return a;
}


void reduce_fraction_inplace(fraction & frac)
{
    // TODO: implement function 7
    int common = gcd(frac);
    frac.denom = frac.denom / common;
    frac.num = frac.num / common;
    // TODO: add short comment to explain which of the gcd() functions your code is calling
    // I choose to use second gcd function because it is implemented by iteration.
    // Function calls are time and space consuming. 
    // For each function call, space needs to be allocated on the memory stack to hold parameters, return addresses, and temporary variables. 
    // So recursion is not as efficient to implement as a iteration.
}

fraction add_fractions(fraction frac1, fraction frac2)
{
    // TODO: implement function 8
    fraction new_frac = 
    {
        frac1.num * frac2.denom + frac2.num * frac1.denom,
        frac1.denom * frac2.denom
    };
    int common = gcd(new_frac);
    new_frac.denom = new_frac.denom / common;
    new_frac.num = new_frac.num / common;

    return new_frac;
}

double sum_fraction_array_approx(fraction frac_array[], int n)
{
    //TODO: implement function 9
    double temp = 0;
    for(int i= 0; i < n; ++i)
    {
        temp = temp + fraction2double(frac_array[i]);
    }

    return temp;
    //TODO: add short comment to explain why this function is approximate
    // Many floating point numbers that can easily be represented in decimal cannot be represented as binary floating point.
    // For example: float number "1.2" can only be represent approximately 
    //     with a binary number 1.0011001100110011001100110011001100110011001100110011.
    // So there is an error when doing floating point operations.
}


//TODO: implement function 10
fraction sum_fraction_array(fraction *p, int n)
{
    fraction temp = {0, 1};
    for (int i = 0; i < n; ++i)
    {
        temp = add_fractions(temp, p[i]);
    }

    return temp;
}


void fill_fraction_array(fraction frac_array[], int n)
{
    fraction temp_frac;
    temp_frac.num = 1;
    for (int i = 1; i <= n; ++i)
    {
        temp_frac.denom = i * (i+1);
        frac_array[i-1] = temp_frac;
    }
}
