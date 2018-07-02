#include <stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct structloc
{
    int i;
    int j;
    int axis;
    int g;
    
}sloc;

//----------------------------------------------
//===POP a word form a linked list Structure====
//----------------------------------------------
typedef struct structpop
{
    struct node *Node;
    char word[100];
    
}spop;


//----------------------------------------------
//=========ADVANCE LINKKED-LIST Structure=======
//----------------------------------------------
typedef struct node
{
    struct node *next;
    char word[50];
    struct node *back;
}words;


//----------------------------------------------
//============ Function initialization =========
//----------------------------------------------
int LEN(char*arr);
words *INSERT(words*a,char*b);
spop *POP(words*a);
void game (char board[100][100],words *WordList,int n);
void write(char board[100][100],char *word,int I,int J,int axis);
sloc *find(char board[100][100],char* word,int n);
void erase(char board[100][100],char *word,int J,int I,int axis);
void printboard(char board[100][100],int n);


int main(int argc, char const *argv[]){

    int i,j, x_i, N = 4;
    int mwl=0;
    int mbl=0;
    char board[100][100];
    char ListofWords[100][100];
    int bn=0,bcount=0,wn=0,wcount=0;

   // printf("Board------------------------\n");
    while (1){
        char ch;
        scanf("%c", &ch);
        if (ch!='\n'){
            board[bn][bcount]=ch;
            bcount++;
        }else if(bcount >0) {
            board[bn][bcount]='\0';
            bn++;
            if (mbl<bcount){
                mbl=bcount;
            }
            bcount=0;
        }else{
            break;
        }
    }

   
   // printf("wordlist------------------------\n");
    while (1){
        char ch;
        scanf("%c", &ch);
        if (ch!='\n'){
            if (ch>='a')
            {
                ch=ch-32;
            }
            ListofWords[wn][wcount]=ch;
            wcount++;
        }else if(wcount >0) {
            ListofWords[wn][wcount]='\0';
            if (mwl<wcount){
                mwl=wcount;
            }
            wn++;
            wcount=0;
        }else{
            break;
        }
    }

    words *WordList;
    words *current;
    WordList=malloc(sizeof(words));
    current=WordList;


    //printf("printing wordlist------------------------\n");
    for (int i = 0; i < wn; ++i)
    {
        //printf("%d %s\n",i,ListofWords[i] );

        current->next=malloc(sizeof(words));
        current->next->back=WordList;
        strcpy(current->next->word,ListofWords[i]);
        current=current->next;
    }
    current->next=NULL;



    current=WordList;
    while (current!=NULL){
        //printf("LL  %s\n",current->word );
        current=current->next;
    }
   //printf("mbl=%d mwl=%d \n",mbl,mwl);
    if (mbl>=mwl){
        game (board,WordList,bn);
    }else{
        printf("IMPOSSIBLE");
    }
    


    return 0;
}

//-----------------------------------------------------------
//==================LENGTH OF A TEXT=========================
//-----------------------------------------------------------
int LEN(char*arr){
    int count=0;
    int c=0;
    while (count>=0){
        if (arr[count]>='A' && arr[count]<='z'){
            c++;
        }
        if (arr[count]=='\0') break;
        count++;
    }
    return c;
}


//-----------------------------------------------------------
//==================== INSERT to A LINKED LIST ===============
//-----------------------------------------------------------
words *INSERT(words*a,char*b){
    words *c;

    c=malloc(sizeof(words));

    c->next=a;
    c->back=a->back;
    strcpy(c->word,b);
    a->back=c;
    c->back->next=c;
    c->next->back=c;
    return c;
}


//-----------------------------------------------------------
//=====================POP from a linked list================
//-----------------------------------------------------------
 spop *POP (words*a){
    spop *p;
    p=malloc(sizeof(spop));
    
    strcpy(p->word,a->word);
    a->back->next=a->next;  
    a->next->back=a->back;
    p->Node=a->back->next;
    return p;
}


//-----------------------------------------------------------
//================ Cross-word game ==========================
//-----------------------------------------------------------
void game (char board[100][100],words *WordList,int n){
    words *current=WordList;
    current=current->next;
    int i=0;
    int numofword=0;
    while (current!=NULL){
        numofword++;\
        current=current->next;
    }
    current=WordList->next;
    //printf("num of words=%d\n",numofword );
    //printboard(board,n);
    //current=INSERT(current,"dddddddddd");
    //spop *pop=POP(current);
    //current=pop->Node;
    //INSERT(current,"fffffffffffff");

    current=WordList;
    current=current->next;
    sloc *loc=malloc(sizeof(sloc));
    int I,J,A;
    words *pus;
    int rounds=0;
    while(current != NULL){
        rounds+=1;
        loc=find(board,current->word,n);
        if (loc->g==0)
        {
            printf("IMPOSSIBLE\n");
            break;
        }
         //printf("word=%s i=%d j=%d\n",current->word,loc->i,loc->j );
        if (loc-> i !=-1 && loc->j!=-1){
            I=loc->i;
            J=loc->j;
            A=loc->axis;
            write(board,current->word,J,I,A);
            numofword--;
            rounds=0;
            current->back->next=current->next;
            if (current->next!=NULL){
                current->next->back=current->back;
            }
            
        }else{
            pus=current;
            current->back->next=current->next;
            if (current->next!=NULL){
                current->next->back=current->back;
            }
            while(current->next!=NULL){
                current=current->next;
            }

            current->next=malloc(sizeof(words));
            current->next->back=current;
            strcpy(current->next->word,pus->word);
            current=current->next;
            current->next=NULL;


        }
        current=WordList;
        current=current->next;
        if (rounds>numofword){
            break;
        }
    }
    // sloc *loc=find(board,"give",n);
    // int I=loc->i,J=loc->j,A=loc->axis;
    // write(board,"give",J,I,A);
    //erase(board,"give",J,I,A);
    if (loc->g!=0){
        printboard(board,n);
    }
     
}

//-----------------------------------------------------------
//================ Find the Location ========================
//-----------------------------------------------------------
sloc *find(char board[100][100],char* word,int n){
    sloc *location;//location matrix 1 by 3
    location=malloc(sizeof(sloc));
    int Bl=strlen(board[1]);//board length of a row
    int len = strlen(word);//word length
    char*H[]={"#"};
    char *St[]={"*"};
    location->g=0;
    int i=0,j=0;
    int G=0;
    for (int i = 0; i < n; ++i)
    {
        
        int Bl=strlen(board[i]);
        for (int j = 0; j <= Bl-len+1; ++j)
        {   
            
            int good=1;
            for (int k = 0; k < len; ++k)
            {
                if(strncmp((char *)&board[i][j+k],H[0],1)!=0 && (int)board[i][j+k]!=(int)word[k])
                {
                    good=0;
                    break;
                }
            }
            
            if (j!=0 && (strncmp((char *)&board[i][j-1],St[0],1)!=0 )){
                good=0;
            }
            if ((j+len)!=(Bl)  && (strncmp((char *)&board[i][j+len],St[0],1)!=0 )){
                good=0;
            }
            //printf("%d %s i=%d j=%d  G=%d\n",good,word,i,j,G );
            if (good==1  )
            {   
                //printf("Done -\n" );
                location->i=i;
                location->j=j;
                location->axis=0;
                G++;
                location->g=G;
                
            }
            //printf("----%s %d %d\n",word,location->i,location->j );
        }
    }
    if (G==1){
        return location;
    }
    G=0;
    for (int i = 0; i < n-len+1; ++i)
    {
        
        int Bl=strlen(board[i]);
        for (int j = 0; j < Bl; ++j)
        {   
            
            int good=1;
            for (int k = 0; k < len; ++k)
            {   
                if(strncmp((char *)&board[i+k][j],H[0],1)!=0 && (int)board[i+k][j]!=(int)word[k] ) {
                    //checking whether the space is a # or the same letter as in the word
                    good=0;
                    break;
                }
            }
            //printf("%d %s i=%d j=%d  G=%d\n",good,word,i,j,G );
            if (i!=0 && (strncmp((char *)&board[i-1][j],St[0],1)!=0 )){
                good=0;

            }if ((i+len)!=n  && (strncmp((char *)&board[i+len][j],St[0],1)!=0 )){
                good=0;
            }
            if (good==1)
            {
                //printf("Done |\n");
                location->j=j;
                location->i=i;
                location->axis=1;
                G++;
                location->g=G;
                
            }
            //printf("%d ||  %s %d %d\n",good,word,location->i,location->j );
        }
    }
    //printf("%s locI=%d locJ=%d locA=%d\n",word,location->i,location->j,location->axis );
    if (G==1){
        return location;
    }else{
        location->i=-1;
        location->j=-1;
        return location;
    }
}

//-----------------------------------------------------------
//================ Write on the Board  ======================
//-----------------------------------------------------------
void write(char board[100][100],char *word,int J,int I,int axis){
    int len = strlen(word);
    

    if (axis==0){
        for (int i=0;i<len;i++){
            board[I][J+i]=word[i];  
        }
    }else{
        for (int i=0;i<len;i++)  {
            board[I+i][J]=word[i];  
        }
    }   
}

//-----------------------------------------------------------
//============ Erase the word from the Board ================
//-----------------------------------------------------------
void erase(char board[100][100],char *word,int J,int I,int axis){
    int len = strlen(word);
    char*H[]={"#"};
    if (axis==0){
        for (int i=0;i<len;i++){
            board[J][I+i]=H[0][0];  
        }
    }else{
        for (int i=0;i<len;i++)  {
            board[J+i][I]=H[0][0];  
        }
    }   
}

//-----------------------------------------------------------
//================== Print the Board ========================
//-----------------------------------------------------------
void printboard(char board[100][100],int n){
    int i=0;

    while(i<n){
        if (i>0){
            printf("\n");
        }
        printf("%s",board[i] );
        i++;
     }
    
}

