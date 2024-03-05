

/*
 * Zad1
 * Implement a class Matrix that will store a two dimensional matrix (N x M) with double coefficients.
 Coefficients should be stored in dynamically allocated one dimensional array (referred as data).
Provide the following functionalities:
 Matrix m1;         // default constructor: N=M=0, data=nullptr
 Matrix m2(3,4);    // N = 3, M = 4, data = N*M doubles set to 0.0
 Matrix m3({{1,2,3},{32, 23, 22},{3,234,23,44}}); // from initializer_list
cout << m2(1,1) << endl;    // 0  - the first element in data (we count from 1)
 cout << m3(2,2) << endl;    // 23
 cout << m3;                 // prints matrix
cout << "Copy semantics \n";
 Matrix m4 = m2;     // copy constructor that makes deep copy of the matrix m2
 m4 = m3;            // copy assignment makes deep copy of the matrix m3
 • Constructor with initializer_list parameter should construct the smallest matrix NxM that
can store provided data. If in given row there is not enough data initialize remaining
elements to zero.
• Provide also destructor that frees allocated memory.
 • All constructors should print short debug information that they was called, similar to the
following output:
 constructor of 3x4 matrix
 constructor of 3x4 matrix from initializer_list
 0
 23
 {1, 2, 3, 0}
 {32, 23, 22, 0}
 {3, 234, 23, 44}
Copy semantics
 copy constructor
 copy assignment operator

 Zad2
 Exercise 2. Move semantics
 Implement move constructor and move assignment operator for class Matrix.
Instead of making a copy of data they should just move data pointer from the source object to the
destination object.
Make sure to leave source object in the correct state and that there are no leaks of resources.
Implement unary operator -  that for given matrix A returns matrix -A.
Observe copy elision that omit copy and move constructors and resulting in zero-copy pass-by
value semantics.
 Example
 cout << "Move semantics \n";
 Matrix m7 = std::move(m2);
 m4 = -m3;
cout << "Copy elision \n";
 Matrix m6 = -m4;
Matrix * pm = new Matrix(-m4);
cout << m6(2,1) << endl; // 32
 Expected output:
 Move semantics
 move constructor
 constructor of 3x4 matrix
 move assignment operator
Copy elision
 constructor of 3x4 matrix
 constructor of 3x4 matrix

 Exercise 3. Inheritance of constructors
 Implement class MatrixWithLabel that is a subclass of Matix and add field that stores matrix label
(as string, default value “A”). Class MatrixWithLabel should inherit all constructors from Matrix
(not reimplement them!) and add two new constructors:
MatrixWithLabel(label, numberOfRows, numberOfColumns)
 MatrixWithLabel(label, initializer_list<...>)
 Add also getLabel and setLabel methods.
 Example
 cout << "Inheritance \n";
 MatrixWithLabel l0("B", 3, 4);
 MatrixWithLabel l1({{1,2},{4,5}});
 l1.setLabel("A");
 MatrixWithLabel l2 = l1;
 MatrixWithLabel l3 = std::move(l1);
 cout << l2.getLabel() << " " << l3.getLabel() << endl;
 //
cout << l1.getLabel() << endl;
 Expected output:
 Inheritance
 constructor of 3x4 matrix
 constructor of 2x2 matrix from initializer_list
 copy constructor
 move constructor
A A
 • Check if default copy an move constructors work as expected.
• Implement your own copy constructor. Observe what happened to default move constructor.
 • Explicitly add default move constructors and assignment operators
 */

#include <iostream>

//#include <numeric>
using namespace std;

class Matrix {
    int N, M;
    double *data;
public:
    Matrix() : N(0), M(0), data(nullptr) {
        cout << "default constructor" << endl;
    }

    Matrix(int N, int M) : N(N), M(M), data(new double[N * M]) {
        fill(data, data + N * M, 0.0);
        cout << "constructor of " << N << "x" << M << " matrix" << endl;
    }

    Matrix(initializer_list<initializer_list<double>> list) {
        N = list.size();
        // Find the maximum number of elements in a row
        // Using lambda function to compare the size of rows
        // max_element returns iterator to the first element in the range (first, last) that is the largest

        M = max_element(list.begin(), list.end(), [](const initializer_list<double>& a, const initializer_list<double>& b) {
            return a.size() < b.size();
        })->size();
        data = new double[N * M];
        int i = 0;
        for (const auto &row : list) {
            int j = 0;
            for (const auto &el : row) {
                data[i * M + j] = el;
                j++;
            }
            fill(data + i * M + j, data + (i + 1) * M, 0.0); // Fill remaining elements with 0
            i++;
        }
        cout << "constructor of " << N << "x" << M << " matrix from initializer_list" << endl;
    }



    ~Matrix() {
        delete[] data;
    }

    friend ostream &operator<<(ostream &os, const Matrix &matrix) {
        for (int i = 0; i < matrix.N; i++) {
            os << "{";
            for (int j = 0; j < matrix.M; j++) {
                os << matrix.data[i * matrix.M + j];
                if (j < matrix.M - 1) {
                    os << ", ";
                }
            }
            os << "}" << endl;
        }
        return os;
    }

    Matrix(const Matrix &other) : N(other.N), M(other.M), data(new double[N * M]) {
        cout << "copy constructor" << endl;
        copy(other.data, other.data + N * M, data); // Using copy algorithm
    }

    Matrix &operator=(const Matrix &other) {
        cout << "copy assignment operator" << endl;
        if (this != &other) {
            delete[] data;
            N = other.N;
            M = other.M;
            data = new double[N * M];
            copy(other.data, other.data + N * M, data); // Using copy algorithm
        }
        return *this;
    }

    Matrix(Matrix &&other) : N(other.N), M(other.M), data(other.data) {
        cout << "move constructor" << endl;
        other.data = nullptr;
    }

    Matrix &operator=(Matrix &&other) {
        cout << "move assignment operator" << endl;
        if (this != &other) {
            delete[] data;
            N = other.N;
            M = other.M;
            data = other.data;
            other.data = nullptr;
        }
        return *this;
    }

    Matrix operator-() const {
        Matrix result(N, M);
        transform(data, data + N * M, result.data, negate<double>()); // Using transform algorithm and negate functor
        return result;
    }

    double &operator()(int i, int j) {
        return data[(i - 1) * M + j - 1];
    }

    double operator()(int i, int j) const {
        return data[(i - 1) * M + j - 1];
    }
};

class MatrixWithLabel : public Matrix {
    string label;
public:
    MatrixWithLabel(const string &label, int N, int M) : Matrix(N, M), label(label) {
    }

    MatrixWithLabel(const string &label, initializer_list<initializer_list<double>> list) : Matrix(list), label(label) {
    }

    string getLabel() const {
        return label;
    }

    void setLabel(const string &label) {
        this->label = label;
    }

    /*
     *  Implement your own copy constructor. Observe what happened to default move constructor.
 • Explicitly add default move constructors and assignment operators
     */

//    MatrixWithLabel(const MatrixWithLabel &other) : Matrix(other), label(other.label) {
//    }
//
//    MatrixWithLabel &operator=(const MatrixWithLabel &other) {
//        cout << "copy assignment operator of matrix with label " << label << endl;
//        if (this != &other) {
//            Matrix::operator=(other);
//            label = other.label;
//        }
//        return *this;
//    }
//
//    MatrixWithLabel(MatrixWithLabel &&other) : Matrix(move(other)), label(move(other.label)) {
//        cout << "move constructor of matrix with label " << label << endl;
//    }
//
//    MatrixWithLabel &operator=(MatrixWithLabel &&other) {
//        cout << "move assignment operator of matrix with label " << label << endl;
//        if (this != &other) {
//            Matrix::operator=(move(other));
//            label = move(other.label);
//        }
//        return *this;
//    }

};

int main() {
    Matrix m1;
    Matrix m2(3,4);
    Matrix m3({{1,2,3},{32, 23, 22},{3,234,23,44}});
    cout << m2(1,1) << endl;  // 0
    cout << m3(2,2) << endl;  // 23
    cout << m3;

    cout << "Copy semantics \n";
    Matrix m4 = m2;
    m4 = m3;

    cout << "Move semantics \n";
    Matrix m7 = move(m2);
    m4 = -m3;

    cout << "Copy elision \n";
    Matrix m6 = -m4;
    Matrix * pm = new Matrix(-m4);
    cout << m6(2,1) << endl; // 32

    cout << "Inheritance \n";
    MatrixWithLabel l0("B", 3, 4);
    MatrixWithLabel l1("a", {{1,2},{4,5}});
    //MatrixWithLabel l1({{1,2},{4,5}});
    l1.setLabel("A");
    MatrixWithLabel l2 = l1;
    MatrixWithLabel l3 = move(l1);
    cout << l2 << endl;
    cout << l3 << endl;
    cout << l2.getLabel() << " " << l3.getLabel() << endl;
    cout << l1.getLabel() << endl;

    return 0;
}
