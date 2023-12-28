#include "ListGraph.h"

Vertex::Vertex(int value) : value(value), next(nullptr) {}

Vertex::~Vertex() { delete next; }

ListGraph::ListGraph(size_t verticies_count) { verticies = new std::vector<Vertex*>(verticies_count); }

ListGraph::ListGraph(const IGraph& graph)
{
    verticies = new std::vector<Vertex*>(graph.VerticesCount());
    Vertex* current;

    for (int i = 0; i < graph.VerticesCount(); i++) {
        std::vector<int> next_verticies = graph.GetNextVertices(i);
        (*verticies)[i] = new Vertex(next_verticies[0]);
        current = (*verticies)[i];
        for (int j = 1; j < next_verticies.size(); j++) {
            current->next = new Vertex(next_verticies[j]);
            current = current->next;
        }
    }
}

void ListGraph::AddEdge(int from, int to) {
    Vertex* current = (*verticies)[from];

    if (!current)
        (*verticies)[from] = new Vertex(to);
    else {
        while (current->next) {
            current = current->next;
        }
        current->next = new Vertex(to);
    }
}

int ListGraph::VerticesCount() const { return verticies->size(); }

std::vector<int> ListGraph::GetNextVertices(int vertex) const {
    std::vector<int> result;
    Vertex* current = (*verticies)[vertex];
    
    while (current) {
        result.push_back(current->value);
        current = current->next;
    }

    return result;
}

std::vector<int> ListGraph::GetPrevVertices(int vertex) const
{
    std::vector<int> result;

    for (int i = 0; i < verticies->size(); i++) {
        std::vector<int> next_verticies = GetNextVertices(i);
        for (int next_vertex : next_verticies) {
            if (next_vertex == vertex)
                result.push_back(i);
        }
    }

    return result;
}

ListGraph::~ListGraph() { delete verticies; }
