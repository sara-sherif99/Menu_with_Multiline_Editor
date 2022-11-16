#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define HOME 71
#define END 79
#define ENTER 13
#define ESC 27
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define BACK 8
#define DELETE 83
#define TAB 9
#define NumSt 48
#define NumEnd 57
#define SmallSt 97
#define SmallEnd 122
#define CapSt 1
#define CapEnd 26

struct Employee
{
    int id;
    char name[20];
    int age;
    float salary;
    float commission;
    float deduction;
};

void gotoxy( int column, int line )
{
    COORD coord;
    coord.X = column;
    coord.Y = line;
    SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ),coord);
}
void textattr(int i)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), i);

}

struct Employee *empPtr;
int size;
char **ptrArr;
char* ptr[6][3];
int pos[6][3];

char* LineEditor(int size)
{

    ptrArr=(char**)malloc(6* sizeof(char*));
    for (int i=0; i<6; i++)
    {
        ptrArr[i]=malloc(size * sizeof(char));
    }
    for (int i=0; i<6; i++)
    {
        for(int j=0; j<3; j++)
        {
            ptr[i][j]=&ptrArr[i][0];
        }
    }
    for (int i=0; i<6; i++)
    {
        for(int j=0; j<3; j++)
        {
            pos[i][j]=30;
        }
    }
    int flag=0;
    char ch;
    int index=0;
    int stKey,endKey;

    gotoxy(pos[index][0],10);
    do
    {

        if (index==1)
        {
            stKey=SmallSt;
            endKey=SmallEnd;
        }
        else
        {
            stKey=NumSt;
            endKey=NumEnd;
        }
        gotoxy(pos[index][1],index);
        ch=getch();
        switch (ch)
        {
        case -32:
            ch=getch();
            switch (ch)
            {
            case LEFT:
                if (pos[index][1]>pos[index][0])
                {
                    ptr[index][1]--;
                    pos[index][1]--;
                }
                break;
            case RIGHT:
                if (pos[index][2]>pos[index][1])
                {
                    ptr[index][1]++;
                    pos[index][1]++;
                }
                break;
            case UP:
                index--;
                if (index<0)
                {
                    index=5;
                }
                if(ptr[index][0]==ptr[index][2])
                {
                    pos[index][1]=pos[index][0];
                }
                else
                {
                    pos[index][1]=pos[index+1][1];
                }
                break;
            case DOWN:
                index++;
                if (index>5)
                {
                    index=0;
                }
                if(ptr[index][0]==ptr[index][2])
                {
                    pos[index][1]=pos[index][0];
                }
                else
                {
                    pos[index][1]=pos[index-1][1];
                }
                break;
            case HOME:
                ptr[index][1]=ptr[index][0];
                pos[index][1] = pos[index][0];
                break;
            case END:
                ptr[index][1]=ptr[index][2];
                pos[index][1] = pos[index][2];
                break;
            case DELETE:
                if (pos[index][1]<pos[index][2])
                {
                    int n=0;
                    for (char* p=ptr[index][1]+2; p<ptr[index][2]; p++)
                    {
                        *(p-1)=*p;
                        gotoxy(pos[index][1]+1+n, index);
                        printf("%c",*(p-1));
                        n++;
                    }
                    gotoxy(pos[index][1]+1+n, index);
                    printf(" ");
                    ptr[index][2]--;
                    pos[index][2]--;
                }
                break;
            }
            break;
        case ESC:
        case ENTER:
            for (int i=0; i<6; i++)
            {
                *ptr[i][2]='\0';
            }
            flag=1;
            break;
        case BACK:
            if (pos[index][1]>pos[index][0])
            {
                pos[index][1]--;
                char* p=ptr[index][1];
                int n=0;
                for (p=ptr[index][1]; p<ptr[index][2]; p++)
                {
                    *(p-1)=*p;
                    gotoxy(pos[index][1]+n, index);
                    printf("%c",*(p-1));
                    n++;
                }
                gotoxy(pos[index][1]+n, index);
                printf(" ");
                ptr[index][1]--;
                ptr[index][2]--;
                pos[index][2]--;
            }
            break;
        default:
            if (isprint(ch)&& ch>=stKey && ch<=endKey)
            {
                if(pos[index][1]<pos[index][0]+size-1)
                {
                    if(pos[index][1]==pos[index][2])
                    {
                        *ptr[index][1]=ch;
                        printf("%c",*ptr[index][1]);
                        ptr[index][1]++;
                        ptr[index][2]++;
                        pos[index][1]++;
                        pos[index][2]++;

                    }
                    else
                    {
                        *ptr[index][1]=ch;
                        printf("%c",*ptr[index][1]);
                        ptr[index][1]++;
                        pos[index][1]++;
                    }
                }
            }
            break;
        }

    }
    while (flag != 1);

    return ptrArr;
}

void InsertEmpolyee(int i)
{
    system("cls");
    gotoxy(0,0);
    printf("Enter Employee id: \n");
    gotoxy(0,1);
    printf("Enter Employee Name: \n");
    gotoxy(0,2);
    printf("Enter Employee age: \n");
    gotoxy(0,3);
    printf("Enter Employee salary: \n");
    gotoxy(0,4);
    printf("Enter Employee commission: \n");
    gotoxy(0,5);
    printf("Enter Employee deduction: \n");

    char** arr=LineEditor(20);
    empPtr[i].id=atoi(arr[0]);
    strcpy(empPtr[i].name,arr[1]);
    empPtr[i].age=atoi(arr[2]);
    empPtr[i].salary=atof(arr[3]);
    empPtr[i].commission=atof(arr[4]);
    empPtr[i].deduction=atof(arr[5]);

}
void DisplayAll()
{
    int x=0;
    for (int i=0; i< size; i++)
    {
        if(empPtr[i].id != -1)
        {
            gotoxy(2,x*8);
            printf("Employee at index %i",i);
            gotoxy(2,x*8+1);
            printf("id: %i\n",empPtr[i].id);
            gotoxy(40,x*8+1);
            printf("name: %s\n",empPtr[i].name);
            gotoxy(2,x*8+2);
            printf("age: %i\n",empPtr[i].age);
            gotoxy(40,x*8+2);
            printf("salary: %f \n",empPtr[i].salary);
            gotoxy(2,x*8+3);
            printf("commission: %f\n",empPtr[i].commission);
            gotoxy(40,x*8+3);
            printf("deduction: %f\n",empPtr[i].deduction);
            gotoxy(20,x*8+4);
            printf("Net Salary: %f\n",(empPtr[i].salary)+(empPtr[i].commission)-(empPtr[i].deduction));
            printf("-------------------------------------------------------------\n");
            x++;
        }

    }

}
void DisplayByIndex(int index, int x)
{
    gotoxy(2,2+x*10);
    printf("Employee at index %i",index);
    gotoxy(2,4+x*10);
    printf("id: %i\n",empPtr[index].id);
    gotoxy(40,4+x*10);
    printf("name: %s\n",empPtr[index].name);
    gotoxy(2,6+x*10);
    printf("age: %i\n",empPtr[index].age);
    gotoxy(40,6+x*10);
    printf("salary: %f \n",empPtr[index].salary);
    gotoxy(2,8+x*10);
    printf("commission: %f\n",empPtr[index].commission);
    gotoxy(40,8+x*10);
    printf("deduction: %f\n",empPtr[index].deduction);
    gotoxy(2,10+x*10);
    printf("Net Salary: %f\n",(empPtr[index].salary)+(empPtr[index].commission)-(empPtr[index].deduction));
    printf("\n");
    printf("\n");
}


int main()
{
    char menu[8][20]= {"New","DisplayAll","DisplayByID","DisplayByName","DeleteAll","DeleteByID","DeleteByName","Exit"};
    int cursor=0;
    char ch;
    char n[20];
    int flg=0;
    int input;
    printf("Enter Number of Employees\n");
    scanf("%i",&input);
    _flushall();
    size=input-1;
    empPtr=malloc(size  *  sizeof(struct Employee));
    for (int i=0; i<size; i++)
    {
        empPtr[i].id=-1;
    }

    do
    {
        int flagID=0;
        int flagName=0;
        int index=0;
        int cid;
        system("cls");
        for(int i=0; i<8; i++)
        {
            if(i==cursor)
            {
                textattr(5);
            }
            else
            {
                textattr(7);
            }
            gotoxy(10,8+i*2);
            _cprintf("%s",menu[i]);
        }
        ch=getch();
        switch (ch)
        {
        case -32:
            ch=getch();
            switch(ch)
            {
            case UP:
                cursor-=1;
                if (cursor<0)
                {
                    cursor=7;
                }
                break;
            case DOWN:
                cursor++;
                if (cursor==8)
                {
                    cursor=0;
                }
                break;
            case HOME:
                cursor=0;
                break;
            case END:
                cursor=8;
                break;
            }
            break;
        case ESC:
            flg=1;
            break;
        case TAB:
            cursor++;
            if (cursor==8)
            {
                cursor=0;
            }
            break;
        case ENTER:
            switch(cursor)
            {
            case 0:
                system("cls");
                do
                {
                    printf("Choose index from 0 to %i: ",size);
                    scanf("%i",&index);
                    _flushall();
                }
                while(index<0 || index>size);
                InsertEmpolyee(index);
                break;
            case 1:
                system("cls");
                DisplayAll();
                getch();
                break;
            case 2:
                system("cls");
                do
                {
                    printf("Choose ID >0 : ");
                    scanf("%i",&cid);
                    _flushall();
                }
                while(cid<0);
                int x =0;
                for (int i=0; i<size; i++)
                {
                    if (empPtr[i].id==cid)
                    {
                        flagID=1;
                        DisplayByIndex(i,x);
                        x++;
                    }

                }
                if (flagID==0)
                {
                    printf("No Employee with this ID");
                }
                getch();
                break;
            case 3:
                system("cls");
                printf("Choose Name: ");
                gets(n);
                _flushall();
                int y =0;
                for (int i=0; i<size; i++)
                {
                    if (!strcmp(empPtr[i].name,n))
                    {
                        flagName=1;
                        DisplayByIndex(i,y);
                        y++;
                    }
                }
                if (flagName==0)
                {
                    printf("No Employee with this Name");
                }
                getch();
                break;
            case 4:
                system("cls");
                printf("Delete All Records? Press y for yes and n for no\n");
                switch (getch())
                {
                case 'y':
                    for (int i=0; i<size; i++)
                    {
                        empPtr[i].id=-1;
                    }
                    break;
                default:
                    break;
                }

                break;
            case 5:
                system("cls");
                do
                {
                    printf("Choose ID >0 : ");
                    scanf("%i",&cid);
                    _flushall();
                }
                while(cid<0);
                for (int i=0; i<size; i++)
                {
                    if (empPtr[i].id==cid)
                    {
                        flagID=1;
                        empPtr[i].id=-1;
                    }

                }
                if (flagID==0)
                {
                    printf("No Employee with this ID");
                }
                getch();
                break;
            case 6:
                system("cls");
                printf("Choose Name: ");
                gets(n);
                _flushall();
                int z =0;
                for (int i=0; i<size; i++)
                {
                    if (!strcmp(empPtr[i].name,n))
                    {
                        flagName=1;
                        DisplayByIndex(i,y);
                        z++;
                    }
                }
                if (flagName != 0)
                {
                    printf("Which employee you want to delete? enter index\n");
                    scanf("%i",&index);
                    _flushall();
                    empPtr[index].id=-1;
                }

                else if (flagName==0)
                {
                    printf("No Employee with this Name");
                }
                getch();
                break;
            case 7:
                flg=1;
                break;
            }

        }
    }
    while(flg != 1);
    free(empPtr);
    return 0;
}
