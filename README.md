In the modul Polynomial a template class Polynom<T> is declared.
Class provides following operations with polynomials and numbers:
<ul>
    <li>Add (+), subtract (-), multiply (*), divide with remainder (/) and get remainder (%);</li>
    <li>Comparaison (==, !=);</li>
    <li>Print a polynomial (<<);</li>
    <li>Calculate value of a polynomial in the given point (());</li>
    <li>Get a coefficient of a polynomial ([]). A coefficient is returned by reference and can be changed.</li>
</ul>

Class provides following methods:
<ul>
    <li>.degree()</li>
    Returns a degree of a polynomial.
    <li>.printc()</li>
    Returns a string, contains coefficients of a polynomial.
    <li>.print(var_name = "x")</li>
    Returns a string, contains a polynomial with given name of variable.
    <li>.max_coef()</li>
    Returns the maximal coefficient of a polynomial.
</ul>

There are following functions with polynomials:
<ul>
    <li>pw(poly, n)</li>
    Returns the n-th power of a polynomial.
    <li>deriv(poly, n)</li>
    Returns the n-th derivative of a polynomial.
    <li>integr(poly)</li>
    Returns an integral of a polynomial.
    <li>integr(poly, a, b)</li>
    Returns an integral of a polynomial calculated from a to b.
    <li>max_deriv_coef(poly1, poly2)</li>
    Returns the maximal derivative coefficient of two polynomials.
</ul>
