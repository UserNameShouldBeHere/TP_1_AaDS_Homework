#include <iostream>
#include <vector>
#include <queue>
#include <set>

class ListGraph {
private:
    std::vector<std::vector<int>>* verticies;

    bool IsCycled(int vertex, std::vector<bool>* visited, int parent) {
        (*visited)[vertex] = true;

        for (int current : (*verticies)[vertex]) {
            if (!(*visited)[current]) {
                if (IsCycled(current, visited, vertex))
                    return true;
            }

            else if (current != parent)
                return true;
        }

        return false;
    }

    void dfs_aux(int v, std::vector<bool>* visited) {
        (*visited)[v] = true;

        for (int i : (*verticies)[v])
            if (!(*visited)[i])
                dfs_aux(i, visited);
    }

    bool isConnected() {
        std::vector<bool>* visited = new std::vector<bool>(verticies->size(), false);

        if (verticies->size() == 0)
            return true;

        for (int i = 0; i < verticies->size(); i++)
            if ((*verticies)[i].size() != 0)
                break;

        dfs_aux(verticies->size() - 1, visited);

        for (int i = 0; i < verticies->size(); i++)
            if ((*visited)[i] == false && (*verticies)[i].size() > 0)
                return false;

        return true;
    }

public:
    ListGraph(int verticies_count) { verticies = new std::vector<std::vector<int>>(verticies_count); }

    void AddEdge(int from, int to) {
        (*verticies)[from].push_back(to);
        (*verticies)[to].push_back(from);
    }

    bool IsTree() {
        std::vector<bool>* visited = new std::vector<bool>(verticies->size(), false);

        if (IsCycled(0, visited, -1))
            return false;

        for (int i = 0; i < verticies->size(); i++)
            if (!(*visited)[i])
                return false;

        return true;
    }

    bool IsEulerian() {
        if (isConnected() == false)
            return false;

        int count = 0;
        for (int i = 0; i < verticies->size(); i++)
            if ((*verticies)[i].size() & 1)
                count++;

        if (count < 2)
            return true;
        else
            return false;
    }

    ~ListGraph() { delete verticies; }
};

int main() {
    ListGraph* graph;

    int verticies_count;
    int edges_count;
    int from, to;

    std::cin >> verticies_count;
    graph = new ListGraph(verticies_count);
    std::cin >> edges_count;

    for (int i = 0; i < edges_count; i++) {
        std::cin >> from >> to;
        graph->AddEdge(from, to);
    }

    std::cout << graph->IsEulerian() << std::endl;

    delete graph;

    return 0;
}
