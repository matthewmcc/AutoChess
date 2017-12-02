#include "stdafx.h"
#include "ChessState.h"
#include <list>
#include <map>

class ChessRules
{
public:
	static ChessRules& getInstance();

	std::list<ChessState> getMoves(ChessState &, int*);

	bool terminalTest(ChessState &);

private:
	// Singleton functions
	ChessRules();
	~ChessRules();
	ChessRules(const ChessRules &);
	const ChessRules & operator = (const ChessRules &);

	const int KNIGHT_ARRAY_LENGTH = 8;
	const int STRAIGHT_ARRAY_LENGTH = 4;
	const int DIAGONAL_ARRAY_LENGTH = 4;
	const int DIA_STRI_ARRAY_LENGTH = 8;
	const int PAWN_MOVES = 2;

	/// Possible moves of pieces
	const int KINGHT_MOVES[8][2] = { {1, 2}, {1, -2}, {2, 1}, {2, -1}, {-1, 2}, {-1, -2}, {-2, 1}, {-2, -1} };
	const int STRAIGHT_MOVES[4][2] = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };
	const int DIAGONAL_MOVES[4][2] = { {1, 1}, {1, -1}, {-1, 1}, {-1, -1} };
	const int DIA_STRI_MOVES[8][2] = { {1, 0}, {0, 1}, {-1, 0}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1} };
	const int PAWN_ATTACK_MOVES_WHITE[2][2] = { {-1, -1}, {1, -1} };
	const int PAWN_ATTACK_MOVES_BLACK[2][2] = { {-1, 1}, {1, 1} };
	int PAWN_WHITE_MOVES[2][2] = { {0, -1}, {0, -2} };
	int PAWN_BLACK_MOVES[2][2] = { { 0, 1 },{ 0, 2 } };

	const int BLACK_PAWN_START_ROW = 1;
	const int WHITE_PAWN_START_ROW = 6;

	std::map<char, int> PIECE_VALUES = { {'_', 0}, {'p', 1}, {'n', 3}, {'b', 3}, {'r', 5}, {'q', 9}, {'k', 100} };

	// These functions are divided by piece color for effiency.
	inline std::list<ChessState> getBlackMoves(ChessState &, int*);
	inline std::list<ChessState> getWhiteMoves(ChessState &, int*);

	inline std::list<ChessState> getBlackPawnMoves(ChessState &, int*);
	inline std::list<ChessState> getWhitePawnMoves(ChessState &, int*);

	inline bool isWhiteInCheck(ChessState &, int*);
	inline bool isBlackInCheck(ChessState &, int*);

	// Get all possible moves for a piece of a certain type
	inline std::list<ChessState> getRookMoves(ChessState &, int*);
	inline std::list<ChessState> getKnightMoves(ChessState &, int*);
	inline std::list<ChessState> getBishopMoves(ChessState &, int*);
	inline std::list<ChessState> getQueenMoves(ChessState &, int*);
	inline std::list<ChessState> getKingMoves(ChessState &, int*);

	inline ChessState createState(ChessState &state, int* pieceToMove, int* move);
	inline void makeMove(ChessState &state, int heurisVal, bool maxPlayer, char movePlay);

	// Gets a pieces location
	inline int* getPieceLoc(ChessState &, char);

	// Checks if the emptyed move is on the board. 
	inline bool inRange(int *);
};

