#include <iostream>
#include <vector>

using namespace std;

int n, k, m, l;
/*  n - колво переключателей
    k - колво состояний
    m - колво ламп
    l - колво ламп, которые необходимо включить */
char*** switches;
int* ans; // для отслеживания какие лапмы включены, а какие нет
int* lamps;
/*Он используется для хранения информации о том,
 * какие лампы воздействует каждый переключатель в каждом из своих состояний.*/
bool allLights() {
    for (int i = 0; i < m; i++) {
        if (lamps[i] != l) {
            return false;
        }
    }
    return true;
}

bool errorLoad(int switchLeft) { // есть ли смысл искать дальше
    for (int i = 0; i < m; i++)
        if (lamps[i] > l || lamps[i] + switchLeft < l) return true;
    return false;
}
/* Если суммарное количество ламп, которые можно включить с помощью
 * оставшихся переключателей, меньше,
 * чем количество ламп, которые необходимо включить,
 * то поиск можно прекратить.*/


bool dfs(int cur_switch) {
    if (cur_switch == n) return allLights(); // достигли ли конца списка переключателей
    if (errorLoad(n - cur_switch)) return false;

    for (int i = 0; i < k; i++) {
        bool added = false;

        for (int j = 0; j < m; j++) {
            if (switches[cur_switch][i][j] == 'X') {
                lamps[j]++;
                added = true;
            }
        }

        if (added) {

            if (dfs(cur_switch + 1)) {
                ans[cur_switch] = i + 1; // переключатели нумеруются с 1
                return true;
            }

            for (int j = 0; j < m; j++) {
                if (switches[cur_switch][i][j] == 'X') {
                    lamps[j]--;
                }
            }
        }
    }
    return false;
}
/*На каждом шаге алгоритма рассматривается очередной переключатель и пытаемся использовать его для включения ламп.
 * Если в результате использования переключателя все лампы включены, то мы нашли ответ. Если же это не произошло,
 * то мы переходим к следующему переключателю. Если ни один из переключателей не приводит к включению всех ламп,
 * то ответа не существует. */



int main() {
    cin >> n >> k >> m >> l;

    switches = new char** [n];
    for (int i = 0; i < n; i++) {
        switches[i] = new char* [k];
        for (int j = 0; j < k; j++) {
            switches[i][j] = new char[m];
            for (int y = 0; y < m; y++) cin >> switches[i][j][y];
        }
    }

    ans = (int*)calloc(n, 4);
    lamps = (int*)calloc(m, 4);

    if (dfs(0)) {
        cout << "YES" << endl;
        for (int i = 0; i < n; ++i) {
            cout << ans[i] << endl;
        }
    }
    else {
        cout << "NO" << endl;
    }

    return 0;
}