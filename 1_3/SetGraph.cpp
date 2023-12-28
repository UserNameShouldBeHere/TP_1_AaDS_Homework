#include "SetGraph.h"

SetGraph::SetGraph(int verticies_count) { verticies = new std::vector<std::unordered_map<int, int>>(verticies_count); }

SetGraph::SetGraph(const IGraph& graph) {
    verticies = new std::vector<std::unordered_map<int, int>>(graph.VerticesCount());

    for (int i = 0; i < graph.VerticesCount(); i++) {
        for (int vertex : graph.GetNextVertices(i)) {
            (*verticies)[i].insert(std::pair<int, int>(vertex, vertex));
        }
    }
}

void SetGraph::AddEdge(int from, int to) { (*verticies)[from].insert(std::pair<int, int>(to, to)); }

int SetGraph::VerticesCount() const { return verticies->size(); }

std::vector<int> SetGraph::GetNextVertices(int vertex) const {
    std::vector<int> result;

    for (int i = 0; i < verticies->size(); i++) {
        if ((*verticies)[vertex].find(i) != (*verticies)[vertex].end())
            result.push_back(i);
    }

    return result;
}

std::vector<int> SetGraph::GetPrevVertices(int vertex) const {
    std::vector<int> result;

    for (int i = 0; i < verticies->size(); i++) {
        if ((*verticies)[i].find(vertex) != (*verticies)[i].end())
            result.push_back(i);
    }

    return result;
}

SetGraph::~SetGraph() { delete verticies; }
