#pragma once
#include <map>

namespace AutoChess {
	/// Possible moves of pieces
	const int KNIGHT_MOVES[8][2] = { { 1, 2 },{ 1, -2 },{ 2, 1 },{ 2, -1 },{ -1, 2 },{ -1, -2 },{ -2, 1 },{ -2, -1 } };
	const int STRAIGHT_MOVES[4][2] = { { 1, 0 },{ 0, 1 },{ -1, 0 },{ 0, -1 } };
	const int DIAGONAL_MOVES[4][2] = { { 1, 1 },{ 1, -1 },{ -1, 1 },{ -1, -1 } };
	const int DIAGONAL_STRAIGHT_MOVES[8][2] = { { 1, 0 },{ 0, 1 },{ -1, 0 },{ 0, -1 },{ 1, 1 },{ 1, -1 },{ -1, 1 },{ -1, -1 } };
	const int WHITE_PAWNS_ATTACK_MOVES[2][2] = { { -1, -1 },{ -1, 1 } };
	const int BLACK_PAWNS_ATTACK_MOVES[2][2] = { { 1, -1 },{ 1, 1 } };
	const int WHITE_PAWNS_MOVES[2][2] = { { -1, 0 },{ -2, 0 } };
	const int BLACK_PAWNS_MOVES[2][2] = { { 1, 0 },{ 2, 0 } };

	/// Lengths of all the arrays above.
	const int KNIGHT_ARRAY_LENGTH = 8;
	const int STRAIGHT_ARRAY_LENGTH = 4;
	const int DIAGONAL_ARRAY_LENGTH = 4;
	const int DIAGONAL_STRAIGHT_ARRAY_LENGTH = 8;
	const int PAWN_MOVES_ARRAY_LENGTH = 2;

	const int BLACK_PAWN_START_ROW = 1;
	const int BLACK_PAWN_END_ROW = 7;
	const int WHITE_PAWN_START_ROW = 6;
	const int WHITE_PAWN_END_ROW = 0;

	const int BLACKS_LOWEST_ASCII_VALUE = 97;
	const int WHITES_HIGHEST_ASCII_VALUE = 90;

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
	const std::map<char, int> PIECE_VALUES = { { EMPTY_TILE, 0 },
	{ BLACK_PAWN, 1 },{ WHITE_PAWN, 1 },
	{ BLACK_KNIGHT, 3 },{ WHITE_KNIGHT, 3 },
	{ BLACK_BISHOP, 3 },{ WHITE_BISHOP, 3 },
	{ BLACK_ROOK, 5 },{ WHITE_ROOK, 5 },
	{ BLACK_QUEEN, 9 },{ WHITE_QUEEN, 9 },
	{ BLACK_KING, 100 },{ WHITE_KING, 100 }, };

	const int PAWN_UPGRADE = BLACK_QUEEN - BLACK_PAWN;
}