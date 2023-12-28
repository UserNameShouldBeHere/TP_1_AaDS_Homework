#include "MatrixGraph.h"

MatrixGraph::MatrixGraph(int verticies_count) {
    verticies = new std::vector<std::vector<int>>(verticies_count);
    
    for (int i = 0; i < verticies_count; i++)
        (*verticies)[i] = std::vector<int>(verticies_count, 0);
}

MatrixGraph::MatrixGraph(const IGraph& graph) {
    verticies = new std::vector<std::vector<int>>(graph.VerticesCount());

    for (int i = 0; i < graph.VerticesCount(); i++)
        (*verticies)[i] = std::vector<int>(graph.VerticesCount());
    
    for (int i = 0; i < graph.VerticesCount(); i++) {
        for (int vertex : graph.GetNextVertices(i)) {
            (*verticies)[i][vertex] = 1;
        }
    }
}

void MatrixGraph::AddEdge(int from, int to) { (*verticies)[from][to] = 1; }

int MatrixGraph::VerticesCount() const { return verticies->size(); }

std::vector<int> MatrixGraph::GetNextVertices(int vertex) const {
    std::vector<int> result;

    std::vector<int> next_verticies = (*verticies)[vertex];
    for (int i = 0; i < next_verticies.size(); i++) {
        if (next_verticies[i] != 0)
            result.push_back(i);
    }

    return result;
}

std::vector<int> MatrixGraph::GetPrevVertices(int vertex) const {
    std::vector<int> result;

    for (int i = 0; i < verticies->size(); i++) {
        if ((*verticies)[i][vertex] != 0)
            result.push_back(i);
    }

    return result;
}

MatrixGraph::~MatrixGraph() { delete verticies; }
