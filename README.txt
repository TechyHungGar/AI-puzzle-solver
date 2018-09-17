A sliding number puzzle game (Candy Crisis), that requires players to make one move at a time. 
This was a school project, completed by myself and my teammate Christian Kellner.

Brief view:

Move: i

	  Puzzle Grid			  Move Grid
---------------------------------------------------------------
	[b][r][r][b][w]		|	[A][B][C][D][E]
	[r][b][r][ ][b]		|	[F][G][H][I][J]
	[r][b][b][r][w]		|	[K][L][M][N][O]
---------------------------------------------------------------

The letters (or candies) around the empty slot are the possible moves (no diagonal moves allowed).
The goal of the game is to make the sequence of candies on the top row, equal to the sequence of candies on the bottom row. 

The heurisitc search will look at all the possible next moves, and go with the one that will bring the state
closer to a winning state. More detailed information about our heurisitc search can be viewed in the power point presentation commited to this repo.
