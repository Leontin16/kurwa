#include <iostream>
#include <chrono>
#include <random>
#include <fstream>
#include <string>
#include "graph.h"
#include "dijkstra.h"
#include "vector.h"
#include "edge.h"
#include "min_heap.h"
#include "vertex.h"

using namespace std;
using namespace std::chrono;

// === АЛГОРИТМЫ ИЗ ТВОЕГО main2.cpp ===

double runAlgoA(const Graph& graph, int source) {
    auto start = high_resolution_clock::now();
    Vector<int> distances = Dijkstra::findShortestPaths(graph, source);
    auto end = high_resolution_clock::now();
    return duration<double>(end - start).count();
}

double runAlgoB(const Graph& graph, int source) {
    auto start = high_resolution_clock::now();
    int n = graph.getNumVertices();
    Vector<int> distances(n);
    Vector<bool> visited(n);

    for (int i = 0; i < n; i++) {
        distances[i] = INT_MAX;
        visited[i] = false;
    }
    distances[source] = 0;

    for (int i = 0; i < n; i++) {
        int minDistance = INT_MAX;
        int u = -1;
        // Линейный поиск минимума O(N)
        for (int j = 0; j < n; j++) {
            if (!visited[j] && distances[j] < minDistance) {
                minDistance = distances[j];
                u = j;
            }
        }
        if (u == -1 || distances[u] == INT_MAX) break;
        visited[u] = true;

        const Vector<Edge>& neighbors = graph.getNeighbors(u);
        for (int j = 0; j < neighbors.size(); j++) {
            const Edge& edge = neighbors[j];
            int v = edge.destination;
            int weight = edge.weight;
            if (!visited[v] && distances[u] < INT_MAX - weight) {
                if (distances[u] + weight < distances[v]) {
                    distances[v] = distances[u] + weight;
                }
            }
        }
    }
    auto end = high_resolution_clock::now();
    return duration<double>(end - start).count();
}

Graph generateGraphFast(int n, long long m, int q, int r) {
    Graph graph(n);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> weight_dist(q, r);
    uniform_int_distribution<> vertex_dist(0, n - 1);

    long long max_edges = (long long)n * (n - 1);
    if (m > max_edges) m = max_edges;


    if (m > max_edges / 2) {
        long long count = 0;
        for (int i = 0; i < n && count < m; i++) {
            for (int j = 0; j < n && count < m; j++) {
                if (i != j) {
                    graph.addEdge(i, j, weight_dist(gen));
                    count++;
                }
            }
        }
    }
    else {
        long long edges_added = 0;
        while (edges_added < m) {
            int u = vertex_dist(gen);
            int v = vertex_dist(gen);
            if (u != v) {
                graph.addEdge(u, v, weight_dist(gen));
                edges_added++;
            }
        }
    }
    return graph;
}

// === ЭКСПЕРИМЕНТЫ ===

void runExperiment3_1() {
    ofstream out("exp3_1.csv");
    out << "n,m_type,m_count,time_A,time_B\n";
    cout << "Start Exp 3.1..." << endl;

    for (int n = 100; n <= 3000; n += 500) {

        long long m1 = ((long long)n * n) / 10;
        Graph g1 = generateGraphFast(n, m1, 1, 1000000);
        double tA1 = runAlgoA(g1, 0);
        double tB1 = runAlgoB(g1, 0);
        out << n << ",dense," << m1 << "," << tA1 << "," << tB1 << "\n";
        cout << "  n=" << n << " dense done." << endl;

        long long m2 = (long long)n * n;
        if (m2 > 10000000) m2 = 10000000;

        Graph g2 = generateGraphFast(n, m2, 1, 1000000);
        double tA2 = runAlgoA(g2, 0);
        double tB2 = runAlgoB(g2, 0);
        out << n << ",full," << m2 << "," << tA2 << "," << tB2 << "\n";
        cout << "  n=" << n << " full done." << endl;
    }
    out.close();
}

void runExperiment3_2() {
    ofstream out("exp3_2.csv");
    out << "n,m_type,m_count,time_A,time_B\n";
    cout << "Start Exp 3.2..." << endl;

    for (int n = 100; n <= 5000; n += 500) {
        
        long long m1 = 100 * n;
        Graph g1 = generateGraphFast(n, m1, 1, 1000000);
        out << n << ",100n," << m1 << "," << runAlgoA(g1, 0) << "," << runAlgoB(g1, 0) << "\n";

        long long m2 = 1000 * n;
        Graph g2 = generateGraphFast(n, m2, 1, 1000000);
        out << n << ",1000n," << m2 << "," << runAlgoA(g2, 0) << "," << runAlgoB(g2, 0) << "\n";

        cout << "  n=" << n << " done." << endl;
    }
    out.close();
}

void runExperiment3_3() {
    ofstream out("exp3_3.csv");
    out << "m,time_A,time_B\n";
    cout << "Start Exp 3.3..." << endl;

    int n = 2000;
    for (long long m = 0; m <= 5000000; m += 500000) {
        if (m == 0) m = 1;
        Graph g = generateGraphFast(n, m, 1, 1000000);
        out << m << "," << runAlgoA(g, 0) << "," << runAlgoB(g, 0) << "\n";
        cout << "  m=" << m << " done." << endl;
    }
    out.close();
}

void runExperiment3_4() {
    ofstream out("exp3_4.csv");
    out << "r,m_type,time_A,time_B\n";
    cout << "Start Exp 3.4..." << endl;

    int n = 1000;
    long long m_dense = n * n;
    long long m_sparse = 1000 * n;

    for (int r = 1; r <= 200; r += 20) {

        Graph g1 = generateGraphFast(n, m_dense, 1, r);
        out << r << ",dense," << runAlgoA(g1, 0) << "," << runAlgoB(g1, 0) << "\n";

        Graph g2 = generateGraphFast(n, m_sparse, 1, r);
        out << r << ",sparse," << runAlgoA(g2, 0) << "," << runAlgoB(g2, 0) << "\n";

        cout << "  r=" << r << " done." << endl;
    }
    out.close();
}

int main() {
    setlocale(LC_ALL, "RU");
    try {
        runExperiment3_1();
        runExperiment3_2();
        runExperiment3_3();
        runExperiment3_4();
        cout << "\nВсе эксперименты завершены. Данные сохранены в *.csv файлы." << endl;
    }
    catch (const std::exception& e) {
        cout << "Error: " << e.what() << endl;
    }
    return 0;
}