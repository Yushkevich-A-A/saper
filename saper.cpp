
#include <iostream>

using namespace std;

int fields[100][100];
int fields_p[100][100];
const int N = 5, M = 5, B = 1;

void print_field() {
    system("cls");
    cout << "   ";
    for (int i = 0; i < M; ++i) {
        if (i + 1 < 10) cout << i + 1 << "  ";
        else cout << i + 1 << " ";
    }
    cout << endl;


    for (int i = 0; i < N; ++i) {
        if (i + 1 < 10) cout << i + 1 << "  ";
        else cout << i + 1 << " ";

        for (int j = 0; j < M; ++j) {
            if (fields_p[i][j] == -2) cout << "-  ";
            else if (fields_p[i][j] == -1)  cout << "f  ";
            else if (fields_p[i][j] == -3)  cout << "*  ";
            else  cout << fields[i][j] << "  ";
        }
        cout << endl;
    }
}

void dfs(int x, int y) {
    if (x < 0 || x >= N || y < 0 || y >= M || fields_p[x][y] > -2) return;
    fields_p[x][y] = fields[x][y];
    if (fields[x][y] > 0) return;
    for (int i2 = x - 1; i2 <= x + 1; ++i2) {
        for (int j2 = y - 1; j2 <= y + 1; ++j2) {
            if (i2 != x || j2 != y) dfs(i2, j2);
        }
    }

}

bool open_cell(int x, int y) {
    if (fields[x][y] == -1) return false;
    if (fields[x][y] > 0) {
        fields_p[x][y] = fields[x][y];
        return true;
    }
    dfs(x, y);
}

bool is_win() {
    int is_opend = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (fields_p[i][j] >= 0) is_opend++;
        }
    }
    return (N * M - B == is_opend);
}

void end_game(bool is_win) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (fields_p[i][j] == -1) fields_p[i][j] = -2;
            if (fields[i][j] == -1) fields_p[i][j] = -3;
        }
    }
    print_field();
    cout << "vi " << (is_win ? "viigrali" : "proigrali") << " \n chtobi nachat novuiu igru vvedite stroku\n";
    string bre;
    cin >> bre;
}

int main()
{
    while (true) {
        srand(time(0));
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                fields[i][j] = 0;
                fields_p[i][j] = -2;
            }
        }
        for (int i = 0; i < B; ++i) {
            while (true) {
                int x = rand() % N;
                int y = rand() % M;
                if (fields[x][y] != -1) {
                    fields[x][y] = -1;
                    break;
                }
            }
        }

        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                if (fields[i][j] != -1) {
                    fields[i][j] = 0;

                    for (int i2 = i - 1; i2 <= i + 1; ++i2) {
                        for (int j2 = j - 1; j2 <= j + 1; ++j2) {
                            if (i2 >= 0 && i2 < N && j2 >= 0 && j2 < M && fields[i2][j2] == -1) {
                                ++fields[i][j];
                            }
                        }
                    }
                }
            }
        }

        while (true) {
            print_field();
            
            cout << endl << endl << endl << "enter command: " << endl;
            string command;
            cin >> command;
            /*
                \o x y - открыть ячейку
                \f x y - поставить флаг
                \n - начать новую игру
                \q - завершение
            */
            if (command == "\\o") {
                int x, y;
                cin >> x >> y;
                --x; --y;
                if (x < 0 || x >= N || y < 0 || y >= M || fields_p[x][y] >= 0) continue;
                if (!open_cell(x, y)) {
                    end_game(false);
                    break;
                }
                if (is_win()) {
                    end_game(true);
                    break;
                }
            }
            else if (command == "\\f") {
                int x, y;
                cin >> x >> y;
                --x; --y;
                if (x < 0 || x >= N || y < 0 || y >= M || fields_p[x][y] >= 0) continue;
                if (fields_p[x][y] == -1) fields_p[x][y] = -2;
                else fields_p[x][y] = -1;
            }
            else if (command == "\\n") {
                break;
            }
            else if (command == "\\q") {
                return 0;
            }


        }
    }
}
