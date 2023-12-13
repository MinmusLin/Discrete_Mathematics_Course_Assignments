/****************************************************************
 * Project Name:  Assignment_6
 * File Name:     assignment_6.cpp
 * File Function: Warshall算法求解传递闭包
 * Author:        Jishen Lin (林继申)
 * Update Date:   2023/12/13
 ****************************************************************/

#include <iostream>
#include <vector>
#include <conio.h>
#include <limits>

/* Define Matrix type */
typedef std::vector<std::vector<int>> Matrix;

/*
 * Function Name:    transitiveClosure
 * Function:         Calculate transitive closure
 * Input Parameters: const Matrix matrix
 * Return Value:     transitive closure
 */
Matrix transitiveClosure(const Matrix matrix)
{
    Matrix mat(matrix);
    size_t size = mat.size();
    for (size_t k = 0; k < size; k++)
        for (size_t i = 0; i < size; i++)
            for (size_t j = 0; j < size; j++)
                mat[i][j] = ((mat[i][j] || (mat[i][k] && mat[k][j])) ? 1 : 0);
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
        std::cout << "+------------------------------------------------------+" << std::endl;
        std::cout << "|               Warshall算法求解传递闭包               |" << std::endl;
        std::cout << "|  Use Warshall Algorithm to Solve Transitive Closure  |" << std::endl;
        std::cout << "+------------------------------------------------------+" << std::endl << std::endl;

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

        /* Transitive closure */
        Matrix transitive = transitiveClosure(matrix);
        std::cout << std::endl << ">>> 传递闭包" << std::endl << std::endl << transitive << std::endl;

        /* Whether to exit the program */
        std::cout << "是否退出程序 [y/n]: ";
    } while (!inputLogicalValue('n', 'y'));
    return 0;
}