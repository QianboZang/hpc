#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include "fraction_toolbox.hpp"

using namespace std;

// read command line arguments
static void readcmdline(fraction & frac, int argc, char* argv[])
{
    if (argc!=3)
    {
        printf("Usage: n d\n");
        printf("  n        numerator of fraction\n");
        printf("  d        denominator of fraction\n");
        exit(1);
    }

    // read n
    frac.num = atoi(argv[1]);

    // read d
    frac.denom = atoi(argv[2]);
}

static void test23467(int argc, char* argv[])
{
    //TODO: implement function
    fraction frac;
    readcmdline(frac, argc, argv);

    cout << "#### 2 ####" << endl;
    fraction square_frac = square_fraction(frac);
    cout << "square_frac = ";
    print_fraction(square_frac);
    cout << "frac = ";
    print_fraction(frac);
    cout << endl;

    cout << "#### 3 ####" << endl;
    square_fraction_inplace(frac);
    cout << "frac = ";
    print_fraction(frac);
    cout << endl;
    
    cout << "#### 4 ####" << endl;
    double value = fraction2double(frac);
    cout << "floating value = " << value << endl;
    cout << endl;

    cout << "#### 6 ####" << endl;
    int common = gcd(frac);
    cout << "greatest common divisor  = " << common << endl;
    cout << endl;

    cout << "#### 7 ####" << endl;
    reduce_fraction_inplace(frac);
    cout << "reduced form fraction = ";
    print_fraction(frac);
    cout << endl;
}

static void test5()
{
    //TODO: implement function
    int a, b;
    cout << "input first number: " << endl;
    cin >> a;
    cout << "input second number: " << endl;
    cin >> b;
    int common = gcd(a, b);
    cout << "greatest common divisor  = " << common << endl;
    cout << endl;
}

static void test_array_functions(int n)
{
    //TODO: implement function
    fraction *p = new fraction [n];
    fill_fraction_array(p, n);
    // cout << "The list of fractions = " << endl;
    // print_fraction_array(p, n);
    // cout << endl;

    fraction sum_frac = sum_fraction_array(p, n);
    cout << "The exact sum = " << endl;
    print_fraction(sum_frac);
    cout << endl;

    double approx_sum = sum_fraction_array_approx(p, n);
    cout << "The approximate sum = " << approx_sum << endl;
    //TODO: find n for which sum function breaks. Explain what is happening.
    // The max integer is (2^32) according to 32-bit restriction.
    // So n(n+1) < 2^32
    // n is approximate to 65536. And as I chech, the function breaks.
}

static void test_toolbox(int argc, char* argv[])
{
    cout << "\n===============  test23467  =============== " << endl;
    test23467(argc, argv);

    cout << "\n=================  test5  ================= " << endl;
    test5();

    cout << "\n==========  test_array_functions  ========= " << endl;
    int n = 5;
    // n = 65536, breaks
    test_array_functions(n);
}

int main(int argc, char* argv[])
{
    test_toolbox(argc, argv);
    
    return 0;
}