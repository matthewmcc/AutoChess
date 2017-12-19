#pragma once
#include <map>

namespace AutoChess {
	/// Possible moves of pieces
	const int KNIGHT_MOVES[8][2] = { { 1, 2 },{ 1, -2 },{ 2, 1 },{ 2, -1 },{ -1, 2 },{ -1, -2 },{ -2, 1 },{ -2, -1 } };
	const int STRAIGHT_MOVES[4][2] = { { 1, 0 },{ 0, 1 },{ -1, 0 },{ 0, -1 } };
	const int DIAGONAL_MOVES[4][2] = { { 1, 1 },{ 1, -1 },{ -1, 1 },{ -1, -1 } };
	const int DIA_STRI_MOVES[8][2] = { { 1, 0 },{ 0, 1 },{ -1, 0 },{ 0, -1 },{ 1, 1 },{ 1, -1 },{ -1, 1 },{ -1, -1 } };
	const int PAWN_ATTACK_MOVES_WHITE[2][2] = { { -1, -1 },{ 1, -1 } };
	const int PAWN_ATTACK_MOVES_BLACK[2][2] = { { -1, 1 },{ 1, 1 } };
	int PAWN_WHITE_MOVES[2][2] = { { 0, -1 },{ 0, -2 } };
	int PAWN_BLACK_MOVES[2][2] = { { 0, 1 },{ 0, 2 } };

	/// Lengths of all the arrays above.
	const int KNIGHT_ARRAY_LENGTH = 8;
	const int STRAIGHT_ARRAY_LENGTH = 4;
	const int DIAGONAL_ARRAY_LENGTH = 4;
	const int DIA_STRI_ARRAY_LENGTH = 8;
	const int PAWN_MOVES = 2;

	const int BLACK_PAWN_START_ROW = 1;
	const int WHITE_PAWN_START_ROW = 6;

	// Player declarers
	const char WHITE_PLAYER = 'W';
	const char BLACK_PLAYER = 'B';

	// Piece charaters values
	static const char WHITE_PAWN = 'P';
	static const char WHITE_ROOK = 'R';
	static const char WHITE_BISHOP = 'B';
	static const char WHITE_KNIGHT = 'N';
	static const char WHITE_QUEEN = 'Q';
	static const char WHITE_KING = 'K';

	static const char BLACK_PAWN = 'p';
	static const char BLACK_ROOK = 'r';
	static const char BLACK_BISHOP = 'b';
	static const char BLACK_KNIGHT = 'n';
	static const char BLACK_QUEEN = 'q';
	static const char BLACK_KING = 'k';

	const char EMPTY_TILE = '_';

	// Heuristic values of all the pieces
	std::map<char, int> PIECE_VALUES = { { EMPTY_TILE, 0 },
	{ BLACK_PAWN, 1 },{ WHITE_PAWN, 1 },
	{ BLACK_KNIGHT, 3 },{ WHITE_KNIGHT, 3 },{ 'b', 3 },{ 'r', 5 },{ 'q', 9 },{ 'k', 100 } };
}