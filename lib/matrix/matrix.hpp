#ifndef MATRIX_HPP_INCLUDED
#define MATRIX_HPP_INCLUDED


#include <iostream>


template<typename T>
class Matrix {
private:
    std::vector<std::vector<T>> matrix; // В виде одномерного
public:
    Matrix() = default;
    unsigned int getStringsCount() const noexcept {
        return matrix.size();
    }
    unsigned int getColumnsCount() const noexcept {
        return getStringsCount() == 0 ? 0 : matrix[0].size();
    }
    std::vector<T>& operator[] (size_t index) {
        if (getColumnsCount() <= index)
            throw std::logic_error("Index Went Beyond the Limits");
        return matrix[index];
    }
    void resize(size_t size_strings, size_t size_columns) {
        matrix.resize(size_strings);
        for (size_t i = 0; i < size_strings; i++)
            matrix[i].resize(size_columns);
    }
};




#endif