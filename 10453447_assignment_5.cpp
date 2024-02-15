// 10453447_assignment_5.cpp : A Matrix class.

#include <iostream>
#include <iomanip>

class Matrix
{
private:
    int rows{}, columns{};
    double* data{ nullptr };
public:
    Matrix() = default;
    Matrix(int in_rows, int in_columns) : rows{in_rows}, columns{in_columns} { data = new double[rows * columns]; };
    Matrix(Matrix& a); // Copy constructor
    Matrix(Matrix&&) noexcept; // Move constructor
    ~Matrix() { delete[] data; };

    void set_rows(const int in_rows) { rows = in_rows; }
    void set_columns(const int in_columns) { columns = in_columns; }
    void set_data(double* in_data) { data = in_data; }
    int get_rows() const { return rows; }
    int get_columns() const { return columns; }
    double* get_data() const { return data; }

    double& operator[](size_t);
    Matrix& operator=(Matrix&);
    Matrix operator+(const Matrix&) const;
    Matrix operator-(const Matrix&) const;
    Matrix operator*(const Matrix&) const;
    void fill_matrix(double values[]) { for (int i{}; i < rows * columns; i++) { data[i] = values[i]; } }
    friend std::ostream& operator<<(std::ostream&, const Matrix&);
    friend std::istream& operator>>(std::istream&, const Matrix&);
};

Matrix::Matrix(Matrix& original) // Copy Constructor
{
    int size = original.rows * original.columns;
    data = nullptr;
    data = new double[size];
    rows = original.rows;
    columns = original.columns;
    for (size_t i{}; i < size; i++) 
    {
        data[i] = original.data[i];
    };
}
Matrix::Matrix(Matrix&& original) noexcept// Move constructor
{
    rows = original.rows;
    columns = original.columns;
    data = original.data;
    original.rows = 0;
    original.columns = 0;
    original.data = nullptr;
}
double& Matrix::operator[](size_t index)
{
    if (index < 0 || index >= (rows * columns))
    {
        std::cout << "Error: trying to access array element out of bounds " << std::endl;
        throw("Out of Bounds error ");
    }
    return data[index];
}
Matrix& Matrix::operator=(Matrix& a) // Assignment deep copy
{
    if (&a == this) { return *this; } // Self-assignment case
    delete[] data; 
    data = nullptr;
    rows = a.rows;
    columns = a.columns;
    int size = a.rows * a.columns;
    if (size > 0)
    {
        data = new double[size];
        for (int i{}; i < size; i++) { data[i] = a.data[i]; }
    }
    return *this;
}
Matrix Matrix::operator+(const Matrix& a) const
{
    if (rows == a.rows && columns == a.columns)
    {
        Matrix rval{ rows, columns };
        for (size_t i{}; i < (rows * columns); i++) {
            rval.data[i] = data[i] + a.data[i];
        }
        return rval;
    } else
    {
        std::cout << "Error: Dimensions of matrices are not equal. " << std::endl;
        throw("Value error");
    }
}
Matrix Matrix::operator-(const Matrix& a) const
{
    if (rows == a.rows && columns == a.columns)
    {
        Matrix rval{ rows, columns };
        for (size_t i{}; i < (rows * columns); i++) {
            rval.data[i] = data[i] - a.data[i];
        }
        return rval;
    }
    else
    {
        std::cout << "Error: Dimensions of matrices are not equal. " << std::endl;
        throw("Value error");
    }
}
Matrix Matrix::operator*(const Matrix& a) const
{
    if (rows == a.rows && columns == a.columns)
    {
        Matrix rval{ rows, columns };
        for (size_t i{}; i < (rows * columns); i++) {
            rval.data[i] = data[i] + a.data[i]; // WRONG!!
        }
        return rval;
    }
    else
    {
        std::cout << "Error: # of rows of matrix A not equal to # of columns of matrix B, or vice versa. " << std::endl;
        throw("Value error");
        return Matrix();
    }
}

std::ostream& operator<<(std::ostream& os, const Matrix& input)
{
    for (int i{}; i < input.rows; i++)
    {
        for (int j{}; j < input.columns; j++)
        {
            os << input.data[j + (i * input.columns)] << " ";
        }
        os << "\n";
    }
    os << std::endl;
    return os;
}
std::istream& operator>>(std::istream& is, const Matrix& destination) // CHANGE!!
{
    int row_num, column_num;
    std::cout << "How many rows does your matrix have?: ";
    std::cin >> row_num;
    std::cout << "How many columns does your matrix have?: ";
    std::cin >> column_num;
    std::cout << "Enter a 1D array of numbers of length rows*columns. Separate numbers with a comma: \n";
 
    return is;
}

int main()
{
    double a_values[9] = { 1,2,3,9,8,7,4,2,6 };
    double b_values[9] = { 5,5,4,1,2,3,6,9,8 };
    double c_values[6] = { 3,4,1,2,5,6 };
    Matrix a(3, 3);
    Matrix b(3, 3);
    Matrix c(2, 3);
    a.fill_matrix(a_values);
    b.fill_matrix(b_values);
    c.fill_matrix(c_values);
    Matrix a_copy = a; // Can only make copies AFTER the original matrix is filled!
    Matrix b_copy;
    b_copy = b;

    std::cout << "Matrix a:\n" << a;
    std::cout << "Matrix b:\n" << b;
    std::cout << "Matrix c:\n" << c;
    std::cout << "Testing copy constructor. Original Matrix a:\n" << a;
    std::cout << "Copy of matrix a : \n" << a_copy;
    std::cout << "Testing assignment operator. Original Matrix b:\n" << b;
    std::cout << "Copy of matrix b: \n" << b_copy;
    std::cout << "a + b = \n" << a + b;
    std::cout << "a - b = \n" << a - b;

    return 0;
}