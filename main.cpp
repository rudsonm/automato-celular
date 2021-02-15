#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <stdio.h>

struct Cell {
    int state;
    Cell(int state) : state(state) {};
};

struct Automaton {
    std::vector<Cell> cells;
    int n, m, k, d;
    Automaton(int n, int m, int d, int k, int *input) : n(n), m(m), k(k), d(d) {
        initCells(input);
    };

    void initCells(int *input) {
        for (int i = 0; i < n; i++) {
            int state = input[i];
            Cell cell(state);
            cells.push_back(cell);
        };
    }

    std::vector<Cell> neighborhoodOf(int cellIndex) {
        std::vector<Cell> neighborhood;
        for(int i = 0; i < n; i++) {
            if (i == cellIndex)
                continue;
            int distance = std::min(std::abs(i - cellIndex), n - std::abs(i - cellIndex));
            if (distance <= d)
                neighborhood.push_back(cells.at(i));
        }
        return neighborhood;
    }

    Cell getCellUpdated(int cellIndex) {        
        std::vector<Cell> neighborhood = neighborhoodOf(cellIndex);
        int sum = cells.at(cellIndex).state;
        for(Cell neighbor : neighborhood) {
            sum += neighbor.state;
        }
        return Cell(sum % m);
    }

    void doNextStep() {
        std::vector<Cell> cellsUpdated;
        for (int i = 0; i < n; i++) {
            Cell cell = getCellUpdated(i);
            cellsUpdated.push_back(cell);
        }
        cells = cellsUpdated;
    }

    void run() {
        for (int i = 0; i < k; i++)
            doNextStep();
    }

    void print() {
        for (Cell cell : cells)
            printf("[%i] ", cell.state);
    }
};

int main() {
    Automaton aut(5, 3, 1, 10, new int[5] {1, 2, 2, 1, 2});
    aut.run();
    aut.print();
}