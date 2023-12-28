#include <iostream>
#include "ListGraph.h"
#include "MatrixGraph.h"

int main() {
    // ListGraph
    ListGraph* list_graph = new ListGraph(3);
    list_graph->AddEdge(0, 1);
    list_graph->AddEdge(2, 1);
    list_graph->AddEdge(0, 2);
    list_graph->AddEdge(1, 2);
    list_graph->AddEdge(2, 0);
    list_graph->AddEdge(2, 2);

    ListGraph* new_graph = new ListGraph((IGraph&)(*list_graph));
    bool flag = true;
    for (int i = 0; i < 3; i++) {
        std::vector<int> next_vertecies = list_graph->GetNextVertices(i);
        std::vector<int> new_next_vertecies = new_graph->GetNextVertices(i);
        std::vector<int> prev_vertecies = list_graph->GetPrevVertices(i);
        std::vector<int> new_prev_vertecies = new_graph->GetPrevVertices(i);
        for (int j = 0; j < next_vertecies.size(); j++) {
            if (next_vertecies[j] != new_next_vertecies[j]) {
                flag = false;
                std::cout << "Error" << std::endl;
                break;
            }
        }
        for (int j = 0; j < prev_vertecies.size(); j++) {
            if (prev_vertecies[j] != new_prev_vertecies[j]) {
                flag = false;
                std::cout << "Error" << std::endl;
                break;
            }
        }
        if (!flag)
            break;
    }

    if (flag)
        std::cout << "List graph done!" << std::endl;

    delete new_graph;

    // MatrixGraph
    MatrixGraph* matrix_graph = new MatrixGraph((IGraph&)(*list_graph));
    flag = true;
    for (int i = 0; i < 3; i++) {
        std::vector<int> next_vertecies = list_graph->GetNextVertices(i);
        std::vector<int> new_next_vertecies = matrix_graph->GetNextVertices(i);
        std::vector<int> prev_vertecies = list_graph->GetPrevVertices(i);
        std::vector<int> new_prev_vertecies = matrix_graph->GetPrevVertices(i);
        for (int vertex : next_vertecies) {
            if (std::find(new_next_vertecies.begin(), new_next_vertecies.end(), vertex) == new_next_vertecies.end()) {
                flag = false;
                std::cout << "Error" << std::endl;
                break;
            }
        }
        for (int vertex : prev_vertecies) {
            if (std::find(new_prev_vertecies.begin(), new_prev_vertecies.end(), vertex) == new_prev_vertecies.end()) {
                flag = false;
                std::cout << "Error" << std::endl;
                break;
            }
        }
        if (!flag)
            break;
    }

    if (flag)
        std::cout << "Matrix graph done!" << std::endl;

    delete matrix_graph;

    //


    //for (int vertex : matrix_graph->GetNextVertices(2))
    //    std::cout << vertex << ' ';
    //std::cout << std::endl;

    delete list_graph;

    return 0;
}