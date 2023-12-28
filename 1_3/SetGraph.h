#pragma once
#include "IGraph.h"
#include <unordered_map>

class SetGraph : public IGraph {
private:
	std::vector<std::unordered_map<int, int>>* verticies;

public:
	SetGraph(int verticies_count);
	SetGraph(const SetGraph& graph) = delete;
	SetGraph(const IGraph& graph);

	// Добавление ребра от from к to.
	virtual void AddEdge(int from, int to) override;

	virtual int VerticesCount() const override;

	virtual std::vector<int> GetNextVertices(int vertex) const override;
	virtual std::vector<int> GetPrevVertices(int vertex) const override;

	virtual ~SetGraph();
};
