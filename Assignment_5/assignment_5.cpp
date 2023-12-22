/****************************************************************
 * Project Name:  Assignment_5
 * File Name:     assignment_5.cpp
 * File Function: ���Ŷ�Ԫ��
 * Author:        Jishen Lin (�ּ���)
 * Update Date:   2023/12/22
 ****************************************************************/

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <memory>
#include <conio.h>
#include <limits>
#include <iomanip>

/* Define TreeNode structure */
struct TreeNode {
    int num;
    std::shared_ptr<TreeNode> left, right;
    TreeNode(int n) : num(n), left(NULL), right(NULL) {}
};

/*
 * Function Name:    initNodes
 * Function:         Initialize tree nodes
 * Input Parameters: std::vector<std::shared_ptr<TreeNode>>& nodes
 *                   const std::vector<int>& frequencies
 * Return Value:     void
 */
void initNodes(std::vector<std::shared_ptr<TreeNode>>& nodes, const std::vector<int>& frequencies)
{
    for (int frequency : frequencies)
        nodes.push_back(std::make_shared<TreeNode>(frequency));
}

/*
 * Function Name:    insertSorted
 * Function:         Sort a vector of shared pointers to TreeNode in ascending order
 * Input Parameters: std::vector<std::shared_ptr<TreeNode>>& nodes
 * Return Value:     void
 */
void insertSorted(std::vector<std::shared_ptr<TreeNode>>& nodes)
{
    std::sort(nodes.begin(), nodes.end(), [](const std::shared_ptr<TreeNode>& a, const std::shared_ptr<TreeNode>& b) {
        return a->num < b->num;
        });
}

/*
 * Function Name:    constructTree
 * Function:         Construct an optimal binary tree
 * Input Parameters: std::vector<std::shared_ptr<TreeNode>>& nodes
 * Return Value:     a shared pointer to the root node
 */
std::shared_ptr<TreeNode> constructTree(std::vector<std::shared_ptr<TreeNode>>& nodes)
{
    while (nodes.size() > 1) {
        /* Sort the nodes in the list */
        insertSorted(nodes);

        /* Take the first node as the left child and remove it from the list */
        auto left = nodes.front();
        nodes.erase(nodes.begin());

        /* Take the next node as the right child and remove it from the list */
        auto right = nodes.front();
        nodes.erase(nodes.begin());

        /* Create a new parent node whose value is the sum of the left and right child's values */
        auto parent = std::make_shared<TreeNode>(left->num + right->num);

        /* Assign the left and right children to the parent node */
        parent->left = left;
        parent->right = right;

        /* Add the parent node back to the list of nodes */
        nodes.push_back(parent);
    }
    return nodes.front();
}

/*
 * Function Name:    printCodes
 * Function:         Print the binary prefix codes
 * Input Parameters: const std::shared_ptr<TreeNode>& node
 *                   const std::string& prefix
 * Return Value:     void
 */
void printCodes(const std::shared_ptr<TreeNode>& node, const std::string& prefix)
{
    if (node) {
        printCodes(node->left, prefix + "0");
        if (!node->left && !node->right)
            std::cout << std::setw(5) << node->num << ": " << prefix << std::endl;
        printCodes(node->right, prefix + "1");
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
        std::cout << "������" << prompt << " [������Χ: " << lowerLimit << "~" << upperLimit << "]: ";
        double tempInput;
        std::cin >> tempInput;
        if (std::cin.good() && tempInput == static_cast<int>(tempInput) && tempInput >= lowerLimit && tempInput <= upperLimit) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return static_cast<int>(tempInput);
        }
        else {
            std::cerr << std::endl << ">>> " << prompt << "���벻�Ϸ�������������" << prompt << "��" << std::endl << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
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
        std::cout << "+-----------------------+" << std::endl;
        std::cout << "|      ���Ŷ�Ԫ��       |" << std::endl;
        std::cout << "|  Optimal Binary Tree  |" << std::endl;
        std::cout << "+-----------------------+" << std::endl << std::endl;

        /* Establish optimal binary tree */
        int num = inputInteger(2, INT_MAX, "���Ŷ�Ԫ���ڵ����");
        std::cout << std::endl << ">>> ���������Ŷ�Ԫ���ڵ�" << std::endl << std::endl;
        std::vector<int> frequencies(num);
        for (int i = 0; i < num; i++) {
            char tmp[64];
            sprintf(tmp, "���Ŷ�Ԫ���ĵ� %d ���ڵ�", i + 1);
            frequencies[i] = inputInteger(0, SHRT_MAX, tmp);
        }
        std::vector<std::shared_ptr<TreeNode>> nodes;
        initNodes(nodes, frequencies);
        auto root = constructTree(nodes);

        /* Print the binary prefix codes */
        std::cout << std::endl << ">>> ���Ŷ�Ԫ������" << std::endl << std::endl;
        printCodes(root, "");

        /* Whether to exit the program */
        std::cout << std::endl << "�Ƿ��˳����� [y/n]: ";
    } while (!inputLogicalValue('n', 'y'));
    return 0;
}