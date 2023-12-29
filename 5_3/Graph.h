// Для построения минимального остовного дерева используйте алгоритм Прима.

#include <iostream>
#include <vector>
#include <queue>

class Vertex {
private:
	float weight;
	int value;
	Vertex* next;

	friend class WeightedListGraph;

public:
	Vertex(int value, float weight) : value(value), weight(weight), next(nullptr) {}

	int Value() const { return value; }
	float Weight() const { return weight; }

	~Vertex() { delete next; }
};

class Comparator {
public:
	bool operator() (Vertex* lhs, Vertex* rhs) {
		return lhs->Weight() > rhs->Weight();
	}
};

class WeightedListGraph {
private:
	std::vector<std::vector<Vertex>>* verticies;

public:
	WeightedListGraph(size_t verticies_count) { verticies = new std::vector<std::vector<Vertex>>(verticies_count); }

	// Добавление ребра от from к to.
	void AddEdge(int from, int to, float weight) {
		(*verticies)[from].push_back(Vertex(to, weight));
		(*verticies)[to].push_back(Vertex(from, weight));
	}

	int VerticesCount() const { return verticies->size(); }

	std::vector<Vertex> GetNextVertices(int vertex) const { return (*verticies)[vertex]; }

	float Create_mst() {
		std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> queue;
		std::vector<float> distances(VerticesCount(), 2500000001);
		std::vector<bool> in_wst(verticies->size(), false);

		int initial_vertex = 0;
		float result = 0;
		queue.push(std::pair<int, int>(0, initial_vertex));
		distances[initial_vertex] = 0;

		while (!queue.empty()) {
			int current = queue.top().second;
			queue.pop();

			in_wst[current] = true;

			for (Vertex vertex : GetNextVertices(current)) {
				int value = vertex.Value();
				float weight = vertex.Weight();

				if (!in_wst[value] && weight < distances[value]) {
					distances[value] = weight;
					queue.push(std::pair<int, int>(distances[value], value));
				}
			}
		}

		for (int i = 0; i < verticies->size(); i++)
			result += distances[i];

        return result;
	}

	~WeightedListGraph() { delete verticies; }
};

//int main() {
//	WeightedListGraph* graph;
//
//	int verticies_count;
//	int edges_count;
//	int from, to, weight;
//
//	std::cin >> verticies_count;
//	graph = new WeightedListGraph(verticies_count);
//	std::cin >> edges_count;
//
//	for (int i = 0; i < edges_count; i++) {
//		std::cin >> from >> to >> weight;
//		graph->AddEdge(from - 1, to - 1, weight);
//	}
//
//	std::cout << graph->Create_mst() << std::endl;
//
//	delete graph;
//
//	return 0;
//}