#include <iostream>
#include <thread>
#include <chrono>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <windows.h>

using namespace std;

class Snake
{
private:
    static const int ROWS = 20;
    static const int COLS = 40;
    static const int MAX_LENGTH = 100;

    int snakeX[MAX_LENGTH];
    int snakeY[MAX_LENGTH];

    int foodX;
    int foodY;

    int score;
    int length;

    char direction;
    char key;

    bool gameOver;

public:
    Snake()
    {
        snakeX[0] = 20;
        snakeY[0] = 10;

        score = 0;
        length = 1;
        direction = 'd';
        key = '\0';
        gameOver = false;

        srand((unsigned)time(NULL));

        generateFood();
    }

    void hideCursor()
    {
        HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

        CONSOLE_CURSOR_INFO info;
        info.dwSize = 100;
        info.bVisible = FALSE;

        SetConsoleCursorInfo(console, &info);
    }

    void gotoXY(int x, int y)
    {
        COORD pos = {(SHORT)x, (SHORT)y};
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    }

    void generateFood()
    {
        bool onSnake;

        do
        {
            onSnake = false;

            foodX = rand() % (COLS - 2) + 1;
            foodY = rand() % (ROWS - 2) + 1;

            for (int i = 0; i < length; i++)
            {
                if (snakeX[i] == foodX && snakeY[i] == foodY)
                {
                    onSnake = true;
                    break;
                }
            }

        } while (onSnake);
    }

    void drawBoard()
    {
        for (int y = 0; y < ROWS; y++)
        {
            for (int x = 0; x < COLS; x++)
            {
                if (y == 0 || y == ROWS - 1)
                {
                    cout << "-";
                }
                else if (x == 0 || x == COLS - 1)
                {
                    cout << "|";
                }
                else
                {
                    bool snakeHere = false;

                    for (int i = 0; i < length; i++)
                    {
                        if (snakeX[i] == x && snakeY[i] == y)
                        {
                            if (i == 0)
                                cout << "@";
                            else
                                cout << "o";

                            snakeHere = true;
                            break;
                        }
                    }

                    if (!snakeHere)
                    {
                        if (x == foodX && y == foodY)
                            cout << "*";
                        else
                            cout << " ";
                    }
                }
            }

            cout << endl;
        }

        cout << "\nScore : " << score;
        cout << "\nLength: " << length;
        cout << "\nPress Q to quit.";
    }

    void handleInput()
    {
        if (_kbhit())
        {
            key = _getch();

            if (key == 'q' || key == 'Q')
            {
                gameOver = true;
                return;
            }

            if ((key == 'w' && direction != 's') ||
                (key == 's' && direction != 'w') ||
                (key == 'a' && direction != 'd') ||
                (key == 'd' && direction != 'a'))
            {
                direction = key;
            }
        }
    }

    void moveSnake()
    {
        for (int i = length - 1; i > 0; i--)
        {
            snakeX[i] = snakeX[i - 1];
            snakeY[i] = snakeY[i - 1];
        }

        switch (direction)
        {
        case 'w':
            snakeY[0]--;
            break;

        case 's':
            snakeY[0]++;
            break;

        case 'a':
            snakeX[0]--;
            break;

        case 'd':
            snakeX[0]++;
            break;
        }
    }

    void checkWallCollision()
    {
        if (snakeX[0] <= 0 ||
            snakeX[0] >= COLS - 1 ||
            snakeY[0] <= 0 ||
            snakeY[0] >= ROWS - 1)
        {
            gameOver = true;
        }
    }

    void checkSelfCollision()
    {
        for (int i = 1; i < length; i++)
        {
            if (snakeX[0] == snakeX[i] &&
                snakeY[0] == snakeY[i])
            {
                gameOver = true;
                break;
            }
        }
    }
    public:
    void checkFood()
    {
        if (snakeX[0] == foodX &&
            snakeY[0] == foodY)
        {
            score++;

            if (length < MAX_LENGTH)
                length++;

            generateFood();
        }
    }

    void draw()
    {
        gotoXY(0, 0);

        drawBoard();

        this_thread::sleep_for(
            chrono::milliseconds(150));
    }

    void gameRun()
    {
        hideCursor();

        cout << "Use WASD to move the snake.\n";
        cout << "Press Q to quit.\n\n";

        while (!gameOver)
        {
            handleInput();

            moveSnake();

            checkWallCollision();

            checkSelfCollision();

            checkFood();

            draw();
        }

        gotoXY(0, ROWS + 3);

        cout << "\n=====================\n";
        cout << "     GAME OVER\n";
        cout << "=====================\n";
        cout << "Final Score : " << score << endl;
        cout << "Length      : " << length << endl;

        system("pause");
    }
};

class Menu
{
public:

    void displayMenu()
    {
        int choice;

        while (true)
        {
            system("cls");

            cout << "=====================\n";
            cout << "     SNAKE GAME\n";
            cout << "=====================\n";
            cout << "1. Start Game\n";
            cout << "2. Exit\n\n";

            cout << "Enter your choice : ";
            cin >> choice;

            switch (choice)
            {
            case 1:
            {
                Snake game;
                game.gameRun();
                break;
            }

            case 2:
            {
                cout << "\nThanks for playing!\n";
                exit(0);
                break;
            }

            default:
            {
                cout << "\nInvalid choice!";
                cout << "\nPress any key to continue...";
                _getch();
            }
            }
        }
    }
};

int main()
{
    Menu menu;

    menu.displayMenu();

    return 0;
}