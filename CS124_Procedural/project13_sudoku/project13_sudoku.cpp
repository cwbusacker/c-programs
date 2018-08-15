/***********************************************************************
* Program:
*    Project 13, Sudoku
*    Brother Falin, CS124
* Author:
*    Chase Busacker
* Summary:
*    Sudoku Game is a program that will run the game of sudoku.
*    It can do the following:

*      Show the instructions
*      Display the board
*      Edit one square
*      Show the possible values for a square
*      Solve this board
*      Write the board to a temporary save file
*      Revert back to temporary save file
*      Save and Quit
*
*    Estimated:  8.0 hrs
*    Actual:     16.0 hrs
************************************************************************/
#include <iostream>
#include <fstream>
#include <string>
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
void executeCommand(char command, int board[][COLS], int saved[][COLS], bool & isSaved);
void editSquare(int board[][COLS]);
string getSaveFilename(string filename);
void saveFilename(string filename, int board[][COLS]);
void displayPossibleValues(int board[][COLS]);
void solveBoard(int board[][COLS], int & numSolutions);
void backtrackSolve(int board[][COLS], vector <RCandPoss> markUp, int & numSolutions);
void computePossibleValues(int board[][COLS], int possibles[], int rowNum, int columnNum);
void getBoxRange(int row, int col, int & minR, int & maxR, int & minC, int & maxC);
void copyBoard(int fromme[][COLS], int tome[][COLS]);


/**********************************************************************
 * MAIN calls each function and creates the main variables to run the
 * program. Also, the while loop will loop the commands until the user
 * wants to save the board.
 ***********************************************************************/
int main()
{
   //variable declarations
   int board[ROWS][COLS];
   int saved[ROWS][COLS];
   int readtest;
   string filename;
   char command;
   bool isSaved = false;

   //read the file and if it fails, make the user enter it again.
   do
   {
      filename = getFilename();
      readtest = readFilename(filename, board);
      if (readtest == -1)
      {
         cout << "ERROR: Invalid Filename" << endl;
      }
   } while (readtest == -1);

   //Show the board and instructions when the game first starts
   displayInstructions();
   displayBoard(board);

   //Run the program until the user wants to 'Q'uit.
   do
   {
      command = getInstructions();
      executeCommand(command, board, saved, isSaved);
   } while (command != 'Q');

   //Get the new file name the user would like to save the board to. 
   do
   {
      cout << "Would you like to save the board in the same location(y/n)? ";
      cin >> command;
      command = tolower(command);
      if (command == 'n')
      {
         filename = getSaveFilename(filename);
      }
      else if (command != 'y')
      {
         cout << "Invalid command. Please try again.\n";
      }
   } while (!(command == 'y' || command == 'n'));

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
   getline(cin, filename);

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
   {
      return -1;
   }
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
/**************************************************************
* getBoxRange takes the row and col values and determines the 
* range for the box.
***************************************************************/
void getBoxRange(const int row, const int col, int & minR, int & maxR, int & minC, int & maxC)
{
   //edit max and min row
   if (row < 3)
   {
      minR = 0;
      maxR = 3;
   }
   else if (row < 6)
   {
      minR = 3;
      maxR = 6;
   }
   else
   {
      minR = 6;
      maxR = 9;
   }

   //edit max and min column.
   if (col < 3)
   {
      minC = 0;
      maxC = 3;
   }
   else if (col < 6)
   {
      minC = 3;
      maxC = 6;
   }
   else
   {
      minC = 6;
      maxC = 9;
   }
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
   cout << "   W  Write the board to a temporary save file\n";
   cout << "   R  Revert back to temporary save file\n";
   cout << "   Q  Save and Quit\n\n";
}

/**********************************************************************
 * displayBoard displays the board to the user.
 ***********************************************************************/
void displayBoard(int board[][COLS]) {

   cout << "   A B C D E F G H I\n";

   for (int r = 0; r < ROWS; r++)
   {
      cout << r + 1 << "  ";
      for (int c = 0; c < COLS; c++)
      {
         //NUMBERS NOT ZERO
         if (board[r][c] != 0)
         {
            //right before a gridline
            //therefore, just display the number (gridline placement)
            if (c == 2 || c == 5 || c == 8)
            {
               cout << board[r][c];
            }
            //not before a gridline
            //display the number AND a space
            else if ( c != 2 && c != 5)
            {
               cout << board[r][c] << " ";
            }
         }
         //NUMBER IS 0 (meaning blank space on the board)
         else
         {
            //right before a gridline
            //display a single space
            if (c == 2 || c == 5 || c == 8)
            {
               cout << " ";
            }
            //not before a gridline
            //display a double space
            else if (c != 2 && c != 5)
            {
               cout << "  ";
            }
         }

         //anytime there is a column of 3 or 6 display a |
         if (c != COLS - 1 && c == 2 || c == 5)
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

   return toupper(command);
}

/**********************************************************************
 * executeCommand will read the command given and tell a function to
 * run depending on the command given.
 ***********************************************************************/
void executeCommand(char command, int board[][COLS], int saved[][COLS], bool & isSaved)
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
      int numSolutions = 0;
   
      copyBoard(board, saved);
      solveBoard(board, numSolutions);
      //attempt to solve the board.
      if (numSolutions == 1)
      {
         cout << "\nSolve Successful\n";
         displayBoard(board);
      }
      //if it could not be solved, then the board is unsolvable.
      else if(numSolutions == 0)
      {
         copyBoard(saved, board);
         cout << "\nInvalid board. No Solutions.\n";
      }
      else
      {
         copyBoard(saved, board);
         cout << "\nInvalid Board. Multiple Solutions.\n";
      }
      
   }
   else if (command == 'R')
   {
      if (isSaved)
      {
         copyBoard(saved, board);
         cout << "\nReverted Successfully\n";
      }
      else
      {
         cout << "\nERROR: No Saved Board.\n";
      }
   }
   else if (command == 'W')
   {
      copyBoard(board, saved);
      cout << "\nTemporary Save Successfully\n";
      isSaved = true;
   }
   //Quit by returning.
   else if (command == 'Q')
   {
      return;
   }
   //uh oh! Invalid command. User must try again.
   else
   {
      cout << "ERROR: Invalid command" << endl;
   }
}

/**********************************************************************
* SolveBoard can be broken into 4 sections of solving attempts.
*
* 1. SINGLE POSSIBLE VALUE:Loop through all the possible values of the empty squares and
*    edit them if they only have a single value.
*
* 2. UNIQUE ROW CANDIDIDATES: Check the possible values of a given square
*    and if it has a unique value when compared to the rows then edit the square.
*
* 3. UNIQUE COLUMN CANDIDATES: Same as #2 except comparing to columns.
*
* 4. UNIQUE BOX CANDIDATES: Same as #2 except comparing to numbers in the box.
*
* Every time a square is edited, the function is called recursively
* because the first section creates a vector of the possible values for
* each empty square, and those values will change each time an edit takes
* place.
***********************************************************************/
void solveBoard(int board[][COLS], int & numSolutions)
{
   //Making sure there is not more than 1 solution.
   if (numSolutions > 1)
   {
      return;
   }
   vector <RCandPoss> markUp; //A "Markup" Of the board (A list of coordinates and their possible values.
   RCandPoss mark; //a mark in one square
   vector <int> possVec; //vector of possible values in a square (depending on the case)
   int possibles[9] = { 1,2,3,4,5,6,7,8,9 }; //array of possibles

/************** SECTION 1: SINGLE POSSIBLE VALUE  *************
****************************************************************/
//Loop through row and columns
   for (int r = 0; r < 9; r++)
   {
      for (int c = 0; c < 9; c++)
      {
         //if the row and column already has a value, move on to the next column or row.
         if (board[r][c] != 0)
         {
            continue;
         }
         //possVec needs to clear before we start building the possible values for this square.
         possVec.clear();

         //computePossibleValues to edit our possibles array.
         computePossibleValues(board, possibles, r, c);

         //loop through the possibles value array and add nonzeros to the possVec vector.
         for (int p = 0; p < 9; p++)
         {
            if (possibles[p] != 0)
            {
               possVec.push_back(possibles[p]);
            }
            //change the value back to it's correct number if it is a zero (used for the next time)
            else
            {
               possibles[p] = p + 1;
            }
         }

         //possVec only had 1 value in it. Edit the square!
         if (possVec.size() == 1)
         {
            board[r][c] = possVec[0];
            solveBoard(board, numSolutions);
            return;

         }

         //otherwise, store the coordinate and possibles in markUp.
         else
         {
            mark.c = c; //column
            mark.r = r; //row
            mark.possibles = possVec; 
            markUp.push_back(mark); 
         }
      }
   }

   //If the markUp is empty, that means we didn't have any coordinates
   //that needed filled, the board is solved.
   if (markUp.empty())
   {
      numSolutions += 1;
      return;
   }
   //More complex algorithm looping through the whole markup
   for (unsigned int i = 0; i < markUp.size(); i++)
   {
      /***********  SECTION 2: UNIQUE CANDIDATE IN ROW ***********
      ************************************************************/

      mark = markUp[i]; //mark is the current square we are looking at
      possVec = mark.possibles; //possVec is it's possibles.
      unsigned int j = i;

      //Set j to be the lowest index in markUp that has the same row value as mark
      while (j > 0 && mark.r == markUp[j].r)
      {
         j--;
      }

      //loop while j is in the range of markup, the rows mark and markUp[j] match
      //and possVec isn't empty (if it is there aren't any unique values).
      while (j < markUp.size() && mark.r == markUp[j].r && !possVec.empty())
      {
         //if j and i are equal we want to make sure we can increment and 
         //then increment.
         if (j == i && (j + 1) < markUp.size() && markUp[j + 1].r == mark.r)
         {
            j++;
         }
         //if we are going out of bounds, break out.
         else if ((j + 1) == markUp.size())
         {
            break;
         }

         //erase any matches.
         for (unsigned int p = 0; p < possVec.size(); p++)
            for (unsigned int q = 0; q < markUp[j].possibles.size() && p < possVec.size(); q++)
            {
               if (possVec[p] == markUp[j].possibles[q])
               {
                  possVec.erase(possVec.begin() + p);

               }
            }
         //increment to the next one.
         j++;
      }

      //If the PossVec has only one value in it, then the value is unique so edit the board.
      if (possVec.size() == 1)
      {
         board[mark.r][mark.c] = possVec[0];
         solveBoard(board, numSolutions);
         return;
      }

      /***********  SECTION 3: UNIQUE CANDIDATE IN COLUMN ***********
      ***************************************************************/
      //Reset possvec
      possVec = mark.possibles;

      //j starts at 0 this time. We want to loop through all the markUp
      //columns are out of order and we have to search.
      j = 0;

      //looping while the possVec isn't empty and j is in range - breaks inside.
      while (!possVec.empty()) 
      {
         //increase j until columns match or j is out of bounds. (But make sure j doesn't equal i)
         while (j < (int)markUp.size() && (mark.c != markUp[j].c || j == i))
         {
            j++;
         }
         
         //if j is not in bounds, then break.
         if (j == markUp.size())
         {
            break;
         }

         //erase if a match is found.
         for (unsigned int p = 0; p < possVec.size(); p++)
         {
            for (unsigned int q = 0; q < markUp[j].possibles.size() && p < possVec.size(); q++)
            {
               if (possVec[p] == markUp[j].possibles[q])
               {
                  possVec.erase(possVec.begin() + p);
               }
            }
         }

         //also increment j here so that we can look
         //at different indexes (otherwise we will be stuck looking at the current item at j)
         j++;
      }

      //if possVec's size is one edit and start over.
      if (possVec.size() == 1)
      {
         board[mark.r][mark.c] = possVec[0];
         solveBoard(board, numSolutions);
         return; 
      }
      /***********  SECTION 4: UNIQUE CANDIDATE IN BOX ***********
      ************************************************************/
      
      //reset the possVec
      possVec = mark.possibles;

      //declare the variables for the box range.
      int minR;
      int maxR;
      int minC;
      int maxC;

      //find the range for the location (variables above will be edited by reference)
      getBoxRange(mark.r, mark.c, minR, maxR, minC, maxC);

      j = 0;
      
      //loop while possVec isn't empty and j is in range - breaks inside
      while (!possVec.empty())
      {
         //increment j until either we find a match(where the row and column are in the box range and not i) or until j is out of range.
         while ((j < markUp.size() && !(markUp[j].r < maxR && markUp[j].r >= minR && markUp[j].c < maxC && markUp[j].c >= minC)) || j == i)
         {
            j++;
         }
         //if j is out of range, we break.
         if (j == markUp.size())
         {
            break;
         }

         //erase any matches between the pairs
         for (unsigned int p = 0; p < possVec.size(); p++)
         {
            for (unsigned int q = 0; q < markUp[j].possibles.size() && p < possVec.size(); q++)
            {
              
               if (possVec[p] == markUp[j].possibles[q])
               {
                  possVec.erase(possVec.begin() + p);
               }
               
            }
         }
         j++;
      }

      //if we only have one option, then we can edit a square and try again.
      if (possVec.size() == 1)
      {
         board[mark.r][mark.c] = possVec[0];
         solveBoard(board, numSolutions);
         return;
      }
   }
   //If the for loop has been exited, then it has been solved as far as possible 
   //without more complex algorithms. The board is still not solved, so we must 
   //use backtracking to solve.
   backtrackSolve(board, markUp, numSolutions);
   return; 
}

/**********************************************************************
* copyBoard will copy the two dimensional arrays that are sent it
* as parameters and copy their values.
***********************************************************************/
void copyBoard(int fromme[][COLS], int tome[][COLS])
{
   for (int r = 0; r < 9; r++)
   {
      for (int c = 0; c < 9; c++)
      {
         tome[r][c] = fromme[r][c];
      }
   }
}


/**********************************************************************
* backtrackSolve will try the possible values for each square and
* see if solveBoard can solve it with that value. If it can't it
* will set the board back to the original value before it was changed.
***********************************************************************/
void backtrackSolve(int board[][COLS], vector <RCandPoss> markUp, int & numSolutions)
{
   if (numSolutions > 1)
   {
      return;
   }
   //we are only concerned about 1 square, recursion will take care of
   //the others. 
   //So declare the saveBoard and initialize the row and col integers.
   //We will save solved board to copy back to board if there is only one solution.
   int saveBoard[9][9];
   int solvedBoard[9][9];
   int row = markUp[0].r;
   int col = markUp[0].c;
   int before;
   //loop through the possible values allowed for this square.
   for (unsigned int i = 0; i < markUp[0].possibles.size(); i++)
   {
      //make a copy of the current board so we can revert back to where 
      //we are if necessary.
      copyBoard(board, saveBoard);
      
      //edit the square with the current possible value.
      board[row][col] = markUp[0].possibles[i];
      

      //check if solveBoard can solve it with the value in that position
      before = numSolutions;
      solveBoard(board, numSolutions);
      if (before + 1 == numSolutions)
      {
         copyBoard(board, solvedBoard);
      }
      if (numSolutions > 1)
      {
         return;
      }
      //it didn't work, reset the board back and try the next value.
      copyBoard(saveBoard, board);
   }
   
   //Since there was only one solution, we can copy it over to the board.
   if (numSolutions == 1)
   {
      copyBoard(solvedBoard, board);
   }
   return;
}

/**************************************************************
 * GetCoordinates will get the coordinates from the user
 * and error check to ensure they are correct.
***************************************************************/
void getCoordinates(char coordinates[], int & rowNum, int & columnNum)
{
   //set the values of row and column to allow the while loop to run.
   bool valid = false;

   while (!valid)
   {
      cout << "What are the coordinates of the square: ";
      cin >> coordinates;

      if (isalpha(coordinates[0]) && isdigit(coordinates[1]))
      {
         coordinates[0] = toupper(coordinates[0]);
         rowNum = coordinates[1] - '1';
         columnNum = coordinates[0] - 'A';
         if (rowNum < ROWS && columnNum < COLS)
            valid = true;
      }
      else if (isalpha(coordinates[1]) && isdigit(coordinates[0]))
      {
         coordinates[1] = toupper(coordinates[1]);
         rowNum = coordinates[0] - '1';
         columnNum = coordinates[1] - 'A';
         if (rowNum < ROWS && columnNum < COLS)
            valid = true;
      }
      if (!valid)
      {
         cout << "Invalid Coordinates. Please try again.";
      }
   }
}

/**************************************************************
* computePossibleValues takes an array of possible values
* and edits them so that the possible values contains only
* zeros and the possible values for the square at the row
* and column.
***************************************************************/
void computePossibleValues(int board[][COLS], int possibles[], int rowNum, int columnNum)
{
   //evaluate rows
   for (int i = 0; i < 9; i++)
   {
      if (board[rowNum][i] != 0)
      {
         possibles[board[rowNum][i] - 1] = 0;
      }
   }

   //evaluate columns
   for (int i = 0; i < 9; i++)
   {
      if (board[i][columnNum] != 0)
      {
         possibles[board[i][columnNum] - 1] = 0;
      }
   }

   //Sudoku BOX boundaries.
   int topRow;
   int bottomRow;
   int leftColumn;
   int rightColumn;

   //determine the sudoku BOX row boundaries
   getBoxRange(rowNum, columnNum, topRow, bottomRow, leftColumn, rightColumn);
  
   //remove values if in sudoku BOX
   for (topRow; topRow < bottomRow; topRow++)
   {
      for (int lc = leftColumn; lc < rightColumn; lc++)
      {
         if (board[topRow][lc] != 0)
         {
            possibles[board[topRow][lc] - 1] = 0;
         }
      }
   }


}

/**********************************************************************
 * editSquare gets a coordinate from the user and sees if it can be
 * edited. If so, it will ask the user for the number to place there.
 * Otherwise it will say that that coordinate is already full.
 ***********************************************************************/
void editSquare(int board[][COLS])
{
   //Get Coordinates for square to edit
   char coordinates[3];
   int columnnum;
   int rownum;
   getCoordinates(coordinates, rownum, columnnum);
   coordinates[2] = 0;

   //If the coordinate is filled, tell the user and return to get the next command    
   if (board[rownum][columnnum] != 0)
   {
      cout << "ERROR: Square \'" << coordinates << "\' is filled\n\n";
      return;
   }

   //compute the possible values for that square
   int possiblenums[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
   computePossibleValues(board, possiblenums, rownum, columnnum);

   //get the number that the user wants to put in the coordinates
   int newnumber;
   cout << "What is the value at \'" << coordinates << "\': ";
   cin >> newnumber;

   //if the value is acceptable, edit the board.
   if (possiblenums[newnumber - 1] != 0)
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
   getline(cin, filename);

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
   char coordinates[3];
   int rownum;
   int columnnum;
   getCoordinates(coordinates, rownum, columnnum);

   //if coordinate location is not filled, show the possible values.
   if (board[rownum][columnnum] == 0)
   {
      // compute the values.
      int possiblenums[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
      computePossibleValues(board, possiblenums, rownum, columnnum);

      cout << "The possible values for \'" << coordinates << "\' are: ";

      bool first = true;

      //   Loop through displaying possible numbers.      
      for (int i = 0; i < 9; i++)
      {

         if (possiblenums[i] != 0)
         {
            //first number! we don't want a comma before it.
            if (first)
            {
               cout << possiblenums[i];
               first = false;
            }
            else
            {
               cout << ", " << possiblenums[i];
            }
         }
      }
      cout << endl << endl;
   }

   //if the square is filled, alert the user.
   else
   {
      cout << "ERROR: Square \'" << coordinates << "\' is filled\n\n";
   }
}
