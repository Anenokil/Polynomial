In the module `Polynomial` a template class `Polynom<T>` is declared.
The class provides following operations with polynomials and numbers:
- Add (`+`), subtract (`-`), multiply (`*`), divide with remainder (`/`) and get remainder (`%`);
- Comparaison (`==`, `!=`);
- Print a polynomial (`<<`);
- Calculate value of a polynomial in the given point (`()`);
- Get a coefficient of a polynomial (`[]`). The coefficient is returned by reference and can be changed.

The class provides following methods:
- `.degree()` \
  Return a degree of a polynomial.
- `.coef_to_str()` \
  Return a string, contains coefficients of a polynomial.
- `.to_str(const string var_name = "x")` \
  Return a string representation of a polynomial with the given variable name.
- `.max_coef()` \
  Return the maximal coefficient of a polynomial.

There are following functions with polynomials:
- `Polynom<T> pw(Polynom<T> const& p, unsigned n)` \
  Return the n-th power of a polynomial.
- `Polynom<T> deriv(Polynom<T> const& p, unsigned n = 1)` \
  Return the n-th derivative of a polynomial.
- `Polynom<T> integr(Polynom<T> const& p)` \
  Return an integral of a polynomial.
- `long double integr(Polynom<T> const& p, long double l, long double r)` \
  Return an integral of a polynomial calculated from a to b.
- `T max_deriv_coef(Polynom<T> const& p1, Polynom<T> const& p2)` \
  Return the maximal derivative coefficient of two polynomials.
