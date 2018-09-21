#include <dos.h>
#include <conio.h>
#include <windows.h>
#include <graphics.h>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>;

using namespace std;
void help();
void game();
void check();
void dead();
void level();
void high();
int snake_x[500],snake_y[500],snake_size = 3,score,highscore,spd = 100,l;
bool checkdied = false,BONUS = false;
int main()
{

    int gdirect = DETECT,gmode;  /* request autodetection */
    initgraph(&gdirect,&gmode,""); /* initialize graphics and local variables */
    char ch;
    setcolor(15);
    settextstyle(4,0,4);
    outtextxy(80,10,"Project-1: Snake game");
    settextstyle(11,0,1);
    setcolor(GREEN);
    outtextxy(100,100,"Presented by: ");
    outtextxy(100,140,"Mutasim Billah-2017831018");
    outtextxy(100,180,"Tahseen Rasheed Chowdhury-2017831019");
    outtextxy(100,280,"Presented to: ");
    outtextxy(100,320,"Asif Mohammad Samir Sir");
    outtextxy(100,340,"Assistant Professor");
    outtextxy(100,360,"IICT,SUST");
    ch=getch();
    cleardevice();
    int cursor_y = 130;


    while(1)
    {

        setcolor(CYAN);
        settextstyle(4,0,5);
        outtextxy(180,30," Snake ");
        setcolor(BLUE);
        settextstyle(3,0,3); /*this part prints menu again but inside while loop,because other functions will return here*/
        outtextxy(200,130,"New Game");
        outtextxy(200,160,"Help");
        outtextxy(200,190,"Select Level");
        outtextxy(200,220,"Highscore");
        outtextxy(200,250,"Exit");
        outtextxy(160,cursor_y,">");
        setcolor(BLACK);
        settextstyle(3,0,3);

        if(kbhit)
        {
            ch = getch();
            setcolor(BLACK);
            outtextxy(160,cursor_y,">");
            if(ch == 13)
            {
                if(cursor_y==250) exit(0);
                else if(cursor_y==160) help();
                else if(cursor_y==130) game();
                else if(cursor_y==190) level();
                else if(cursor_y==220) high();
            }
        }
        setcolor(WHITE);
        if(ch==80)
        {
            cursor_y+=30;
            if(cursor_y > 250)
            {
                cursor_y=130;
            }
        }
        if(ch==72)
        {
            cursor_y-=30;
            if(cursor_y < 130)
            {
                cursor_y=250;
            }
        }
        setcolor(BLACK);
        outtextxy(160,cursor_y,">");
    }

    return 0;
}
void help()
{
    setcolor(WHITE);
    outtextxy(100,300,"Move the snake using the Arrow keys.");
    outtextxy(100,330,"Press 'Alt' to Pause");
    char ch = getch();
    clearviewport();
    return;
}
void game()
{
    clearviewport();
    freopen("GameData.dat","r",stdin);


    cin >> highscore;

    cleardevice();


    char ch;
    string key = "right";
    int maxx = getmaxx();
    int maxy = getmaxy()-50;
    int x = 130,y = 130;

    int food_x = rand()%maxx,food_y = rand()%maxy;
    int temp;
    temp = food_x%13;
    food_x-=temp;
    temp = food_y%13;
    food_y-=temp;
    int i = 0;
    int bonus = 500;

    if(food_x < 25 || food_x > maxx -25 || food_y < 25 || food_y > maxy - 25)
    {
        while(food_x < 25 || food_x > maxx -25 || food_y < 25 || food_y > maxy - 25)
        {
            food_x = rand()%maxx,food_y = rand()%maxy;
            temp = food_x%13;
            food_x-=temp;
            temp = food_y%13;
            food_y-=temp;
        }
    }
    while(true)
    {
        clearviewport();

        if(score >0 && score%5==4) BONUS = true;
        else
        {
            bonus = 500;
            BONUS = false;
        }
        if(!BONUS || bonus == 0)
        {
            setcolor(BLACK);
            outtextxy(250,10,"Hurry!! 888");
            setcolor(CYAN);
            setfillstyle(SOLID_FILL,CYAN);
            circle(food_x,food_y,5); //x position,y position,size
            floodfill(food_x,food_y,CYAN);

        }
        else
        {
            setcolor(RED);
            setfillstyle(SOLID_FILL,RED);
            circle(food_x,food_y,10);
            floodfill(food_x,food_y,RED);

            char spp[1000];
            setcolor(BLACK);
            sprintf(spp,"Hurry!! %d",bonus);
            outtextxy(250,10,"Hurry!! 888");
            setcolor(YELLOW);
            outtextxy(250,10,spp);
            // clears
        }
        maxx = getmaxx();
        maxy = getmaxy()-50;
        setcolor(WHITE);

        setcolor(GREEN);


       /** rectangle(0,0,maxx-0,maxy-0);
        rectangle(1,1,maxx-1,maxy-1);
        rectangle(2,2,maxx-2,maxy-2);
        rectangle(3,3,maxx-3,maxy-3);
        rectangle(4,4,maxx-4,maxy-4);
        rectangle(6,5,maxx-5,maxy-5);*/

        setcolor(LIGHTGREEN);
        setfillstyle(3,LIGHTGREEN);
        bar(0,0,maxx,17);
        bar(0,maxy-6,maxx,maxy+7);
        bar(0,0,17,maxy-6 );
        bar(maxx-13,13,maxx,maxy-6);

        setcolor(WHITE);
        line(0,maxy+8,maxx,maxy+8);
        if(kbhit())
        {
            ch = getch();
            if(ch == 0) ch = getch();
            if(ch == 72 && key != "down" ) key = "up";
            if(ch == 80 && key != "up") key = "down";
            if(ch == 75 && key != "right") key = "left";
            if(ch == 77 && key != "left") key = "right";
            if(ch == 27)
            {
                cleardevice();
                return;
            }

        }



        if(i < 3)
        {
            snake_x[i] = x;
            snake_y[i] = y;
            i++;
        }
        else
        {
            for(int _size = snake_size; _size >= 0; _size--)
            {
                snake_x[_size+1] = snake_x[_size];
                snake_y[_size+1] = snake_y[_size];
            }



            snake_x[0] = x;
            snake_y[0] = y;

            setcolor(WHITE);
            circle(snake_x[0],snake_y[0],8);
            setfillstyle(SOLID_FILL,WHITE);
            floodfill(snake_x[0],snake_y[0],WHITE);

            setcolor(LIGHTBLUE);
            for(int _size = 1; _size < snake_size; _size++)
            {
                circle(snake_x[_size],snake_y[_size],5);
                setfillstyle(SOLID_FILL,LIGHTBLUE);
                floodfill(snake_x[_size],snake_y[_size],LIGHTBLUE);
            }

            char ara[100];
            sprintf(ara,"Score: %d",score);
            setcolor(WHITE);
            outtextxy(00,maxy+10,ara);
            sprintf(ara,"Bestscore: %d",highscore);
            setcolor(WHITE);
            outtextxy(450,maxy+10,ara);

            delay(spd);

        }
        if(x == food_x && y== food_y)
        {
            snake_size++;
            score++;
            /* Snake eats food*/
            if(score%5==0 && score>0) score+=bonus;

            food_x = rand()%maxx,food_y = rand()%maxy;
            temp = food_x%13;
            food_x-=temp;
            temp = food_y%13;
            food_y-=temp;

            if(food_x < 25 || food_x > maxx -25 || food_y < 25 || food_y > maxy - 25)
            {
                while(food_x < 25 || food_x > maxx -25 || food_y < 25 || food_y > maxy - 25)
                {
                    food_x = rand()%maxx,food_y = rand()%maxy;
                    temp = food_x%13;
                    food_x-=temp;
                    temp = food_y%13;
                    food_y-=temp;
                }
            }
        }
        if(key == "right") x = x+13;
        if(x > maxx) x =0;
        if(key == "left") x = x-13;
        if(x < 0) x = maxx-(maxx%13);
        if(key == "up") y = y-13;
        if(y > maxy) y = 0;
        if(key == "down") y = y+13;
        if(y < 0) y = maxy-(maxy%13);
        check();
        if(checkdied)
        {
            dead();
            return;
        }

        if(BONUS)
        {
            if(bonus>0)
                bonus-=10;
        }
        setcolor(BLACK);
        circle(snake_x[0],snake_y[0],8);
        setfillstyle(SOLID_FILL,BLACK);
        floodfill(snake_x[0],snake_y[0],BLACK);

        for(int _size = 1; _size < snake_size; _size++)
        {
            circle(snake_x[_size],snake_y[_size],5);
            setfillstyle(SOLID_FILL,BLACK);
            floodfill(snake_x[_size],snake_y[_size],BLACK);
        }

    }
}
void check()
{
    freopen("GameData.dat","w",stdout);
    if(highscore < score)
        cout << score << endl;
    else cout << highscore << endl;
    int maxx=getmaxx(),maxy=getmaxy();
    for(int i = 1; i < snake_size; i++)
    {
        if((snake_x[0] == snake_x[i] && snake_y[0] == snake_y[i]) || (snake_x[0] <= 15 || snake_y[0] <= 15|| snake_x[0] >= maxx-10 || snake_y[0] >= maxy-60))
        {
            delay(1000);
            setcolor(WHITE);
            for(int i = 0; i < snake_size; i++)
            {
                circle(snake_x[i],snake_y[i],5);
                setfillstyle(SOLID_FILL,RED);
                floodfill(snake_x[i],snake_y[i],WHITE);
            }
            settextstyle(2,0,20);
            setcolor(WHITE);
            outtextxy(160,180,"GAME OVER!");
            setcolor(3);
            settextstyle(1,0,3);
            outtextxy(200,380,"Press any key to continue.");
            while(1)
            {
                if(kbhit())
                {
                    char ch = getch();
                    if(ch == 13)
                    {
                        clearviewport();
                        checkdied = true;
                        return;
                    }
                }
            }
        }
    }
}
void dead()
{
    checkdied = false;
    snake_size = 3;
    score = 0;
//    clearviewport();
}
void level()
{
    char ch;
    char ara[100];
    while(true)
    {

        int i = abs(spd/10.-10);
        sprintf(ara,"SELECT LEVEL : %d",i);
        setcolor(WHITE);
        outtextxy(180,350,ara);

        if(kbhit())
        {
            ch = getch();
            if(ch == 80)
            {
                spd-=10;
                if(spd < 0) spd = 100;
            }
            else if(ch == 72)
            {
                spd+=10;
                if(spd > 100) spd = 0;
            }
            else if(ch == 13)
                break;
            sprintf(ara,"SELECT LEVEL : %d",i);
            setcolor(BLACK);
            outtextxy(180,350,ara);
        }
    }

    clearviewport();
}
void high()
{
    freopen("GameData.dat","r",stdin);
    cin >> highscore;
    char ara[100];
    sprintf(ara,"Highscore: %d",highscore);
    setcolor(WHITE);
    outtextxy(200,350,ara);
    char ch = getch();
    clearviewport();
}
