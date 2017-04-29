
 ChessGames(Console Application)
 
 Implements  Reversi Game, MagicSquare and NineAlmonds Game using C++

========================================================================
1. The NineAlmonds Game works well. 
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


2. The MagicSquare Game also works good.
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


/////////////////////////////////////////////////////////////////////////////
