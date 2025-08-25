#include <vector>
#include <stdexcept>
#include <type_traits>
#include <iostream>

using std::vector;

// Matrix Addition
template<typename T>
vector<vector<T>> matrixAdd(const vector<vector<T>>& m1, const vector<vector<T>>& m2) {
    static_assert(std::is_arithmetic<T>::value, "matrixAdd requires arithmetic types.");

    if (m1.size() != m2.size() || m1[0].size() != m2[0].size()) {
        throw std::invalid_argument("Matrices must have the same dimensions for addition.");
    }

    size_t rows = m1.size();
    size_t cols = m1[0].size();
    vector<vector<T>> result(rows, vector<T>(cols));

    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            result[i][j] = m1[i][j] + m2[i][j];
        }
    }

    return result;
}

// Matrix Multiplication
template<typename T>
vector<vector<T>> matrixMult(const vector<vector<T>>& m1, const vector<vector<T>>& m2) {
    static_assert(std::is_arithmetic<T>::value, "matrixMult requires arithmetic types.");

    size_t rows_m1 = m1.size();
    size_t cols_m1 = m1[0].size();
    size_t rows_m2 = m2.size();
    size_t cols_m2 = m2[0].size();

    if (cols_m1 != rows_m2) {
        throw std::invalid_argument("Number of columns in matrix A must equal number of rows in matrix B.");
    }

    vector<vector<T>> result(rows_m1, vector<T>(cols_m2, 0));

    for (size_t i = 0; i < rows_m1; ++i) {
        for (size_t j = 0; j < cols_m2; ++j) {
            for (size_t k = 0; k < cols_m1; ++k) {
                result[i][j] += m1[i][k] * m2[k][j];
            }
        }
    }

    return result;
}

template<typename T>
vector<vector<T>> matrixMult(const vector<vector<T>>& m) {
    vector<vector<T>> res;
    for(int i = 0; i < m.size(); i++){
        for(int j = 0; j< m[0].size(); j++) {
            res[i][j] = m[j][i];
        }
    }
    return res;


}



// Print Matrix
template <typename T>
void printMatrix(const vector<vector<T>>& mat) {
    for (size_t i = 0; i < mat.size(); ++i) {
        std::cout << "{ ";
        for (size_t j = 0; j < mat[i].size(); ++j) {
            std::cout << mat[i][j];
            if (j < mat[i].size() - 1)
                std::cout << ", ";
        }
        std::cout << " }" << std::endl;
    }
}

int main() {
    vector<vector<int>> arr1 {{2, 0}, {0, 2}};
    vector<vector<int>> arr2 {{1, 2}, {2, 1}};

    vector<vector<int>> res = matrixMult(arr1, arr2);

    printMatrix(res);

    return 0;
}
