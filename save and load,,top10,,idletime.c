//part of **save and load** **top10** **time of idle cpu time**
#include <stdbool.h>
#include <time.h>
#include <windows.h>
#include<math.h>
#include <dirent.h>
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"

FILE *fs;
FILE *p_r;
FILE *fptr;
FILE *fptr2;

int  score1=0 , score2=0 ;
int undo=0;
int case_input=0;
char rank_direct[100]="D:\\save.txt";
char name1[100] ,name2[100];
int load=0;
int compu;
clock_t t1;
clock_t t2;
int player1=0,player2=0;
char go[40][40][40];
int step=0;
char op='0';
int cheak_go[100][1000];
int turns[1000];
int save_score1[1000];
int save_score2[1000];

void save(){
                --step;
            fclose(fs);
            char g[1000]="./dotsandboxs/";
            int n=strlen(g);
            for(int i=n; i<strlen(name1)+n; ++i)
                g[i]=name1[i-n];
            n=strlen(g);
            for(int i=n; i<strlen(name2)+n; ++i)
                g[i]=name2[i-n];
            g[strlen(g)]='.';g[strlen(g)]='t';g[strlen(g)]='x';g[strlen(g)]='t';

            char c;
            fs=fopen("./private/test.txt","r");
            fptr2=fopen(g,"w+");
            c = fgetc(fs);
            while (c != EOF)
            {
                fputc(c, fptr2);
                c = fgetc(fs);
            }
            fclose(fptr2);
            fs = fopen("./private/test.txt","a+");


    }

/*************************************************/


void load(){
	    system("cls");
	    load=1;
        struct dirent *de;
        DIR *dr = opendir("./dotsandboxs");
        if (dr == NULL){
            printf("Could not open current directory" );
            return 0;
        }
        char direct [1000][1000];
        int i=0;
        while ((de = readdir(dr)) != NULL){
                strcpy(direct[i],de->d_name);
                ++i;
        }
        for(int j=2;j<i;++j){
            printf("%d- %s\n",j-1,direct[j]);
        }
        printf(CYAN"Choose a play to load from(1-%d) : "RESET,i-2);
        closedir(dr);
        int file;
        char term;int temp;
        while(1){
            while(scanf("%d%c", &file, &term) != 2 || term != '\n'){
                while((temp=getchar()) != EOF && temp != '\n');
                    printf(RED"ENTER A NUMBER : "RESET);
                }
                if(file>0&&file<i-1){
                    break;
                }
                else{
                    printf(RED"ENTER CORRECT FILE : "RESET);
                }
        }
        ++file;

        char file_direct [1000]="./dotsandboxs/";
        for(int g=0;g<strlen(direct[file]);++g){
            file_direct[strlen(file_direct)]=direct[file][g];
        }

        fptr = fopen(file_direct,"r");
	    if((load==1&&fscanf(fptr,"%d",&compu)==1)){
            if(compu>0&&compu<=2){
            --compu;

            }
        }
        fprintf(fs,"%d ",compu+1);
        fscanf(fptr,"%s",&name1);
        fprintf(fs,"%s ",name1);
        if(compu==0){
            fscanf(fptr,"%s",&name2);
            fprintf(fs,"%s ",name2);
        }
        else{
            name2[0]='c';name2[1]='o';name2[2]='m';name2[3]='p';name2[4]='u';name2[5]='t';name2[6]='e';name2[7]='r';
        }
}


/****************************************************/


void top10 {

        p_r=fopen(rank_direct,"r");
        int a[100] ;char b[100][100];
        i=0;
        while(fscanf(p_r, "%s %d",b[i] ,&a[i])!=-1){++i;}
        printf("\n");
        for(int j=0;j<i;++j){
            for(int k=0;k<i-j-1;++k){
                if(a[k]<a[k+1]){
                    int x = a[k];
                    a[k]=a[k+1];
                    a[k+1]=x;
                    char y[100];
                    strcpy(y,b[k]);
                    strcpy(b[k],b[k+1]);
                    strcpy(b[k+1],y);
                }
            }
        }
        system("cls");
        printf(BLUE"RANK    NAME        SCORE\n"RESET);
        for(int j=0;j<i&&j<10;++j)
            printf(CYAN "%d\t%s ---> %d\n" RESET,j+1,b[j],a[j]);
        //fclose(p_r);
        printf(GREEN"\n\nEXIT:E\t\ MAIN MENU : M \n (E or M) : "RESET) ;
        char case3 [1000];
        while(1){
            scanf("%s",case3);
             if(strlen(case3)>1){
                printf(RED"PLEASE ENTER VALID CHOICE (one char only [E OR M]) : "RESET);
             }
             else if(case3[0]=='M'||case3[0]=='m'){
                break;
             }
             else if(case3[0]=='E'||case3[0]=='e'){
                exit(0);
             }
             else{
                printf(RED"PLEASE ENTER VALID CHOICE (one char only [E OR M]) : "RESET);
             }
        }

}


/******************************************************/
void Wait(int seconds)
{

 clock_t endwait;
 endwait = clock () + seconds * CLK_TCK;
 while (clock() < endwait) {}
}
void* stopwatch(void * arg)
{
    int i;
int m=1;
i=0;
while (1==1)
{
  Wait( 1 );
	i++;


if (i%60==0){
    printf("\n %d minutes passed ",m);
    m=m+1;
}}return NULL ;
}
void* scan(void * arg){
int n;
scanf("%d",&n);}

void idletimer(){
    int n;
    pthread_t newthread ;
    pthread_t newthread2 ;
    pthread_create(&newthread, NULL , stopwatch , NULL );
    pthread_join(&newthread , NULL);
    pthread_create(&newthread2, NULL , scanf("%d",&n) , NULL );
printf("%d",n);
}
