#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#include <time.h>

typedef struct
{
    float x;
    float y;
    int traka;
    int sirina;
    int visina;
    int lvStr, dsStr;
}lik;

typedef struct
{
    float x;
    float y;
    int traka;
    int aktivno;
    int sirina;
    int visina;
    int lijevaStr, desnaStr;
}prepreka;

typedef struct
{
    lik player;
    prepreka prepreka[6];
}objekti;

void menu();
void playerMove(objekti *obj, char *T);
void drawPlayer(objekti *obj);
void drawPrepreke(objekti *obj);
void game(objekti *obj, float *p, char *T, int *Gs);
void obstacleSpawn(objekti *obj);
void gameOver();

int main()
{
    srand(time(NULL));

    int gameState = 0, *Gs=&gameState;
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");
    int mx, my;
    float speed = 5;
    float *Ps = &speed;
    char tipka = 0;
    char *T = &tipka;

    objekti obj;
    obj.player.x = 50;
    obj.player.y = 240;
    obj.player.traka = 1;
    obj.player.sirina = 40;
    obj.player.visina = 20;

    for (int i=0; i<6; i++)
    {
        obj.prepreka[i].aktivno = 0;
    }

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
        game(&obj, Ps, T, Gs);
        delay(16);

        if (gameState == 2)
            break;
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

void drawPlayer(objekti *obj)
{
    setcolor(RED);
    setfillstyle(1, RED);
    ellipse(obj->player.x, obj->player.y, 0, 360, obj->player.sirina, obj->player.visina);
    floodfill(obj->player.x, obj->player.y, RED);

    obj->player.lvStr = obj->player.x-obj->player.sirina;
    obj->player.dsStr = obj->player.x+obj->player.sirina;
}

void drawPrepreke(objekti *obj)
{
    for (int i=0; i<6; i++)
    {
        if (obj->prepreka[i].aktivno == 1)
        {
            setcolor(LIGHTGRAY);
            setfillstyle(1, LIGHTGRAY);
            bar(obj->prepreka[i].x-20, obj->prepreka[i].y-20, (obj->prepreka[i].x-20)+obj->prepreka[i].sirina, (obj->prepreka[i].y-20)+obj->prepreka[i].visina);
            obj->prepreka[i].lijevaStr = obj->prepreka[i].x-20;
            obj->prepreka[i].desnaStr = (obj->prepreka[i].x-20)+obj->prepreka[i].sirina;
        }
    }
}

void obstacleSpawn(objekti *obj)
{
    static int lastLane = -1;

    for (int i=0; i<6; i++)
    {
        if (obj->prepreka[i].aktivno == 0)
        {
            int obstacleLane = rand()%3;

            while (obstacleLane == lastLane)
            {
                obstacleLane = rand()%3;
            }

            lastLane = obstacleLane;

            obj->prepreka[i].aktivno = 1;
            obj->prepreka[i].x = 700;
            obj->prepreka[i].traka = obstacleLane;
            obj->prepreka[i].sirina = 70;
            obj->prepreka[i].visina = 50;

            if (obstacleLane == 0)
            {
                obj->prepreka[i].y = 80;
            }
            else if (obstacleLane == 1)
            {
                obj->prepreka[i].y = 240;
            }
            else
                obj->prepreka[i].y = 400;

            break;
        }
    }

}

void playerMove(objekti *obj, char *T)
{
    while (kbhit())
    {
        *T = getch();
    }

    if (*T == 'w')
    {
        obj->player.y -= 160;
        *T = 0;
        obj->player.traka -= 1;
    }
    else if (*T == 's')
    {
        obj->player.y += 160;
        *T = 0;
        obj->player.traka += 1;
    }

    if ((obj->player.y < 0) || (obj->player.traka < 0))
    {
        obj->player.y = 80;
        obj->player.traka = 0;
    }
    else if ((obj->player.y > 480) || (obj->player.traka > 2))
    {
        obj->player.y = 400;
        obj->player.traka = 2;
    }
}

void game(objekti *obj, float *p, char *T, int *Gs)
{
    static float brojac = 0;
    static int collision = 0;

    cleardevice();

    setcolor(WHITE);
    line(0, 160, 640, 160);
    line(0, 320, 640, 320);

    playerMove(obj, T);

    drawPlayer(obj);

    brojac += *p;

    if (brojac >= 200)
    {
        obstacleSpawn(obj);
        brojac = 0;
    }

    for (int i=0; i<6; i++)
    {
        if (obj->prepreka[i].aktivno == 1)
        {
            obj->prepreka[i].x -= *p;
            if ((obj->prepreka[i].traka == obj->player.traka) && ((obj->prepreka[i].lijevaStr <= obj->player.dsStr) && (obj->prepreka[i].desnaStr >= obj->player.lvStr)))
            {
                collision = 1;
            }

            if (obj->prepreka[i].x < -100)
            {
                obj->prepreka[i].aktivno = 0;
            }
        }
    }

    if (collision == 1)
    {
        *Gs = 2;
    }

    drawPrepreke(obj);
}

