/* 
 * File:   baffle.cpp
 * Author: ronald_baasland
 *
 * Created on November 7, 2010, 6:53 PM
 * Modified on November 15, 2010
 *
 * This program is a game that consists of a two-dimensional black box with
 * numbers between 0 and 39 on all sides.
 *
 * There are a number of obstructions, called baffles, which you cannot see,
 * placed in the box. The object of the game is to find the baffles. You select
 * a number between 0 and 39, which activates a laser beam originating at that
 * location. You are then told where the beam leaves the box. If the beam does
 * not encounter a baffle, it will exit directly opposite to where it entered.
 * If the beam encounters a baffle, it will be deflected at right angles, either
 * right or left, depending on the direction of the baffle. You can locate the
 * baffles by shooting beams into the box, using the deflections of the beams as
 * hints to the placement of the direction of the baffles.
 */

#include <iostream> //For input and output to the console
#include <cstdlib> //For random number generator
#include <iomanip> //To manipulate output to the console
using namespace std;

//All the protocols for the functions.
void setGrid(int[][12]);
void setBaffle(int[][12], int);
void display();
void printGrid(int[][12]);
void guessBaffle(int[][12],int,int);
void laserShot(int[][12],int);

int main()
{
    char choice; //Varivale for menu choice
    int level; // variable for the difficulty choice
    int arr[12][12]; // Declaration for the main array
    setGrid(arr); // Set the numbers in the 12 x 12 array
    int shot; // variable to get location to shoot from
    int shots = 0; //Counter for number of shots
    bool location; //boolean to show if the shot is in bounds
    int guesses; //Counter to keep track of guesses
    int totalScore; //Variable to keep track of the total score

    cout << "Welcome!" << endl;

   //Do while loop to validate the difficulty level
    do
    {
        cout << "Please enter your difficulty level" << endl;
        cout << "1 - Beginner" << endl;
        cout << "2 - Intermediate" << endl;
        cout << "3 - Advanced" << endl;
        cout << "Your difficulty: ";
        cin >> level;
    }
    while (level < 1 || level > 3);

    //The next if statement sets the amount of baffles depending on difficulty
    if (level == 1)
        setBaffle(arr,4);
    else if (level == 2)
        setBaffle(arr,7);
    else
        setBaffle(arr,10);

    //This do while loop validates the input for the menu
    do
    {
        //Displays the menu options
        cout << endl;
        cout << "Please select your choice from then menu" << endl;
        cout << "'L' or 'l' - Laser shot(Input a location to shoot from(0 - 39)" << endl;
        cout << "'G' or 'g' - Guess(Input the location 1 - 10)(example:x = 3 , y = 5)" << endl;
        cout << "'S' or 's' - Score (Displays your score)" << endl;
        cout << "'P' or 'p' - Print the current grid showing the baffles you found" << endl;
        cout << "'Q' or 'q' - Quit" << endl;
        cout << "'A' or 'a' - Print all the baffles" << endl;
        cin >> choice;
        cout << endl;

        int x,y;
        switch(choice)
        {
           case 'a':
           case 'A':
                printGrid(arr);
                break;
            case 'g':
            case 'G':
                cout << "x = ";
                cin >> x;
                cout << "y = ";
                cin >> y;
                guesses++;
                guessBaffle(arr,x,y);
                break;
            case 'l':
            case 'L':
                location = false;
                cout << "Please enter the location to shoot from" << endl;
                cin >> shot;
                shots++;
                while (location != true)
                {
                    if (shot < 0 || shot > 39)
                    {
                        cout << "Invalid shot! (Must be 0 - 39)" << endl;
                        cout << "Please enter the location to shoot from" << endl;
                        cin >> shot;
                    }
                    else
                        location = true;

                }
                cout << "laser shot #" << shots<< " exited the box at ";
                laserShot(arr,shot);
                break;
            case 'p':
            case 'P':
                display();
                break;
            case 's':
            case 'S':
                cout << "Number of shots: " << shots << endl;
                cout << "Number of guesses: " << guesses << endl;
                totalScore = (2*guesses) + shots;
                cout << "Current Score: " << totalScore << endl;
                break;
            case 'q':
            case 'Q':
                choice = 'q';
                break;
            default:
                cout << endl;

        }
    }

    while(choice != 'q');

    return 0;
}

/* setBaffle
 *
 *This function assigns baffles based on the difficulty level
 */


void setBaffle(int arr[][12], int baffles)
{
    int x;
    int y;
    srand((unsigned)time(0));
    for(int i = 0; i < baffles; i++)
    {
     x = (rand()%10)+1; //Sets a random number between 1 and 10
     y = (rand()%10)+1; //sets a random number between 1 and 10
     arr[x][y] = (rand()%2)+1;
    }
}

/* setGrid
 *
 * This function sets up a 12 X 12 grid with numbers 0 - 39 going around it
 */


void setGrid(int arr[][12])
{
    for (int i = 1; i < 11; i++)
    {
        arr[0][i] = i + 9;
    }

    for(int i = 1; i < 11; i++)
    {
        for(int j = 1; j < 11; j++)
        {
            arr[i][j] = 0;
        }
    }

    for(int i = 1; i <= 10; i++)
    {
        arr[i][0] = 10 - i;
        arr[i][11] = i + 19;

    }

    for (int i = 1; i < 11; i++)
    {
        arr[11][i] = 40 - i;

    }
}

/* printGrid
 *
 * This function displays the 12 X 12 array
 *
 */
void printGrid(int arr[][12])
{
    cout << setw(5);
    for(int i = 0; i < 12; i++)
    {
        for(int j = 0; j < 12; j++)
        {
           cout << arr[i][j] << setw(5);
        }
        cout << endl;
    }
}

/* guessBaffle
 *
 * This function takes the guess, x, and y, from the user and checks to see if
 * its a baffle. if it is, it displays you found a baffle, if not it says better
 * luck next time.
 *
 */


void guessBaffle(int arr[][12], int x, int y)
{
    if(arr[x][y] == 1 || arr[x][y] == 2)
        cout << "Congratulations you found a baffle!" << endl;
    else
        cout << "Sorry, better luck next time" << endl;
}


/* laserShot
 *
 * This function will shot the laser through the position the user selects
 *
 */
void laserShot(int arr[][12],int shot)
{
    int f;
    int k;
    bool found = false;
    do
    {
        for(int i = 0; i < 12; i++)
        {
            for (int j = 0; j < 12; j++)
           {
               if (arr[i][j] == shot)
               {
                   f = i;
                   k = j;
                   found = true;
              }
          }
      }
    }
    while (found != true);

    if (f == 0)
    {
        for (f; f < 12; f++)
        {
            if (f == 11)
                cout << arr[f][k] << endl;
        }
    }
    if (f == 11)
    {
         for (f; f >= 0; f--)
        {
            if (f == 0)
                cout << arr[f][k] << endl;
        }
    }
    if (k == 0)
    {
        for (k; k < 12; k++)
        {
            if (k == 11)
                cout << arr[f][k] << endl;
        }
    }
    if (k == 11)
    {
        for (k; k >= 0; k--)
        {
            if (k == 0)
                cout << arr[f][k] << endl;
        }
    }
}

/* display
 *
 * This function displays an array without the baffles
 *
 */

void display()
{
    int arr[12][12];
    arr[0][0] = 0;
    arr[0][11] = 0;
    arr[11][0] = 0;
    arr[11][11] = 0;

    for (int i = 1; i < 11; i++)
    {
        arr[0][i] = i + 9;
    }

    for(int i = 1; i < 11; i++)
    {
        for(int j = 1; j < 11; j++)
        {
            arr[i][j] = 0;
        }
    }

    for(int i = 1; i <= 10; i++)
    {
        arr[i][0] = 10 - i;
        arr[i][11] = i + 19;

    }

    for (int i = 1; i < 11; i++)
    {
        arr[11][i] = 40 - i;

    }

    cout << setw(5);
    for(int i = 0; i < 12; i++)
    {
        for(int j = 0; j < 12; j++)
        {
           cout << arr[i][j] << setw(5);
        }
        cout << endl;
    }

}