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
struct Board {
    struct Sprite BoardSprite;
    struct Position BoardPosition;
};
struct Ability {
    struct Sprite AbilitySprite;
};
void Spawn(int x, int y, struct Board Cell) {
    std::cout << Cell.BoardSprite.Symbol;
    Cell.BoardPosition.x = x;
    Cell.BoardPosition.y = y;
}
void Spawn(int x, int y, struct Player Cell) {
    std::cout << Cell.PlayerSprite.Symbol;
    Cell.PlayerPosition.x = x;
    Cell.PlayerPosition.y = y;
}
void BuildBoard(int maxX, int maxY, struct Board Cell) {
    for (int i = 0; i < maxY; i++) {
        for (int j = 0; j < maxX; j++) {
            Spawn(j, i, Cell);
        }
        std::cout << "\n";
    }
}
int main() {
    int maxX = 20, maxY = 10;
    struct Board Board;
    struct Player Player;
    Board.BoardSprite.Symbol = 'O';
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
