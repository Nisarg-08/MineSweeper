#include <bits/stdc++.h>
using namespace std;

#define BEGINNER 0
#define INTERMEDIATE 1
#define ADVANCEED 2
#define MAXSIDE 25
#define MAXMINES 99
#define MOESIZE 526

int side,mines;

bool isValid(int row,int col){
	return (row>=0)&&(row<side)&&(col>=0)&&(col<side);
}

bool isMine(int row,int col,char realboard[][MAXSIDE]){
	if(realboard[row][col]=='*')
		return true;
	else
		return false;
	}
	
void makeMove(int *x,int *y){
	cout<<"Enter Move ( row , column ) -> ";

	scanf("%d %d", x, y);
	return;
}

void printBoard(char myBoard[][MAXSIDE]){
	int i,j;
	cout<<"    ";
	for(i=0;i<side;i++)
	cout<<i<<" ";
	cout<<endl;
	for(int i=0;i<side;i++){
		cout<<i<<"   ";
		for(int j=0;j<side;j++){
			cout<<myBoard[i][j]<<" ";
		}
		cout<<endl;
	}
	return;
}

int countAdjacentMines(int row,int col,int mine[][2],char realBoard[][MAXSIDE]){
	int i,count=0;
	if(isValid(row-1,col)==true){
		if(isMine(row-1,col,realBoard))
			count++;
	}
	
	if(isValid(row+1,col)==true){
		if(isMine(row+1,col,realBoard))
			count++;
	}
	
	if(isValid(row,col+1)==true){
		if(isMine(row,col+1,realBoard))
			count++;
	}
	
	if(isValid(row,col-1)==true){
		if(isMine(row,col-1,realBoard))
			count++;
	}
	
	if(isValid(row-1,col+1)==true){
		if(isMine(row-1,col+1,realBoard))
			count++;
	}
	
	if(isValid(row-1,col-1)==true){
		if(isMine(row-1,col-1,realBoard))
			count++;
	}
	
	if(isValid(row+1,col+1)==true){
		if(isMine(row+1,col+1,realBoard))
			count++;
	}
	
	if(isValid(row+1,col-1)==true){
		if(isMine(row+1,col-1,realBoard))
			count++;
	}
	
	return count;
}
int ch=1;
bool playUntil(char myBoard[][MAXSIDE],char realBoard[][MAXSIDE],int mine[][2],int row,int col,int *movesleft){
	
	if(myBoard[row][col]!='-')
	return false;
	int i,j;
	if(realBoard[row][col]=='*'){
		if(!ch)
		return false;
		ch=0;
		myBoard[row][col]='*';
		for(i=0;i<mines;i++)
			myBoard[mine[i][0]][mine[i][1]]='*';
			printBoard(myBoard);
			cout<<"\nYou Lost!\n";
			return true;		
	}
	
	else{
		int count = countAdjacentMines(row,col,mine,realBoard);
		(*movesleft)--;
		myBoard[row][col] = count + '0';
		if(!count){	
				
				
				if (isValid (row-1, col) == true) 
            { 
                   if (isMine (row-1, col, realBoard) == false) 
                   playUntil(myBoard, realBoard, mine, row-1, col, movesleft); 
            }
   
            if (isValid (row+1, col) == true) 
            { 
                   if (isMine (row+1, col, realBoard) == false) 
                    playUntil(myBoard, realBoard, mine, row+1, col, movesleft); 
            } 
   
            if (isValid (row, col+1) == true) 
            { 
                if (isMine (row, col+1, realBoard) == false) 
                    playUntil(myBoard, realBoard, mine, row, col+1, movesleft); 
            } 
  
            if (isValid (row, col-1) == true) 
            { 
                   if (isMine (row, col-1, realBoard) == false) 
                    playUntil(myBoard, realBoard, mine, row, col-1, movesleft); 
            } 
  
           
            if (isValid (row-1, col+1) == true) 
            { 
                if (isMine (row-1, col+1, realBoard) == false) 
                    playUntil(myBoard, realBoard, mine, row-1, col+1, movesleft); 
            } 
  
            if (isValid (row-1, col-1) == true) 
            { 
                 if (isMine (row-1, col-1, realBoard) == false) 
                    playUntil(myBoard, realBoard, mine, row-1, col-1, movesleft); 
            } 
  
            
            if (isValid (row+1, col+1) == true) 
            { 
                 if (isMine (row+1, col+1, realBoard) == false) 
                    playUntil(myBoard, realBoard, mine, row+1, col+1, movesleft); 
            } 
  
            
            if (isValid (row+1, col-1) == true) 
            { 
                if (isMine (row+1, col-1, realBoard) == false) 
                    playUntil(myBoard, realBoard, mine, row+1, col-1, movesleft); 
            } 
        } 
  
        return (false);
	}
}

void placeMines(int mine[][2],char realBoard[][MAXSIDE]){
	bool mark[MAXSIDE*MAXSIDE];
	memset(mark,false,sizeof(mark));
	
	for(int i=0;i<mines;){
		int random=rand()%(side*side);
		int x=random/side;
		int y=random%side;
		if(mark[random]==false){
			mine[i][0]=x;
			mine[i][1]=y;
			realBoard[x][y]='*';
			mark[random]=true;
			i++;
		}
	}
	return;
}

void initialise(char realBoard[][MAXSIDE],char myBoard[][MAXSIDE]){
	srand(time(NULL));
	for(int i=0;i<side;i++){
		for(int j=0;j<side;j++){
			myBoard[i][j]=realBoard[i][j]='-';
		}
	}
	return;
}

void cheat(char realBoard[][MAXSIDE]){
	cout<<"The Mine Locatin are-\n";
	printBoard(realBoard);
	return;
	}

void replaceMine(int row,int col,char realBoard[][MAXSIDE]){
	for(int i=0;i<side;i++){
		for(int j=0;j<side;j++){
			if(realBoard[i][j]!='*'){
				realBoard[i][j]='*';
				realBoard[row][col]='-';
				/* change mine index in mine[] for replaced mine */
				return;
			}
		}
	}
	return;
}

void playMineSweeper(){
	bool gameover=false;
	char myBoard[MAXSIDE][MAXSIDE],realBoard[MAXSIDE][MAXSIDE];
	int movesleft=side*side-mines,x,y;
	int mine[MAXMINES][2];
	
	initialise(realBoard,myBoard);
	
	placeMines(mine,realBoard);
	
	int currentIndex=0;
	while(!gameover){
		cout<<"Current Status : \n";
		printBoard(myBoard);
		makeMove(&x,&y);
		if(currentIndex==0){
			if(isMine(x,y,realBoard))
			replaceMine(x,y,realBoard);
		}
		currentIndex++;
		gameover=playUntil(myBoard,realBoard,mine,x,y,&movesleft);
		ch=1;
		if((gameover==false)&&(movesleft==0)){
			cout<<"\nYou Won!!\n";
			gameover=true;
		}
	}
	return;
}

void chooseDifficulty(){
	int level;
	cout<<"Enter Difficulty Level\n 0 , 1 or 2 => ";
	cin>>level;
	if(level==0)
	{side=9;
	mines=10;
	}
	if(level==1)
	{side=16;
	mines=40;
	}
	if(level==2)
	{side=24;
	mines=99;
	}
	return;
}




int main(){
	
	chooseDifficulty();
	playMineSweeper();
	
	return 0;
}
