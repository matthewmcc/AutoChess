/// Board state structure

/// Character array structure
/// X 01234567
/// 0 WBWBWBWB
/// 1 BWBWBWBW
/// 2 WBWBWBWB
/// 3 BWBWBWBW
/// 4 WBWBWBWB
/// 5 BWBWBWBW
/// 6 WBWBWBWB
/// 7 BWBWBWBW

/// Chess Piece ascii representation
/// White pieces upper case and Black pieces lower case
/// Pawn = P, Rook = R, Knight = N, Bishop = B, Queen= Q and King = K;

/// LastMove structure
///		X					0									1
///		0 X coord of last moved pieces previous location.	Y coord
///		1 X coord of pieces new location on this state.		X coord

/// Current turn is either equal to 'W' or 'B'

/// Black is represented by lower case (DEC ASCII 97 >=) and White by UPPERCASE (DEC ASCII 90 =<).

#pragma once
class ChessState
{
public:
	// Initializes the new state as the game start state
	ChessState();
	ChessState(char *state, int *lastMove);
	~ChessState();

	void initNewBoard();

	char boardState[8][8];// [8][8];
	int lastMove[2][2];// [2][2];
	char movePlayer;
	int heuristicVal; 
	bool maxPlayer;
};



