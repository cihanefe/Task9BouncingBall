#include <iostream>
#include <cstdlib>
#include <windows.h>
using namespace std;

int genislik = 50, yukseklik = 20, uzunluk;
bool gameLoop = true;

int n = 1;

void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO     cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}
void ClearScreen()
{
    HANDLE hOut;
    COORD Position;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    Position.X = 0;
    Position.Y = 0;
    SetConsoleCursorPosition(hOut, Position);
}

class Ekran {
public:
    Ekran(int x, int y) {
        ShowConsoleCursor(false);
        screenx = x;
        screeny = y;
        for (int i = 0; i < screeny; i++) {
            for (int j = 0; j < screenx; j++) {
                if (j == 0 || j == screenx - 1) {
                    sScreen[j][i] = '|';
                }
                else if ( i == screeny - 1) {
                    sScreen[j][i] = '-';
                }
                else {
                    sScreen[j][i] = ' ';
                }
                dScreen[j][i] = ' ';
            }
            cout << endl;
        }
    }

    void sAddChar(int x, int y, char c) {
        if (x != 0 && x != screenx - 1 && y != 0 && y != screeny - 1) {
            sScreen[x][y] = c;
        }
    }
    void dAddChar(int x, int y, char c) {
        if (x != 0 && x != screenx - 1 && y != 0 && y != screeny - 1) {
            dScreen[x][y] = c;
        }
    }

    void drawScreen() {
        x = "";
        for (int i = 0; i < screeny; i++) {
            for (int j = 0; j < screenx; j++) {
                if (dScreen[j][i] != ' ') {
                    x += dScreen[j][i];
                    x += " ";
                }
                else {
                    x += sScreen[j][i];
                    x += " ";
                }
            }
            x += "\n";
        }
        ClearScreen();
        cout << x;
    }
     
    int screenx;
    int screeny;
    char sScreen[100][100];
    char dScreen[100][100];
private:

    string x;
};

class Dinamik {
public:
    Dinamik() {
        karakterx = 0;
        karaktery = 0;
        a = 0;
        karakters = ' ';
        ekran = NULL;
    }
    void physics() {
            while (karaktery != yukseklik - 2) {
                ekran->dScreen[karakterx][karaktery] = ' ';
                karaktery += 2;

                if (karakterx == genislik - 2 || karakterx == 1) {
                    a *= -1;
                }
                karakterx = karakterx + a;

                ekran->dScreen[karakterx][karaktery] = karakters;
                ekran->drawScreen();
                Sleep(50);
            }
            n = n / 2;
            jump();
        
    }

    void jump() {
            for (int i = 0; i < n; i++) {
                ekran->dScreen[karakterx][karaktery] = ' ';
                karaktery -= 2;
                if (karakterx == genislik - 2 || karakterx == 1) {
                    a *= -1;
                }
                karakterx = karakterx + a; 

                ekran->dScreen[karakterx][karaktery] = karakters;
                ekran->drawScreen();

                Sleep(100);
            }
    }

protected:
    int karakterx, karaktery, a;
    char karakters;
    Ekran* ekran;
};

class Player : public Dinamik {
public:
    Player(int x, int y, char sembol, Ekran& e) {
        karakterx = x;
        karaktery = y;
        karakters = sembol;
        ekran = &e;
        ekran->dAddChar(karakterx, karaktery, karakters);
    }
    
    void move()
    {
        if (GetAsyncKeyState(VK_RIGHT) < 0 && karakterx < genislik-2)
        {
            ekran->dScreen[karakterx][karaktery] = ' ';
            karakterx++;
            a = 1;
        }
        else if (GetAsyncKeyState(VK_LEFT) < 0 && karakterx > 1)
        {
            ekran->dScreen[karakterx][karaktery] = ' ';
            karakterx--;
            a = -1;
        }
        else if (GetAsyncKeyState(VK_DOWN) < 0 )
        {
            a = 0;
        }
        else if (GetAsyncKeyState(VK_SPACE) < 0 && karaktery == yukseklik - 2) {
            n = 6;
            jump();
        }

        ekran->dScreen[karakterx][karaktery] = karakters;
        ekran->drawScreen();
    }
};

int main()
{
    //cin >> genislik >> yukseklik;
    Ekran ekran(genislik, yukseklik);
    Player player(6, yukseklik - 2, 'O', ekran);

    while (gameLoop) {
        player.move();
        player.physics();
        Sleep(70);
    }

    return 0;
}
