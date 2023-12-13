/****************************************************************
 * Project Name:  Assignment_2
 * File Name:     assignment_2.cpp
 * File Function: �����߼�����
 * Author:        Jishen Lin (�ּ���)
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
    std::cout << "|          �����߼�����           |" << std::endl;
    std::cout << "|  Propositional Logic Reasoning  |" << std::endl;
    std::cout << "+---------------------------------+" << std::endl << std::endl;

    /* Problem description */
    std::cout << ">>> ��������" << std::endl;
    std::cout << "    [���� 1] ӪҵԱ A �� B ͵���ֱ�" << std::endl;
    std::cout << "    [���� 2] �� A ����������������Ӫҵʱ��" << std::endl;
    std::cout << "    [���� 3] �� B �ṩ��֤����ȷ�������δ����" << std::endl;
    std::cout << "    [���� 4] �� B �ṩ��֤�ݲ���ȷ��������������Ӫҵʱ��" << std::endl;
    std::cout << "    [���� 5] ����������" << std::endl << std::endl;
    std::cout << ">>> �����Ԫ��ʾ" << std::endl;
    std::cout << "    [���� A] ӪҵԱ A ͵���ֱ�" << std::endl;
    std::cout << "    [���� B] ӪҵԱ B ͵���ֱ�" << std::endl;
    std::cout << "    [���� C] ��������Ӫҵʱ��" << std::endl;
    std::cout << "    [���� D] B �ṩ��֤����ȷ" << std::endl;
    std::cout << "    [���� E] ����δ����" << std::endl << std::endl;

    /* Propositional logic reasoning */
    for (int i = 0; i < pow(2, 5); i++) {
        bool A = i & 0b1;
        bool B = i & 0b10;
        bool C = i & 0b100;
        bool D = i & 0b1000;
        bool E = i & 0b10000;
        if ((A || B) && (!A || C) && (!D || E) && (D || !C) && !E) {
            std::cout << ">>> �����߼�������: A = " << (A ? "True" : "False") << ", B = " << (B ? "True" : "False") << std::endl << std::endl;
            std::cout << ">>> ����ӪҵԱ " << (A ? "A" : "") << (B ? "B" : "") << " ͵���ֱ�" << std::endl;
        }
    }

    /* Wait for enter to quit */
    std::cout << std::endl << "Press Enter to Quit" << std::endl;
    while (_getch() != '\r')
        continue;

    /* Program ends */
    return 0;
}