/****************************************************************
 * Project Name:  Assignment_4
 * File Name:     assignment_4.cpp
 * File Function: ��С������
 * Author:        Jishen Lin (�ּ���)
 * Update Date:   2023/12/3
 ****************************************************************/

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <limits>
#include <conio.h>

/* Macro definitions */
#define MEMORY_ALLOCATION_ERROR -1
#define INF INT_MAX

/* Define MinimumSpanningTree class */
class MinimumSpanningTree {
private:
    int vertex;
    int** graph;
    int* parent;
    int* key;
    bool* mstSet;
public:
    MinimumSpanningTree(int V);
    ~MinimumSpanningTree();
    int minKey(void);
    void printMST(int startVertex);
    void primMST(int startVertex);
    void setWeight(int src, int dst, int weight);
};

/*
 * Function Name:    MinimumSpanningTree
 * Function:         Constructed function
 * Input Parameters: int V
 * Notes:            Class external implementation of member functions
 */
MinimumSpanningTree::MinimumSpanningTree(int V)
{
    vertex = V;
    graph = new(std::nothrow) int* [vertex];
    if (graph == NULL) {
        std::cerr << "Error: Memory allocation failed." << std::endl;
        exit(MEMORY_ALLOCATION_ERROR);
    }
    for (int i = 0; i < vertex; i++) {
        graph[i] = new(std::nothrow) int[vertex];
        if (graph[i] == NULL) {
            std::cerr << "Error: Memory allocation failed." << std::endl;
            exit(MEMORY_ALLOCATION_ERROR);
        }
    }
    for (int i = 0; i < vertex; i++)
        for (int j = 0; j < vertex; j++)
            graph[i][j] = 0;
    parent = new(std::nothrow) int[vertex];
    if (parent == NULL) {
        std::cerr << "Error: Memory allocation failed." << std::endl;
        exit(MEMORY_ALLOCATION_ERROR);
    }
    key = new(std::nothrow) int[vertex];
    if (key == NULL) {
        std::cerr << "Error: Memory allocation failed." << std::endl;
        exit(MEMORY_ALLOCATION_ERROR);
    }
    mstSet = new(std::nothrow) bool[vertex];
    if (mstSet == NULL) {
        std::cerr << "Error: Memory allocation failed." << std::endl;
        exit(MEMORY_ALLOCATION_ERROR);
    }
}

/*
 * Function Name:    ~MinimumSpanningTree
 * Function:         Destructor
 * Notes:            Class external implementation of member functions
 */
MinimumSpanningTree::~MinimumSpanningTree()
{
    for (int i = 0; i < vertex; i++)
        delete[] graph[i];
    delete[] graph;
    delete[] parent;
    delete[] key;
    delete[] mstSet;
}

/*
 * Function Name:    minKey
 * Function:         Find the edge with the minimum weight
 * Input Parameters: void
 * Return Value:     the edge with the minimum weight
 */
int MinimumSpanningTree::minKey(void)
{
    int minVal = INF, minIndex = -1;
    for (int i = 0; i < vertex; i++) {
        if (!mstSet[i] && key[i] < minVal) {
            minVal = key[i];
            minIndex = i;
        }
    }
    return minIndex;
}

/*
 * Function Name:    printMST
 * Function:         Print minimum spanning tree (MST)
 * Input Parameters: int startVertex
 * Return Value:     void
 */
void MinimumSpanningTree::printMST(int startVertex)
{
    for (int i = startVertex + 1; i < vertex + startVertex; i++)
        std::cout << static_cast<char>(parent[i % vertex] + 'A') << " --(" << graph[i % vertex][parent[i % vertex]] << ")--> " << static_cast<char>(i % vertex + 'A') << std::endl;
}

/*
 * Function Name:    primMST
 * Function:         Generate minimum spanning tree using Prim algorithm
 * Input Parameters: int startVertex
 * Return Value:     void
 */
void MinimumSpanningTree::primMST(int startVertex)
{
    /* Initialize all keys as infinite and mstSet as false */
    for (int i = 0; i < vertex; i++) {
        key[i] = INF;
        mstSet[i] = false;
    }

    /* Initialize the starting vertex in MST */
    key[startVertex] = 0;
    parent[startVertex] = -1;

    /* Prim algorithm */
    for (int count = 0; count < vertex; count++) {
        int u = minKey();
        mstSet[u] = true; // Add the picked vertex to the MST Set
        for (int v = 0; v < vertex; v++)
            if (graph[u][v] && !mstSet[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
    }

    /* Print the constructed minimum spanning tree (MST) */
    printMST(startVertex);
}

/*
 * Function Name:    setWeight
 * Function:         Set the weight of a specific edge
 * Input Parameters: int src
 *                   int dst
 *                   int weight
 * Return Value:     void
 */
void MinimumSpanningTree::setWeight(int src, int dst, int weight)
{
    graph[src][dst] = weight;
    graph[dst][src] = weight;
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
 * Function Name:    inputStartVertex
 * Function:         Input start vertex
 * Input Parameters: int vertex
 * Return Value:     start vertex
 */
int inputStartVertex(int vertex)
{
    std::cout << std::endl << "�����뽨����С����������ʼ�ڵ� [���뷶Χ: A~" << static_cast<char>(vertex + 'A' - 1) << "]: ";
    char optn;
    while (true) {
        optn = _getch();
        if (optn == 0 || optn == -32)
            optn = _getch();
        else if (optn >= 'A' && optn <= vertex + 'A' - 1) {
            std::cout << optn << std::endl << std::endl;
            return optn - 'A';
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
    /* System entry prompt */
    std::cout << "+-------------------------+" << std::endl;
    std::cout << "|       ��С������        |" << std::endl;
    std::cout << "|  Minimum Spanning Tree  |" << std::endl;
    std::cout << "+-------------------------+" << std::endl;

    /* Establish road network */
    std::cout << std::endl << ">>> �봴��·��" << std::endl << std::endl;
    int vertex = inputInteger(2, 'Z' - 'A' + 1, "���У�·���ڵ㣩����");
    MinimumSpanningTree MST(vertex);
    std::cout << std::endl << ">>> ���У�·���ڵ㣩A";
    for (int i = 1; i < vertex; i++)
        std::cout << "��" << static_cast<char>(i + 'A');
    std::cout << " �����ɹ�" << std::endl;

    /* Input the distance between any two cities */
    std::cout << std::endl << ">>> �����������������У�·���ڵ㣩֮��ľ���" << std::endl;
    std::cout << std::endl << ">>> ���������У�·���ڵ㣩֮��û��·������ " << SHRT_MAX << " ��ʾ��������" << std::endl << std::endl;
    for (int i = 0; i < vertex; i++)
        for (int j = i + 1; j < vertex; j++) {
            char tmp[64];
            sprintf(tmp, "���У�·���ڵ㣩%c �� %c ֮��ľ���", i + 'A', j + 'A');
            MST.setWeight(i, j, inputInteger(1, SHRT_MAX, tmp));
        }

    /* Generate minimum spanning tree using Prim algorithm */
    int startVertex = inputStartVertex(vertex);
    std::cout << ">>> ���� Prim ��С������:" << std::endl << std::endl;
    MST.primMST(startVertex);

    /* Wait for enter to quit */
    std::cout << std::endl << "Press Enter to Quit" << std::endl;
    while (_getch() != '\r')
        continue;

    /* Program ends */
    return 0;
}