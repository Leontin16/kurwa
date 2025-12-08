#include <iostream>
#include <chrono>
#include <random>
#include <fstream>
#include <string>
#include <algorithm>
#include <cmath>
#include "graph.h"
#include "dijkstra.h"
#include "vector.h"
#include "edge.h"
#include "min_heap.h"
#include "vertex.h"

using namespace std;
using namespace std::chrono;

// === АЛГОРИТМЫ ===

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

// === ГЕНЕРАЦИЯ ГРАФОВ ===

Graph generateGraph(int n, long long m, int q, int r) {
    Graph graph(n);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> weight_dist(q, r);

    if (m > 0) {
        if (m > (long long)n * (n - 1) / 2) {
            m = min(m, (long long)n * (n - 1));
            long long edges_added = 0;

            for (int i = 0; i < n && edges_added < m; i++) {
                for (int j = 0; j < n && edges_added < m; j++) {
                    if (i != j) {
                        graph.addEdge(i, j, weight_dist(gen));
                        edges_added++;
                    }
                }
            }
        }
        else {
            uniform_int_distribution<> vertex_dist(0, n - 1);
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
    }
    return graph;
}


void runExperiment3_1() {
    ofstream out("exp3_1.csv");
    out << "n,m_type,m_count,time_A,time_B\n";
    cout << "=== ЭКСПЕРИМЕНТ 3.1 ===" << endl;
    cout << "n = 1..10001, шаг 100" << endl;
    cout << "q = 1, r = 1000000" << endl << endl;

    int q = 1;
    int r = 1000000;
    int source = 0;

    for (int n = 1; n <= 10001; n += 100) {
        long long m_a = (long long)n * n / 10;
        if (m_a < 1) m_a = 1;

        cout << "n=" << n << ", m~" << m_a << " (n^2/10) ... ";

        Graph g_a = generateGraph(n, m_a, q, r);
        double tA_a = runAlgoA(g_a, source);
        double tB_a = runAlgoB(g_a, source);

        out << n << ",n2_div_10," << m_a << "," << tA_a << "," << tB_a << "\n";
        cout << "A=" << tA_a << "s, B=" << tB_a << "s" << endl;

        long long m_b = (long long)n * n;
        long long max_edges = (long long)n * (n - 1);
        if (m_b > max_edges) m_b = max_edges;

        cout << "n=" << n << ", m~" << m_b << " (n^2) ... ";

        Graph g_b = generateGraph(n, m_b, q, r);
        double tA_b = runAlgoA(g_b, source);
        double tB_b = runAlgoB(g_b, source);

        out << n << ",n2," << m_b << "," << tA_b << "," << tB_b << "\n";
        cout << "A=" << tA_b << "s, B=" << tB_b << "s" << endl;
    }

    out.close();
    cout << "\nЭксперимент 3.1 завершен. Данные в exp3_1.csv\n" << endl;
}



void runExperiment3_2() {
    ofstream out("exp3_2.csv");
    out << "n,m_type,m_count,time_A,time_B\n";
    cout << "=== ЭКСПЕРИМЕНТ 3.2 ===" << endl;
    cout << "n = 101..10001, шаг 100" << endl;
    cout << "q = 1, r = 1000000" << endl << endl;

    int q = 1;
    int r = 1000000;
    int source = 0;

    for (int n = 101; n <= 10001; n += 100) {
        long long m_a = 100 * (long long)n;

        cout << "n=" << n << ", m~" << m_a << " (100n) ... ";

        Graph g_a = generateGraph(n, m_a, q, r);
        double tA_a = runAlgoA(g_a, source);
        double tB_a = runAlgoB(g_a, source);

        out << n << ",100n," << m_a << "," << tA_a << "," << tB_a << "\n";
        cout << "A=" << tA_a << "s, B=" << tB_a << "s" << endl;

        long long m_b = 1000 * (long long)n;
        long long max_edges = (long long)n * (n - 1);
        if (m_b > max_edges) m_b = max_edges;

        cout << "n=" << n << ", m~" << m_b << " (1000n) ... ";

        Graph g_b = generateGraph(n, m_b, q, r);
        double tA_b = runAlgoA(g_b, source);
        double tB_b = runAlgoB(g_b, source);

        out << n << ",1000n," << m_b << "," << tA_b << "," << tB_b << "\n";
        cout << "A=" << tA_b << "s, B=" << tB_b << "s" << endl;
    }

    out.close();
    cout << "\nЭксперимент 3.2 завершен. Данные в exp3_2.csv\n" << endl;
}


void runExperiment3_3() {
    ofstream out("exp3_3.csv");
    out << "m,time_A,time_B\n";
    cout << "=== ЭКСПЕРИМЕНТ 3.3 ===" << endl;
    cout << "n = 10001 (фиксировано)" << endl;
    cout << "m = 0..1000000, шаг 100000" << endl;
    cout << "q = 1, r = 1000000" << endl << endl;

    int n = 10001;
    int q = 1;
    int r = 1000000;
    int source = 0;

    for (long long m = 0; m <= 1000000; m += 100000) {
        if (m == 0) {
            cout << "m=0 (граф без рёбер) ... ";
            Graph g(n);
            double tA = runAlgoA(g, source);
            double tB = runAlgoB(g, source);
            out << "0," << tA << "," << tB << "\n";
            cout << "A=" << tA << "s, B=" << tB << "s" << endl;
        }
        else {
            cout << "m=" << m << " ... ";
            Graph g = generateGraph(n, m, q, r);
            double tA = runAlgoA(g, source);
            double tB = runAlgoB(g, source);
            out << m << "," << tA << "," << tB << "\n";
            cout << "A=" << tA << "s, B=" << tB << "s" << endl;
        }
    }

    out.close();
    cout << "\nЭксперимент 3.3 завершен. Данные в exp3_3.csv\n" << endl;
}


void runExperiment3_4() {
    ofstream out("exp3_4.csv");
    out << "r,m_type,time_A,time_B\n";
    cout << "=== ЭКСПЕРИМЕНТ 3.4 ===" << endl;
    cout << "n = 10001 (фиксировано)" << endl;
    cout << "r = 1..200, шаг 1" << endl;
    cout << "q = 1" << endl << endl;

    int n = 10001;
    int q = 1;
    int source = 0;

    long long m_dense = (long long)n * n;
    long long max_edges = (long long)n * (n - 1);
    if (m_dense > max_edges) m_dense = max_edges;

    long long m_sparse = 1000 * (long long)n;
    if (m_sparse > max_edges) m_sparse = max_edges;

    for (int r = 1; r <= 200; r++) {
        cout << "r=" << r << " ... ";

        Graph g_dense = generateGraph(n, m_dense, q, r);
        double tA_dense = runAlgoA(g_dense, source);
        double tB_dense = runAlgoB(g_dense, source);
        out << r << ",dense," << tA_dense << "," << tB_dense << "\n";

        Graph g_sparse = generateGraph(n, m_sparse, q, r);
        double tA_sparse = runAlgoA(g_sparse, source);
        double tB_sparse = runAlgoB(g_sparse, source);
        out << r << ",sparse," << tA_sparse << "," << tB_sparse << "\n";

        cout << "A_dense=" << tA_dense << "s, B_dense=" << tB_dense << "s, ";
        cout << "A_sparse=" << tA_sparse << "s, B_sparse=" << tB_sparse << "s" << endl;
    }

    out.close();
    cout << "\nЭксперимент 3.4 завершен. Данные в exp3_4.csv\n" << endl;
}

// === ОСНОВНАЯ ПРОГРАММА ===

int main() {
    setlocale(LC_ALL, "RU");

    try {
        cout << "==========================================" << endl;
        cout << "ПРОГРАММА ДЛЯ ПРОВЕДЕНИЯ ЭКСПЕРИМЕНТОВ" << endl;
        cout << "Алгоритм Дейкстры: 15-куча vs Массивы" << endl;
        cout << "==========================================" << endl << endl;

        // Запуск экспериментов по порядку
        runExperiment3_1();
        runExperiment3_2();
        runExperiment3_3();
        runExperiment3_4();

        cout << "==========================================" << endl;
        cout << "ВСЕ ЭКСПЕРИМЕНТЫ ЗАВЕРШЕНЫ!" << endl;
        cout << "Результаты сохранены в файлы:" << endl;
        cout << "- exp3_1.csv (зависимость от n при разных m)" << endl;
        cout << "- exp3_2.csv (зависимость от n при m∝n)" << endl;
        cout << "- exp3_3.csv (зависимость от m при фиксированном n)" << endl;
        cout << "- exp3_4.csv (зависимость от диапазона весов r)" << endl;
        cout << "==========================================" << endl;
    }
    catch (const std::exception& e) {
        cout << "ОШИБКА: " << e.what() << endl;
        return 1;
    }

    return 0;
}