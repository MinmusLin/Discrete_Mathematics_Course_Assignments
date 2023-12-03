/****************************************************************
 * Project Name:  Assignment_1_1
 * File Name:     assignment_1_1.cpp
 * File Function: 命题逻辑联接词
 * Author:        Jishen Lin (林继申)
 * Update Date:   2023/12/3
 ****************************************************************/

#include <iostream>
#include <conio.h>

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
            std::cout << optn << std::endl << std::endl;
            return optn == falseValue ? false : true;
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
        std::cout << "+-----------------------------------+" << std::endl;
        std::cout << "|          命题逻辑联接词           |" << std::endl;
        std::cout << "|  Propositional Logic Connectives  |" << std::endl;
        std::cout << "+-----------------------------------+" << std::endl << std::endl;

        /* Enter the value of P and Q */
        std::cout << "请输入 P 的值 [0/1]: ";
        bool p = inputLogicalValue();
        std::cout << "请输入 Q 的值 [0/1]: ";
        bool q = inputLogicalValue();

        /* Propositional logic connectives */
        std::cout << ">>> 合取: P∧Q = " << (p && q) << std::endl << std::endl; // Conjunction
        std::cout << ">>> 析取: P∨Q = " << (p || q) << std::endl << std::endl; // Disjunction
        std::cout << ">>> 条件: P→Q = " << (!p || q) << std::endl << std::endl; // Implication
        std::cout << ">>> 双向条件: P←→Q = " << ((!p || q) && (!q || p)) << std::endl << std::endl; // Equivalence

        /* Whether to exit the program */
        std::cout << "是否退出程序 [y/n]: ";
    } while (!inputLogicalValue('n', 'y'));
    return 0;
}