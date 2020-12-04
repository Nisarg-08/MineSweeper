#include <bits/stdc++.h>
using namespace std;

#define what_is(x) cout<<#x<<" = "<<x<<"\n";


int LEVEL=0, SIZE=0, MINES=0, movesLeft=0;

// First Move is always valid.
bool firstMove = true;

// To traverse 8 cells around a cell in a matrix.
int x[8] = { -1, -1, -1,  0,  0,  1,  1,  1 };
int y[8] = { -1,  0,  1, -1,  1, -1,  0,  1 };

vector< vector<char> > realBoard, displayBoard; // DataStructure.

// Functions Declarations.
void printBoard( vector< vector<char> >&) ;
bool isValid( int, int) ;
void setSIZE();
void initialize();
void selectMove( int&, int& );
void changeBoard( int, int );
bool checkOutcome( int, int );
void playGame();
void endGame( bool );
//_______________


void printBoard(vector<vector<char>>& board){
    cout << "    ";
    for(int i=0; i<SIZE; ++i)
    {
        cout << i;
        cout << (i<10?"  ":" ");
    }
    cout<<"\n";
    
    for(int i=0; i<SIZE; ++i){
        cout << i ;
        cout << (i<10?"  |":" |");

        for(int j=0; j<SIZE; ++j){
            cout << board[i][j];
            cout << "  ";//(j<10?"  ":" ");
        }
        cout << "|\n";
    }
    cout << "\n";
}

bool isValid(int row, int col){
    if(row<0 || col<0 || row>=SIZE || col>=SIZE){
        return false;
    }
    else{
        return true;
    }
}

void setSIZE(){
    switch(LEVEL){
        case(0):{
            SIZE = 5;
            MINES = 10;
            break;
        }
        case(1):{
            SIZE = 10;
            MINES = 25;
            break;
        }
        case(2):{
            SIZE = 15;
            MINES = 35;
            break;
        }
        default:{
            SIZE = 5;
            MINES = 8;
            break;
        }
    }

    movesLeft = SIZE*SIZE - MINES;

}
void initialize(){
    cout << "Choose LEVEL: \n";
    cout << "0, 1 or 2 => ";
    cin >> LEVEL;

    setSIZE();

    realBoard = vector<vector<char>>(SIZE,vector<char>(SIZE,'-'));
    displayBoard = vector<vector<char>>(SIZE,vector<char>(SIZE,'-'));

    int mines = MINES;
    srand(time(NULL));
    while(mines){
        int random = rand()%(SIZE*SIZE);
        int row = random/SIZE;
        int col = random%SIZE;
        if(realBoard[row][col] == '-'){
            realBoard[row][col] = '*';
            --mines;            
        }
    }

}

void selectMove(int& row, int& col){
    int maxAttemp = 15;
    while(--maxAttemp)
    {
        int tRow, tCol;
        cout << "Enter Cell Row & Column : \n";
        cin >> tRow;
        cin >> tCol;

        if(!isValid(tRow,tCol)){
            cout << row << " " << col << "\n";
            cout << "Enter valid cells.\n";}
        else{
            row = tRow;
            col = tCol;
            break; 
        }

    }
}

void changeBoard(int row, int col){
    bool minePlaced = false;
    if(isValid(row,col)){
        for(int i=0; i<SIZE; ++i){
            for(int j=0; j<SIZE; ++j){
                if(realBoard[i][j] == '-')
                { realBoard[i][j] = '*'; 
                  realBoard[row][col] = '-';
                  minePlaced = true;
                break;
                }
            }
            if(minePlaced)
            break;
        }
    }

    for(int i=0; i<SIZE; ++i){
        for(int j=0; j<SIZE; ++j){
            if(realBoard[i][j] == '*')
                { continue; }
            int count = 0;
            for(int k=0; k<8; ++k){
                if(isValid(i+x[k], j+y[k]) && realBoard[i+x[k]][j+y[k]] == '*')
                {
                    count++;
                }
            }
            realBoard[i][j] = count+'0';
        }
    }
}

bool checkOutcome(int row,int col){
    if(realBoard[row][col] == '*')
    {
        if(firstMove){
            changeBoard(row, col);
            displayBoard[row][col] = realBoard[row][col];
            firstMove = false;
        }
        else{
            return true;
        }
    }
    else{
        if(firstMove){
            changeBoard(-1, -1);
            firstMove = false;
        }
        displayBoard[row][col] = realBoard[row][col];
        if(displayBoard[row][col] == '0'){
            stack<pair<int,int>> s;
            s.push({row,col});
            while(!s.empty()){
                auto it = s.top();
                int r = it.first, c = it.second;
                s.pop();
            for(int k=0; k<8; ++k){
                if(isValid(r+x[k], c+y[k]))
                {
                    char temp = realBoard[r+x[k]][c+y[k]];
                    if(temp == '0' && displayBoard[r+x[k]][c+y[k]] == '-')
                    { s.push({r+x[k],c+y[k]}); }
                    
                    displayBoard[r+x[k]][c+y[k]] = temp;
                    --movesLeft;
                }
            }
            }
        }
    }

    return false;
}


void playGame(){
    int row ,col ;
    while(movesLeft--){
        printBoard(displayBoard);
        row = col = -1;
        selectMove(row,col);

        bool isOver = checkOutcome(row,col);
        if(isOver){
            endGame(false);
            return;
        }

    }

    endGame(true);
}

void endGame(bool won){
    if(won){
        cout << "Congrats You Won!!\n";
    }
    else{
        cout << "You Lost!\n";
        printBoard(realBoard);
        cout << "Sometimes Luck is not with us,\n but that wasn't the case today.\n";
    }
    
}

int main(){
   
    initialize();

    playGame();

   return 0;
}
