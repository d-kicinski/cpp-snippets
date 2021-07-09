#include <iostream>


#include <array>
#include <cstdio>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>


class Matrix
{
public:
    int const size = 4;
    using vector_t = std::vector<float>;
    std::shared_ptr<vector_t> _data;

    auto data() -> std::vector<float> & { return *_data; }
    auto data() const -> std::vector<float>  { return *_data; }
    auto at(int pos) -> float & { return (*_data)[pos]; }
    auto begin() -> vector_t::iterator { return _data->begin(); }
    auto end() -> vector_t::iterator { return _data->end(); }
    auto begin() const -> vector_t::iterator { return _data->begin(); }
    auto end() const -> vector_t::iterator { return _data->end(); }

    friend class Matrix;
    friend auto operator<<(std::ostream &os, const Matrix &matrix) -> std::ostream &;
    friend auto copy(Matrix const &matrix) -> Matrix;
    friend auto print(Matrix const &matrix, std::string const &name) -> void;

    Matrix()
    {
        _data = std::make_shared<std::vector<float>>(size);
        std::cout << "Matrix()" << std::endl;
    }
    ~Matrix()
    {
        std::cout << "~Matrix()" << std::endl;
    }
    Matrix(Matrix const &matrix)
    {
        // *this object is not initialized so new object is created on the basis on given same object, should make copy
        // called when eg::
        //    Matrix matrix(matrix2);
        //    Matrix matrix = matrix2;

        _data = matrix._data;
        std::cout << "Matrix(Matrix const &)" << std::endl;
    }
    Matrix(Matrix && matrix) noexcept     {
        _data = matrix._data;
        std::cout << "Matrix(Matrix &&)" << std::endl;
    }
    auto operator=(Matrix const & matrix) -> Matrix&
    {
        // *this object is initialized so here whe just set its values based on passed object
        _data = matrix._data;
        std::cout << "operator=(Matrix const &)" << std::endl;
        return *this;
    }

    auto operator=(Matrix && matrix) -> Matrix&
    {
        // *this object is initialized so here whe just set its values based on passed object
        _data = matrix._data;
        std::cout << "operator=(Matrix &&)" << std::endl;
        return *this;
    }
};

auto copy(Matrix const &matrix) -> Matrix
{
    Matrix matrix_copy(matrix);
    matrix_copy._data = std::make_shared<std::vector<float>>(matrix.size);
    std::copy(matrix.begin(), matrix.begin(), matrix_copy.begin());
    return matrix_copy;
}

std::ostream &operator<<(std::ostream &os, const Matrix &matrix)
{
    std::stringstream ss;
    ss << "{";
    for (auto &v : *matrix._data) {
        ss << " " << v;
    }
    ss << " }";
    os << ss.str();
    return os;
}

auto print(const Matrix &matrix, std::string const &name) -> void
{
    std::cout << "[" << name  << "] "<< matrix << std::endl;
}

auto print() -> void { std::cout << std::endl; }

auto create_matrix() -> Matrix {
    Matrix matrix;
    return matrix;
}


int main()
{

    {
        Matrix matrix;
        std::vector<float> vector = matrix.data();
        std::vector<float> &vector_ref = matrix.data();

        print(matrix, "matrix");
        vector.at(0) = 10;
        print(matrix, "vector.at(0)");
        vector_ref.at(1) = 11;
        print(matrix, "vector_ref.at(1)");
        matrix.at(2) = 12;
        print(matrix, "matrix.at(2)");
    }
    print();
    print();
    {
        Matrix matrix;
        print(matrix, "matrix");
        print();

        Matrix matrix_copy(matrix);
        matrix_copy.at(0) = 10;
        print(matrix_copy, "matrix_copy");
        print(matrix, "matrix");
        print();

        Matrix matrix_copy_assigment = matrix;
        matrix_copy_assigment.at(1) = 11;
        print(matrix_copy, "matrix_copy_assigment");
        print(matrix, "matrix");
        print();
    }
    print();
    print();
    {
        Matrix matrix, matrix2;
        print(matrix, "matrix");
        print(matrix2, "matrix2");

        matrix2 = matrix;
        matrix2.at(0) = 10;
        print(matrix, "matrix");
        print(matrix2, "matrix2");
        print();
    }
    print();
    print();
    {
        Matrix matrix;
        Matrix matrix_copy = copy(matrix);
        matrix_copy.at(0) = 10;
        print(matrix, "matrix");
        print(matrix_copy, "matrix_copy");
    }
    print();
    print();
    {
        Matrix matrix(create_matrix());
        Matrix matrix2 = create_matrix();
        matrix2 = create_matrix();
    }


//    Matrix matrix_ref = get_reference();
//    print(matrix_ref, "matrix_ref");


    //    std::string result = exec("");
    //    std::cout << result << std::endl;
    //    using vector_t = std::vector<float>;
    //    std::shared_ptr<vector_t> _data = std::make_shared<std::vector<float>>(10);
    //    std::cout << _data.use_count() << std::endl;
    //    auto _data2 = _data;
    //    _data2->at(0) = 1337;
    //    _data2->at(5) = 69;
    //
    //    std::cout << _data.use_count() << std::endl;
    //    std::cout << _data2.use_count() << std::endl;
    //    auto it = _data->begin();
    //    auto value = it[5];
    //    int val = int();
    //    bool boolean = bool();
    //    std::cout << boolean << std::endl;
    //
    //    int i = 1;
}
