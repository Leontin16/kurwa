#include <iostream>
#include <sstream>
#include <fstream>
#include "graph.h"
#include "dijkstra.h"

int main() {
    system("chcp 65001 > nul");
    setlocale(LC_ALL, "RU");

    std::cout << "=== АЛГОРИТМ ДЕЙКСТРЫ ===" << std::endl;

    try {
        std::ifstream inputFile("input.txt");
        if (!inputFile.is_open()) {
            std::cout << "Ошибка: не удалось открыть файл input.txt" << std::endl;
            return 1;
        }

        int n, m, source;
        inputFile >> n >> m;

        if (n <= 0 || m < 0) {
            throw "Неверное количество вершин или рёбер";
        }

        std::cout << "Создан граф с " << n << " вершинами и " << m << " рёбрами." << std::endl;

        Graph graph(n);

        for (int i = 0; i < m; i++) {
            int u, v, w;
            inputFile >> u >> v >> w;

            u = u - 1;
            v = v - 1;

            if (u < 0 || u >= n || v < 0 || v >= n || w < 0) {
                std::cout << "Ошибка: неверные данные ребра! Пропускаем..." << std::endl;
                continue;
            }

            graph.addEdge(u, v, w);
            std::cout << "Добавлено ребро: " << u + 1 << " -> " << v + 1 << " (вес: " << w << ")" << std::endl;
        }

        inputFile >> source;
        source = source - 1;
        inputFile.close();

        if (source < 0 || source >= n) {
            throw "Неверная начальная вершина";
        }

        std::cout << "\nЗапуск алгоритма Дейкстры из вершины " << source + 1<< "..." << std::endl;

        Vector<int> distances = Dijkstra::findShortestPaths(graph, source);

        std::ofstream outputFile1("output_detailed.txt");
        std::ofstream outputFile2("output_simple.txt");

        outputFile1 << "=== ПОДРОБНЫЕ РЕЗУЛЬТАТЫ ===" << std::endl;
        outputFile1 << "Кратчайшие расстояния от вершины " << source + 1<< ":" << std::endl;
        for (int i = 0; i < n; i++) {
            outputFile1 << "Вершина " << i + 1 << ": ";
            if (distances[i] == INT_MAX) {
                outputFile1 << "недостижима (INF)";
            }
            else {
                outputFile1 << distances[i];
            }
            outputFile1 << std::endl;
        }

        outputFile2 << "=== ПРОСТОЙ ФОРМАТ ===" << std::endl;
        for (int i = 0; i < n; i++) {
            outputFile2 << i+1 << ":" << (distances[i] == INT_MAX ? "INF" : std::to_string(distances[i])) << std::endl;
        }

        outputFile1.close();
        outputFile2.close();

        std::cout << "\n=== РЕЗУЛЬТАТЫ ===" << std::endl;
        for (int i = 0; i < n; i++) {
            std::cout << "Вершина " << i + 1 << ": ";
            if (distances[i] == INT_MAX) {
                std::cout << "недостижима";
            }
            else {
                std::cout << distances[i];
            }
            std::cout << std::endl;
        }

        std::cout << "\n=== СТАТИСТИКА ===" << std::endl;
        int reachable = 0;
        int unreachable = 0;
        int minDistance = INT_MAX;
        int maxDistance = 0;

        for (int i = 0; i < n; i++) {
            if (distances[i] == INT_MAX) {
                unreachable++;
            }
            else {
                reachable++;
                if (distances[i] < minDistance) minDistance = distances[i];
                if (distances[i] > maxDistance) maxDistance = distances[i];
            }
        }

        std::cout << "Достижимых вершин: " << reachable << std::endl;
        std::cout << "Недостижимых вершин: " << unreachable << std::endl;

        if (reachable > 0) {
            std::cout << "Минимальное расстояние: " << minDistance << std::endl;
            std::cout << "Максимальное расстояние: " << maxDistance << std::endl;
        }

        std::cout << "\nРезультаты записаны в файлы:" << std::endl;
        std::cout << "- output_detailed.txt (подробный формат)" << std::endl;
        std::cout << "- output_simple.txt (простой формат)" << std::endl;
        std::cout << "\nАлгоритм завершен успешно!" << std::endl;

    }
    catch (const char* error) {
        std::cout << "Ошибка: " << error << std::endl;
        return 1;
    }
    catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}