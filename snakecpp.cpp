#include<iostream>
#include <thread>
#include <chrono>
#include<conio.h>
#include <cstdlib>
#include <ctime>
using namespace std;
const int rows = 20;
const int cols = 40;
const int max_length = 100; 
int snakex[max_length] = {20};
int snakey[max_length] = {10};
int score = 0;
int foodx;
int foody;
int length = 1;
char key= '\0';
char direction = 'd';
bool game_over = false;
void draw_board(int snakeX[], int snakeY[], int foodX, int foodY, int length)
{

    for(int y = 0; y < rows; y++)
    {
        for(int x = 0; x < cols; x++)
        {
            if(y == 0 || y == rows - 1)
            {
                cout << "-";
            }
            else if(x == 0 || x == cols - 1)
            {
                cout << "|";
            }
            else
            {
                bool snakeHere = false;

                for(int i = 0; i < length; i++)
                {
                    if(x == snakeX[i] && y == snakeY[i])
                    {
                        cout << "O";
                        snakeHere = true;
                        break;
                    }
                }

                if(!snakeHere)
                {
                    if(x == foodX && y == foodY)
                    {
                        cout << "*";
                    }
                    else
                    {
                        cout << " ";
                    }
                }
            }
        }
        cout << endl;
    }
}
void handle_input()
{
    if(_kbhit())
    {
        key = _getch();

        if(key == 'q')
        {
            game_over = true;
        }
        else if(key=='w'||key=='a'||key=='s'||key=='d')
        {
            if((key == 'w' && direction == 's') || (key == 's' && direction == 'w') || (key == 'a' && direction == 'd') || (key == 'd' && direction == 'a'))
            {
                cout<<"You can't go in that direction!"<<endl;
            }
            else
            {
                direction = key;
            }
        }
    }
}
void move_snake()
    {
        for(int i = length - 1; i > 0; i--)
        {
            snakex[i] = snakex[i - 1];
            snakey[i] = snakey[i - 1];
        } 
    

        switch(direction)
        {
            case 'w':
                snakey[0]--;
                break;
            case 'a':
                snakex[0]--;
                break;
            case 's':
                snakey[0]++;
                break;
            case 'd':
                snakex[0]++;
                break;
        } 
    }
void check_collision()
    {
        if(snakex[0] <= 0 || snakex[0] >= cols-1 || snakey[0] <= 0 || snakey[0] >= rows-1)
        {
            cout << "You hit the wall!" << endl;
            cout<< "Game Over!" << endl;
            game_over = true;
        }
    }
void check_self_collision()
    {
        for(int i = 1; i < length; i++)
        {
            if(snakex[0] == snakex[i] && snakey[0] == snakey[i])
            {
                cout << "You hit yourself!" << endl;
                cout<< "Game Over!" << endl;
                game_over = true;
                break;
            }
        }
    }
void check_food()
    {
        bool food_on_snake = false;
        if(snakex[0] == foodx && snakey[0] == foody)
        {
            score++;
            if(length < max_length)
            {
                length++;
            }
            do
            {
                foodx = rand() % (cols - 2) + 1;
                foody = rand() % (rows - 2) + 1;

                for(int i = 0; i < length; i++)
                {
                    if(snakex[i]== foodx && snakey[i] == foody)
                    {
                        food_on_snake = true;
                        break;
                    }
                    else
                    {
                        food_on_snake = false;
                    }
                }
            }
            while(food_on_snake);
        }
    }
void draw()
    {
        draw_board(snakex, snakey, foodx, foody, length);

        cout << endl;
        cout << "Score: " << score << endl;
        cout << "Length = " << length << endl;
        
        this_thread::sleep_for(chrono::milliseconds(200));

    }
void gamerun()
{
    cout << "Use WASD to move the snake. Press 'q' to quit." << endl;
    srand(time(NULL));
    foodx = rand() % (cols - 2) + 1;
    foody = rand() % (rows - 2) + 1;
    while(!game_over)
    {
        handle_input();
        move_snake();
        check_collision();
        check_self_collision();
        check_food();
        if(length >= max_length)
        {
            cout << "You win!" << endl;
            game_over = true;
        }
        system("cls");
        draw();
    }
    if(game_over)
    {
        cout << "=====================\n";
        cout << "     GAME OVER\n";
        cout << "=====================\n";
        cout << "Final Score : " << score << endl;
        cout << "Length      : " << length << endl;

        system("pause");
    }
}
int main()
{
    gamerun();
    return 0;
} 