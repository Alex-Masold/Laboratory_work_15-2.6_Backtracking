#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 50;
int n, m, ans = 0;
int possition[MAXN]; // весь в нулях
vector<vector<char>> board(MAXN, vector<char>(MAXN));
bool ok;

void search(int nLine) {
    if (nLine == n) {
        ans++;
        if (ans == 1) {
            cout << "YES" << endl;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    if (possition[i] == j) {
                        cout << "X";
                    }
                    else
                        cout << ".";
                }
                cout << endl;
            }
        }
        return;
    }
    for (int nCol = 0; nCol < m; nCol++) // перебор елементов по строке
    {
        if (board[nLine][nCol] == '?') // если елемент на линии nLIne = ?
        {
            ok = true;
            for (int i = 0; i < nLine; i++)
            {
                if (possition[i] == nCol || possition[i] + i == nCol + nLine || possition[i] - i == nCol - nLine)
                {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                possition[nLine] = nCol;
                search(nLine + 1);
                possition[nLine] = -1;
            }
        }
    }
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> board[i][j];

    search(0);
    if (ans == 0)
        cout << "NO" << endl;

    return 0;
}

//#include <iostream>
//#include <fstream>
//#include <vector>
//
//int main()
//{
//	using namespace std;
//	ifstream in("input.txt", ios::in);
//	int M, N;
//	char c;
//
//	in >> M >> N;
//
//	vector<vector<int>> desk(M, vector<int>(N));
//
//	for (int i = 0; i < M; i++)
//	{
//		for (int j = 0; j < N; j++)
//		{
//			in >> c;
//			switch (c)
//			{
//			case ('.'):
//				desk[i][j] = 0;
//				break;
//			case ('?'):
//				desk[i][j] = 1;
//				break;
//			}
//		}
//	}
//	in.close();
//
//	for (int i = 0; i < M; i++)
//	{
//		for (int j = 0; j < N; j++)
//		{
//			cout << desk[i][j] << ' ';
//		}
//		cout << endl;
//	}
//}