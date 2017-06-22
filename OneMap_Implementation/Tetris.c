#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <math.h>

#define FILENAME "Tetris"
#define WIDTHS 10
#define HEIGHTS 13

typedef struct
{
    int x[4];
    int y[4];
}SHAPE;

//char GameMap[HEIGHTS+1][WIDTHS+1]; //[HEIGHT][WIDTHS]
char ObjMap[HEIGHTS+1][WIDTHS+1];
//const int HEIGHTS=14, WIDTHS=15;//Heights=y-1,Widths=x-1
const char CharShape='#';
const char CharMap=' ';
int NextType;
int score;
int NoMove=0;
SHAPE object;
SHAPE NextObj;
void welcome();
void PrintMap();
void CreatObj(SHAPE*, int,int,int);
void rotateObj(char );
void moveObj(char);
void InitializeMap();
int CheckMap();


void main()
{
    int i;
    char inputkey;
    InitializeMap();
    welcome();
    srand(time(0));
    NextType=rand()%7;
    CreatObj(&object,NextType,WIDTHS/2,HEIGHTS+1);
    NextType=rand()%7;
    PrintMap();
    while (1)
    {
        while (kbhit())
        {
            inputkey=getch();
            if (inputkey==' '|| inputkey==13)
                inputkey=getch();
            if (inputkey=='g')
                NextType=1;
            else if (inputkey=='f')
                NextType=4;
            else if (inputkey=='h')
                NextType=0;
            if (inputkey=='1' || inputkey=='3' || inputkey=='z' || inputkey=='x' || inputkey==77 || inputkey==75 || inputkey==80 || inputkey==72 || inputkey=='6' || inputkey=='4' || inputkey=='8' || inputkey=='2' || inputkey=='d' || inputkey=='a' || inputkey=='w' || inputkey=='s')
            {
                moveObj(inputkey);
                rotateObj(inputkey);
                PrintMap();
            }
            //break;
        }
        CreatObj(&NextObj,NextType,1,0);
        moveObj('s');//move down
        PrintMap();
        if (NoMove)
        {
        for (i=0;i<=3;i++)
            if (object.y[i]<=HEIGHTS+1&&object.x[i]<=WIDTHS)
                {ObjMap[object.y[i]][object.x[i]]=CharShape;}
        CreatObj(&object,NextType,WIDTHS/2,HEIGHTS+2);
        //CreatObj(&NextObj,NextType,1,0);
        NextType=rand()%7;

        PrintMap();
        }

        if (CheckMap())
            break;
        inputkey=' ';
        _sleep(300);
    }
    printf("\nYou Lost!\n>>Press ESC to exit...");
    while(getch()!=27);//hit esc to exit
    return;
}

void CreatObj(SHAPE* thing,int type, int xRef, int yRef)
{
    //type=1;
    switch (type)
    {
        case 0:
        // 1
        //2R3
            *thing=(SHAPE){{xRef,xRef,xRef-1,xRef+1},{yRef,yRef+1,yRef,yRef}};
            break;
        case 1:
        //1R23
            *thing=(SHAPE){{xRef,xRef-1,xRef+1,xRef+2},{yRef,yRef,yRef,yRef}};
            break;
        case 2:
        //12
        // R3
            *thing=(SHAPE){{xRef,xRef-1,xRef,xRef+1},{yRef,yRef+1,yRef+1,yRef}};
            break;
        case 3:
        // 12
        //3R
            *thing=(SHAPE){{xRef,xRef,xRef+1,xRef-1},{yRef,yRef+1,yRef+1,yRef}};
            break;
        case 4:
        //12
        //R3
            *thing=(SHAPE){{xRef,xRef,xRef+1,xRef+1},{yRef,yRef+1,yRef+1,yRef}};
            break;
        case 5:
        //1
        //2R3
            *thing=(SHAPE){{xRef,xRef-1,xRef-1,xRef+1},{yRef,yRef+1,yRef,yRef}};
            break;
        case 6:
        //  1
        //2R3
            *thing=(SHAPE){{xRef,xRef+1,xRef-1,xRef+1},{yRef,yRef+1,yRef,yRef}};
            break;
    }
    if (thing==&object){moveObj('s');}
    return;
}

void rotateObj(char direction)
{
    int i;
    int xdif, ydif;
    int iRef=0;
    int CenX=object.x[0];
    int CenY=object.y[0];
    switch (direction)
    {
    case 'z': case '1'://Anticlockwise
        if (object.x[0]==0)
            CenX++;
        if (object.x[0]==WIDTHS)
            CenX--;
        for (i=0;i<=3;i++)
        {
            ydif = object.y[i]-CenY;
            xdif = object.x[i]-CenX;
            if (ObjMap[CenY + xdif][CenX - ydif]=='#' || CenY + xdif<0)
                return;
        }
        for (i=0;i<=3;i++)
        {
            ydif = object.y[i]-CenY;
            xdif = object.x[i]-CenX;
            object.x[i]=CenX - ydif;
            object.y[i]=CenY + xdif;
        }
        break;

    case 'x': case '3'://Clockwise
        if (object.x[0]==WIDTHS)
            CenX--;
        if (object.x[0]==0)
            CenX++;
        for (i=0;i<=3;i++)
        {
            ydif = object.y[i]-CenY;
            xdif = object.x[i]-CenX;
            if (ObjMap[CenY - xdif][CenX + ydif]=='#' || CenY - xdif<0)
                return;
        }
        for (i=0;i<=3;i++)
        {
            ydif = object.y[i]-CenY;
            xdif = object.x[i]-CenX;
            object.x[i]=CenX + ydif;
            object.y[i]=CenY - xdif;
        }
        break;
    }
    return;
}

void moveObj(char direction)
{
    int i;
    NoMove=0;

    for (i=0;i<=3;i++)
    {
        if (object.y[i]<=HEIGHTS&&object.x[i]<=WIDTHS)
            ObjMap[object.y[i]][object.x[i]]=CharMap;
    }
    switch(direction)
    {
        case 77: case '6': case'd'://right
            for (i=0;i<=3;i++)
            {
                if (ObjMap[object.y[i]][object.x[i]+1]==CharShape || object.x[i]>=WIDTHS)
                return;
            }
            for (i=0;i<=3;i++)
            {
                /*if (object.y[i]<=HEIGHTS&&object.x[i]<=WIDTHS)
                    ObjMap[object.y[i]][object.x[i]]=CharMap;*/
                object.x[i]+=1;
            }
            break;
        case 75: case '4': case'a'://left
            for (i=0;i<=3;i++)
            {
                if (ObjMap[object.y[i]][object.x[i]-1]==CharShape || object.x[i]<=0)
                return;
            }
            for (i=0;i<=3;i++)
            {
                /*if (object.y[i]<=HEIGHTS&&object.x[i]<=WIDTHS)
                    ObjMap[object.y[i]][object.x[i]]=CharMap;*/
                object.x[i]-=1;
            }
            break;
        case 80: case '2': case's'://down
            for (i=0;i<=3;i++)
            {
                if (ObjMap[object.y[i]-1][object.x[i]]==CharShape || object.y[i]==0)
                {
                    //exitcode=1;
                    NoMove=1;
                    return;
                }
            }
            /*if (NoMove)
            {
                for (i=0;i<=3;i++)
                    if (object.y[i]<=HEIGHTS&&object.x[i]<=WIDTHS)
                        {ObjMap[object.y[i]][object.x[i]]=CharShape;}
                CreatObj(&object,NextType,WIDTHS/2,HEIGHTS+2);
                NextType=rand()%7;
                PrintMap();
                return;
            }*/
            for (i=0;i<=3;i++)
            {
                /*if (object.y[i]<=HEIGHTS&&object.x[i]<=WIDTHS)
                    ObjMap[object.y[i]][object.x[i]]=CharMap;*/
                object.y[i]-=1;
            }
            break;
    }
    NoMove=0;
    return;
}

void InitializeMap()
{
    int i,j;
    /**Reset Map arrays*/
    for (j = HEIGHTS;j>=0;j--)
    {
        for (i=0;i<=WIDTHS;i++ )
        {
            //GameMap[j][i]=CharMap;
            ObjMap[j][i]=CharMap;
        }
    }

}

void PrintMap()
{
    system("cls");
    int i,j;
    /*
    //Reset the GameMap array
    for (j = HEIGHTS;j>=0;j--)
    {
        for (i=0;i<=WIDTHS;i++ )
        {
            GameMap[j][i]=ObjMap[j][i];
        }
    }
    */
     /**Insert the Object*/
    for (i=0;i<=3;i++)
    {
        if (object.y[i]<=HEIGHTS&&object.x[i]<=WIDTHS)
        ObjMap[object.y[i]][object.x[i]]=CharShape;
    }

    /**Print map*/
    for (j = HEIGHTS;j>=0;j--)
    {
        printf("|");
        //printf("%c",j+'0');
        for (i=0;i<=WIDTHS;i++)
        {
            printf("%c",ObjMap[j][i]);
        }
        printf("|\n");
    }

    /**print lower border*/
    for (i=0;i<=WIDTHS+2;i++ )
    {
         printf("-");
    }
    printf("\n\nYour Score is: %d\n\n",score);
    printf("Next shape:\n");
    //CreatObj(&NextObj,NextType,1,0);

    /**Print NextObj*/
    int ObjCtr,ifoutput;
    for (j=1;j>=0;j--)
    {
        printf(">>\t");
        for (i=0;i<=3;i++)
        {
            ifoutput=0;
            for (ObjCtr=0;ObjCtr<=3;ObjCtr++)
            {
                if (i==NextObj.x[ObjCtr] && j==NextObj.y[ObjCtr])
                {
                    printf("%c", CharShape);
                    ifoutput=1;
                }
            }
            if (!ifoutput)
                printf(" ");
        }
        printf("\n");
    }
    return;
}

int CheckMap()
{
    int i,j;
    int ctr;
    static int ctrIfMoved=0;
    int move_j;
    for (j=HEIGHTS;j>=0;j--)
    {
        ctr=0;
        for (i=0;i<=WIDTHS;i++)
        {
            if (ObjMap[j][i]==CharShape)
                ctr++;
        }
        if (ctr==WIDTHS+1)
        {
            //system("pause");
            score++;
            for (move_j=j;move_j<=HEIGHTS-1;move_j++)
            {
                for (i=0;i<=WIDTHS;i++)
                {
                    ObjMap[move_j][i]=CharMap;
                    ObjMap[move_j][i]=ObjMap[move_j+1][i];
                }
            }
        }
    }
    if (NoMove)
    {
        for (i=0;i<=WIDTHS;i++)
            if (ObjMap[HEIGHTS][i]==CharMap)
            return 1;
    }
    return 0;
}

void welcome()
{
    char titlename[100];
    sprintf(titlename,"title %s",FILENAME);
    system(titlename);

    printf("\n\tWelcome to %s\n\n",FILENAME);
    printf("\n====================>>Game Manual<<====================\n\n");
    printf(">>\tPress a or 4: move to the left\t\t<<\n");
    printf(">>\tPress d or 6: move to the right\t\t<<\n");
    printf(">>\tPress z or 1: rotate anticlockwise\t<<\n");
    printf(">>\tPress x or 3: rotate clockwise\t\t<<\n");
    printf(">>\tPress s or 2: move downward\t\t<<\n");
    printf(">>\tPress space or enter to pause\t\t<<\n");
    printf("\nPress any key to start the game...");
    getch();
}
