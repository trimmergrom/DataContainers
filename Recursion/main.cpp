#include<iostream>

int fibonacci(int number)
{
    if (number == 0) return 0;
    if (number == 1) return 1;
    return (fibonacci(number - 1) + fibonacci(number - 2));
}
double f_exp(int base, int exp)
{
    if (exp == 0)return 1;
    if (exp > 0)return base * f_exp(base, exp - 1);
    if (exp < 0)return 0;    
}

long long int fctr(int number)
{
    if (number < 0) return 0;
    if (number == 0) return 1;
    else return number * fctr(number - 1);
}

void main()
{
    int N;
    int exp;
    std::cout << "Enter N: "; std::cin >> N;
    for (int count = 0; count < N; ++count)
    {
        std::cout << fibonacci(count) << "\t";
    }
    std::cout << std::endl;
    std::cout << "Enter exponent: "; std::cin >> exp;
    std::cout << "pow( " << N << " , " << exp << " ) = " << f_exp(N, exp) << std::endl;
    std::cout << N << "! = " << fctr(N) << std::endl;  
}