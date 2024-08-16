#include <iostream>

double square(double x) // square a double precision floating-point number
{
    return x * x;
}

void print_square(double x) // si es void no se usa el return 0, pues void significa que no devuelve un valor
{
    std::cout << "El cuadrado de " << x << " es " << square(x) << '\n';
}

int main()
{
    print_square(2);
    print_square(108);
    return 0;    
}