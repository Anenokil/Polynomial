#include <iostream>
#include "Polynomial.h"

typedef long double TC;

int main()
{
    Tmp<int> a;
    const unsigned degree_p = 3;
    //const unsigned degree_q = 2;
    const unsigned size_p = degree_p + 1;
    //const unsigned size_q = degree_q + 1;
    TC coefs_p[size_p] = { 2, 4, 5, 3 };
    //TC coefs_q[size_q] = { 3, 3, 1 };
    Polynom<TC> p(degree_p, coefs_p);
    Polynom<TC> q = 0;
    std::cin >> q;
    
    std::cout << "P  = " << p << std::endl;
    std::cout << "Q  = " << q << std::endl;
    std::cout << "P' = " << deriv(p) << std::endl;
    std::cout << "Q' = " << deriv(q) << std::endl;
    std::cout << "max deriv coef = " << max_deriv_coef(p, q) << std::endl;

    Polynom<TC> pq = p * q;
    std::cout << "P * Q  = " << pq << std::endl;
    std::cout << "P / Q  = " << p / q << std::endl;
    std::cout << "P % Q  = " << p % q << std::endl;
    std::cout << "int PQ = " << integr(pq) << std::endl;
}
