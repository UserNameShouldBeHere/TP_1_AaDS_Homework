// Дан невзвешенный неориентированный граф.В графе может быть несколько кратчайших путей между какими - то вершинами.Найдите количество различных кратчайших путей между заданными вершинами.
// Требования: сложность O(V + E).

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

struct IGraph {
	virtual ~IGraph() {}

	// Добавление ребра от from к to.
	virtual void AddEdge(int from, int to) = 0;

	virtual int VerticesCount() const = 0;

	virtual std::vector<int> GetNextVertices(int vertex) const = 0;
	virtual std::vector<int> GetPrevVertices(int vertex) const = 0;
};

class MatrixGraph : public IGraph {
private:
	std::vector<std::vector<int>>* verticies;

public:
	MatrixGraph(int verticies_count) { verticies = new std::vector<std::vector<int>>(verticies_count); }

	MatrixGraph(const MatrixGraph& graph) = delete;

	MatrixGraph(const IGraph& graph) {
		verticies = new std::vector<std::vector<int>>(graph.VerticesCount());

		for (int i = 0; i < graph.VerticesCount(); i++) {
			for (int vertex : graph.GetNextVertices(i))
				(*verticies)[i].push_back(vertex);
		}
	}

	// Добавление ребра от from к to.
	virtual void AddEdge(int from, int to) override {
		(*verticies)[from].push_back(to);
		(*verticies)[to].push_back(from);
	}

	virtual int VerticesCount() const override { return verticies->size(); }

	virtual std::vector<int> GetNextVertices(int vertex) const override {
		return (*verticies)[vertex];
	}

	virtual std::vector<int> GetPrevVertices(int vertex) const override {
		std::vector<int> result;

		for (int i = 0; i < verticies->size(); i++) {
			for (int next_vertex : GetNextVertices(i)) {
				if (vertex == next_vertex && std::find(result.begin(), result.end(), i) == result.end())
					result.push_back(i);
			}
		}

		return result;
	}

	virtual ~MatrixGraph() { delete verticies; }
};

int count_shortes_roads(const IGraph& graph, int start, int end) {
	std::vector<bool> visited(graph.VerticesCount(), false);
	std::vector<int> distances(graph.VerticesCount(), 200001);
	std::vector<int> paths(graph.VerticesCount(), 0);
	std::queue<int> queue;

	queue.push(start);
	visited[start] = true;
	distances[start] = 0;
	paths[start] = 1;
	int current_vertex;
	int count = 0;

	while (!queue.empty()) {
		current_vertex = queue.front();
		queue.pop();

		for (int vertex : graph.GetNextVertices(current_vertex)) {
			if (!visited[vertex]) {
				queue.push(vertex);
				visited[vertex] = true;
			}

			if (distances[vertex] > distances[current_vertex] + 1) {
				distances[vertex] = distances[current_vertex] + 1;
				paths[vertex] = paths[current_vertex];
			}
			else if (distances[vertex] == distances[current_vertex] + 1)
				paths[vertex] += paths[current_vertex];
		}
	}

	return paths[end];
}

int main() {
	MatrixGraph* graph;

	int verticies_count;
	int edges_count;
	int from, to;

	std::cin >> verticies_count;
	graph = new MatrixGraph(verticies_count);
	std::cin >> edges_count;

	for (int i = 0; i < edges_count; i++) {
		std::cin >> from >> to;
		graph->AddEdge(from, to);
	}

	std::cin >> from >> to;

	std::cout << count_shortes_roads((IGraph&)(*graph), from, to) << std::endl;

	delete graph;

    return 0;
}

//7
//7
//0 3
//0 1
//1 2
//1 5
//2 4
//4 6
//5 6
//0 6