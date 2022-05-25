#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

void line();
void swap(char x[], char y[], int z);
void swap1(char x[],char y[]);
void name(char x[]);
void check(char x[], char y[], int z);

int main(){

    FILE *day; //file name
    int q=0; //while loop integer, day
    int i=0; //for loop integer
    int operation; //chosen operation(1/2/3)
    char description[39]=""; //description of the event
    char begin[6]=""; //hour of beginning
    char end[6]=""; //hour of ending
    int add; //number of events already entered
    char buffer[10][58]; //buffers for file strings
    char g; //used to allow "press any key to..."
    int del; //which string user wants to delete
    char choose; //changes the q or chooses the operation
    char help[100];
    char time[5]={'T','i','m','e'};
    char monday[8]={'M','o','n','d','a','y'};
    char tuesday[9]={'T','u','e','s','d','a','y'};
    char wednesday[11]={'W','e','d','n','e','s','d','a','y'};
    char thursday[10]={'T','h','u','r','s','d','a','y'};
    char friday[8]={'F','r','i','d','a','y'};
    char saturday[10]={'S','a','t','u','r','d','a','y'};
    char sunday[8]={'S','u','n','d','a','y'};

    while(q==0 || q==1 || q==2 || q==3 || q==4 || q==5 || q==6){

//---------------------------------------------------------------------------------------------------------------------------------------------------

        if(q==0){  //open file
            day=fopen("monday.txt", "r");
        }
        else if(q==1){
            day=fopen("tuesday.txt", "r");
        }
        else if(q==2){
            day=fopen("wednesday.txt", "r");
        }
        else if(q==3){
            day=fopen("thursday.txt", "r");
        }
        else if(q==4){
            day=fopen("friday.txt", "r");
        }
        else if(q==5){
            day=fopen("saturday.txt", "r");
        }
        else if(q==6){
            day=fopen("sunday.txt", "r");
        }
        for(i=0;i<10;i++){ //copying strings from file to buffers
            fgets(buffer[i], sizeof(buffer[i]), day);
        }
        fclose(day);

//---------------------------------------------------------------------------------------------------------------------------------------------------

        if(day==NULL){ //creating text files if they don't exists already
            for(i=0;i<10;i++){
                for(int j=0;j<57;j++){
                    buffer[i][j]=' ';
                }
                buffer[i][0]=buffer[i][14]=buffer[i][55]='|';
                buffer[i][56]='\n';
                buffer[i][57]='\0';
            }
            swap(buffer[0], time, 2);
            if(q==0){
                swap(buffer[0], monday, 16);
            }
            else if(q==1){
                swap(buffer[0], tuesday, 16);
            }
            else if(q==2){
                swap(buffer[0], wednesday, 16);
            }
            else if(q==3){
                swap(buffer[0], thursday, 16);
            }
            else if(q==4){
                swap(buffer[0], friday, 16);
            }
            else if(q==5){
                swap(buffer[0], saturday, 16);
            }
            else if(q==6){
                swap(buffer[0], sunday, 16);
            }
        }

//---------------------------------------------------------------------------------------------------------------------------------------------------

        add=0;
        for(i=1;i<9;i++){ //checking how many events has been already added
            if(buffer[i][2]!=' ' && buffer[i][8]!=' ' && buffer[i][16]!=' '){
                add++;
            }
        }

//---------------------------------------------------------------------------------------------------------------------------------------------------

        if(operation==1){
            system("cls");
            operation=0;
            if(add>=8){
                printf("\nLimit of events reached\nPress any key to continue\n");
                g=_getch();
                system("cls");
            }
            else{
                printf("\nEnter the description of the event:\n");
                scanf(" %38[^\n]s", &description);
                check(description, help, 37);
                printf("\nEnter time of begining:\n");
                scanf(" %5[^\n]s", &begin);
                check(begin, help, 4);
                printf("\nEnter time of ending:\n");
                scanf(" %5[^\n]s", &end);
                check(end, help, 4);
                swap(buffer[add+1], begin, 2);
                swap(buffer[add+1], end, 8);
                swap(buffer[add+1], description, 16);
                buffer[add+1][7]='-';
                add++;
                system("cls");
            }
        }

        else if(operation==2){
            system("cls");
            operation=0;
            if(add==0){
                system("cls");
                printf("\nThere is no events to delete\nPress any key to continue\n");
                g=_getch();
                system("cls");
            }
            else{
                printf("\nChoose with event you want to delete:\n");
                for(i=1;i<add+1;i++){
                    printf("(%d) ", i);
                    name(buffer[i]);
                }
                scanf("%d", &del);
                if(del<=0 || del>add){
                    system("cls");
                    printf("Wrong number\nPress any key to continue\n");
                    g=_getch();
                    system("cls");
                }
                else{
                    system("cls");
                    for(i=del;i<9;i++){
                        for(int j=0;j<58;j++){
                            buffer[i][j]=buffer[i+1][j];
                        }
                    }
                    add=add-1;
                }
            }

        }

        else if(operation==3){
            system("cls");
            return 0;
        }

//---------------------------------------------------------------------------------------------------------------------------------------------------

       for(i=1;i<10;i++){  //time should be like 01.23, this converts 1 into 01.00, 12 into 12.00, 1.23 into 01.23
            if(buffer[i][2]!=' ' && buffer[i][3]!=' ' && buffer[i][4]!=' ' && buffer[i][5]!=' ' && buffer[i][6]==' '){
                for(int j=6;j>1;j--){
                    buffer[i][j]=buffer[i][j-1];
                }
                buffer[i][2]='0';
            }
            else if(buffer[i][2]!=' ' && buffer[i][3]!=' ' && buffer[i][4]==' ' && buffer[i][5]==' ' && buffer[i][6]==' '){
                buffer[i][4]='.';
                buffer[i][5]=buffer[i][6]='0';
            }
            else if(buffer[i][2]!=' ' && buffer[i][3]==' ' && buffer[i][4]==' ' && buffer[i][5]==' ' && buffer[i][6]==' '){
                buffer[i][3]=buffer[i][2];
                buffer[i][2]=buffer[i][5]=buffer[i][6]='0';
                buffer[i][4]='.';
            }

            if(buffer[i][8]!=' ' && buffer[i][9]!=' ' && buffer[i][10]!=' ' && buffer[i][11]!=' ' && buffer[i][12]==' '){
                for(int j=12;j>7;j--){
                    buffer[i][j]=buffer[i][j-1];
                }
                buffer[i][8]='0';
            }
            else if(buffer[i][8]!=' ' && buffer[i][9]!=' ' && buffer[i][10]==' ' && buffer[i][11]==' ' && buffer[i][12]==' '){
                buffer[i][10]='.';
                buffer[i][11]=buffer[i][12]='0';
            }
            else if(buffer[i][8]!=' ' && buffer[i][9]==' ' && buffer[i][10]==' ' && buffer[i][11]==' ' && buffer[i][12]==' '){
                buffer[i][9]=buffer[i][8];
                buffer[i][8]=buffer[i][11]=buffer[i][12]='0';
                buffer[i][10]='.';
            }
        }

//---------------------------------------------------------------------------------------------------------------------------------------------------

        for(i=0;i<10;i++){ //sorting events according to time
            for(int j=0;j<10;j++){
                if(j!=0 && buffer[j][2]!=' ' && buffer[j+1][2]!=' ' && buffer[j][2]>buffer[j+1][2]){
                    swap1(buffer[j],buffer[j+1]);
                }
                else if(j!=0 && buffer[j][2]!=' ' && buffer[j+1][2]!=' ' && buffer[j][2]==buffer[j+1][2]){
                    if(j!=0 && buffer[j][3]!=' ' && buffer[j+1][3]!=' ' && buffer[j][3]>buffer[j+1][3]){
                        swap1(buffer[j],buffer[j+1]);
                    }
                    else if(j!=0 && buffer[j][3]!=' ' && buffer[j+1][3]!=' ' && buffer[j][3]==buffer[j+1][3]){
                        if(j!=0 && buffer[j][5]!=' ' && buffer[j+1][5]!=' ' && buffer[j][5]>buffer[j+1][5]){
                            swap1(buffer[j],buffer[j+1]);
                        }
                        else if(j!=0 && buffer[j][5]!=' ' && buffer[j+1][5]!=' ' && buffer[j][5]==buffer[j+1][5]){
                            if(j!=0 && buffer[j][6]!=' ' && buffer[j+1][6]!=' ' && buffer[j][6]>buffer[j+1][6]){
                                swap1(buffer[j],buffer[j+1]);
                            }
                        }
                    }
                }
            }
        }

//---------------------------------------------------------------------------------------------------------------------------------------------------

        if(q==0){
            day=fopen("monday.txt", "w");
        }
        else if(q==1){
            day=fopen("tuesday.txt", "w");
        }
        else if(q==2){
            day=fopen("wednesday.txt", "w");
        }
        else if(q==3){
            day=fopen("thursday.txt", "w");
        }
        else if(q==4){
            day=fopen("friday.txt", "w");
        }
        else if(q==5){
            day=fopen("saturday.txt", "w");
        }
        else if(q==6){
            day=fopen("sunday.txt", "w");
        }
        for(i=0;i<10;i++){  //printing new strings into the file
            fprintf(day, "%s", buffer[i]);
        }
        fclose(day);

//---------------------------------------------------------------------------------------------------------------------------------------------------

        printf("\n\tChoose the operation:\n\t*(1) Add a new event\n\t*(2) Delete an event\n\t*(3) Close the program\n\t*(<) Previous day\n\t*(>) Next day\n");
        printf("\n");
        line();
        printf("\n\t%s", buffer[0]);
        line();
        for(i=1;i<add+1;i++){
            printf("\n\t%s", buffer[i]);
            line();
        }
        printf("\n");

//---------------------------------------------------------------------------------------------------------------------------------------------------

        choose=_getch(); //choose the operation you want to make
        if(choose==','){
            if(q>=1){
                q=q-1;
            }
            else if(q==0){
                q=6;
            }
        }
        else if(choose=='.'){
            if(q<=5){
                q=q+1;
            }
            else if(q==6){
                q=0;
            }
        }
        else if(choose=='1'){
            operation=1;
        }
        else if(choose=='2'){
            operation=2;
        }
        else if(choose=='3'){
            operation=3;
        }
        else{
            system("cls");
            printf("\nThere is no operation like this\nPress any key to continue\n");
            g=_getch();
        }
        system("cls");
    }
}

//---------------------------------------------------------------------------------------------------------------------------------------------------

void line()
{
    printf("\t+");
    for(int i=0;i<13;i++){
        printf("-");
    }
    printf("+");
    for(int i=0;i<40;i++){
        printf("-");
    }
    printf("+");
}

void swap(char x[], char y[], int z)
{
    for(int i=0;i<y[i]!='\0';i++){
        x[i+z]=y[i];
    }
}

void swap1(char x[],char y[])
{
    char change[58];
    for(int i=0;i<58;i++){
        change[i]=x[i];
        x[i]=y[i];
        y[i]=change[i];
    }
}

void name(char x[])
{
    for(int i=16;i<55;i++){
        printf("%c", x[i]);
    }
    printf("\n");
}

void check(char x[], char y[], int z)
{
    int i=0;
    while(x[i]!='\0'){
        i++;
    }
    if(i>z){
        scanf("%[^\n]s", &y);
    }
}
