#include <iostream>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include <thread>

using namespace std;

const int kWidth = 80;
const int kHeight = 20;

int snakeHeadX, snakeHeadY;
int fruitPosX, fruitPosY;
int playerScore;
int snakeTailX[100], snakeTailY[100];
int snakeTailLength;
enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
Direction snakeDirection;
bool gameOver;

void InitializeGame()
{
    gameOver = false;
    snakeDirection = STOP;
    snakeHeadX = kWidth / 2;
    snakeHeadY = kHeight / 2;
    fruitPosX = rand() % kWidth;
    fruitPosY = rand() % kHeight;
    playerScore = 0;
    snakeTailLength = 0;
}

void RenderGame(string playerName)
{
    system("cls");

    for (int i = 0; i < kWidth + 2; i++)
        cout << "-";
    cout << endl;

    for (int i = 0; i < kHeight; i++)
    {
        for (int j = 0; j <= kWidth; j++)
        {
            if (j == 0 || j == kWidth)
                cout << "|";
            if (i == snakeHeadY && j == snakeHeadX)
                cout << "O";
            else if (i == fruitPosY && j == fruitPosX)
                cout << "#";
            else
            {
                bool printTail = false;
                for (int k = 0; k < snakeTailLength; k++)
                {
                    if (snakeTailX[k] == j && snakeTailY[k] == i)
                    {
                        cout << "o";
                        printTail = true;
                    }
                }
                if (!printTail)
                    cout << " ";
            }
        }
        cout << endl;
    }

    for (int i = 0; i < kWidth + 2; i++)
        cout << "-";
    cout << endl;

    cout << playerName << "'s Score: " << playerScore << endl;
}

void UpdateGame()
{
    int prevX = snakeTailX[0];
    int prevY = snakeTailY[0];
    int prev2X, prev2Y;
    snakeTailX[0] = snakeHeadX;
    snakeTailY[0] = snakeHeadY;

    for (int i = 1; i < snakeTailLength; i++)
    {
        prev2X = snakeTailX[i];
        prev2Y = snakeTailY[i];
        snakeTailX[i] = prevX;
        snakeTailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (snakeDirection)
    {
    case LEFT:
        snakeHeadX--;
        break;
    case RIGHT:
        snakeHeadX++;
        break;
    case UP:
        snakeHeadY--;
        break;
    case DOWN:
        snakeHeadY++;
        break;
    }

    if (snakeHeadX >= kWidth || snakeHeadX < 0 || snakeHeadY >= kHeight || snakeHeadY < 0)
        gameOver = true;

    for (int i = 0; i < snakeTailLength; i++)
    {
        if (snakeTailX[i] == snakeHeadX && snakeTailY[i] == snakeHeadY)
            gameOver = true;
    }

    if (snakeHeadX == fruitPosX && snakeHeadY == fruitPosY)
    {
        playerScore += 10;
        fruitPosX = rand() % kWidth;
        fruitPosY = rand() % kHeight;
        snakeTailLength++;
    }
}

void GetUserInput()
{
    char input;
    cin >> input;
    switch (input)
    {
    case 'a':
        if (snakeDirection != RIGHT)
            snakeDirection = LEFT;
        break;
    case 'd':
        if (snakeDirection != LEFT)
            snakeDirection = RIGHT;
        break;
    case 'w':
        if (snakeDirection != DOWN)
            snakeDirection = UP;
        break;
    case 's':
        if (snakeDirection != UP)
            snakeDirection = DOWN;
        break;
    case 'x':
        gameOver = true;
        break;
    }
}

int SetDifficulty()
{
    int delayFactor, choice;
    cout << "\nSET DIFFICULTY\n1: Easy\n2: Medium\n3: Hard\nChoose difficulty level: ";
    cin >> choice;
    switch (choice)
    {
    case 1:
        delayFactor = 150;
        break;
    case 2:
        delayFactor = 100;
        break;
    case 3:
        delayFactor = 50;
        break;
    default:
        delayFactor = 100;
    }
    return delayFactor;
}

int main()
{
    srand(time(NULL)); // Seed for random number generation
    string playerName;
    cout << "Enter your name: ";
    cin >> playerName;
    int delayFactor = SetDifficulty();

    InitializeGame();
    while (!gameOver)
    {
        RenderGame(playerName);
        GetUserInput();
        UpdateGame();
        // Sleep for delayFactor milliseconds
        this_thread::sleep_for(chrono::milliseconds(delayFactor));
    }

    cout << "Game Over! Your final score is: " << playerScore << endl;

    return 0;
}
