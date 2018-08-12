/***********************************************************************
* Program:
*    Project 13, Sudoku          
*    Brother Falin, CS124
* Author:
*    Chase Busacker
* Summary: 
*    This is the final sudoku game. 
*
*    Estimated:  8.0 hrs   
*    Actual:     16.0 hrs
*      Canceling possible values for values that were in the box
       instead of a row or column.
************************************************************************/
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <vector>
using namespace std;

#define ROWS 9
#define COLS 9

struct RCandPoss
{
   unsigned short int r;
   unsigned short int c;
   vector <int> possibles;
};

string getFilename();
int readFilename(string filename, int board[][COLS]);
void displayInstructions();
void displayBoard(int board[][COLS]);
char getInstructions();
void executeCommand(char command, int board[][COLS]);
void editSquare(int board[][COLS]);
string getSaveFilename(string filename);
void saveFilename(string filename, int board[][COLS]);
void displayPossibleValues(int board[][COLS]);
bool solveBoard(int board[][COLS]);
bool backtrackSolve(int board[][COLS], vector <RCandPoss> markUp);
void computePossibleValues(int board[][COLS], int possibles[], int rowNum, int columnNum);


/**********************************************************************
 * MAIN calls each function and creates the main variables to run the
 * program. Also, the while loop will loop the commands until the user
 * wants to save the board.
 ***********************************************************************/
int main()
{
   //variable declarations
   int board[ROWS][COLS];
   int readtest;
   string filename;
   char command;

   //read the file and if it fails, make the user enter it again.
   do
   {
      filename = getFilename();
      readtest = readFilename(filename, board);
      if(readtest == -1)
         cout << "ERROR: Invalid Filename" << endl;
   }
   while (readtest == -1);
   
   //Show the board and instructions when the game first starts
   displayInstructions();
   displayBoard(board);

   //Run the program until the user wants to 'Q'uit.
   do
   {
      command = getInstructions();
      executeCommand(command, board);
   }
   while (command != 'Q');

   //Get the new file name the user would like to save the board to. 
   do
   {
      cout << "Would you like to save the board in the same location(y/n)? ";
      cin >> command;

      if (command == 'n')
         filename = getSaveFilename(filename);
      else if(command != 'y')
         cout << "Invalid command. Please try again.\n";
   }
   while (!(command == 'y' || command == 'n'));
   
   //save the board to the filename.
   saveFilename(filename, board);

   return 0;
}

/**********************************************************************
 * getFilename will get the location of the file that their sudoku 
 * board is located.
 ***********************************************************************/
string getFilename()
{
   string filename;
   cout << "Where is your board located? ";
   cin >> filename;

   return filename;
}

/**********************************************************************
 * readFilename is in charge of reading in file into the board and
 * organizing it into a Sudoku board.
 ***********************************************************************/
int readFilename(string filename, int board[][COLS])
{
   ifstream fin;

   fin.open(filename.c_str());

   if (fin.fail())
      return -1;

   for (int r = 0; r < ROWS; r++)
   {
      for (int c = 0; c < COLS; c++)
      {
         fin >> board[r][c];
      }
   }

   fin.close();

   return 0;
}   

/**********************************************************************
 * displayInstructions displays the instructions to the user.
 ***********************************************************************/
void displayInstructions()
{
   cout << "Options:\n";
   cout << "   ?  Show these instructions\n";
   cout << "   D  Display the board\n";
   cout << "   E  Edit one square\n";
   cout << "   P  Show the possible values for a square\n";
   cout << "   S  Solve this board\n";
   cout << "   Q  Save and Quit\n\n";
}

/**********************************************************************
 * displayBoard displays the board to the user.
 ***********************************************************************/
void displayBoard(int board[][COLS]){

   cout << "   A B C D E F G H I\n";
   
   for (int r = 0; r < ROWS; r++)
   {
      cout << r + 1 << "  ";
      for (int c = 0; c < COLS; c++)
      {
         //NUMBERS NOT ZERO

         //right before a gridline
         //therefore, just display the number (gridline placement)
         if ((board[r][c] != 0) && (c == 2 || c == 5 || c == 8))
            cout << board[r][c];
         //not before a gridline
         //display the number AND a space
         else if (board[r][c] != 0 && c != 2 && c != 5)
            cout << board[r][c] << " ";


         
         //NUMBER IS 0 (meaning blank space on the board)
         
         //right before a gridline
         //display a single space
         else if (board[r][c] == 0 && (c == 2 || c == 5 || c == 8))
            cout << " ";
         //not before a gridline
         //display a double space
         else if (board[r][c] == 0 && c != 2 && c != 5)
            cout << "  ";
         
         //anytime there is a column of 3 or 6 display a |
         if ( c != COLS - 1 && c == 2 || c == 5)
            cout << "|";
      }
      cout << endl;

      if (r == 2 || r == 5)
      {
         cout << "   -----+-----+-----\n";
      }
   }
   cout << endl;
}

/**********************************************************************
 * getInstructions waits for the user to input a command and returns
 * that character to main.
 ***********************************************************************/
char getInstructions()
{

   char command;
   cout << "> ";
   cin >> command;

   return toupper (command);
}

/**********************************************************************
 * executeCommand will read the command given and tell a function to
 * run depending on the command given.
 ***********************************************************************/
void executeCommand(char command, int board[][COLS])
{
   //edit square because command was an 'E'
   if (command == 'E')
      editSquare(board);

   //display the board because the command was a 'D'
   else if (command == 'D')
      displayBoard(board);

   //display the instructions because the command was a '?'
   else if (command == '?')
   {
      displayInstructions();
      cout << endl;
   }

   //compute the values for a sqaure
   else if (command == 'P')
      displayPossibleValues(board);

   //Solve the Board
   else if (command == 'S')
   {
      if(solveBoard(board))
      {
         cout << "Solve Successful\n";
         displayBoard(board);
      }
      else
      {
         cout << "Board UnSolvable\nBoard Solved as far as possible:\n";
         displayBoard(board);
      }  
   }
   //Quit by returning.
   else if (command == 'Q')
      return;
   
   //uh oh! Invalid command. User must try again.
   else
      cout << "ERROR: Invalid command" << endl;
}

bool solveBoard(int board[][COLS])
{
   cerr << "SOLVEBOARD" << endl; 
   displayBoard(board);
   vector <RCandPoss> markUp;
   RCandPoss mark;
   vector <int> possVec;
   int possibles[9] = {1,2,3,4,5,6,7,8,9};
   int pause;
   cin >> pause;
    
      for (int r = 0; r < 9; r++)
      {
         for (int c = 0; c < 9; c++)
         {
	    if(board[r][c] != 0)
	      continue;
            possVec.clear();
            computePossibleValues(board, possibles, r, c);
            for (int p = 0; p < 9; p++)

               if (possibles[p] != 0)
               {
                  possVec.push_back(possibles[p]);
               }
               else
                  possibles[p] = p + 1;
            if (possVec.size() == 1)
	    {
               board[r][c] = possVec[0];
	       return solveBoard(board);
               
            }
	    else
            {
		mark.c = c;
                mark.r = r;
                mark.possibles = possVec;
		markUp.push_back(mark);
            }
         }
      }
   
   if (markUp.empty())
     return true;
   else
   {
     //cout << "After basic algorithm.\n";
     //displayBoard(board);
     RCandPoss current;
     for(int i = 0; i < markUp.size(); i++)  {
        current = markUp[i];
	possVec = current.possibles;
	int j = i;
        while(j > -1 && markUp[i].r == markUp[j].r)
           j--;
        
        while(current.r == markUp[j + 1].r && !possVec.empty()) {
        j++;
        if (j == i)
        j++;
        for(int p = 0; p < possVec.size(); p++)
            for(int q = 0; q < markUp[j].possibles.size(); q++){
                 if(possVec[p] == markUp[j].possibles[q])
                     possVec.erase(possVec.begin() + p); } }
        if(possVec.size() == 1) {
           board[current.r][current.c] = possVec[0];
   //        solveBoard(board);
           return solveBoard(board);
           
        }
        possVec = current.possibles;
        j = -1;
        while((j + 1) < markUp.size() && !possVec.empty()) {
           j++;
           while(j < (int)markUp.size() && (current.c != markUp[j].c || j == i))
              j++;
              if (j == markUp.size())
                   break;
              for(int p = 0; p < possVec.size(); p++)
                  for(int q = 0; q < markUp[j].possibles.size(); q++) { 
                     if(possVec[p] == markUp[j].possibles[q])
                         possVec.erase(possVec.begin() + p);
                  }    }
	if(possVec.size() == 1){
  //         cerr << "COL CHANGED IT @" << current.r << current.c << endl;
           board[current.r][current.c] = possVec[0];
           return solveBoard(board);
         }

        
        possVec = current.possibles;
        int minR;
        int maxR;
        int minC;
        int maxC;
        if(current.r < 3)
        {
           minR = 0;
           maxR = 3;
        }
        else if (current.r < 6){
           minR = 3;
           maxR = 6;
        }
        else{
        minR = 6;
        maxR = 9;
        }
        if (current.c < 3){
        minC = 0;
        maxC = 3;
        }else if (current.c < 6){
        minC = 3;
        maxC = 6;
        }else{
        minC = 6;
        maxC = 9;}

        j = 0;
        //cerr << endl << current.r << ":" << current.c << endl;
        while(j < markUp.size() && !possVec.empty())
        {
        //cerr << "LINE:";
        
        while((j < markUp.size() &&  !(markUp[j].r < maxR && markUp[j].r >= minR && markUp[j].c < maxC && markUp[j].c >= minC)) || j == i) j++;
         if (j == markUp.size())
           break;
        //cerr << markUp[j].r << "," << markUp[j].c << endl;
        for(int p = 0; p < possVec.size(); p++)
               for(int q = 0; q < markUp[j].possibles.size(); q++)
		{
                  if (current.r == 0 && current.c == 1)
        //              cout << possVec[p] << " = " << markUp[j].possibles[q] << endl;
                     if(possVec[p] == markUp[j].possibles[q])
                              possVec.erase(possVec.begin() + p);
                }
        j++;
        }
        if (possVec.size() == 1){
        //cerr << "board@" << current.r << current.c << "=?" << possVec[0] << endl;
        board[current.r][current.c] = possVec[0];
	if(markUp.size() == 1)
          return true;
       
        }
   }

  }
return backtrackSolve(board, markUp);
}
void copyBoard(int fromme[][9], int tome[][9])
{
for(int r = 0; r < 9; r++)
   for(int c = 0; c < 9; c++)
      tome[r][c] = fromme[r][c];
} 

bool backtrackSolve(int board[][9], vector <RCandPoss> markUp)
{
   bool solved;
   cerr << "BACK SOLVE\n";
   displayBoard(board);
   int row, col;
   cin >> row;
   int saveBoard[9][9];
   if(markUp.empty())
   {
      cerr << "MARKUP EMPTY!\n";
      return true;
   }
   else
   {
   row = markUp[0].r;
   col = markUp[0].c;
   }
   for(int i = 0; i < markUp[0].possibles.size(); i++)
   {
   cerr << "LOOPING" << row << col << " = "<< markUp[0].possibles[i] << endl;
   copyBoard(board, saveBoard);
   board[row][col] = markUp[0].possibles[i];
  // markUp.erase(markUp.begin());
   if(solveBoard(board))
   {   cerr << "SOLVED!!!"; return true; }
   cerr << "RESETTING BOARD\n\n";
   copyBoard(saveBoard, board);
   }
 
   cerr << "BACK RETURNS FALSE!" <<endl;
return false;
}
/**************************************************************
 * GetCoordinates will get the coordinates from the user
 * and error check to ensure they are correct.
***************************************************************/
void getCoordinates(char* coordinates, int & rowNum, int & columnNum)
{
   //set the values of row and column to allow the while loop to run.
   bool valid = false;

   while(!valid)
   {
      cout << "What are the coordinates of the square: ";
      cin >> coordinates;

      if(isalpha(coordinates[0]) && isdigit(coordinates[1]))
      {  coordinates[0] = toupper(coordinates[0]);
         rowNum = coordinates[1] - '1';
         columnNum = coordinates[0] - 'A';
         if(rowNum < ROWS && columnNum < COLS)
            valid = true;
      }
      else if(isalpha(coordinates[1]) && isdigit(coordinates[0]))
      {
         coordinates[1] = toupper(coordinates[1]);
         rowNum = coordinates[0] - '1';
         columnNum = coordinates[1] - 'A';
         if (rowNum < ROWS && columnNum < COLS)
            valid = true; 
      }
      if(!valid)
      {
         cout << "Invalid Coordinates. Please try again.";
      }
   }   
}

void computePossibleValues(int board[][COLS], int* possibles, int rowNum, int columnNum)
{
   //evaluate rows
   for(int i = 0; i < 9; i++)
      if (board[rowNum][i] != 0)
         possibles[board[rowNum][i] - 1] = 0;
   
   //evaluate columns
   for(int i = 0; i < 9; i++)
      if (board[i][columnNum] != 0)
         possibles[board[i][columnNum] - 1] = 0;

   //Sudoku BOX boundaries.
   int topRow;
   int bottomRow;
   int leftColumn;
   int rightColumn;
   
   //determine the sudoku BOX row boundaries
   if(rowNum < 3)
   {
      topRow = 0;
      bottomRow = 3;
   }
   else if(rowNum < 6)
   {
      topRow = 3;
      bottomRow = 6; 
   }
   else if(rowNum < 9)
   {
      topRow = 6;
      bottomRow = 9;
   }

   //determine the sudoku BOX column boundaries
   if(columnNum < 3)
   {
      leftColumn = 0;
      rightColumn = 3;
   }
   else if(columnNum < 6)
   {
      leftColumn = 3;
      rightColumn = 6;
   }
   else if(columnNum < 9)
   {
      leftColumn = 6;
      rightColumn = 9;
   }

   //remove values if in sudoku BOX
   for(topRow; topRow < bottomRow; topRow++)
      for(int lc = leftColumn; lc < rightColumn; lc++)
         possibles[board[topRow][lc] - 1] = 0;


   
}
/**********************************************************************
 * editSquare gets a coordinate from the user and sees if it can be
 * edited. If so, it will ask the user for the number to place there.
 * Otherwise it will say that that coordinate is already full.
 ***********************************************************************/
void editSquare(int board[][COLS])
{
   //Get Coordinates for square to edit
   char coordinates[2];
   int columnnum;
   int rownum;
   getCoordinates(coordinates, rownum, columnnum); 
   
   //If the coordinate is filled, tell the user and return to get the next command    
   if (board[rownum][columnnum] != 0)  
   {
      cout << "ERROR: Square \'" << coordinates << "\' is filled\n\n";
      return;
   }

   //compute the possible values for that square
   int possiblenums[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9};
   computePossibleValues(board, possiblenums, rownum, columnnum); 
   
   //get the number that the user wants to put in the coordinates
   int newnumber;
   cout << "What is the value at \'" << coordinates << "\': ";
   cin >> newnumber;
   
   //if the value is acceptable, edit the board.
   if (possiblenums[newnumber -1] != 0)
   {
      board[rownum][columnnum] = newnumber;
      cout << endl;
   }

   //Otherwise, tell the user that the value is invalid.
   else
   {
      cout << "ERROR: Value \'" << newnumber
           << "\' in square \'" << coordinates
           << "\' is invalid" << endl << endl;
   }
}
   


/**********************************************************************
 * getSaveFilename will get the location of the board that the user
 * wants to save the file.
 ***********************************************************************/
string getSaveFilename(string filename)
{
   cout << "What file would you like to write your board to: ";
   cin >> filename;

   return filename;
}

/**********************************************************************
 * saveFilename is in charge of reading the board into the new filename.
 ***********************************************************************/
void saveFilename(string filename, int board[][COLS])
{
   ofstream fout;

   fout.open(filename.c_str());

   for (int r = 0; r < ROWS; r++)
   {
      for (int c = 0; c < COLS; c++)
      {
         fout << board[r][c] << " ";
      }
   }
   cout << "Board written successfully" << endl;
}

/*********************************************************************
 * computeValues will take compute and display the values that
 * a given square can hold.
 *******************************************************************/
void displayPossibleValues(int board[][COLS])
{
   //get the coordinates the user wants the program to display the possible values for.
   char coordinates[2];
   int rownum;
   int columnnum;
   getCoordinates(coordinates, rownum, columnnum);

   //if coordinate location is not filled, show the possible values.
   if (board[rownum][columnnum] == 0)
   {
      // compute the values.
      int possiblenums[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9};
      computePossibleValues(board, possiblenums, rownum, columnnum);
      
      cout << "The possible values for \'" << coordinates << "\' are: ";      
      
      bool first = true;

      //   Loop through displaying possible numbers.      
      for (int i = 0; i < 9; i++)
      {

         if (possiblenums[i] != 0)
         {   
            if(first)
            {
               cout << possiblenums[i];
               first = false;
            }
            else
               cout << ", " << possiblenums[i];
         }
      }
      cout << endl << endl;
   }
   
   //if the square is filled, alert the user.
   else
      cout << "ERROR: Square \'" << coordinates << "\' is filled\n\n";
}
