/****************************************************************
 * Project Name:  Assignment_3
 * File Name:     assignment_3.cpp
 * File Function: 关系的自反、对称、传递闭包
 * Author:        Jishen Lin (林继申)
 * Update Date:   2023/12/22
 ****************************************************************/

#include <iostream>
#include <vector>
#include <conio.h>
#include <limits>

/* Define Matrix type */
typedef std::vector<std::vector<int>> Matrix;

/*
 * Function Name:    reflexiveClosure
 * Function:         Calculate reflexive closure
 * Input Parameters: const Matrix matrix
 * Return Value:     reflexive closure
 */
Matrix reflexiveClosure(const Matrix matrix)
{
    Matrix mat(matrix);
    size_t size = mat.size();
    for (size_t i = 0; i < size; i++)
        mat[i][i] = 1;
    return mat;
}

/*
 * Function Name:    symmetricClosure
 * Function:         Calculate symmetric closure
 * Input Parameters: const Matrix matrix
 * Return Value:     symmetric closure
 */
Matrix symmetricClosure(const Matrix matrix)
{
    Matrix mat(matrix);
    size_t size = mat.size();
    for (size_t i = 0; i < size; i++)
        for (size_t j = 0; j < size; j++)
            if (mat[i][j])
                mat[j][i] = 1;
    return mat;
}

/*
 * Function Name:    multiplyMatrices
 * Function:         Multiply matrices
 * Input Parameters: const Matrix& a
 *                   const Matrix& b
 * Return Value:     result
 */
Matrix multiplyMatrices(const Matrix& a, const Matrix& b)
{
    size_t n = a.size();
    Matrix result(n, std::vector<int>(n, 0));
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            for (size_t k = 0; k < n; k++) {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return result;
}

/*
 * Function Name:    transitiveClosure
 * Function:         Calculate transitive closure
 * Input Parameters: const Matrix matrix
 * Return Value:     transitive closure
 */
Matrix transitiveClosure(const Matrix matrix)
{
    Matrix mat(matrix);
    size_t n = matrix.size();
    for (size_t m = 2; m <= n; m++) {
        Matrix matPower = multiplyMatrices(mat, matrix);
        for (size_t i = 0; i < n; i++) {
            for (size_t j = 0; j < n; j++) {
                mat[i][j] = static_cast<int>(matPower[i][j] > 0);
            }
        }
    }
    return mat;
}

/*
 * Function Name:    operator<<
 * Function:         Overload operator <<
 * Input Parameters: std::ostream& out
 *                   const Matrix& matrix
 * Return Value:     out
 */
std::ostream& operator<<(std::ostream& out, const Matrix& matrix)
{
    size_t size = matrix.size();
    for (size_t i = 0; i < size; i++) {
        out << (i == 0 ? "Matrix = [" : "         ");
        for (size_t j = 0; j < size; j++) {
            out << " " << matrix[i][j];
            if (j < size - 1)
                out << ",";
        }
        out << (i < size - 1 ? ",\n " : " ]\n");
    }
    out << std::endl << "Relationship = { ";
    bool first = true;
    for (size_t i = 0; i < size; i++)
        for (size_t j = 0; j < size; j++)
            if (matrix[i][j]) {
                if (first)
                    first = false;
                else
                    out << ", ";
                out << "<" << char('a' + i) << ", " << char('a' + j) << ">";
            }
    out << " }" << std::endl;
    return out;
}

/*
 * Function Name:    inputLogicalValue
 * Function:         Input logical value
 * Input Parameters: char falseValue
 *                   char trueValue
 * Return Value:     true / false
 */
bool inputLogicalValue(char falseValue = '0', char trueValue = '1')
{
    while (true) {
        char optn = _getch();
        if (optn == 0 || optn == -32)
            optn = _getch();
        else if (optn == falseValue || optn == trueValue) {
            std::cout << optn;
            return optn == falseValue ? false : true;
        }
    }
}

/*
 * Function Name:    inputInteger
 * Function:         Input an integer
 * Input Parameters: int lowerLimit
 *                   int upperLimit
 *                   const char* prompt
 * Return Value:     an integer
 */
int inputInteger(int lowerLimit, int upperLimit, const char* prompt)
{
    while (true) {
        std::cout << "请输入" << prompt << " [整数范围: " << lowerLimit << "~" << upperLimit << "]: ";
        double tempInput;
        std::cin >> tempInput;
        if (std::cin.good() && tempInput == static_cast<int>(tempInput) && tempInput >= lowerLimit && tempInput <= upperLimit) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return static_cast<int>(tempInput);
        }
        else {
            std::cerr << std::endl << ">>> " << prompt << "输入不合法，请重新输入" << prompt << "！" << std::endl << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

/*
 * Function Name:    main
 * Function:         Main function
 * Return Value:     0
 */
int main()
{
    do {
        /* System entry prompt */
        system("cls");
        std::cout << "+--------------------------------------------------------------+" << std::endl;
        std::cout << "|                  关系的自反、对称、传递闭包                  |" << std::endl;
        std::cout << "|  Reflexive, Symmetric and Transitive Closures of a Relation  |" << std::endl;
        std::cout << "+--------------------------------------------------------------+" << std::endl << std::endl;

        /* Input matrix */
        int size = inputInteger(2, 26, "关系矩阵大小");
        Matrix matrix(size, std::vector<int>(size));
        std::cout << std::endl << ">>> 请输入关系矩阵 [0/1]" << std::endl << std::endl;
        for (int i = 0; i < size; i++) {
            std::cout << (i == 0 ? "Matrix = [" : "         ");
            for (int j = 0; j < size; j++) {
                std::cout << " ";
                matrix[i][j] = (inputLogicalValue() ? 1 : 0);
                if (j < size - 1)
                    std::cout << ",";
            }
            std::cout << (i < size - 1 ? ",\n " : " ]\n");
        }

        /* Reflexive closure */
        Matrix reflexive = reflexiveClosure(matrix);
        std::cout << std::endl << ">>> 自反闭包" << std::endl << std::endl << reflexive << std::endl;

        /* Symmetric closure */
        Matrix symmetric = symmetricClosure(matrix);
        std::cout << ">>> 对称闭包" << std::endl << std::endl << symmetric << std::endl;

        /* Transitive closure */
        Matrix transitive = transitiveClosure(matrix);
        std::cout << ">>> 传递闭包" << std::endl << std::endl << transitive << std::endl;

        /* Whether to exit the program */
        std::cout << "是否退出程序 [y/n]: ";
    } while (!inputLogicalValue('n', 'y'));
    return 0;
}