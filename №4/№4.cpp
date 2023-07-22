#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>
using namespace std;

const int n = 9;

// функция для вывода сетки
void printGrid(vector<vector<int>>& grid) {
    ofstream out("output.txt", ios::app);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            out << grid[i][j];
        }
        out << endl;
    }
    out << endl;
}

// функция для поверки вставляемого числа
bool isSafe(vector<vector<int>>& grid, int row, int col, int num) {
    // Проверка, есть ли число уже в строке или столбце
    for (int i = 0; i < n; i++) {
        if (grid[row][i] == num || grid[i][col] == num) {
            return false;
        }
    }

    // Проверка, есть ли число уже блоке
    int box_row = row - row % 3;
    int box_col = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[i + box_row][j + box_col] == num) {
                return false;
            }
        }
    }
    return true;
}

bool solveSudoku(vector<vector<int>>& grid) {
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            // находим пустое место
            if (grid[row][col] == 0) {
                // подбираем число от 1 до 9
                for (int num = 1; num <= 9; num++) {
                    // выполняем проверку
                    if (isSafe(grid, row, col, num)) {
                 
                        grid[row][col] = num;

                        // идем дальше в рекурсию (лес)
                        if (solveSudoku(grid)) {
                            return true;
                        }

                        // Если рекурсивный вызов не сработал, производится откат и попытка следующего числа
                        grid[row][col] = 0;
                    }
                }

                // Если ни одно из чисел не подходит
                return false;
            }
        }
    }

    // все хорошо - рекурсия закончилась
    return true;
}

int main()
{
    
    ifstream in("input.txt", ios::in);
    ofstream out("output.txt");
    out.close();
    int n;
    char c;
    in >> n;
    for (int i = 0; i < n; i++)
    {
        // запихихиваем в массив данные
        vector<vector<int>> grid(9, vector<int>(9));
        for (int k = 0; k < 9; k++)
        {
            for (int j = 0; j < 9; j++)
            {
                in >> c;
                if (c == '.')
                {
                    grid[k][j] = 0;
                }
                else
                {
                    grid[k][j] = grid[k][j] * 10 + c - '0';
                }
            }
        }

        /*cout << "Initial Grid:" << endl;
        printGrid(grid);
        cout << endl;*/

        if (solveSudoku(grid)) {
            printGrid(grid);
        }
        else {
            cout << "No solution exists." << endl;
        }
    }
}