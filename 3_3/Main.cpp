// Требуется отыскать самый выгодный маршрут между городами.
// Требования: время работы O((N + M)logN), где N - количество городов, M - известных дорог между ними.

#include <iostream>
#include <vector>
#include <queue>

class Vertex {
private:
	int weight;
	int value;
	Vertex* next;

	friend class WeightedListGraph;

public:
	Vertex(int value, int weight) : value(value), weight(weight), next(nullptr) {}
	
	int Value() const { return value; }
	int Weight() const { return weight; }

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
	WeightedListGraph(const WeightedListGraph& graph) = delete;

	// Добавление ребра от from к to.
	void AddEdge(int from, int to, int weight) {
		(*verticies)[from].push_back(Vertex(to, weight));
		(*verticies)[to].push_back(Vertex(from, weight));
	}

	int VerticesCount() const { return verticies->size(); }

	std::vector<Vertex> GetNextVertices(int vertex) const { return (*verticies)[vertex]; }

	int get_min_distance(int from, int to) {
		std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> queue;
		std::vector<unsigned long> dist(VerticesCount(), 2500000001);

		queue.push(std::pair<int, int>(0, from));
		dist[from] = 0;

		while (!queue.empty()) {
			int u = queue.top().second;
			queue.pop();

			for (Vertex vertex : GetNextVertices(u)) {
				int v = vertex.Value();
				int weight = vertex.Weight();

				if (dist[v] > dist[u] + weight) {
					dist[v] = dist[u] + weight;
					queue.push(std::pair<int, int>(dist[v], v));
				}
			}
		}

		return dist[to];
	}

	~WeightedListGraph() { delete verticies; }
};

int main() {
	WeightedListGraph* graph;

	int verticies_count;
	int edges_count;
	int from, to, weight;

	std::cin >> verticies_count;
	graph = new WeightedListGraph(verticies_count);
	std::cin >> edges_count;

	for (int i = 0; i < edges_count; i++) {
		std::cin >> from >> to >> weight;
		graph->AddEdge(from, to, weight);
	}

	std::cin >> from >> to;

	std::cout << graph->get_min_distance(from, to) << std::endl;

	delete graph;

    return 0;
}