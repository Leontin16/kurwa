/*
#include <iostream>
#include <chrono>
#include <random>
#include <queue>
#include <functional>
#include "graph.h"
#include "dijkstra.h"
using namespace std;
using namespace std::chrono;

double algorithmA(const Graph& graph, int source) {
    auto start = high_resolution_clock::now();
    Vector<int> distances = Dijkstra::findShortestPaths(graph, source);
    auto end = high_resolution_clock::now();

    duration<double> duration = end - start;
    return duration.count();
}

// Алгоритм B - Дейкстра с бинарной кучей (зачем)
double algorithmB(const Graph& graph, int source) {
    auto start = high_resolution_clock::now();

    int n = graph.getNumVertices();
    vector<int> distances(n, INT_MAX);
    distances[source] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({ 0, source });

    while (!pq.empty()) {
        int u = pq.top().second;
        int dist_u = pq.top().first;
        pq.pop();

        if (dist_u != distances[u]) continue;

        const Vector<Edge>& neighbors = graph.getNeighbors(u);
        for (int i = 0; i < neighbors.size(); i++) {
            const Edge& edge = neighbors[i];
            int v = edge.destination;
            int weight = edge.weight;

            if (distances[u] < INT_MAX - weight) {
                int newDistance = distances[u] + weight;

                if (newDistance < distances[v]) {
                    distances[v] = newDistance;
                    pq.push({ newDistance, v });
                }
            }
        }
    }

    auto end = high_resolution_clock::now();
    duration<double> duration = end - start;
    return duration.count();
}

Graph generateRandomGraph(int n, int m, int q, int r) {
    Graph graph(n);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> vertex_dist(0, n - 1);
    uniform_int_distribution<> weight_dist(q, r);

    int edges_added = 0;
    while (edges_added < m) {
        int u = vertex_dist(gen);
        int v = vertex_dist(gen);
        int w = weight_dist(gen);

        if (u != v) {
            graph.addEdge(u, v, w);
            edges_added++;
        }
    }

    return graph;
}

int main() {
    setlocale(LC_ALL, "RU");

    try {
        cout << "=== ПРОГРАММА ДЛЯ ЭКСПЕРИМЕНТОВ ===" << endl;
        cout << "Введите параметры графа:" << endl;

        int n, m, q, r;
        cout << "Число вершин (n): ";
        cin >> n;
        cout << "Число рёбер (m): ";
        cin >> m;
        cout << "Нижняя граница весов (q): ";
        cin >> q;
        cout << "Верхняя граница весов (r): ";
        cin >> r;

        if (n <= 0 || m < 0 || q < 0 || r < q) {
            throw "Неверные параметры графа";
        }

        cout << "\nГенерация случайного графа..." << endl;
        Graph graph = generateRandomGraph(n, m, q, r);

        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> source_dist(0, n - 1);
        int source = source_dist(gen);

        cout << "Начальная вершина: " << source << endl;

        cout << "\nЗапуск алгоритмов..." << endl;

        double timeA = algorithmA(graph, source);
        double timeB = algorithmB(graph, source);

        cout << "\n=== РЕЗУЛЬТАТЫ ЭКСПЕРИМЕНТА ===" << endl;
        cout << "Алгоритм A (15-куча): " << timeA << " секунд" << endl;
        cout << "Алгоритм B (бинарная куча): " << timeB << " секунд" << endl;
        cout << "Отношение времени (A/B): " << (timeA / timeB) << endl;

        cout << "\n=== ДОПОЛНИТЕЛЬНЫЕ ЭКСПЕРИМЕНТЫ ===" << endl;
        vector<int> test_sizes = { 100, 500, 1000, 2000 };

        for (int test_n : test_sizes) {
            int test_m = test_n * 2;
            Graph test_graph = generateRandomGraph(test_n, test_m, q, r);
            int test_source = source_dist(gen) % test_n;

            double test_timeA = algorithmA(test_graph, test_source);
            double test_timeB = algorithmB(test_graph, test_source);

            cout << "n=" << test_n << ", m=" << test_m << ": ";
            cout << "A=" << test_timeA << "s, B=" << test_timeB << "s, A/B=" << (test_timeA / test_timeB) << endl;
        }

    }
    catch (const char* error) {
        cout << "Ошибка: " << error << endl;
        return 1;
    }

    return 0;
}

*/

#include <iostream>
#include <chrono>
#include <random>
#include "graph.h"
#include "dijkstra.h"
#include "vector.h"
#include <climits>
using namespace std;
using namespace std::chrono;

// Алгоритм A - Дейкстра с 15-кучей (наша реализация)
double algorithmA(const Graph& graph, int source) {
    auto start = high_resolution_clock::now();
    Vector<int> distances = Dijkstra::findShortestPaths(graph, source);
    auto end = high_resolution_clock::now();

    duration<double> duration = end - start;
    return duration.count();
}

// Алгоритм B - Дейкстра с метками (массивы)
double algorithmB(const Graph& graph, int source) {
    auto start = high_resolution_clock::now();

    int n = graph.getNumVertices();
    Vector<int> distances(n);
    Vector<bool> visited(n);

    // Инициализация
    for (int i = 0; i < n; i++) {
        distances[i] = INT_MAX;
        visited[i] = false;
    }
    distances[source] = 0;

    // Основной цикл
    for (int i = 0; i < n; i++) {
        // Находим вершину с минимальным расстоянием среди непосещенных
        int minDistance = INT_MAX;
        int u = -1;

        for (int j = 0; j < n; j++) {
            if (!visited[j] && distances[j] < minDistance) {
                minDistance = distances[j];
                u = j;
            }
        }

        if (u == -1 || distances[u] == INT_MAX) {
            break;
        }

        visited[u] = true;

        // Обновляем расстояния до соседей
        const Vector<Edge>& neighbors = graph.getNeighbors(u);
        for (int j = 0; j < neighbors.size(); j++) {
            const Edge& edge = neighbors[j];
            int v = edge.destination;
            int weight = edge.weight;

            if (!visited[v] && distances[u] < INT_MAX - weight) {
                int newDistance = distances[u] + weight;
                if (newDistance < distances[v]) {
                    distances[v] = newDistance;
                }
            }
        }
    }

    auto end = high_resolution_clock::now();
    duration<double> duration = end - start;
    return duration.count();
}

Graph generateRandomGraph(int n, int m, int q, int r) {
    Graph graph(n);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> vertex_dist(0, n - 1);
    uniform_int_distribution<> weight_dist(q, r);

    int edges_added = 0;
    while (edges_added < m) {
        int u = vertex_dist(gen);
        int v = vertex_dist(gen);
        int w = weight_dist(gen);

        if (u != v) {
            graph.addEdge(u, v, w);
            edges_added++;
        }
    }

    return graph;
}

int main() {
    setlocale(LC_ALL, "RU");

    try {
        cout << "=== ПРОГРАММА ДЛЯ ЭКСПЕРИМЕНТОВ ===" << endl;
        cout << "Введите параметры графа:" << endl;

        int n, m, q, r;
        cout << "Число вершин (n): ";
        cin >> n;
        cout << "Число рёбер (m): ";
        cin >> m;
        cout << "Нижняя граница весов (q): ";
        cin >> q;
        cout << "Верхняя граница весов (r): ";
        cin >> r;

        if (n <= 0 || m < 0 || q < 0 || r < q) {
            throw "Неверные параметры графа";
        }

        cout << "\nГенерация случайного графа..." << endl;
        Graph graph = generateRandomGraph(n, m, q, r);

        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> source_dist(0, n - 1);
        int source = source_dist(gen);

        cout << "Начальная вершина: " << source << endl;

        cout << "\nЗапуск алгоритмов..." << endl;

        double timeA = algorithmA(graph, source);
        double timeB = algorithmB(graph, source);

        cout << "\n=== РЕЗУЛЬТАТЫ ЭКСПЕРИМЕНТА ===" << endl;
        cout << "Алгоритм A (15-куча): " << timeA << " секунд" << endl;
        cout << "Алгоритм B (метки/массивы): " << timeB << " секунд" << endl;
        cout << "Отношение времени (A/B): " << (timeA / timeB) << endl;

        cout << "\n=== ДОПОЛНИТЕЛЬНЫЕ ЭКСПЕРИМЕНТЫ ===" << endl;
        vector<int> test_sizes = { 100, 500, 1000, 2000 };

        for (int test_n : test_sizes) {
            int test_m = test_n * 2;
            Graph test_graph = generateRandomGraph(test_n, test_m, q, r);
            int test_source = source_dist(gen) % test_n;

            double test_timeA = algorithmA(test_graph, test_source);
            double test_timeB = algorithmB(test_graph, test_source);

            cout << "n=" << test_n << ", m=" << test_m << ": ";
            cout << "A=" << test_timeA << "s, B=" << test_timeB << "s, A/B=" << (test_timeA / test_timeB) << endl;
        }

    }
    catch (const char* error) {
        cout << "Ошибка: " << error << endl;
        return 1;
    }

    return 0;
}