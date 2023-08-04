#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
using namespace std;

class Logic {
public:
    int life[81][2];  //Вспомогательный двумерный массив
    int dots[81][2];  //Вспомогательный двумерный массив
    int board[9][9];  //Игровое поле
    int coun = 0;  //Вспомогательный каунтер

    void isEnd() {  // Окончание игры
        system("cls");
        for (int i1 = 0; i1 < 9; i1++) {    //Захвати территории
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
        for (int i1 = 0; i1 < 9; i1++) { //Финальный захват камнеей
            for (int j1 = 0; j1 < 9; j1++) {
                if (board[i1][j1] == 1 || board[i1][j1] == 2) {
                    clean();
                    breath(i1, j1);
                    capture();
                    clean();
                }
            }
        }
        for (int i1 = 0; i1 < 9; i1++) { //Финальныое выведение поля в консоль
            for (int j1 = 0; j1 < 9; j1++) {
                cout << board[i1][j1] << " ";
            }
            cout << endl;
        }
        cout << "Игра окончена\n";
        cout << "Счет первого игрока " << score(1) << endl << "Счет второго игрока " << score(2) << endl; //Выведение финального счета игроков
        if (score(1) > score(2)) { //Выведение кто победил
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

    void reset() {  //Очищение игрового поля
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                board[i][j] = 0;
            }
        }
    }

    void clean() { //Очищение вспомогательных массивов и каунтера
        for (int i = 0; i < 81; i++) {
            for (int j = 0; j < 2; j++) {
                life[i][j] = -1;
                dots[i][j] = -1;
            }
        }
        coun = 0;
    }

    void breath(int i, int j) { //Сбор кластера точек одного игрока и точек дыхание этого кластера
        bool flag = true;
        for (int i1 = 0; i1 < 81; i1++) { //Проверка на наличие точки точки с данными координатами в массиве кластера 
            if ((i == dots[i1][0]) && (j == dots[i1][1])) {
                flag = false;
            }
        }
        if (flag == true) {
            dots[coun][0] = i; //Добовление точки в массив кластера
            dots[coun][1] = j;
            coun++;
            if (i != 0) {  //Проверка верхнего края поля
                if ((board[i - 1][j] == 0) || (board[i - 1][j] == -board[i][j])) { //Проверка является ли соседняя точка точкой дыхания
                    life[coun][0] = i - 1; //Добавление в массив точке дыхания
                    life[coun][1] = j;
                }
                else if (board[i - 1][j] == board[i][j]) { //Если точка не является точкой дыхания проверка является ли точкой кластера
                    breath(i - 1, j);
                }
            }
            if (i != 8) { //Проверка нижнего края поля
                if ((board[i + 1][j] == 0) || (board[i + 1][j] == -board[i][j])) { //Проверка является ли соседняя точка точкой дыхания
                    life[coun][0] = i + 1;//Добавление в массив точке дыхания
                    life[coun][1] = j;
                }
                else if (board[i + 1][j] == board[i][j]) { //Если точка не является точкой дыхания проверка является ли точкой кластера
                    breath(i + 1, j);
                }
            }
            if (j != 0) { //Проверка левого края поля
                if ((board[i][j - 1] == 0) || (board[i][j - 1] == -board[i][j])) { //Проверка является ли соседняя точка точкой дыхания
                    life[coun][0] = i; //Добавление в массив точке дыхания
                    life[coun][1] = j - 1;
                }
                else if (board[i][j - 1] == board[i][j]) { //Если точка не является точкой дыхания проверка является ли точкой кластера
                    breath(i, j - 1);
                }
            }
            if (j != 8) { //Проверка правого края поля
                if ((board[i][j + 1] == 0) || (board[i][j + 1] == -board[i][j])) { //Проверка является ли соседняя точка точкой дыхания
                    life[coun][0] = i; //Добавление в массив точке дыхания
                    life[coun][1] = j + 1;
                }
                else if (board[i][j + 1] == board[i][j]) { //Если точка не является точкой дыхания проверка является ли точкой кластера
                    breath(i, j + 1);
                }
            }
        }
    }

    void capture() { //Захват кластера точек если у него отсутствуют точки дыхания
        bool flag = true;
        for (int i = 0; i < 81; i++) { //Провекра наличия точек дыхания
            if ((life[i][0] != -1) && (life[i][1] != -1)) {
                flag = false;
            }
        }
        if (flag == true) {
            for (int i = 0; i < coun; i++) { //Захват, если точки дыхания отсутствуют
                board[dots[i][0]][dots[i][1]] = 0;
            }
            clean();
        }
    }

    void freeland(int i, int j, int whoturn, int coun2) { //Сбор кластера свободных территорий и точек окружающих его
        bool flag = true;
        for (int i1 = 0; i1 < 81; i1++) { //Проверка входит ли точка в массив кластера свободных территорий
            if ((i == dots[i1][0]) && (j == dots[i1][1])) {
                flag = false;
            }
        }
        if (flag == true) {
            if (board[i][j] != whoturn) {
                dots[coun][0] = i; //Добавление точки в массив кластера свободных точек
                dots[coun][1] = j;
                coun++;
            }
            if (i != 0) { //Проверка верхнего края поля
                if (board[i - 1][j] != whoturn) { //Проверка является ли точка точкой свободный территории
                    freeland(i - 1, j, whoturn, coun2);
                }
                else if (board[i - 1][j] == whoturn) { //Проверка является ли точка ограничивающей
                    life[coun2][0] = i - 1; //Добавление в массив граничных точек
                    life[coun2][1] = j;
                    coun2++;
                }
            }
            if (i != 8) { //Проверка нижнего края поля
                if (board[i + 1][j] != whoturn) { //Проверка является ли точка точкой свободный территории
                    freeland(i + 1, j, whoturn, coun2);
                }
                else if (board[i + 1][j] == whoturn) { //Проверка является ли точка ограничивающей
                    life[coun2][0] = i + 1; //Добавление в массив граничных точек
                    life[coun2][1] = j;
                    coun2++;
                }
            }
            if (j != 0) { //Проверка левого края поля
                if (board[i][j - 1] != whoturn) { //Проверка является ли точка точкой свободный территории
                    freeland(i, j - 1, whoturn, coun2);
                }
                else if (board[i][j - 1] == whoturn) { //Проверка является ли точка ограничивающей
                    life[coun2][0] = i; //Добавление в массив граничных точек
                    life[coun2][1] = j - 1;
                    coun2++;
                }
            }
            if (j != 8) { //Проверка правого края поля
                if (board[i][j + 1] != whoturn) { //Проверка является ли точка точкой свободный территории
                    freeland(i, j + 1, whoturn, coun2);
                }
                else if (board[i][j + 1] == whoturn) { //Проверка является ли точка ограничивающей
                    life[coun2][0] = i; //Добавление в массив граничных точек
                    life[coun2][1] = j + 1;
                    coun2++;
                }
            }
        }
    }
    
    bool connection() {
        int con, solocon = 0; //Количество соединений у точки и количество точек с одним соединенмем
        for (int i = 0; i < 81; i++) { 
            if (life[i][0] != -1) {
                con = 0;
                for (int j = 0; j < 81; j++) {
                    for (int i1 = -1; i1 < 2; i1++) {
                        for (int j1 = -1; j1 < 2; j1++) {
                                if ((life[i][0] + i1 == life[j][0]) && (life[i][1] + j1 == life[j][1])) { //Проверка является ли точка содиненной с данной
                                    con++;
                            }
                        }
                    }
                }
                if (con == 0) { //Проверка количества соединений точки 
                    return false;
                }
                else if (con == 1) {
                    solocon++;
                }
            }
        }
        if (solocon > 4) { //Проверка количества точек с одним соединением
            return false;
        }
        return true;
    }

    void freelandconquer(int who) { //Захват свободных территорий занесенных в массив кластера
        bool flag = true;
        for (int i = 0; i < 81; i++) {
            if ((life[i][0] != -1) && (life[i][1] != -1)) {
                if (board[life[i][0]][life[i][1]] != who) { //Проверка на однородность массива ограничивающих точек
                    flag = false;
                }
            }
        }
        if ((coun < 35) && (connection()) && (flag)) { //Проверка необходимых условий
            for (int i = 0; i < coun; i++) { //Захват свободной территории
                board[dots[i][0]][dots[i][1]] = -board[life[0][0]][life[0][1]];
            }
        }
        clean();
    }

    int score(int player) { //Подсчет очков заданного игрока
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
        sf::RenderWindow window(sf::VideoMode(621, 621), "Go"); //Игровое окно
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
        window.display(); //Выведение начального игрового поля
        setlocale(LC_ALL, "Russian"); //Использование русского языка в консоли
        cout << "Управление стрелками, чтобы сбросить поле нажмите R \n z - спасовать ход (2 паса подряд - ничья) \n У каждого игрока по 20 комней, но использовать их все не обязательно \n Счет очков идет по захваченным территория и пленным, отмеченым в конце номером игрока умноженым на -1 \n esc чтобы выключить \n Удачи!";
        HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(handle, FOREGROUND_RED); //Изменение цвета текста в консоли
        int key, stone1 = 20, stone2 = 20, pas = 0, whoturn = 2, i = 4, j = 4; //Номер нажатой кнопки, камни первого и второго игрока, кол-во пасов подряд, игрок кто будет хлдтть следующим, кто ходит, начальнык координаты
        while (window.isOpen()) { //Цикл работающий пока открыто окно
            key = _getch(); // Считывание нажатой кнопки
            cout << "Нажимайте кнопки, чтобы выбрать ячейки";
            while ((key != 13) && (key != 122) && (key != 239) && (key != 27)) { //Проверка на нажатие z, enter, esc
                system("cls");
                switch (key)
                {
                case 27: window.close(); //esc(Выключение программы)
                    break;
                case 75: if (j != 0) { //Стрелка влево и провека возможности перемещения туда
                    j--;
                }
                       else {
                    cout << "Перемещение влево невозможно\n";
                }
                       break;
                case 72: if (i != 0) { i--; } //Стрелка вверх и провека возможности перемещения туда
                       else {
                    cout << "Перемещение вверх невозможно\n";
                }
                       break;
                case 77: if (j != 8) { j++; } //Стрелка вправо и провека возможности перемещения туда
                       else {
                    cout << "Перемещение вправо невозможно\n";
                }
                       break;
                case 80: if (i != 8) { i++; } //Стрелка вниз и провека возможности перемещения туда
                       else {
                    cout << "Перемещение вниз невозможно\n";
                }
                       break;
                case 114: reset(); //кнопка r(перезапуск)
                    stone1 = 20;
                    stone2 = 20;
                    break;
                case 170: reset();//кнопка r(перезапуск)
                    stone1 = 20;
                    stone2 = 20;
                    break;
                }
                window.clear(); //Выведение выбранной клетки
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
                for (int i1 = 0; i1 < 9; i1++) { //Выведение игрового поля
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
                cout << "-------------------------------------------------------\n Ходит игрок номер " << whoturn; //Выведение кто ходит
                key = _getch();
            }
            if ((key == 239) || (key == 122)) { //Проверка паса(Нажатя z)
                pas++;
                switch (whoturn) { //Смена игрока
                case 1: whoturn++;
                    break;
                case 2: whoturn--;
                    break;
                }
                if (pas == 2) { // Провека двух пасов подряд
                    isEnd(); // Окончание игры
                    window.clear(); //Выведение окончательного поля
                    window.draw(rectangle);
                    window.draw(sprite);
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
                    while ((key != 114) && (key != 170)) { //Бесконеченый цикл пока не перезапустят поле
                        key = _getch();
                        cout << "Для рестарта нажмите R\n";
                    }
                    reset(); //Перезапуск игры
                    stone1 = 20;
                    stone2 = 20;
                }
                else {
                    system("cls");
                    if (whoturn == 1) { //Выведение кто ходит
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
                    for (int i1 = 0; i1 < 9; i1++) { //выведение игрового поля в консоль
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
                    cout << "-------------------------------------------------------\n Ходит игрок номер " << whoturn; //Выведение кто ходит в консоль
                }
            }
            else if (key == 27) { //Выключение если нажат esc
                break;
            }
            else {
                pas = 0; //Обнуление пасов подряд если 1 из игроков не пасовал
                if ((board[i][j] == 0) || (board[i][j] == -whoturn)) { //Проверка является ли выбранная клетка пустой
                    clean();
                    board[i][j] = whoturn; //Ставит камень
                    bool flag = true;
                    for (int i1 = 0; i1 < 9; i1++) { //Захваты после поставленного камня
                        for (int j1 = 0; j1 < 9; j1++) {
                            if ((board[i1][j1] == 1 || board[i1][j1] == 2) && ((i1 != i) || (j1 != j))) {
                                clean();
                                breath(i1, j1);
                                capture();
                                clean();
                            }
                        }
                    }
                    clean();
                    breath(i, j);
                    for (int i = 0; i < 81; i++) { //Проверка является ли ход самоубийственным
                        if ((life[i][0] != -1) && (life[i][1] != -1)) {
                            flag = false;
                        }
                    }
                    if (flag == true) { //Отмена хода если он самоубийственный
                        board[i][j] = 0;
                    }
                    system("cls");
                    window.clear(); //Выведение игрового поля после хода игрока
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
                    switch (whoturn) { //Смена ходящего игрока если ход не самоубийственный и отнятие камней у походившего игрока
                    case 1: if (board[i][j] != 0) {
                        stone1--;
                        if (stone2 != 0) {
                            whoturn++;
                        }
                    }
                          else { cout << "Самоубийственный ход невозможен\n"; }
                          break;
                    case 2: if (board[i][j] != 0) {
                        stone2--;
                        if (stone1 != 0) {
                            whoturn--;
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