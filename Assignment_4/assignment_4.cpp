/****************************************************************
 * Project Name:  Assignment_4
 * File Name:     assignment_4.cpp
 * File Function: 最小生成树
 * Author:        Jishen Lin (林继申)
 * Update Date:   2023/12/22
 ****************************************************************/

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <limits>
#include <conio.h>
#include <vector>
#include <algorithm>

/* Macro definitions */
#define MEMORY_ALLOCATION_ERROR -1
#define INF INT_MAX

/* Define Edge structure */
struct Edge {
    int src;
    int dst;
    int weight;
    bool operator<(const Edge& other) const { return this->weight < other.weight; }
};

/* Define MinimumSpanningTree class */
class MinimumSpanningTree {
private:
    int vertex;
    int total;
    int** graph;
    std::vector<Edge> edges;
    std::vector<int> parent;
    std::vector<int> rank;
    int findSet(int i);
    void unionSets(int x, int y);
public:
    MinimumSpanningTree(int V);
    ~MinimumSpanningTree();
    int getTotal(void) const;
    void kruskalMST(void);
    void setWeight(int src, int dst, int weight);
};

/*
 * Function Name:    findSet
 * Function:         Find in Union-Find
 * Input Parameters: int i
 * Notes:            Class external implementation of member functions
 */
int MinimumSpanningTree::findSet(int i)
{
    if (parent[i] != i)
        parent[i] = findSet(parent[i]);
    return parent[i];
}

/*
 * Function Name:    unionSets
 * Function:         Union in Union-Find
 * Input Parameters: int x
 *                   int y
 * Notes:            Class external implementation of member functions
 */
void MinimumSpanningTree::unionSets(int x, int y)
{
    int xroot = findSet(x), yroot = findSet(y);
    if (rank[xroot] < rank[yroot])
        parent[xroot] = yroot;
    else if (rank[xroot] > rank[yroot])
        parent[yroot] = xroot;
    else {
        parent[yroot] = xroot;
        rank[xroot]++;
    }
}

/*
 * Function Name:    MinimumSpanningTree
 * Function:         Constructed function
 * Input Parameters: int V
 * Notes:            Class external implementation of member functions
 */
MinimumSpanningTree::MinimumSpanningTree(int V)
{
    vertex = V;
    total = 0;
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
}

/*
 * Function Name:    getTotal
 * Function:         Get the total distance
 * Input Parameters: void
 * Return Value:     total distance
 */
int MinimumSpanningTree::getTotal(void) const
{
    return total;
}

/*
 * Function Name:    kruskalMST
 * Function:         Generate minimum spanning tree using Kruskal algorithm
 * Input Parameters: void
 * Return Value:     void
 */
void MinimumSpanningTree::kruskalMST(void)
{
    /* Initialize parent and rank arrays for Union-Find */
    parent.resize(vertex);
    rank.resize(vertex, 0);
    for (int i = 0; i < vertex; ++i) {
        parent[i] = i;
    }

    /* Sort all edges in ascending order of their weights */
    std::sort(edges.begin(), edges.end());
    std::vector<Edge> result; // Stores the edges in the MST
    int count = 0; // Keeps track of the number of edges added to the MST

    /* Iterate through all edges */
    for (const auto& edge : edges) {
        int x = findSet(edge.src); // Find the set of the source vertex
        int y = findSet(edge.dst); // Find the set of the destination vertex
        if (x != y) {
            result.push_back(edge);
            unionSets(x, y);
            count++;
            if (count == vertex - 1)
                break;
        }
    }

    /* Print the edges in the MST */
    for (const auto& edge : result) {
        std::cout << static_cast<char>(edge.src + 'A') << " --(" << edge.weight << ")-- " << static_cast<char>(edge.dst + 'A') << std::endl;
        total += edge.weight;
    }
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
    edges.push_back({ src, dst, weight });
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
        std::cout << "+-------------------------+" << std::endl;
        std::cout << "|       最小生成树        |" << std::endl;
        std::cout << "|  Minimum Spanning Tree  |" << std::endl;
        std::cout << "+-------------------------+" << std::endl;

        /* Establish road network */
        std::cout << std::endl << ">>> 请创建路网" << std::endl << std::endl;
        int vertex = inputInteger(2, 'Z' - 'A' + 1, "城市（路网节点）个数");
        MinimumSpanningTree MST(vertex);
        std::cout << std::endl << ">>> 城市（路网节点）A";
        for (int i = 1; i < vertex; i++)
            std::cout << "、" << static_cast<char>(i + 'A');
        std::cout << " 创建成功" << std::endl;

        /* Input the distance between any two cities */
        std::cout << std::endl << ">>> 请输入任意两个城市（路网节点）之间的距离" << std::endl;
        std::cout << std::endl << ">>> 若两个城市（路网节点）之间没有路请输入 " << SHRT_MAX << " 表示输入上限" << std::endl << std::endl;
        for (int i = 0; i < vertex; i++)
            for (int j = i + 1; j < vertex; j++) {
                char tmp[64];
                sprintf(tmp, "城市（路网节点）%c 和 %c 之间的距离", i + 'A', j + 'A');
                MST.setWeight(i, j, inputInteger(1, SHRT_MAX, tmp));
            }

        /* Generate minimum spanning tree using Kruskal algorithm */
        std::cout << std::endl << ">>> 建立 Kruskal 最小生成树:" << std::endl << std::endl;
        MST.kruskalMST();
        std::cout << std::endl << ">>> Kruskal 最小生成树的总权重为 " << MST.getTotal() << std::endl << std::endl;

        /* Whether to exit the program */
        std::cout << "是否退出程序 [y/n]: ";
    } while (!inputLogicalValue('n', 'y'));
    return 0;
}