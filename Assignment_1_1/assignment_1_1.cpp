/****************************************************************
 * Project Name:  Assignment_1_1
 * File Name:     assignment_1_1.cpp
 * File Function: �����߼����Ӵ�
 * Author:        Jishen Lin (�ּ���)
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
        std::cout << "|          �����߼����Ӵ�           |" << std::endl;
        std::cout << "|  Propositional Logic Connectives  |" << std::endl;
        std::cout << "+-----------------------------------+" << std::endl << std::endl;

        /* Enter the value of P and Q */
        std::cout << "������ P ��ֵ [0/1]: ";
        bool p = inputLogicalValue();
        std::cout << "������ Q ��ֵ [0/1]: ";
        bool q = inputLogicalValue();

        /* Propositional logic connectives */
        std::cout << ">>> ��ȡ: P��Q = " << (p && q) << std::endl << std::endl; // Conjunction
        std::cout << ">>> ��ȡ: P��Q = " << (p || q) << std::endl << std::endl; // Disjunction
        std::cout << ">>> ����: P��Q = " << (!p || q) << std::endl << std::endl; // Implication
        std::cout << ">>> ˫������: P����Q = " << ((!p || q) && (!q || p)) << std::endl << std::endl; // Equivalence

        /* Whether to exit the program */
        std::cout << "�Ƿ��˳����� [y/n]: ";
    } while (!inputLogicalValue('n', 'y'));
    return 0;
}