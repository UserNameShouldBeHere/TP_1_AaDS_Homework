#pragma once
#include "IGraph.h"

class Vertex {
private:
	int value;
	Vertex* next;

	friend class ListGraph;

public:
	Vertex(int value);

	~Vertex();
};

class ListGraph : IGraph {
private:
	std::vector<Vertex*>* verticies;

public:
	ListGraph(size_t verticies_count);
	ListGraph(const ListGraph& graph);

	// Добавление ребра от from к to.
	virtual void AddEdge(int from, int to) override;

	virtual int VerticesCount() const override;

	virtual std::vector<int> GetNextVertices(int vertex) const override;
	virtual std::vector<int> GetPrevVertices(int vertex) const override;

	virtual ~ListGraph();
};
