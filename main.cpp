#include <iostream>
#include <windows.h>
#include <algorithm>
#include <deque>
#include "Player.h"
#include "Fruit.h"

using namespace std;

void DrawField(pair<int, int> Field, const Player& Player1, const Fruit& Fruit1, HANDLE hConsole) {
    for (int i = 0; i < Field.second; ++i) {
        for (int j = 0; j < Field.first; ++j) {
            WORD color = (i == 0 || i == Field.second - 1 || j == 0 || j == Field.first - 1) ? 0xCC :
                find(Player1.PlayerBody.begin(), Player1.PlayerBody.end(), make_pair(j, i)) != Player1.PlayerBody.end() ? 0x22 :
                (i == Fruit1.FruitPosition.second && j == Fruit1.FruitPosition.first) ? 0x1F : 0x00;

            SetConsoleTextAttribute(hConsole, color);
            cout << "  ";
        }
        cout << endl;
    }
    SetConsoleTextAttribute(hConsole, 0x0C);
}
void RunGame() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    Player Player;
    Fruit Fruit;

    constexpr pair<int, int> Field = {20, 20};

    while (true) {
        switch(Player.CheckPlayerMovement(Fruit.FruitPosition, Field)) {
            case 2:
                return;
            case 1:
                Fruit.FruitPosition = Fruit.RelocateFruit(Player.PlayerPosition, Player.PlayerBody, Field);
                Player.score += 1;
            default:
                DrawField(Field, Player, Fruit, hConsole);
                cout << "Score: " << Player.score << endl;
                SetConsoleCursorPosition(hConsole, {0, 0});
        }
    }
}

int APIENTRY WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    while(true) {
        if (MessageBox(nullptr, "PLAY???", "Snake Game(Made by Luiz Gabriel)", MB_YESNO) != IDYES) {
            break;
        }
        AllocConsole();
        freopen("CONOUT$", "w", stdout);

        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

        CONSOLE_CURSOR_INFO cursorInfo = {100, FALSE};
        SetConsoleCursorInfo(hConsole, &cursorInfo);

        RunGame();

        string message = "YOU LOST! PLAY AGAIN?";
        if (MessageBox(nullptr, message.c_str(), "GAME OVER", MB_YESNO) != IDYES) {
            break;
        }
    }
    return 0;
}