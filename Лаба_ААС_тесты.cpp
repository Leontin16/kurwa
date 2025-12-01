#include <iostream>
#include <vector>
#include <string>
#include "graph.h"
#include "dijkstra.h"
#include "vector.h"
#include "edge.h"
#include "min_heap.h"
#include "vertex.h"

using namespace std;

struct TestCase {
    string name;
    int n; // число вершин
    vector<vector<int>> edges; // [u, v, w]
    int source;
    vector<int> expected;
};

class DijkstraTester {
private:
    static const int INF = -1;

    int convertINF(int value) {
        return (value == INF) ? INT_MAX : value;
    }

    bool compareResults(const Vector<int>& actual, const vector<int>& expected) {
        if (actual.size() != expected.size()) {
            cout << " Размеры не совпадают: actual=" << actual.size()
                << ", expected=" << expected.size() << endl;
            return false;
        }

        bool success = true;
        for (int i = 0; i < actual.size(); i++) {
            int actual_val = actual[i];
            int expected_val = convertINF(expected[i]);

            if (actual_val != expected_val) {
                cout << "  ❌ Вершина " << (i + 1) << ": actual=";
                if (actual_val == INT_MAX) cout << "INF";
                else cout << actual_val;
                cout << ", expected=";
                if (expected_val == INT_MAX) cout << "INF";
                else cout << expected_val;
                cout << endl;
                success = false;
            }
        }
        return success;
    }

public:
    void runTest(const TestCase& test) {
        cout << "Тест: " << test.name << endl;
        cout << "Граф: " << test.n << " вершин, " << test.edges.size() << " рёбер" << endl;
        cout << "Источник: вершина " << (test.source + 1) << endl;

        // Создаем граф
        Graph graph(test.n);

        // Добавляем рёбра
        for (const auto& edge : test.edges) {
            int u = edge[0];
            int v = edge[1];
            int w = edge[2];
            graph.addEdge(u, v, w);
        }

        // Запускаем алгоритм Дейкстры
        try {
            Vector<int> distances = Dijkstra::findShortestPaths(graph, test.source);

            // Проверяем результаты
            if (compareResults(distances, test.expected)) {
                cout << " ТЕСТ ПРОЙДЕН" << endl;
            }
            else {
                cout << " ТЕСТ ПРОВАЛЕН" << endl;
            }
        }
        catch (const exception& e) {
            cout << "  ОШИБКА ВЫПОЛНЕНИЯ: " << e.what() << endl;
        }
        cout << endl;
    }
};

int main() {
    setlocale(LC_ALL, "RU");
    cout << "=== ФУНКЦИОНАЛЬНЫЕ ТЕСТЫ АЛГОРИТМА ДЕЙКСТРЫ ===" << endl << endl;

    DijkstraTester tester;

    //  Тестовые случаи
    vector<TestCase> tests = {
        // Тест 1: Простой линейный граф
        {
            "Линейный граф (3 вершины)",
            3,
            {{0, 1, 10}, {1, 2, 20}}, // 1->2:10, 2->3:20
            0,
            {0, 10, 30} // 1:0, 2:10, 3:30
        },

        // Тест 2: Граф из условия задачи
        {
            "Граф из условия лабораторной",
            5,
            {
                {0, 1, 10}, {0, 4, 100}, {0, 3, 30},  // 1->2:10, 1->5:100, 1->4:30
                {1, 2, 50},                           // 2->3:50  
                {2, 4, 10},                           // 3->5:10
                {3, 2, 20}, {3, 4, 60}                // 4->3:20, 4->5:60
            },
            0,
            {0, 10, 50, 30, 60} // 1:0, 2:10, 3:50, 4:30, 5:60
        },

        // Тест 3: Граф с недостижимыми вершинами
        {
            "Граф с недостижимыми вершинами",
            4,
            {{0, 1, 5}, {2, 3, 10}}, // 1->2:5, 3->4:10
            0,
            {0, 5, -1, -1} // 1:0, 2:5, 3:INF, 4:INF
        },

        // Тест 4: Одна вершина
        {
            "Граф с одной вершиной",
            1,
            {},
            0,
            {0} // 1:0
        },

        // Тест 5: Несколько путей к вершине (выбор кратчайшего)
        {
            "Несколько путей к вершине",
            4,
            {
                {0, 1, 10}, {0, 2, 20},  // 1->2:10, 1->3:20
                {1, 3, 5}, {2, 3, 15}    // 2->4:5, 3->4:15
            },
            0,
            {0, 10, 20, 15} // 1:0, 2:10, 3:20, 4:15 (через 2: 10+5=15)
        },

        // Тест 6: Полный граф (каждая с каждой)
        {
            "Полный граф (3 вершины)",
            3,
            {
                {0, 1, 5}, {0, 2, 8},
                {1, 0, 5}, {1, 2, 2},
                {2, 0, 8}, {2, 1, 2}
            },
            0,
            {0, 5, 7} // 1:0, 2:5, 3:5+2=7
        },

        // Тест 7: Граф с циклом
        {
            "Граф с циклом",
            3,
            {
                {0, 1, 3}, {1, 2, 4}, {2, 0, 2} // 1->2:3, 2->3:4, 3->1:2
            },
            0,
            {0, 3, 7} // 1:0, 2:3, 3:3+4=7
        },

        // Тест 8: Больший граф для проверки сложных маршрутов
        {
            "Сложный граф (6 вершин)",
            6,
            {
                {0, 1, 7}, {0, 2, 9}, {0, 5, 14},
                {1, 2, 10}, {1, 3, 15},
                {2, 3, 11}, {2, 5, 2},
                {3, 4, 6},
                {4, 5, 9}
            },
            0,
            {0, 7, 9, 20, 26, 11} // Проверка сложных маршрутов
        }
    };

    // Запуск всех тестов
    int passed = 0;
    int total = tests.size();

    for (const auto& test : tests) {
        tester.runTest(test);
        passed++;
    }

    // Статистика
    cout << "=== РЕЗУЛЬТАТЫ ТЕСТИРОВАНИЯ ===" << endl;
    cout << "Пройдено: " << passed << "/" << total << " тестов" << endl;

    if (passed == total) {
        cout << "ВСЕ ТЕСТЫ ПРОЙДЕНЫ УСПЕШНО!" << endl;
    }
    else {
        cout << "НЕКОТОРЫЕ ТЕСТЫ ПРОВАЛЕНЫ" << endl;
    }

    return 0;
}