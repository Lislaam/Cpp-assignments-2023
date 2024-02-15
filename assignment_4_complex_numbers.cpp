// 10453447_assignment_4.cpp : A class for creating and operating with complex numbers
//

#include <iostream>
#include <iomanip>

class Complex {
private:
    double real{}, imaginary{};

public:
    // Constructors / destructors:
    Complex() = default; 
    Complex(double in_real, double in_imaginary) : real{ in_real }, imaginary{ in_imaginary } {}
    ~Complex() {}

    // Getters and Setters:
    void set_real(const double in_real) { real = in_real; }
    void set_imaginary(const double in_imaginary) { imaginary = in_imaginary; }

    double get_real() const { return real; }
    double get_imaginary() const { return imaginary; }

    // Member functions:
    double real_part() { return real; };
    double imaginary_part() { return imaginary; };
    double modulus() { return sqrt(pow(real,2) + pow(imaginary,2)); }
    double argument() { return atan(imaginary / real); }

    Complex conjugate() {
        double imaginary_conj = 0 - imaginary;
        return Complex(real, imaginary_conj);
    }

    // Overloaded operators:
    Complex operator+(const Complex& number) {
        Complex temp{ real + number.real, imaginary + number.imaginary };
        return temp;
    }

    Complex operator-(const Complex& number) {
        Complex temp{ real - number.real, imaginary - number.imaginary };
        return temp;
    }

    Complex operator*(const Complex& number) {
        Complex temp{ (real * number.real) - (imaginary * number.imaginary), (real * number.imaginary) + (imaginary * number.real)};
        return temp;
    }

    Complex operator/(const Complex& number) {
        double denominator = (number.real * number.real) + (number.imaginary * number.imaginary);
        Complex temp{ ((real * number.real) + (imaginary * number.imaginary)) / denominator, 
            ((imaginary * number.real) - (real * number.imaginary)) / denominator };
        return temp;
    }

    friend std::ostream& operator << (std::ostream& os, const Complex& number);
    friend std::istream& operator >> (std::istream& is, Complex& number);
};

std::ostream& operator << (std::ostream& os, const Complex& number) {
    std::cout << std::setprecision(3);
    char sign{}; // Sign of imaginary part
    if (number.imaginary > 0 || number.imaginary == 0) { sign = '+';}

    os << number.real << sign << number.imaginary << "i" << std::endl;
    return os; 
}

std::istream& operator >> (std::istream& is, Complex& number) { 
    double real_part{}, imaginary_part{};
    char sign{}, i{};

    // Read in the form a+ib or a-ib
    is >> real_part >> sign >> i >> imaginary_part;

    if (sign == '-' && imaginary_part != 0) {
        number.set_real(real_part);
        number.set_imaginary(-imaginary_part);
    }
    if (sign == '+' || imaginary_part == 0) {
        number.set_real(real_part);
        number.set_imaginary(imaginary_part);
    }

    return is;
}


int main()
{
    Complex a{ 3,4 };
    Complex b{ 1,-2 };
    Complex c{};

    std::cout << a.real_part() << std::endl; // 3
    std::cout << b.imaginary_part() << std::endl; // -2
    std::cout << a.modulus() << std::endl; // 5
    std::cout << a.argument() << std::endl; // 0.927
    std::cout << a.conjugate(); // 3 - 4i

    std::cout << a + b; // 4 + 2i
    std::cout << a - b; // 2 + 6i
    std::cout << a * b; // 11 - 2i
    std::cout << a / b; // -1 + 2i

    std::cout << "\nEnter a complex number to store in variable 'c', in the form a+ib or a-ib: "; 
    std::cin >> c;
    std::cout << "c = " << c;
}

