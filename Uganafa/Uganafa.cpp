// Uganafa.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
struct Position {
    int x;
    int y;
};
struct Sprite {
    char Symbol;
};
struct Player {
    struct Sprite PlayerSprite;
    struct Position PlayerPosition;
};
struct Cell {
    struct Sprite CellSprite;
    struct Position CellPosition;
    bool passable;
};
struct Ability {
    struct Sprite AbilitySprite;
    struct Position AbilityPosition;
    int WhatAbility;

};
struct Enemy {
    struct Sprite EnemySprite;
    struct Position EnemyPosition;
    int hp;
};
struct Boss {
    struct Sprite BossSprite;
    struct Position BossPosition;
    int hp;
};
struct Board {
    struct Player Player;
    struct Cell Cell;
    struct Ability Ability;
    struct Enemy Enemy;
    struct Boss Boss;
};
void Spawn(int x, int y, struct Position &myPosition, struct Sprite &mySprite) {
    std::cout << mySprite.Symbol;
    myPosition.x = x;
    myPosition.y = y;
}
void BuildBoard(int maxX, int maxY, struct Board &Board) {
    for (int i = 0; i < maxY; i++) {
        for (int j = 0; j < maxX; j++) {
            struct Cell Cell;
            Cell.CellSprite.Symbol = Board.Cell.CellSprite.Symbol;
            Cell.passable = true;
            if (i == 0 || j == 0|| i == maxY - 1 || j == maxX - 1) {
                Spawn(j, i, Cell.CellPosition, Cell.CellSprite);
                Cell.passable = false;
            }
            else if (i == 1 && j == 1)Spawn(j, i, Board.Player.PlayerPosition, Board.Player.PlayerSprite);
            else if (i == maxY - 2 && j == maxX - 2)Spawn(j, i, Board.Boss.BossPosition, Board.Boss.BossSprite);
            else if (std::rand() % 20 == 0 && Cell.passable)Spawn(j, i, Board.Ability.AbilityPosition, Board.Ability.AbilitySprite);
            else if (std::rand() % 10 == 0 && Cell.passable)Spawn(j, i, Board.Enemy.EnemyPosition, Board.Enemy.EnemySprite);
            else Spawn(j, i, Cell.CellPosition, Cell.CellSprite);

        }
        std::cout << "\n";
    }
}
int main() {
    int maxX = 20, maxY = 10;
    struct Board Board;
    Board.Cell.CellSprite.Symbol = '.';
    Board.Player.PlayerSprite.Symbol = '@';
    Board.Boss.BossSprite.Symbol = '&';
    Board.Ability.AbilitySprite.Symbol = 'z';
    Board.Enemy.EnemySprite.Symbol = 'a';
    Board.Ability.WhatAbility = 1;
    Board.Enemy.hp = 3;
    Board.Boss.hp = 9;
    BuildBoard(maxX, maxY, Board);
}
// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
