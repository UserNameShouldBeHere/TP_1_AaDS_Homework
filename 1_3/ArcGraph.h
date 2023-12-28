#pragma once
#include "IGraph.h"

class ArcGraph : public IGraph {
private:
	std::vector<std::pair<int, int>>* edges;

public:
	ArcGraph(int verticies_count);
	ArcGraph(const ArcGraph& graph) = delete;
	ArcGraph(const IGraph& graph);

	// Добавление ребра от from к to.
	virtual void AddEdge(int from, int to) override;

	virtual int VerticesCount() const override;

	virtual std::vector<int> GetNextVertices(int vertex) const override;
	virtual std::vector<int> GetPrevVertices(int vertex) const override;

	virtual ~ArcGraph();
};
