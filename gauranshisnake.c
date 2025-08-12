#include <stdio.h>
#include <conio.h>
#include <windows.h>

int i, j, height = 20, width = 20;
int gameover, score;
int x, y, fruitX, fruitY, flag;

// Snake's tail
int tailX[100], tailY[100];
int nTail;

void setup() {
    gameover = 0;
    x = height / 2;
    y = width / 2;
label1:
    fruitX = rand() % 20;
    if (fruitX == 0)
        goto label1;
label2:
    fruitY = rand() % 20;
    if (fruitY == 0)
        goto label2;
    score = 0;
}

void draw() {
    system("cls");
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            if (i == 0 || i == height - 1 || j == 0 || j == width - 1) {
                printf("#");
            } else {
                if (i == x && j == y)
                    printf("O");
                else if (i == fruitX && j == fruitY)
                    printf("F");
                else {
                    int print = 0;
                    for (int k = 0; k < nTail; k++) {
                        if (tailX[k] == i && tailY[k] == j) {
                            printf("o");
                            print = 1;
                        }
                    }
                    if (print == 0)
                        printf(" ");
                }
            }
        }
        printf("\n");
    }
    printf("Score = %d\n", score);
}

void input() {
    if (_kbhit()) {
        switch (_getch()) {
        case 'a':
            flag = 1;
            break;
        case 's':
            flag = 2;
            break;
        case 'd':
            flag = 3;
            break;
        case 'w':
            flag = 4;
            break;
        case 'x':
            gameover = 1;
            break;
        }
    }
}

void logic() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (flag) {
    case 1:
        y--;
        break;
    case 2:
        x++;
        break;
    case 3:
        y++;
        break;
    case 4:
        x--;
        break;
    default:
        break;
    }

    if (x < 1 || x > height - 2 || y < 1 || y > width - 2)
        gameover = 1;

    for (int i = 0; i < nTail; i++) {
        if (tailX[i] == x && tailY[i] == y)
            gameover = 1;
    }

    if (x == fruitX && y == fruitY) {
    label3:
        fruitX = rand() % 20;
        if (fruitX == 0)
            goto label3;
    label4:
        fruitY = rand() % 20;
        if (fruitY == 0)
            goto label4;
        score += 10;
        nTail++;
    }
}

int main() {
    int m, n;

    setup();
    while (!gameover) {
        draw();
        input();
        logic();
        Sleep(100); // sleep time (controls speed)
    }
    return 0;
}
