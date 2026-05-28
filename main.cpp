#include <stdio.h>
#include <graphics.h>
#include <conio.h>

typedef struct
{
    float x;
    float y;
    int traka;
    int sirina;
    int visina;
}lik;

typedef struct
{
    lik player;
    lik prepreke;
    lik coins;
    int money;
}objekti;

void menu();
void game(objekti *obj);
void enemySpawn(lik *en, lik *ob);
void coinSpawn(lik *cn);
void gameOver();

int main()
{
    int gameState = 0;
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");
    int mx, my;
    float deltaTime = 0.016;

    objekti obj;
    obj.player.x = 120;
    obj.player.y = 240;
    obj.player.traka = 1;
    obj.player.sirina = 60;
    obj.player.visina = 20;

    obj.prepreke.x = 680;
    obj.prepreke.y = 240;
    obj.player.traka = 1;
    obj.player.sirina = 80;
    obj.player.visina = 50;

    obj.money = 0;

    while (gameState == 0)
    {
        menu();
        if (ismouseclick(WM_LBUTTONDOWN))
        {
            mx = mousex();
            my = mousey();
            clearmouseclick(WM_LBUTTONDOWN);
            if (((mx>200) && (mx<400)) && ((my>100) && (my<170)))
            {
                gameState = 1;
            }
        }

        delay(16);
    }

    cleardevice();

    while (gameState == 1)
    {
        game(&obj);
        delay(16);
    }

    getch();
    closegraph();
    return 0;
}

void menu()
{
    settextstyle(4, 0, 5);
    outtextxy(150, 50, "Auto Surfer");

    setfillstyle(1,CYAN);
    bar(200,100,400,170);
    settextstyle(4, 0, 4);
    outtextxy(250, 120, "Igraj");

    setfillstyle(1,CYAN);
    bar(200,200,400,270);
    settextstyle(4, 0, 4);
    outtextxy(210, 220, "Trgovina");

    setfillstyle(1,CYAN);
    bar(200,300,400,370);
    settextstyle(4, 0, 4);
    outtextxy(250, 320, "Izlaz");
}
void game(objekti *obj)
{
    line(0, 160, 640, 160);
    line(0, 320, 640, 320);

    playerMove(&obj->player)

}