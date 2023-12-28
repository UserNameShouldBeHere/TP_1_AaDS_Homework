#include "ArcGraph.h"
#include <set>

ArcGraph::ArcGraph(int verticies_count) { edges = new std::vector<std::pair<int, int>>(); }

ArcGraph::ArcGraph(const IGraph& graph) {
    edges = new std::vector<std::pair<int, int>>();

    for (int i = 0; i < graph.VerticesCount(); i++) {
        for (int vertex : graph.GetNextVertices(i)) {
            edges->push_back(std::pair<int, int>(i, vertex));
        }
    }
}

void ArcGraph::AddEdge(int from, int to) { edges->push_back(std::pair<int, int>(from, to)); }

int ArcGraph::VerticesCount() const {
    std::set<int> verticies;
    for (std::pair<int, int> edge : *edges) {
        verticies.insert(edge.first);
        verticies.insert(edge.second);
    }

    return verticies.size();
}

std::vector<int> ArcGraph::GetNextVertices(int vertex) const {
    std::vector<int> verticies;
    for (std::pair<int, int> edge : *edges) {
        if (edge.first == vertex)
            verticies.push_back(edge.second);
    }

    return verticies;
}

std::vector<int> ArcGraph::GetPrevVertices(int vertex) const {
    std::vector<int> verticies;
    for (std::pair<int, int> edge : *edges) {
        if (edge.second == vertex)
            verticies.push_back(edge.first);
    }

    return verticies;
}

ArcGraph::~ArcGraph() { delete edges; }
