#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <iostream>
#include <string>
#include <cmath> /* log, sqrt */

/* return absolute value of number */
template <typename T>
T absol(T val)
{
    return val >= 0 ? val : -val;
}

/*template <typename T>
class Tmp
{
public:
    Tmp();
};*/

/* return array copy */
template <typename T>
T* arr_cp(T const* src, unsigned size)
{
    if (size == 0) {
        throw std::invalid_argument("size must be non-zero");
    }

    T* dst = new T[size];
    for (unsigned i = 0; i < size; ++i) {
        dst[i] = src[i];
    }
    return dst;
}

template <typename TCoef>
class Polynom
{
private:
    unsigned degree_; /* the degree of the polynomial */
    TCoef* coef_; /* coefficients of the polynomial */
    /* (coef_[0] + coef_[1] * x + ... + coef_[degree_] * x ^ degree_) */

    /* increase the degree by n and fill the leading coefficients with zeros */
    void add_zeroes(unsigned n)
    {
        TCoef* tmp = new TCoef[degree_ + 1 + n];
        
        /* copy low coefficients */
        for (unsigned i = 0; i <= degree_; ++i) {
            tmp[i] = coef_[i];
        }
        /* fill the leading coefficients with zeros */
        for (unsigned i = 0; i < n; ++i) {
            tmp[degree_ + 1 + i] = 0;
        }
        
        delete[] coef_;
        coef_ = tmp;
    }

public:
    /* copy constructor */
    Polynom(Polynom const& p) : degree_(p.degree_), coef_(arr_cp(p.coef_, p.degree_ + 1))
    {}
    
    /* conversion constructor
     * convert a number to 0-degree polynomial */
    Polynom(const TCoef n) : degree_(0)
    {
        coef_ = new TCoef[1];
        coef_[0] = n;
    }
    
    /* construct a monomial: coef * x ^ degree */
    Polynom(const TCoef coef, unsigned degree) : degree_(degree)
    {
        coef_ = new TCoef[degree + 1];
        coef_[degree] = coef;
    }

    /* construct a polynomial by given degree and array of coefficients */
    Polynom(unsigned degree, const TCoef coef[]) : degree_(degree)
    {
        /* if coefficients are not specified then set them to 0 */
        if (coef == nullptr) {
            coef_ = new TCoef[degree + 1];
            for (unsigned i = 0; i <= degree; ++i) {
                coef_[i] = 0;
            }
        } else {
            coef_ = arr_cp(coef, degree + 1);
        }
    }

    /* destructor */
    ~Polynom(void)
    {
        /* deallocate memory */
        delete[] coef_;
    }

    /* degree getter */
    unsigned degree(void) const
    {
        return degree_;
    }

    /* return string representation of coefficients */
    std::string coef_to_str(void) const
    {
        std::string res = std::to_string(coef_[0]);
        for (unsigned i = 1; i <= degree_; ++i) {
            res += ", " + std::to_string(coef_[i]);
        }
        return res;
    }

    /* return string representation of a polynomial */
    std::string to_str(const std::string var_name = "x") const
    {
        std::string res = "";
        bool is_first = 1;
        for (unsigned i = 0; i <= degree_; ++i) {
            if (coef_[i] != 0) {
                /* print sign of term */
                if (is_first) {
                    is_first = 0;
                    if (coef_[i] < 0) {
                        res += " - ";
                    }
                } else {
                    res += coef_[i] > 0 ? " + " : " - ";
                }
                /* print absolute value of term */
                if (absol(coef_[i]) != 1 || i == 0) {
                    res += std::to_string(absol(coef_[i]));
                }
                /* print variable */
                if (i == 1) {
                    res += var_name;
                } else if (i > 1) {
                    res += var_name + "^" + std::to_string(i);
                }
            }
        }
        /* if polynomial is zero */
        if (is_first) {
            res += "0";
        }
        return res;
    }

    /* assign this polynomial the value of another polynomial */
    Polynom& operator=(Polynom const& p)
    {
        /* check if this object and the given object are same objects */
        if (&p == this) {
            return *this;
        }
        
        /* copy fields values */
        degree_ = p.degree_;
        delete[] coef_;
        coef_ = arr_cp(p.coef_, p.degree_ + 1);
        /* return this object */
        return *this;
    }

    /* return this object */
    Polynom& operator+(void)
    {
        return *this;
    }
    
    /* return this object (const) */
    const Polynom& operator+(void) const
    {
        return *this;
    }

    /* return a copy of this polynomial multiplied by -1 */
    Polynom operator-(void) const
    {
        Polynom<TCoef> tmp(*this);
        tmp *= -1;
        return tmp;
    }

    Polynom& operator+=(Polynom const& p)
    {
        if (degree_ < p.degree_) {
            add_zeroes(p.degree_ - degree_);
        }
        for (unsigned i = 0; i <= p.degree_; ++i) {
            coef_[i] += p.coef_[i];
        }
        return *this;
    }

    Polynom& operator-=(Polynom const& p)
    {
        if (degree_ < p.degree_) {
            add_zeroes(p.degree_ - degree_);
        }
        for (unsigned i = 0; i <= p.degree_; ++i) {
            coef_[i] -= p.coef_[i];
        }
        return *this;
    }

    Polynom& operator*=(Polynom const& p)
    {
        *this = *this * p;
        return *this;
    }

    Polynom& operator/=(Polynom const& p)
    {
        *this = *this / p;
        return *this;
    }

    Polynom& operator%=(Polynom const& p)
    {
        *this = *this % p;
        return *this;
    }

    /* compare two polynomials */
    bool operator==(Polynom const& p) const
    {
        if (degree_ != p.degree_) {
            return 0;
        }
        for (unsigned i = 0; i <= degree_; ++i) {
            if (coef_[i] != p.coef_[i]) {
                return 0;
            }
        }
        return 1;
    }

    /* compare two polynomials */
    bool operator!=(Polynom const& p) const
    {
        return !(*this == p);
    }

    /* coefficient getter */
    TCoef& operator[](unsigned index) const
    {
        if (index > degree_) {
            throw std::out_of_range("index is out of range");
        }
        
        return coef_[index];
    }

    /* coefficient getter (const) */
    /*TCoef const& operator[](unsigned index) const
    {
        return (*this)[index];
    }*/

    /* return value of a polynomial in the given point */
    long double operator()(long double point) const
    {
        long double res = 0;
        long double pow_val = 1;
        for (unsigned i = 0; i <= degree_; ++i) {
            res += coef_[i] * pow_val;
            pow_val *= point;
        }
        return res;
    }
    
    /* return the maximal coefficient of a polynomial */
    TCoef max_coef(void)
    {
        TCoef max_c = coef_[0];
        for (unsigned i = 1; i <= degree_; ++i) {
            if (coef_[i] > max_c) {
                max_c = coef_[i];
            }
        }
        return max_c;
    }
};

/* return sum of two polynomials */
template <typename TCoef>
Polynom<TCoef> operator+(Polynom<TCoef> const& p1, Polynom<TCoef> const& p2)
{
    Polynom<TCoef> tmp = p1;
    return tmp += p2;
}

/* return difference of two polynomials */
template <typename TCoef>
Polynom<TCoef> operator-(Polynom<TCoef> const& p1, Polynom<TCoef> const& p2)
{
    Polynom<TCoef> tmp = p1;
    return tmp -= p2;
}

template <typename TCoef>
Polynom<TCoef> operator*(Polynom<TCoef> const& p1, Polynom<TCoef> const& p2)
{
    unsigned pow1 = p1.degree();
    unsigned pow2 = p2.degree();
    unsigned pow12 = pow1 + pow2;
    Polynom<TCoef> tmp(pow12, nullptr);
    for (unsigned i = 0; i <= pow1; ++i) {
        for (unsigned j = 0; j <= pow2; ++j) {
            tmp[i + j] += p1[i] * p2[j];
        }
    }
    return tmp;
}

template <typename TCoef>
Polynom<TCoef> operator/(Polynom<TCoef> const& p1, Polynom<TCoef> const& p2)
{
    unsigned pow1 = p1.degree();
    unsigned pow2 = p2.degree();
    unsigned pow12 = pow1 - pow2;
    Polynom<TCoef> ans(pow12, nullptr);

    Polynom<TCoef> rem = p1;
    for (unsigned i = 0; i <= pow12; ++i) {
        Polynom<TCoef> tmp_mult(pow12 - i, nullptr);
        ans[pow12 - i] = tmp_mult[pow12 - i] = rem[pow1 - i] / p2[pow2];
        rem -= p2 * tmp_mult;
    }
    return ans;
}

template <typename TCoef>
Polynom<TCoef> operator%(Polynom<TCoef> const& p1, Polynom<TCoef> const& p2)
{
    unsigned pow1 = p1.degree();
    unsigned pow2 = p2.degree();
    unsigned pow12 = pow1 - pow2;
    Polynom<TCoef> ans(pow12, nullptr);

    Polynom<TCoef> rem = p1;
    for (unsigned i = 0; i <= pow12; ++i) {
        Polynom<TCoef> tmp_mult(pow12 - i, nullptr);
        ans[pow12 - i] = tmp_mult[pow12 - i] = rem[pow1 - i] / p2[pow2];
        rem -= p2 * tmp_mult;
    }
    return rem;
}

/* write polynomial to ostream */
template <typename TCoef>
std::ostream& operator<<(std::ostream& strm, Polynom<TCoef> const& p)
{
    strm << p.to_str();
    return strm;
}

/* write polynomial to ostream */
template <typename TCoef>
std::istream& operator>>(std::istream& strm, Polynom<TCoef> & p)
{
    unsigned degree;
    strm >> degree;
    
    Polynom<TCoef> tmp(degree, nullptr);
    for (unsigned i = 0; i <= degree; ++i) {
        strm >> tmp[i];
    }

    p = tmp;
    return strm;
}
/*{
    strm >> p.degree_;
    delete[] p.coef_;
    p.coef_ = new TCoef[p.degree_ + 1];
    for (unsigned i = 0; i <= p.degree_; ++i) {
        strm >> p.coef_;
    }
    return strm;
}*/

/* return n-th power of a polynomial */
template <typename T>
Polynom<T> pw(Polynom<T> const& p, unsigned n)
{
    Polynom<T> res = 1;
    for (unsigned i = 0; i < n; ++i) {
        res *= p;
    }
    return res;
}

/* return 1-st derivative of a polynomial */
template <typename T>
Polynom<T> deriv(Polynom<T> const& p)
{
    unsigned degree = p.degree();

    if (degree == 0) {
        Polynom<T> res = 0;
        return res;
    }

    Polynom<T> res(degree - 1, nullptr);
    for (unsigned i = 0; i < degree; ++i) {
        res[i] = p[i + 1] * (i + 1);
    }
    return res;
}

/* return n-th derivative of a polynomial */
template <typename T>
Polynom<T> deriv(Polynom<T> const& p, unsigned n)
{
    Polynom<T> res = p;
    for (unsigned i = 0; i < n; ++i) {
        res = deriv(res);
    }
    return res;
}

/* return integral of a polynomial */
template <typename T>
Polynom<T> integr(Polynom<T> const& p)
{
    unsigned degree = p.degree();

    if (degree == 0) {
        if (p[0] == 0) {
            Polynom<T> res = 0;
            return res;
        }

        Polynom<T> res(p[0], 1);
        return res;
    }

    Polynom<T> res(degree + 1, nullptr);
    for (unsigned i = 0; i <= degree; ++i) {
        res[i + 1] = p[i] / (i + 1);
    }
    return res;
}

/* integrate polynomial from left to right limit */
template <typename T>
long double integr(Polynom<T> const& p, long double l, long double r)
{
    Polynom<T> integral = integr(p);
    return integral(r) - integral(l);
}

/* return the maximal coefficient of two polynomials derivatives */
template <typename TCoef>
TCoef max_deriv_coef(Polynom<TCoef> const& p1, Polynom<TCoef> const& p2)
{
    const TCoef max1 = deriv(p1).max_coef();
    const TCoef max2 = deriv(p2).max_coef();
    return max2 > max1 ? max2 : max1;
}

#endif
