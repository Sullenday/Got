#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
using namespace std;

class Logic {
public:
    int life[81][2];
    int dots[81][2];
    int board[9][9];
    int coun = 0;

    void isEnd() {
        system("cls");
        for (int i1 = 0; i1 < 9; i1++) {
            for (int j1 = 0; j1 < 9; j1++) {
                    clean();
                    freeland(i1, j1, 1, 0);
                    freelandconquer(1);
                    clean();
                    freeland(i1, j1, 2, 0);
                    freelandconquer(2);
                    clean();
            }
        }
        for (int i1 = 0; i1 < 9; i1++) {
            for (int j1 = 0; j1 < 9; j1++) {
                if (board[i1][j1] == 1 || board[i1][j1] == 2) {
                    clean();
                    breath(i1, j1);
                    capture();
                    clean();
                }
            }
        }
        for (int i1 = 0; i1 < 9; i1++) {
            for (int j1 = 0; j1 < 9; j1++) {
                cout << board[i1][j1] << " ";
            }
            cout << endl;
        }
        cout << "Игра окончена\n";
        cout << "Счет первого игрока " << score(1) << endl << "Счет второго игрока " << score(2) << endl;
        if (score(1) > score(2)) {
            cout << "Побеждает первый игрок\n";
        }
        else if (score(2) > score(1)) {
            cout << "Побеждает второй игрок\n";
        }
        else {
            cout << "Ничья!!!\n";
        }
        cout << "Для рестарта нажмите R\n";
    }

    void reset() {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                board[i][j] = 0;
            }
        }
    }

    void clean() {
        for (int i = 0; i < 81; i++) {
            for (int j = 0; j < 2; j++) {
                life[i][j] = -1;
                dots[i][j] = -1;
            }
        }
        coun = 0;
    }

    void breath(int i, int j) {
        bool flag = true;
        for (int i1 = 0; i1 < 81; i1++) {
            if ((i == dots[i1][0]) && (j == dots[i1][1])) {
                flag = false;
            }
        }
        if (flag == true) {
            dots[coun][0] = i;
            dots[coun][1] = j;
            coun++;
            if (i != 0) {
                if ((board[i - 1][j] == 0) || (board[i - 1][j] == -board[i][j])) {
                    life[coun][0] = i - 1;
                    life[coun][1] = j;
                }
                else if (board[i - 1][j] == board[i][j]) {
                    breath(i - 1, j);
                }
            }
            if (i != 8) {
                if ((board[i + 1][j] == 0) || (board[i + 1][j] == -board[i][j])) {
                    life[coun][0] = i + 1;
                    life[coun][1] = j;
                }
                else if (board[i + 1][j] == board[i][j]) {
                    breath(i + 1, j);
                }
            }
            if (j != 0) {
                if ((board[i][j - 1] == 0) || (board[i][j - 1] == -board[i][j])) {
                    life[coun][0] = i;
                    life[coun][1] = j - 1;
                }
                else if (board[i][j - 1] == board[i][j]) {
                    breath(i, j - 1);
                }
            }
            if (j != 8) {
                if ((board[i][j + 1] == 0) || (board[i][j + 1] == -board[i][j])) {
                    life[coun][0] = i;
                    life[coun][1] = j + 1;
                }
                else if (board[i][j + 1] == board[i][j]) {
                    breath(i, j + 1);
                }
            }
        }
    }

    void capture() {
        bool flag = true;
        for (int i = 0; i < 81; i++) {
            if ((life[i][0] != -1) && (life[i][1] != -1)) {
                flag = false;
            }
        }
        if (flag == true) {
            int oppos;
            if (board[dots[0][0]][dots[0][1]] == 1) {
                oppos = 2;
            }
            else {
                oppos = 1;
            }
            for (int i = 0; i < coun; i++) {
                board[dots[i][0]][dots[i][1]] = 0;
            }
            clean();
        }
    }

    void freeland(int i, int j, int whoturn, int coun2) {
        bool flag = true;
        for (int i1 = 0; i1 < 81; i1++) {
            if ((i == dots[i1][0]) && (j == dots[i1][1])) {
                flag = false;
            }
        }
        if (flag == true) {
            if (board[i][j] != whoturn) {
                dots[coun][0] = i;
                dots[coun][1] = j;
                coun++;
            }
            if (i != 0) {
                if (board[i - 1][j] != whoturn) {
                    freeland(i - 1, j, whoturn, coun2);
                }
                else if (board[i - 1][j] == whoturn) {
                    life[coun2][0] = i - 1;
                    life[coun2][1] = j;
                    coun2++;
                }
            }
            if (i != 8) {
                if (board[i + 1][j] != whoturn) {
                    freeland(i + 1, j, whoturn, coun2);
                }
                else if (board[i + 1][j] == whoturn) {
                    life[coun2][0] = i + 1;
                    life[coun2][1] = j;
                    coun2++;
                }
            }
            if (j != 0) {
                if (board[i][j - 1] != whoturn) {
                    freeland(i, j - 1, whoturn, coun2);
                }
                else if (board[i][j - 1] == whoturn) {
                    life[coun2][0] = i;
                    life[coun2][1] = j - 1;
                    coun2++;
                }
            }
            if (j != 8) {
                if (board[i][j + 1] != whoturn) {
                    freeland(i, j + 1, whoturn, coun2);
                }
                else if (board[i][j + 1] == whoturn) {
                    life[coun2][0] = i;
                    life[coun2][1] = j + 1;
                    coun2++;
                }
            }
        }
    }
    
    bool connection() {
        int con, solocon = 0;
        for (int i = 0; i < 81; i++) {
            if (life[i][0] != -1) {
                con = 0;
                for (int j = 0; j < 81; j++) {
                    for (int i1 = -1; i1 < 2; i1++) {
                        for (int j1 = -1; j1 < 2; j1++) {
                                if ((life[i][0] + i1 == life[j][0]) && (life[i][1] + j1 == life[j][1])) {
                                    con++;
                            }
                        }
                    }
                }
                if (con == 0) {     
                    return false;
                }
                else if (con == 1) {
                    solocon++;
                }
            }
        }
        if (solocon > 4) {
            return false;
        }
        return true;
    }

    void freelandconquer(int who) {
        int counter = 0;
        bool flag = true;
        for (int i = 0; i < 81; i++) {
            if (life[i][0] != -1) {
                counter++;
            }
        }
        for (int i = 0; i < 81; i++) {
            if ((life[i][0] != -1) && (life[i][1] != -1)) {
                if (board[life[i][0]][life[i][1]] != who) {
                    flag = false;
                }
            }
        }
        if ((coun == 1) && ((dots[0][0] == 0) && (dots[0][1] == 0) || (dots[0][0] == 0) && (dots[0][1] == 8) || (dots[0][0] == 8) && (dots[0][1] == 0) || (dots[0][0] == 8) && (dots[0][1] == 8))) {
            counter = 3;
        }
        if ((coun < 35) && (connection()) && (flag)) {
            for (int i = 0; i < coun; i++) {
                board[dots[i][0]][dots[i][1]] = -board[life[0][0]][life[0][1]];
            }
        }
        clean();
    }

    int score(int player) {
        int count = 0;
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (board[i][j] == -player) {
                    count++;
                }
            }
        }
        return count;
    }


    void game() {
        sf::RenderWindow window(sf::VideoMode(621, 621), "Go");
        sf::Texture texture;
        sf::CircleShape shape(20.f);
        sf::RectangleShape rectangle(sf::Vector2f(1000.f, 1000.f));
        rectangle.setFillColor(sf::Color(224, 224, 244));
        window.draw(rectangle);
        texture.loadFromFile("image.png", sf::IntRect(20, 20, 0, 0));
        sf::Sprite sprite;
        sprite.setTexture(texture);
        sprite.setPosition(20.f, 20.f);
        window.draw(sprite);
        window.display();
        setlocale(LC_ALL, "Russian");
        cout << "Управление стрелками, чтобы сбросить поле нажмите R \n z - спасовать ход (2 паса подряд - ничья) \n У каждого игрока по 20 комней, но использовать их все не обязательно \n Счет очков идет по захваченным территория и пленным, отмеченым в конце номером игрока умноженым на -1 \n esc чтобы выключить \n Удачи!";
        HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(handle, FOREGROUND_RED);
        int key, stone1 = 20, stone2 = 20, pas = 0, oppos = 1, whoturn = 2, i = 4, j = 4;
        while (window.isOpen()) {
            key = _getch();
            cout << "Нажимайте кнопки, чтобы выбрать ячейки";
            while ((key != 13) && (key != 122) && (key != 239) && (key != 27)) {
                system("cls");
                switch (key)
                {
                case 27: window.close();
                    break;
                case 75: if (j != 0) {
                    j--;
                }
                       else {
                    cout << "Перемещение влево невозможно\n";
                }
                       break;
                case 72: if (i != 0) { i--; }
                       else {
                    cout << "Перемещение вверх невозможно\n";
                }
                       break;
                case 77: if (j != 8) { j++; }
                       else {
                    cout << "Перемещение вправо невозможно\n";
                }
                       break;
                case 80: if (i != 8) { i++; }
                       else {
                    cout << "Перемещение вниз невозможно\n";
                }
                       break;
                case 114: reset();
                    stone1 = 20;
                    stone2 = 20;
                    break;
                case 170: reset();
                    stone1 = 20;
                    stone2 = 20;
                    break;
                }
                window.clear();
                window.draw(rectangle);
                window.draw(sprite);
                if (whoturn == 1) {
                    shape.setRadius(10.f);
                    shape.setFillColor(sf::Color::White);
                    shape.setPosition(0, 0);
                    window.draw(shape);
                    shape.setRadius(20.f);
                }
                else {
                    shape.setRadius(10.f);
                    shape.setFillColor(sf::Color::Black);
                    shape.setPosition(0, 0);
                    window.draw(shape);
                    shape.setRadius(20.f);
                }
                for (int i1 = 0; i1 < 9; i1++) {
                    for (int j1 = 0; j1 < 9; j1++) {
                        if (board[i1][j1] == 1) {
                            float i2, j2;
                            shape.setFillColor(sf::Color::White);
                            i2 = 10 + 70 * i1;
                            j2 = 10 + 70 * j1;
                            shape.setPosition(j2, i2);
                            window.draw(shape);
                        }
                        else if (board[i1][j1] == 2) {
                            float i2, j2;
                            shape.setFillColor(sf::Color::Black);   
                            i2 = 10 + 70 * i1;
                            j2 = 10 + 70 * j1;
                            shape.setPosition(j2, i2);
                            window.draw(shape);
                        }
                        if ((i1 == i) && (j1 == j)) {
                            shape.setRadius(10.f);
                            shape.setFillColor(sf::Color::Green);
                            shape.setPosition(20 + 70 * j1, 20 + 70 * i1);
                            window.draw(shape);
                            shape.setRadius(20.f);
                            SetConsoleTextAttribute(handle, FOREGROUND_GREEN);
                            cout << board[i1][j1] << " ";
                            SetConsoleTextAttribute(handle, FOREGROUND_RED);
                        }
                        else { cout << board[i1][j1] << " "; }
                    }
                    cout << endl;
                }
                window.display();
                cout << "-------------------------------------------------------\n Ходит игрок номер " << whoturn;
                key = _getch();
            }
            if ((key == 239) || (key == 122)) {
                pas++;
                switch (whoturn) {
                case 1: whoturn++;
                    oppos--;
                    break;
                case 2: whoturn--;
                    oppos++;
                    break;
                }
                if (pas == 2) {
                    isEnd();
                    window.clear(); 
                    window.draw(rectangle);
                    window.draw(sprite);
                    if (whoturn == 1) {
                        shape.setRadius(10.f);
                        shape.setFillColor(sf::Color::White);
                        shape.setPosition(0, 0);
                        window.draw(shape);
                        shape.setRadius(20.f);
                    }
                    else {
                        shape.setRadius(10.f);
                        shape.setFillColor(sf::Color::Black);
                        shape.setPosition(0, 0);
                        window.draw(shape);
                        shape.setRadius(20.f);
                    }
                    for (int i1 = 0; i1 < 9; i1++) {
                        for (int j1 = 0; j1 < 9; j1++) {
                            if (board[i1][j1] == 1) {
                                float i2, j2;
                                shape.setFillColor(sf::Color::White);
                                i2 = 10 + 70 * i1;
                                j2 = 10 + 70 * j1;
                                shape.setPosition(j2, i2);
                                window.draw(shape);
                            }
                            else if (board[i1][j1] == 2) {
                                float i2, j2;
                                shape.setFillColor(sf::Color::Black);
                                i2 = 10 + 70 * i1;
                                j2 = 10 + 70 * j1;
                                shape.setPosition(j2, i2);
                                window.draw(shape);
                            }
                        }
                    }
                    window.display();
                    key = _getch();
                    while ((key != 114) && (key != 170)) {
                        key = _getch();
                        cout << "Для рестарта нажмите R\n";
                    }
                    reset();
                    stone1 = 20;
                    stone2 = 20;
                }
                else {
                    system("cls");
                    if (whoturn == 1) {
                        shape.setRadius(10.f);
                        shape.setFillColor(sf::Color::White);
                        shape.setPosition(0, 0);
                        window.draw(shape);
                        shape.setRadius(20.f);
                    }
                    else {
                        shape.setRadius(10.f);
                        shape.setFillColor(sf::Color::Black);
                        shape.setPosition(0, 0);
                        window.draw(shape);
                        shape.setRadius(20.f);
                    }
                    window.display();
                    for (int i1 = 0; i1 < 9; i1++) {
                        for (int j1 = 0; j1 < 9; j1++) {
                            if ((i1 == i) && (j1 == j)) {
                                SetConsoleTextAttribute(handle, FOREGROUND_GREEN);
                                cout << board[i1][j1] << " ";
                                SetConsoleTextAttribute(handle, FOREGROUND_RED);
                            }
                            else { cout << board[i1][j1] << " "; }
                        }
                        cout << endl;
                    }
                    cout << "-------------------------------------------------------\n Ходит игрок номер " << whoturn;
                }
            }
            else if (key == 27) {
                break;
            }
            else {
                pas = 0;
                if ((board[i][j] == 0) || (board[i][j] == -whoturn)) {
                    clean();
                    board[i][j] = whoturn;
                    bool flag = true;
                    breath(i, j);
                    for (int i = 0; i < 81; i++) {
                        if ((life[i][0] != -1) && (life[i][1] != -1)) {
                            flag = false;
                        }
                    }
                    if (!flag) {
                        for (int i1 = 0; i1 < 9; i1++) {
                            for (int j1 = 0; j1 < 9; j1++) {
                                if ((board[i1][j1] == 1 || board[i1][j1] == 2) && ((i1 != i) || (j1 != j))) {
                                    clean();
                                    breath(i1, j1);
                                    capture();
                                    clean();
                                }
                            }
                        }
                    }
                    clean();
                    if (flag == true) {
                        board[i][j] = 0;
                    }
                    system("cls");
                    window.clear();
                    window.draw(rectangle);
                    window.draw(sprite);
                    if (whoturn == 1) {
                        shape.setRadius(10.f);
                        shape.setFillColor(sf::Color::White);
                        shape.setPosition(0, 0);
                        window.draw(shape);
                        shape.setRadius(20.f);
                    }
                    else {
                        shape.setRadius(10.f);
                        shape.setFillColor(sf::Color::Black);
                        shape.setPosition(0, 0);
                        window.draw(shape);
                        shape.setRadius(20.f);
                    }
                    for (int i1 = 0; i1 < 9; i1++) {
                        for (int j1 = 0; j1 < 9; j1++) {
                            if (board[i1][j1] == 1) {
                                float i2, j2;
                                shape.setFillColor(sf::Color::White);
                                i2 = 10 + 70 * i1;
                                j2 = 10 + 70 * j1;
                                shape.setPosition(j2, i2);
                                window.draw(shape);
                            }
                            else if (board[i1][j1] == 2) {
                                float i2, j2;
                                shape.setFillColor(sf::Color::Black);
                                i2 = 10 + 70 * i1;
                                j2 = 10 + 70 * j1;
                                shape.setPosition(j2, i2);
                                window.draw(shape);
                            }
                            cout << board[i1][j1] << " ";
                        }
                        cout << endl;
                    }
                    window.display();
                    switch (whoturn) {
                    case 1: if (board[i][j] != 0) {
                        stone1--;
                        if (stone2 != 0) {
                            whoturn++;
                            oppos--;
                        }
                    }
                          else { cout << "Самоубийственный ход невозможен\n"; }
                          break;
                    case 2: if (board[i][j] != 0) {
                        stone2--;
                        if (stone1 != 0) {
                            whoturn--;
                            oppos++;
                        }
                    }
                          else { cout << "Самоубийственный ход невозможен\n"; }
                          break;
                    }
                    if ((stone1 <= 0) && (stone2 <= 0)) {
                        isEnd();
                        window.clear();
                        window.draw(rectangle);
                        window.draw(sprite);
                        if (whoturn == 1) {
                            shape.setRadius(10.f);
                            shape.setFillColor(sf::Color::White);
                            shape.setPosition(0, 0);
                            window.draw(shape);
                            shape.setRadius(20.f);
                        }
                        else {
                            shape.setRadius(10.f);
                            shape.setFillColor(sf::Color::Black);
                            shape.setPosition(0, 0);
                            window.draw(shape);
                            shape.setRadius(20.f);
                        }
                        for (int i1 = 0; i1 < 9; i1++) {
                            for (int j1 = 0; j1 < 9; j1++) {
                                if (board[i1][j1] == 1) {
                                    float i2, j2;
                                    shape.setFillColor(sf::Color::White);
                                    i2 = 10 + 70 * i1;
                                    j2 = 10 + 70 * j1;
                                    shape.setPosition(j2, i2);
                                    window.draw(shape);
                                }
                                else if (board[i1][j1] == 2) {
                                    float i2, j2;
                                    shape.setFillColor(sf::Color::Black);
                                    i2 = 10 + 70 * i1;
                                    j2 = 10 + 70 * j1;
                                    shape.setPosition(j2, i2);
                                    window.draw(shape);
                                }
                            }
                        }
                        window.display();
                        key = _getch();
                        while ((key != 114) && (key != 170)) {
                            key = _getch();
                            cout << "Для рестарта нажмите R\n";
                        }
                        reset();
                        stone1 = 20;
                        stone2 = 20;
                    }
                }
                else {
                    cout << "Нельзя ставить на занятую уже занятую ячейчку, поставьте в не занятую" << endl;
                }
            }
        }
    }
};

int main()
{
    Logic Go;
    Go.reset();
    Go.game();
}