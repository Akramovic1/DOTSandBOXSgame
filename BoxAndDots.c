#include"DOTSandBOXS.1.h"

int main(){
    fs = fopen("./private/test.txt","w+");
    fs = fopen("./private/test.txt","a+");

    while(1){
    main_menu();
    if(case_input==3){
        continue;
    }
    system("");
    int n , possible,temp;
    char term;
    printf(YELLOW"ENTER NUM OF POINTS : "RESET);
    if(!(load==1&&fscanf(fptr,"%d",&n)==1)){
        while(1){
            while(scanf("%d%c", &n, &term) != 2 || term != '\n'){
                while((temp=getchar()) != EOF && temp != '\n');
                printf(RED"ENTER NUM OF POINTS : "RESET);
            }
            if(n>0){
                break;
            }
            else{
                printf(RED"ENTER NUM OF POINTS : "RESET);
            }
        }
    }
    fprintf(fs,"%d ",n);
    t1 = clock();
    possible = (n-1)*n*2 ;   //the num of input till the game end
    n = n*2 - 1 ;            // num of new matrix

    int cheak[possible+1];
    for(int i=0;i<possible+1;++i)
        cheak[i]=0;
    for(int i=0;i<possible+1;++i)
        turns[i]=0;

    char arr[1000][1000] ;
    for (int i = 0 ; i < n ; i++){
        for (int j = 0 ; j < n ; j++){
           arr[i][j]='0';
        }
    }

    int i=0 , j=0 ;
    step=0;

    while(step < possible){
        bool myturn = 1 ;
        while(step < possible && myturn == 1 &&(turns[step]==0||turns[step]==1)){
                system("cls");
                print_grid(arr,n,score1,score2,1,possible-step);
                input(arr,cheak,possible,0,1);
                myturn = formbox(arr,n,&score1,'A') ;
        }

        bool histurn = 1 ;
        if (step >= possible)break;
        while(step < possible && histurn == 1&&(turns[step]==0||turns[step]==2)){
                system("cls");
                print_grid(arr,n,score1,score2,2,possible-step);
                input(arr,cheak,possible,compu,2);
                histurn = formbox(arr,n,&score2,'B') ;
        }

    }
    system("cls");
    print_grid(arr,n,score1,score2,0,0);
    p_r=fopen(rank_direct,"a+");
    if (score1 > score2) {
            printf(GREEN"\n\n\n\t congratulations ,"CYAN"%s"RESET" YOU WON THIS ROUND :)\n\n\n"RESET,name1);
            fprintf(p_r,"%s %d ",name1,score1);
    }
    else if (score1 < score2){
            printf(GREEN"\n\n\n\t congratulations ,"YELLOW"%s"RESET" YOU WON THIS ROUND :)\n\n\n"RESET,name2);
            fprintf(p_r,"%s %d ",name2,score2);
            }
    else printf(GREEN"\n\n\n\t THIS GAME IS TIED \n\n\n"RESET);
    fclose(p_r);
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
    return 0;
}
