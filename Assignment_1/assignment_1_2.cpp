/****************************************************************
 * Project Name:  Assignment_1_2
 * File Name:     assignment_1_2.cpp
 * File Function: 真值表、主范式
 * Author:        Jishen Lin (林继申)
 * Update Date:   2023/12/21
 ****************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <cmath>
#include <cctype>
#include <conio.h>
#include <algorithm>

/*
 * Function Name:    extractVariables
 * Function:         Split expression into unique variables
 * Input Parameters: const std::string& expression
 * Return Value:     variables
 */
std::set<char> extractVariables(const std::string& expression)
{
    std::set<char> variables;
    for (char ch : expression)
        if (isalpha(ch))
            variables.insert(ch);
    return variables;
}

/*
 * Function Name:    isOperator
 * Function:         Determine whether a character is an operator
 * Input Parameters: char ch
 * Return Value:     true / false
 */
bool isOperator(char ch)
{
    return ch == '!' || ch == '&' || ch == '|' || ch == '^' || ch == '~';
}

/*
 * Function Name:    getPrecedence
 * Function:         Get precedence
 * Input Parameters: char op
 * Return Value:     precedence
 */
int getPrecedence(char op)
{
    switch (op) {
        case '!': // Negation
            return 3;
        case '&': // Conjunction
        case '|': // Disjunction
            return 2;
        case '^': // Implication
        case '~': // Equivalence
            return 1;
        default: // Default
            return 0;
    }
}

/*
 * Function Name:    applyOperator
 * Function:         Apply operator
 * Input Parameters: char op
 *                   bool a
 *                   bool b
 * Return Value:     true / false
 */
bool applyOperator(char op, bool a, bool b = false)
{
    switch (op) {
        case '!':
            return !a; // Negation
        case '&':
            return a && b; // Conjunction
        case '|':
            return a || b; // Disjunction
        case '^':
            return !a || b; // Implication
        case '~':
            return a == b; // Equivalence
        default:
            exit(-1);
    }
}

/*
 * Function Name:    infixToPostfix
 * Function:         Convert an infix mathematical expression to its corresponding postfix notation
 * Input Parameters: const std::string& expression
 * Return Value:     a queue containing the postfix notation of the input expression
 */
std::queue<char> infixToPostfix(const std::string& expression)
{
    std::stack<char> ops; // Stack to hold operators
    std::queue<char> postfix; // Queue to hold postfix expression
    for (char ch : expression) {
        if (isalpha(ch)) {
            // If character is an operand (variable), add it to the postfix queue
            postfix.push(ch);
        }
        else if (ch == '(') {
            // If character is an opening parenthesis, push it onto the stack
            ops.push(ch);
        }
        else if (ch == ')') {
            // If character is a closing parenthesis, pop all operators from the stack
            // and add to postfix queue until an opening parenthesis is encountered
            while (!ops.empty() && ops.top() != '(') {
                postfix.push(ops.top());
                ops.pop();
            }
            ops.pop(); // Pop the opening parenthesis from the stack
        }
        else if (isOperator(ch)) {
            // If character is an operator, pop operators from the stack
            // with higher or equal precedence and add to postfix queue
            while (!ops.empty() && getPrecedence(ops.top()) >= getPrecedence(ch)) {
                postfix.push(ops.top());
                ops.pop();
            }
            ops.push(ch); // Push the current operator onto the stack
        }
    }
    while (!ops.empty()) {
        // After reading the expression, pop any remaining
        // operators from the stack and add to postfix queue
        postfix.push(ops.top());
        ops.pop();
    }
    return postfix; // Return the postfix expression
}

/*
 * Function Name:    calculatePostfix
 * Function:         Calculate a given postfix notation expression
 * Input Parameters: std::queue<char>& postfix
 *                   const std::map<char, bool>& values
 * Return Value:     true / false
 */
bool calculatePostfix(std::queue<char>& postfix, const std::map<char, bool>& values)
{
    std::stack<bool> s; // Stack to hold boolean values during calculation
    while (!postfix.empty()) {
        char ch = postfix.front();
        postfix.pop();
        if (isalpha(ch))
            s.push(values.at(ch)); // If the character is an operand, push its boolean value onto the stack
        else {
            if (ch == '!') {
                bool a = s.top(); // Pop the top value
                s.pop(); // Remove the top value from the stack
                s.push(!a); // Apply the NOT operation and push the result back onto the stack
            }
            else {
                bool b = s.top(); // Pop the first (right operand) value
                s.pop(); // Remove the value from the stack
                bool a = s.top(); // Pop the second (left operand) value
                s.pop(); // Remove the value from the stack
                s.push(applyOperator(ch, a, b)); // Apply the binary operation and push the result back onto the stack
            }
        }
    }
    return s.top(); // Return the final result from the top of the stack
}

/*
 * Function Name:    calculateExpression
 * Function:         Calculate expression
 * Input Parameters: const std::string& expression
 *                   const std::map<char, bool>& values
 * Return Value:     true / false
 */
bool calculateExpression(const std::string& expression, const std::map<char, bool>& values)
{
    /* Convert an infix mathematical expression to its corresponding postfix notation */
    auto postfix = infixToPostfix(expression);

    /* Calculate a given postfix notation expression */
    return calculatePostfix(postfix, values);
}

/*
 * Function Name:    printBinary
 * Function:         Print binary number with specified number of bits
 * Input Parameters: int number
 *                   int bits
 * Return Value:     void
 */
void printBinary(int number, int bits)
{
    for (int i = bits - 1; i >= 0; i--)
        std::cout << ((number >> i) & 1);
}

/*
 * Function Name:    outputTruthTableAndNormalForms
 * Function:         Output truth table and normal forms (CNF and DNF)
 * Input Parameters: const std::string& expression
 * Return Value:     void
 */
void outputTruthTableAndNormalForms(const std::string& expression)
{
    /* Function to print the separator line in the truth table */
    auto printSeparator = [](int numVariables) {
        for (int i = 0; i < numVariables; i++)
            std::cout << "+-----";
        std::cout << "+-------+" << std::endl;
        };

    /* Extract unique variables from the expression */
    auto variables = extractVariables(expression);
    int numVariables = static_cast<int>(variables.size());
    std::cout << std::endl << ">>> 变量个数: " << numVariables << std::endl;

    /* Start printing the truth table */
    std::cout << std::endl << ">>> 真值表" << std::endl << std::endl;
    printSeparator(numVariables);

    /* Print the header row of the truth table */
    std::cout << "| ";
    for (char var : variables)
        std::cout << " " << var << "  | ";
    std::cout << "Value |" << std::endl;
    printSeparator(numVariables);

    /* Store the results of the expression for each combination of variables */
    std::vector<int> results;
    for (int i = 0; i < std::pow(2, numVariables); i++) {
        /* Set the values for each variable and print the row in the truth table */
        std::cout << "|  ";
        std::map<char, bool> values;
        int index = 0;
        for (char var : variables) {
            values[var] = ((i >> (numVariables - 1 - index++)) & 1) == 1;
            std::cout << values[var] << "  |  ";
        }

        /* Calculate the result of the expression with the current set of values */
        bool result = calculateExpression(expression, values);
        results.push_back(result ? 1 : 0);
        std::cout << " " << result << "   |" << std::endl;
    }
    printSeparator(numVariables);

    /* Print the main conjunctive normal form (CNF) */
    bool first = true;
    std::cout << std::endl << ">>> 主合取范式: ";
    bool isAlwaysTrue = std::find(results.begin(), results.end(), 0) == results.end(); // Check if the expression is always true
    if (isAlwaysTrue)
        std::cout << "1";
    else {
        /* For each false result, add a clause to the CNF */
        for (int i = 0; i < std::pow(2, numVariables); i++)
            if (results[i] == 0) {
                if (first) {
                    std::cout << "M<" << i << ">";
                    first = false;
                }
                else
                    std::cout << "∧M<" << i << ">";
            }
    }

    /* Print false sssignments */
    first = true;
    std::cout << std::endl << std::endl << ">>> 成假赋值: ";
    if (isAlwaysTrue)
        std::cout << "无";
    else {
        for (int i = 0; i < std::pow(2, numVariables); i++)
            if (results[i] == 0) {
                if (first) {
                    printBinary(i, numVariables);
                    first = false;
                }
                else {
                    std::cout << "、";
                    printBinary(i, numVariables);
                }
            }
    }

    /* Print the main disjunctive normal form (DNF) */
    first = true;
    std::cout << std::endl << std::endl << ">>> 主析取范式: ";
    bool isAlwaysFalse = std::find(results.begin(), results.end(), 1) == results.end(); // Check if the expression is always false
    if (isAlwaysFalse)
        std::cout << "0";
    else {
        /* For each true result, add a clause to the DNF */
        for (int i = 0; i < std::pow(2, numVariables); i++)
            if (results[i] == 1) {
                if (first) {
                    std::cout << "m<" << i << ">";
                    first = false;
                }
                else
                    std::cout << "∨m<" << i << ">";
            }
    }

    /* Print true sssignments */
    first = true;
    std::cout << std::endl << std::endl << ">>> 成真赋值: ";
    if (isAlwaysFalse)
        std::cout << "无";
    else {
        for (int i = 0; i < std::pow(2, numVariables); i++)
            if (results[i] == 1) {
                if (first) {
                    printBinary(i, numVariables);
                    first = false;
                }
                else {
                    std::cout << "、";
                    printBinary(i, numVariables);
                }
            }
    }
    std::cout << std::endl << std::endl;
}

/*
 * Function Name:    replaceAll
 * Function:         Replace all occurrences of a substring in a string with another substring
 * Input Parameters: std::string str
 *                   const std::string& from
 *                   const std::string& to
 * Return Value:     string
 */
std::string replaceAll(std::string str, const std::string& from, const std::string& to)
{
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to); // Replace from with to at start_pos
        start_pos += to.length(); // Move past the end of the newly inserted substring
    }
    return str;
}

/*
 * Function Name:    replaceSymbols
 * Function:         Replace specific symbol substrings in the input string with their designated replacements
 * Input Parameters: std::string input
 * Return Value:     string
 */
std::string replaceSymbols(std::string input)
{
    input = replaceAll(input, "&", "∧"); // Replace "&" with "∧"
    input = replaceAll(input, "|", "∨"); // Replace "|" with "∨"
    input = replaceAll(input, "~", "←→"); // Replace "~" with "←→"
    input = replaceAll(input, "^", "→"); // Replace "^" with "→"
    return input;
}

/*
 * Function Name:    isValidExpression
 * Function:         Check if a expression is valid
 * Input Parameters: const std::string& expression
 * Return Value:     true / false
 */
bool isValidExpression(const std::string& expression)
{
    if (expression.empty()) {
        std::cout << ">>> 命题公式为空，请重新输入！" << std::endl;
        return false;
    }
    std::stack<char> parentheses;
    char previous = '\0';
    for (char ch : expression) {
        if (!((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')) && !isOperator(ch) && ch != '(' && ch != ')') {
            std::cout << ">>> 命题公式存在非法字符输入，请重新输入！" << std::endl;
            return false;
        }
        if (previous == '\0' && (ch == '&' || ch == '|' || ch == '~' || ch == '^')) {
            std::cout << ">>> 命题公式不能以二元运算符开始，请重新输入！" << std::endl;
            return false;
        }
        if (previous == '(' && ch == ')') {
            std::cout << ">>> 命题公式存在空括号，请重新输入！" << std::endl;
            return false;
        }
        if (previous == '!' && ch == '!') {
            std::cout << ">>> 命题公式存在不合法的连续取非操作，请重新输入！" << std::endl;
            return false;
        }
        if (ch == '!' && isalpha(previous)) {
            std::cout << ">>> 命题公式中取非运算符前不可连接变量，请重新输入！" << std::endl;
            return false;
        }
        if ((isalpha(ch) && previous == ')') || (ch == '(' && isalpha(previous))) {
            std::cout << ">>> 命题公式中变量与括号的连接不正确，请重新输入！" << std::endl;
            return false;
        }
        if (ch == '(')
            parentheses.push(ch);
        else if (ch == ')') {
            if (parentheses.empty()) {
                std::cout << ">>> 命题公式括号不匹配，请重新输入！" << std::endl;
                return false;
            }
            parentheses.pop();
        }
        if (isalpha(ch) && isalpha(previous)) {
            std::cout << ">>> 命题公式仅适用于单字符变量，不适用于多字符变量，请重新输入！" << std::endl;
            return false;
        }
        if ((ch == '&' || ch == '|' || ch == '~' || ch == '^') && (!isalpha(previous) && previous != ')')) {
            std::cout << ">>> 命题公式中每个二元运算符前后必须连接变量，请重新输入！" << std::endl;
            return false;
        }
        previous = ch;
    }
    if (previous == '&' || previous == '|' || previous == '~' || previous == '^' || previous == '!') {
        std::cout << ">>> 命题公式不能以运算符结尾，请重新输入！" << std::endl;
        return false;
    }
    if (!parentheses.empty()) {
        std::cout << ">>> 命题公式括号不匹配，请重新输入！" << std::endl;
        return false;
    }
    return true;
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
        std::cout << "+-----------------------------------+" << std::endl;
        std::cout << "|          真值表、主范式           |" << std::endl;
        std::cout << "|  Truth Table and Prime Implicant  |" << std::endl;
        std::cout << "+-----------------------------------+" << std::endl << std::endl;
        std::cout << ">>> 命题公式输入要求" << std::endl;
        std::cout << "    [1] 字符 '!' 表示非（Negation）" << std::endl;
        std::cout << "    [2] 字符 '&' 表示与（Conjunction）" << std::endl;
        std::cout << "    [3] 字符 '|' 表示或（Disjunction）" << std::endl;
        std::cout << "    [4] 字符 '^' 表示蕴含（Implication）" << std::endl;
        std::cout << "    [5] 字符 '~' 表示等值（Equivalence）" << std::endl;
        std::cout << "    [6] 命题公式中只存在以下 59 种字符: a-z A-Z ! & | ^ ~ ( )" << std::endl;
        std::cout << "    [7] 命题公式中的括号嵌套匹配" << std::endl;
        std::cout << "    [8] 命题公式仅适用于单字符变量，不适用于多字符变量" << std::endl;
        std::cout << "    [9] 命题公式中每个运算符前后必须连接变量（\"!!a\"请输入为\"!(!a)\"）" << std::endl;

        /* Input a a propositional formula */
        std::string expression;
        do {
            std::cout << std::endl << "请输入命题公式: ";
            std::cin >> expression;
            std::cout << std::endl;
        } while (!isValidExpression(expression));
        std::cout << ">>> 命题公式: " << replaceSymbols(expression) << std::endl;

        /* Output truth table and normal forms (CNF and DNF) */
        outputTruthTableAndNormalForms(expression);

        /* Whether to exit the program */
        std::cout << "是否退出程序 [y/n]: ";
    } while (!inputLogicalValue('n', 'y'));
    return 0;
}