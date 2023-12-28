#pragma once
#include "IGraph.h"

class MatrixGraph : public IGraph {
private:
	std::vector<std::vector<int>>* verticies;

public:
	MatrixGraph(int verticies_count);
	MatrixGraph(const MatrixGraph& graph) = delete;
	MatrixGraph(const IGraph& graph);

	// Добавление ребра от from к to.
	virtual void AddEdge(int from, int to) override;

	virtual int VerticesCount() const override;

	virtual std::vector<int> GetNextVertices(int vertex) const override;
	virtual std::vector<int> GetPrevVertices(int vertex) const override;

	virtual ~MatrixGraph();
};
