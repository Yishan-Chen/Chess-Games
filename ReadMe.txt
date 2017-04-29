========================================================================
    CONSOLE APPLICATION : Lab4G Project Overview
========================================================================
Team members: Novi Wang, Eason Chen
1. The NineAlmonds Game works well as before. 
When enter "[projectname] NineAlmonds", the game board shows up.
You can play it by inputing coordinate, for example, you enter 2,2 for the start position and 2,0 for end.
4
3   A A A
2   A   A
1   A   A
0     A
X 0 1 2 3 4
2,2 to 2,0
Then you can choose to continue this turn or not. 
When you enter "quit" to exit the game, and it will ask do you want to save it or not.
If you enter "y", then the game is saved and the next time you open the game, it automatically recover the saved game board  
*************************
prompt:
1.Input a valid coordinate of a square on the board, such as (x,x)
2. Quit the game(Input 'quit')
quit
Do you want to save the game(y/n)
y
1 turns were played
H:\My Documents\Visual Studio 2015\Projects\Lab4G\Debug>Lab4G.exe NineAlmonds

4
3   A A A
2   A   A
1   A   A
0     A
X 0 1 2 3 4
Tip: Please input two valid coordinates

prompt:
1.Input a valid coordinate of a square on the board, such as (x,x)
2. Quit the game(Input 'quit')
**************************************************
For this game, we just use the copy-assignment operator when assigning The nine almonds game to the base game. We don't need 
any copy constructor, move sonstructor or destructor as we don't need to copy or refer the nine almonds game object. We have 
a method that initialize everything. We just call this function when we need a new game. We don't have move
assignment as we don't need to set an object’s value by transferring the implementation from the r-value reference passed to it.
In our design, it's unnecessary to create multiple NineAlmonds objects. So we just use copy assignment operator.


2. The MagicSquare Game works good as before.
When enter "[projectname] MagicSquare", the game board shows up.
You can play it by inputing coordinate and value, for example, you enter 0,0 then enter 4.
***************************

prompt:
1.Input a valid coordinate of a square on the board, such as (x,x)
2. Quit the game(Input 'quit')
0,0
Please enter quit or the value of the piece
4

2
1
0 4
X 0 1 2
Available pieces: 1 2 3 5 6 7 8 9
******************************************
Whenever it promps up for inputing coordinate or value, you can choose to enter "quit" to exit the game.
Then it will ask you if you want to save it or not.
Same as the NineAlmonds Game, the next time you enter "[projectname] MagicSquare" it will automatically present the saved game
board and you can continue your previous game.
********************************************************
quit
Do you want to save the game(y/n)
y
1 turns were played
H:\My Documents\Visual Studio 2015\Projects\Lab4G\Debug>Lab4G.exe MagicSquare

2
1
0 4
X 0 1 2
Available pieces: 1 2 3 5 6 7 8 9

prompt:
1.Input a valid coordinate of a square on the board, such as (x,x)
2. Quit the game(Input 'quit')
**************************************************************
For this game, we also just use the copy-assignment operator when assigning magicsquare game to the base game. We don't need 
any copy constructor, move sonstructor or destructor as we don't need to copy or refer the MagicSquare game object. We also 
don't have move assignment as we don't need to set an object’s value by transferring the implementation from the r-value reference passed to it.
As before, in our design, it's unnecessary to create multiple MagicSquare objects or refering and copying it. We just read from 
file and reset the variables. So we just use copy assignment operator.

3. Reversi Game also works good.
When enter "[projectname] Reversi player1 player2", the game board shows up. The third command is the name for first player and
the fourth command is the name for the second player. The first player plays first with the black piece which is represented by
"X", and the second player keeps the white piece which is represented by "O".
You need to enter the coordinate of your next step. And it will not let you enter "invalid move". For example, if you play first 
and enter 0,0   it doesn't change the color of any white piece, and it will ask you to reenter a valid move like 2,3.
***************************************************************

prompt:
1.Input a valid coordinate of a square on the board, such as (x,x)
2. Quit the game(Input 'quit')
0,0

illegal moves, please input again
64

7

6

5

4       X O

3       O X

2

1

0

X 0 1 2 3 4 5 6 7
plyaer1 is a player2 is b current player is a turn is 0

It's a's turn to play
all valid black

prompt:
1.Input a valid coordinate of a square on the board, such as (x,x)
2. Quit the game(Input 'quit')
2,3
27
64

7

6

5

4       X O

3     X X X

2

1

0

X 0 1 2 3 4 5 6 7
plyaer1 is a player2 is b current player is b turn is 1

It's b's turn to play

prompt:
1.Input a valid coordinate of a square on the board, such as (x,x)
2. Quit the game(Input 'quit')
********************************************************************
When one player has no more valid move but the board is still empty, then it directly goes to the other player's turn
The game keeps going until No empty place left in the game board, and the person who has more pieces wins.
**************************************************
7 O X X X X O O O

6 X O O X X X X X

5 X X X O X O X X

4 X X O X X X X X

3 X O X X X X O X

2 X X X X X X X X

1 X X X X X X X X

0 X X X X X X X X

X 0 1 2 3 4 5 6 7

60 turns it took to complete the game successfully
*********************************************************
For this game, although there are two players, we still just use the copy-assignment operator when assigning reversi game to 
the base game. We don't need any copy constructor, move sonstructor or destructor as we don't need to copy or refer the 
Reversi game object. We also don't have move assignment as we don't need to set an object’s value by transferring the implementation 
from the r-value reference passed to it. As before, in our design, it's unnecessary to create multiple Reversi objects or refering
 and copying it. We just read from file, get the previous two players and the one who is going to play. The file also have aline
that holds all game piece displays. So we just need to read the line and recreate the gamepiece array. Also, the initialize function
handles everything when we need a new game.
========================================================================

AppWizard has created this Lab4G application for you.

This file contains a summary of what you will find in each of the files that
make up your Lab4G application.


Lab4G.vcxproj
    This is the main project file for VC++ projects generated using an Application Wizard.
    It contains information about the version of Visual C++ that generated the file, and
    information about the platforms, configurations, and project features selected with the
    Application Wizard.

Lab4G.vcxproj.filters
    This is the filters file for VC++ projects generated using an Application Wizard. 
    It contains information about the association between the files in your project 
    and the filters. This association is used in the IDE to show grouping of files with
    similar extensions under a specific node (for e.g. ".cpp" files are associated with the
    "Source Files" filter).

Lab4G.cpp
    This is the main application source file.

/////////////////////////////////////////////////////////////////////////////
Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named Lab4G.pch and a precompiled types file named StdAfx.obj.

/////////////////////////////////////////////////////////////////////////////
Other notes:

AppWizard uses "TODO:" comments to indicate parts of the source code you
should add to or customize.

/////////////////////////////////////////////////////////////////////////////
