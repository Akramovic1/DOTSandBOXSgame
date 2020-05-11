#include<stdio.h>
#include<stdlib.h>
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

void go_equal_check (int cheak[],int n,int step){
    ++n;
    n/=2;
    n=2*n*(n-1)+1;
    for(int j=0;j<n;++j){
        cheak_go[step][j]=cheak[j];
    }
}
void cheak_equal_go (int cheak[],int n,int step){
    ++n;
    n/=2;
    n=2*n*(n-1)+1;
    for(int j=0;j<n;++j){
        cheak[j]=cheak_go[step][j];
    }
}



void go_equal_arr (char arr[][1000], int n,int step){
	for(int i=0;i<n;++i){
        for(int j=0;j<n;++j){
            go[step][i][j]=arr[i][j];
        }
  }
}
void arr_equal_go (char arr[][1000], int n,int step){
	for(int i=0;i<n;++i){
        for(int j=0;j<n;++j){
            arr[i][j]=go[step][i][j];
        }
  }
}


bool formbox (char arr[][1000],int n,int *score,char c){
    bool k = 0;

    for (int i = 0 ; i < n-2 ; i+=2){
        for (int j = 1 ; j < n-1 ; j+=2){
            if (arr[i][j] != '0' && arr[i+1][j-1] != '0' && arr[i+1][j+1] != '0' && arr[i+2][j] != '0' ){
                  if (arr[i+1][j] == '0' ){
                        arr[i+1][j] = c ;
                        ++*score;
                        k = true ;
                  }

            }

        }
    }

    return k ;
}


//======================================================================================================================================================================/////


void print_grid(char arr[][1000],int n,int score1 ,int score2,int turn ,int remain){
    int counter=0;
    system("");

printf(RED "\t\t\t      DOTS AND BOXS \n\n" RESET) ;
if (turn==1)printf(CYAN "========= IT IS THE %s 'S  TURN ========\n" RESET,name1) ;
if (turn==2)printf(YELLOW "========= IT IS THE %s 'S  TURN ========\n" RESET,name2) ;
    for (int i = 0 ; i < n ; i++){
            printf("\t\t\t\t");
        for (int j = 0 ; j < n ; j++){
            if (arr[j][i]=='0'&&i%2==0&&j%2==0) printf("%c",254) ;
            else if (arr[j][i]=='1' && i%2 ==0){ printf(CYAN"%c%c%c%c" RESET ,196,196,196,196);++counter;}
            else if (arr[j][i]=='1' && i%2 !=0){ printf(CYAN"| " RESET );++counter;}
            else if (arr[j][i]=='2' && i%2 ==0){ printf(YELLOW"%c%c%c%c" RESET ,196,196,196,196);++counter;}
            else if (arr[j][i]=='2' && i%2 !=0) {printf(YELLOW"| " RESET );++counter;}
            else if (arr[j][i]=='A' ) printf(CYAN " %c " RESET,arr[j][i]) ;
            else if (arr[j][i]=='B' ) printf(YELLOW " %c " RESET,arr[j][i]);
            else if (arr[j][i]=='0'&& i%2 !=0&& j%2 !=0&&(i+j)%2==0) printf("   ") ;
            else if (arr[j][i]=='0'&&i%2 !=0) {if(counter<9){printf("%d ",++counter);}else {printf("%d",++counter);}}
            else if (arr[j][i]=='0'&& i%2 ==0) {if(counter<9){printf(" %d  ",++counter);}else {printf(" %d ",++counter);}};
        }
        printf("\n") ;
    }
    t2 = clock() - t1;
    int t = t2/CLOCKS_PER_SEC;
    printf(CYAN "\n\n%s score :%d " YELLOW "%s score :%d " GREEN "Remaining Stacks:%d " CYAN "TIME PASSED :%d minuts %d Seconds \n\n"RESET,name1,score1,name2,score2,remain,t/60,(t%60));
    printf(CYAN"Number of %s MOVES: %d "YELLOW"Number of %s MOVES: %d \n",name1,player1,name2,player2);
    printf(GREEN"Undo:U\tRedo:R\tSave:S\tExit:E\n\n"RESET);
}

//======================================================================================================================================================================/////
//======================================================================================================================================================================/////
//======================================================================================================================================================================/////


int input(char arr[][1000],int cheak[],int n,int computer,int player){
    int h,t;
    save_score1[step]=score1;
    save_score2[step]=score2;
    go_equal_arr(arr,n,step);
    go_equal_check(cheak,n,step);
    turns[step]=player;
    ++step;
    op='0';
    int input=0;
    if(computer){
        int u=1;
        while(cheak[u]==1){
            ++u;
        }
        input=u;
    }
    else{
        printf(BLUE "**ENTER THE NUMBER OF STICK : " RESET);
        while(1){
            char f[100];
            int d=0;
            int valid=1;
            if(!(load==1&&fscanf(fptr,"%s",&f)==1)){
                scanf("%s",&f);
            }
            //printf("%d",strlen(f));
            for(int i=0;i<strlen(f);++i){
                if(isdigit(f[0])!=isdigit(f[i])){
                   valid=0;
                }
            }
            if(isdigit(f[0])==0&&isalpha(f[0])==0){
                valid=0;
            }
            if(valid){
                if(isdigit(f[0])==1){
                    for(int i=0;i<strlen(f);++i){
                    d=d+(f[strlen(f)-1-i]-'0')*pow(10,i);
                    }
                    if(d>0&&d<=n&&cheak[d]==0){
                        input=d;
                        break;
                    }
                }
                else{
                    if(strlen(f)==1){
                        if(f[0]=='u'||f[0]=='U'){
                            op='u';
                            break;
                        }
                        else if(f[0]=='r'||f[0]=='R'){
                            op='r';
                            break;
                        }
                        else if(f[0]=='s'||f[0]=='S'){
                            op='s';
                            break;
                        }
                        else if(f[0]=='e'||f[0]=='E'){
                            op='e';
                            break;
                        }

                    }
                }
            }
            printf(RED"PLEASE ENTER VALID VALUE : " RESET);
    }

}
if(input!=0){
    if(!computer){
        fprintf(fs,"%d ",input);
    }
    int nn=n+1;
    nn/=2;
    nn=2*nn*(nn-1)+1;
    if(undo){
        if(compu){
            if(computer==1){

            }
            else{
                undo=0;
                for(int i=step;i<nn;++i){
                    turns[i]=0;
                }
            }
        }
        else{
            undo=0;
            for(int i=step;i<nn;++i){
                turns[i]=0;
            }
        }
    }

    int counter=0 ;
    ++cheak[input];
    for (int i = 0 ; i < n ; i++){
        for (int j = 0 ; j < n ; j++){
                if(counter<input){
                h=j;
                t=i;
                //break;
            }
            if (arr[j][i]=='0'&&i%2==0&&j%2==0);
            else if (arr[j][i]=='1' && i%2 ==0){ ++counter;}
            else if (arr[j][i]=='1' && i%2 !=0){ ++counter;}
            else if (arr[j][i]=='2' && i%2 ==0){++counter;}
            else if (arr[j][i]=='2' && i%2 !=0) {++counter;}
            else if (arr[j][i]=='A' );
            else if (arr[j][i]=='B' ) ;
            else if (arr[j][i]=='0'&& i%2 !=0&& j%2 !=0&&(i+j)%2==0) ;
            else if (arr[j][i]=='0'&&i%2 !=0) ++counter;
            else if (arr[j][i]=='0'&& i%2 ==0)++counter;

        }
    }

    if(player==1){
        player1 ++ ;
        arr[h][t] = '1';

    }
    else{
        ++player2;
        arr[h][t] = '2';

    }
}
else{
    if(op!='s'&&op!='S')
        fprintf(fs,"%c ",op);
    switch(op){
        case 'u':
            if(compu){
                if(step>3){
                    for(int f=2;f<step;++f){
                        if(turns[step-f]==2){
                            //turns[step-f]=0;
                            --player2;
                        }
                        else{
                            step=step-f;
                            break;
                        }
                    }
                }
                else{
                    --player2;
                    step=step-4;
                    }
                if(step<0){step=0;}
                arr_equal_go(arr,n,step);
                cheak_equal_go(cheak,n,step);
                --player1;
                if(player2<0){player2=0;}
                if(player1<0){player1=0;}
            }
            else{
                step-=2;
                if(step<0){step=0;}
                arr_equal_go(arr,n,step);
                cheak_equal_go(cheak,n,step);
                if(turns[step]==1){
                    --player1;
                }
                else if (turns[step]==2){
                    --player2;
                }
            }
            score1=save_score1[step];
            score2=save_score2[step];
            turns[0]=1;
            undo=1;
            if(player1<0){player1=0;}
            if(player2<0){player2=0;}
            break;
        case 'r':
            if(compu){
                if(undo&&turns[step]!=0){
                    arr_equal_go(arr,n,step);
                    cheak_equal_go(cheak,n,step);
                    ++player1;

                }
                else{
                    --step;
                }

            }
            else{
                if(undo&&turns[step]!=0){
                    arr_equal_go(arr,n,step);
                    cheak_equal_go(cheak,n,step);
                    if(turns[step-1]==1){
                        ++player1;
                    }
                    else if (turns[step-1]==2){
                        ++player2;
                    }
                }
                else{
                    --step;
                }
            }
            score1=save_score1[step];
            score2=save_score2[step];
            break;

        case's':
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
            break;
        default:
            exit(0);
            break;
    }
}
}


//======================================================================================================================================================================/////
//======================================================================================================================================================================/////
//======================================================================================================================================================================/////
//======================================================================================================================================================================/////
//======================================================================================================================================================================/////
//======================================================================================================================================================================/////


void main_menu(){
    system("");
    system("cls");
    char m;
    printf(RED"\n\n\t\t\t%c%c%c  %c%c%c%c%c%c%c%c%c%c%c%c%c%c     %c%c%c      %c%c%c%c%c%c  %c%c%c\t"YELLOW"%c%c%c%c%c%c%c%c%c%c%c%c",219,219,187,219,219,187,219,219,219,219,219,219,219,187,219,219,187,219,219,187,219,219,219,219,219,187,219,219,187,201,205,205,205,205,205,205,205,205,205,205,187);
    printf(RED"\n\t\t\t%c%c%c  %c%c%c%c%c%c%c%c%c%c%c%c%c%c     %c%c%c     %c%c%c%c%c%c%c%c %c%c%c\t"YELLOW"%c  %c  %c%c%c%c %c",219,219,186,219,219,186,219,219,201,205,205,205,205,188,219,219,186,219,219,186,219,219,201,205,205,219,219,187,219,219,186,186,223,219,223,223,220,186);
    printf(RED"\n\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c  %c%c%c     %c%c%c     %c%c%c  %c%c%c %c%c%c\t"YELLOW"%c %c%c%c %c  %c %c",219,219,219,219,219,219,219,186,219,219,219,219,219,187,219,219,186,219,219,186,219,219,186,219,219,186,219,219,186,186,223,219,223,219,219,186);
    printf(RED"\n\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c  %c%c%c     %c%c%c     %c%c%c  %c%c%c %c%c%c\t"YELLOW"%c %c%c%c %c  %c %c",219,219,201,205,205,219,219,186,219,219,201,205,205,188,219,219,186,219,219,186,219,219,186,219,219,186,200,205,188,186,220,219,220,219,219,186);
    printf(RED"\n\t\t\t%c%c%c  %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c %c%c%c\t"YELLOW"%c%c%c%c%c%c%c%c%c%c%c%c",219,219,186,219,219,186,219,219,219,219,219,219,219,187,219,219,219,219,219,219,219,187,219,219,219,219,219,219,219,187,200,219,219,219,219,219,201,188,219,219,187,200,205,205,205,205,205,205,205,205,205,205,188);
    printf(RED"\n\t\t\t%c%c%c  %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c %c%c%c%c%c%c  %c%c%c"RESET,200,205,188,200,205,188,200,205,205,205,205,205,205,188,200,205,205,205,205,205,205,188,200,205,205,205,205,205,205,188,200,205,205,205,205,188,200,205,188);

    // dots boxes

    printf(BLUE"\n\n\n");
    printf("\t\t%c%c%c%c%c%c%c%c %c%c%c%c%c%c %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c       %c%c%c%c%c%c%c  %c%c%c%c%c%c %c%c%c  %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,187,219,219,219,219,219,187,219,219,219,219,219,219,219,219,187,219,219,219,219,219,219,219,187,219,219,219,219,219,219,187,219,219,219,219,219,187,219,219,187,219,219,187,219,219,219,219,219,219,219,187,219,219,219,219,219,219,219,187);
    printf("\n\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c       %c%c%c%c%c%c%c %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,201,205,205,219,219,186,219,219,201,205,205,219,219,187,200,205,205,219,219,201,205,205,188,219,219,201,205,205,205,205,188,219,219,201,205,219,219,186,219,219,201,205,205,219,219,187,200,219,219,187,219,219,201,188,219,219,201,205,205,205,205,188,219,219,201,205,205,205,205,188);
    printf("\n\t\t%c%c%c  %c%c%c%c%c%c  %c%c%c   %c%c%c   %c%c%c%c%c%c%c%c       %c%c%c%c%c%c%c%c%c%c%c  %c%c%c %c%c%c%c%c%c %c%c%c%c%c%c  %c%c%c%c%c%c%c%c",219,219,186,219,219,186,219,219,186,219,219,186,219,219,186,219,219,219,219,219,219,219,187,219,219,219,219,219,219,219,187,219,219,186,219,219,186,200,219,219,219,201,188,219,219,219,219,219,187,219,219,219,219,219,219,219,187);
    printf("\n\t\t%c%c%c  %c%c%c%c%c%c  %c%c%c   %c%c%c    %c%c%c%c%c%c%c       %c%c%c%c%c%c%c%c%c%c%c  %c%c%c %c%c%c%c%c%c %c%c%c%c%c%c   %c%c%c%c%c%c%c",219,219,186,219,219,186,219,219,186,219,219,186,219,219,186,200,205,205,205,219,219,186,219,219,201,205,205,219,219,186,219,219,186,219,219,186,219,219,201,219,219,187,219,219,201,205,205,188,200,205,205,205,219,219,186);
    printf("\n\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c   %c%c%c   %c%c%c%c%c%c%c%c       %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,186,200,219,219,219,219,219,201,188,219,219,186,219,219,219,219,219,219,219,186,219,219,219,219,219,219,219,186,200,219,219,219,219,219,201,188,219,219,201,188,200,219,219,187,219,219,219,219,219,219,219,187,219,219,219,219,219,219,219,186);
    printf("\n\t\t%c%c%c%c%c%c%c%c %c%c%c%c%c%c    %c%c%c   %c%c%c%c%c%c%c%c       %c%c%c%c%c%c%c%c %c%c%c%c%c%c %c%c%c  %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n\n\n",200,205,205,205,205,205,205,188,200,205,205,205,205,188,200,205,188,200,205,205,205,205,205,205,188,200,205,205,205,205,205,205,188,200,205,205,205,205,188,200,205,188,200,205,188,200,205,205,205,205,205,205,188,200,205,205,205,205,205,205,188);

    printf(GREEN"\n\n\n\n\n\n\n\n\t\tTo continue press Enter" RESET);

    getchar();
    system("cls");
    printf(YELLOW"======================Dots and Boxs=========================\n\n" RESET) ;
    printf(GREEN "1-START PLAY" BLUE "\n\n2-LOAD GAME\n\n3-Top 10\n\n4-Exit\n\n\n" YELLOW "What would you like to do : " RESET);
    int input,temp;char term;

    while(1){
        while(scanf("%d%c", &input, &term) != 2 || term != '\n'){
            while((temp=getchar()) != EOF && temp != '\n');
            printf(RED"PLEASE ENTER NUMBER : " RESET);
        }
        if(input>0&&input<=4){
            break;
        }
        else{
            printf(RED"PLEASE ENTER VALID NUMBER : " RESET);
        }
    }
    case_input=input;
    switch(input){
	case 1:
	    system("cls");
	    printf(GREEN "1-PLAYER 1 " RED "vs" GREEN " PLAYER 2" GREEN "\n2-PLAYER 1 " RED "vs" GREEN " COMPUTER" BLUE "\n(1 or 2) : " RESET);
	    while(1){
            while(scanf("%d%c", &compu, &term) != 2 || term != '\n'){
                while((temp=getchar()) != EOF && temp != '\n');
                printf(RED"PLEASE ENTER NUMBER : " RESET);
            }
            if(compu>0&&compu<=2){
                --compu;
                break;
            }
            else{
                printf(RED"PLEASE ENTER VALID NUMBER : " RESET);
            }
        }
        fprintf(fs,"%d ",compu+1);
        system("cls");
        printf(CYAN "PLEASE ENTER PLAYER 1 NAME : " RESET);
        scanf("%s",&name1);
        fprintf(fs,"%s ",name1);
        if(compu==0){
            printf(YELLOW "PLEASE ENTER PLAYER 2 NAME : " RESET);
            scanf("%s",&name2);
            fprintf(fs,"%s ",name2);
        }
        else{
            name2[0]='c';name2[1]='o';name2[2]='m';name2[3]='p';name2[4]='u';name2[5]='t';name2[6]='e';name2[7]='r';
        }
    break;
	case 2:
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
        break;
	case 3:

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
			break;
	default :
	    exit(0);
			break;
}



}

