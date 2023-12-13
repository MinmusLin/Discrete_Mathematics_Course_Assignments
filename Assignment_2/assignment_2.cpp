/****************************************************************
 * Project Name:  Assignment_2
 * File Name:     assignment_2.cpp
 * File Function: 命题逻辑推理
 * Author:        Jishen Lin (林继申)
 * Update Date:   2023/12/13
 ****************************************************************/

#include <iostream>
#include <conio.h>
#include <cmath>

/*
 * Function Name:    main
 * Function:         Main function
 * Return Value:     0
 */
int main()
{
    /* System entry prompt */
    std::cout << "+---------------------------------+" << std::endl;
    std::cout << "|          命题逻辑推理           |" << std::endl;
    std::cout << "|  Propositional Logic Reasoning  |" << std::endl;
    std::cout << "+---------------------------------+" << std::endl << std::endl;

    /* Problem description */
    std::cout << ">>> 问题描述" << std::endl;
    std::cout << "    [命题 1] 营业员 A 或 B 偷了手表" << std::endl;
    std::cout << "    [命题 2] 若 A 作案，则作案不在营业时间" << std::endl;
    std::cout << "    [命题 3] 若 B 提供的证据正确，则货柜未上锁" << std::endl;
    std::cout << "    [命题 4] 若 B 提供的证据不正确，则作案发生在营业时间" << std::endl;
    std::cout << "    [命题 5] 货柜上了锁" << std::endl << std::endl;
    std::cout << ">>> 命题变元表示" << std::endl;
    std::cout << "    [命题 A] 营业员 A 偷了手表" << std::endl;
    std::cout << "    [命题 B] 营业员 B 偷了手表" << std::endl;
    std::cout << "    [命题 C] 作案不在营业时间" << std::endl;
    std::cout << "    [命题 D] B 提供的证据正确" << std::endl;
    std::cout << "    [命题 E] 货柜未上锁" << std::endl << std::endl;

    /* Propositional logic reasoning */
    for (int i = 0; i < pow(2, 5); i++) {
        bool A = i & 0b1;
        bool B = i & 0b10;
        bool C = i & 0b100;
        bool D = i & 0b1000;
        bool E = i & 0b10000;
        if ((A || B) && (!A || C) && (!D || E) && (D || !C) && !E) {
            std::cout << ">>> 命题逻辑推理结果: A = " << (A ? "True" : "False") << ", B = " << (B ? "True" : "False") << std::endl << std::endl;
            std::cout << ">>> 所以营业员 " << (A ? "A" : "") << (B ? "B" : "") << " 偷了手表" << std::endl;
        }
    }

    /* Wait for enter to quit */
    std::cout << std::endl << "Press Enter to Quit" << std::endl;
    while (_getch() != '\r')
        continue;

    /* Program ends */
    return 0;
}