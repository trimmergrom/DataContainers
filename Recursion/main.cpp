#include<iostream>

void elevator(int floor)
{
    if (floor == 0)
    {
        std::cout << "You at andeground" << std::endl;
        return;
    }
    //std::cout << "You at " << floor << "floor" << std::endl;
    elevator(floor - 1);
    std::cout << "You at " << floor << "floor" << std::endl;
}
int fibonacci(double number)
{
    if (number == 0) return 0;
    if (number == 1) return 1;
    return (fibonacci(number - 1) + fibonacci(number - 2));
}
double f_exp(double base, int exp)
{
    /*if (exp < 0) return f_exp(1 / base, -exp);
    if (exp == 0) return 1;
    else return base*f_exp(base, exp -1);*/
    /*if (exp == 0)return 1;
    if (exp > 0)return base * f_exp(base, exp - 1);
    if (exp < 0)return 1/base *f_exp(base, exp + 1);*/
   return exp == 0 ? 1 : exp > 0 ? base*f_exp(base, exp - 1) : f_exp(1/base, -exp);
}

long long int fctr(int number)
{
   /* if (number == 0) return 1;
    if (number < 0) return 0;
    else return number * fctr(number - 1);*/
    return number == 0 ? 1 : number * fctr(number - 1);
}

#define HOME_WORK
//#define ELEVATOR
void main()
{
   
#ifdef ELEVATOR
    int floor;
    std::cout << "Enter yuor floor: "; std::cin >> floor;
    elevator(floor);
#endif // ELEVATOR


#ifdef HOME_WORK
    double N;
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
#endif // HOME_WORK

}