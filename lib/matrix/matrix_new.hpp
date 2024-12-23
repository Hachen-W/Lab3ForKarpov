#ifndef MATRIX_HPP_INCLUDED
#define MATRIX_HPP_INCLUDED


#include <iostream>
#include <iomanip>
using namespace std;


template<typename T>
class Matrix {
    int m_rows, m_cols;
    T* m_values;
public:
    Matrix() {
        m_rows = 0;
        m_rows = 0;
        m_values = nullptr;
    }
    Matrix(int rows, int cols) {
        m_rows = rows;
        m_cols = cols;
        m_values = new T[m_cols * m_rows];
    }
    Matrix(const Matrix& other) {
        m_rows = other.m_rows;
        m_cols = other.m_cols;
        m_values = new T[m_cols * m_rows];
        for (int i = 0; i < m_rows*m_cols; ++i) {
            m_values[i] = other.m_values[i];
        }
    }
    ~Matrix() {
        if (nullptr != m_values)
            delete[] m_values;
    }
    T& get(int i, int j) const {
        return m_values[i*m_cols+j];
    }
    int getStringsCount() const {
        return m_rows;
    }
    int getColumnsCount() const {
        return m_cols;
    }
    void resize(int rows, int cols) {
        T* temp = m_values;
        m_rows = rows;
        m_cols = cols;
        
        m_values = new T[m_rows*m_cols];
        if (temp) {
            delete[] temp;
        }
    }
};


#endif