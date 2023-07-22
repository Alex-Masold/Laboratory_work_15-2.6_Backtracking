#include <iostream>
#include <vector>
#include <valarray>

using namespace std;

typedef unsigned long long int ulli;

struct Item
{
    ulli value = NULL, weight = NULL;
};

int main()
{
    ulli n, w;
    cin >> n >> w;
    Item* arr = new Item[n];
    for (int i = 0; i < n; i++)
        cin >> arr[i].weight >> arr[i].value;

    ulli maxValue = 0;
    vector<ulli> maxNabor;
    vector<ulli> tempNabor; // временный набор, который содержит индексы включенных предметов;
    ulli tempWeight = 0; // временный вес
    ulli tempValue = 0; // временная стоимость
    for (int nabor = 0; nabor < pow(2, n); nabor++)
    {
        tempNabor.clear();
        tempValue = 0;
        tempWeight = 0;
        for (int i = 0; i < n; i++)
        {
            ulli mask = 1 << i;
            if ((nabor & mask) > 0) // вычисляем  вес и стоим. временного набора
            {
                tempValue += arr[i].value;
                tempWeight += arr[i].weight;
                tempNabor.push_back(i);
            }
        }
        if (tempWeight <= w && tempValue > maxValue) // запись максимального
        {
            maxValue = tempValue;
            maxNabor = tempNabor;
        }
    }

    cout << maxValue << ' ' << maxNabor.size() << endl;
    for (ulli i = 0; i < maxNabor.size(); i++)
        cout << maxNabor[i] + 1 << " ";
}

/*Эта строка создает маску из битов,
    которая используется для проверки,
    включен ли i-й предмет в текущий набор.*/