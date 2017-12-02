#include "stdafx.h"
#include "ChessRules.h"
#include <algorithm>
#include <list>

ChessRules::ChessRules() {}
ChessRules::~ChessRules() {}

// Function to insure class is only used as singleton.
ChessRules& ChessRules::getInstance()
{
	static ChessRules instance;
	return instance;
}

/// Is the king in check?
///		If not can another piece on that team move?
///	else
///		can the king move.
///			No? can a piece block the check?
///
bool ChessRules::terminalTest(ChessState &currState) {
	int kingLoc[2];

	/// Black moves
	if (currState.movePlayer == 'B') {
		if (isBlackInCheck(currState, kingLoc))
	}
	else {

	}
}

std::list<ChessState> ChessRules::getWhiteMoves(ChessState &currState, int * pieceToMove) {
	char pieceType;
	std::list<ChessState> moves = std::list<ChessState>();

	// Checks every place on the board for black pieces and then
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			pieceType = currState.boardState[pieceToMove[i]][pieceToMove[j]];
			if (pieceType <= 90) {
				// Calls the correct move function given the piece to move.
				switch (pieceType)
				{
				case 'P': {
					moves.merge(getWhitePawnMoves(currState, pieceToMove));
					break;
				}
				case 'R': {
					moves.merge(getRookMoves(currState, pieceToMove));
					break;
				}
				case 'N': {
					moves.merge(getKnightMoves(currState, pieceToMove));
					break;
				}
				case 'B': {
					moves.merge(getBishopMoves(currState, pieceToMove));
					break;
				}
				case 'Q': {
					moves.merge(getQueenMoves(currState, pieceToMove));
					break;
				}
				case 'K': {
					moves.merge(getKingMoves(currState, pieceToMove));
					break;
				}
				default:
					break;
				}
			}
		}
	}

	return moves;
}

std::list<ChessState> ChessRules::getBlackMoves(ChessState &currState, int * pieceToMove)
{
	char pieceType;
	std::list<ChessState> moves = std::list<ChessState>();

	// Checks every place on the board for black pieces and then
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			pieceType = currState.boardState[pieceToMove[i]][pieceToMove[j]];
			if (pieceType >= 97) {
				// Calls the correct move funciton given the piece to move.
				switch (pieceType)
				{
				case 'p': {
					moves.merge(getBlackPawnMoves(currState, pieceToMove));
					break;
				}
				case 'r': {
					moves.merge(getRookMoves(currState, pieceToMove));
					break;
				}
				case 'n': {
					moves.merge(getKnightMoves(currState, pieceToMove));
					break;
				}
				case 'b': {
					moves.merge(getBishopMoves(currState, pieceToMove));
					break;
				}
				case 'q': {
					moves.merge(getQueenMoves(currState, pieceToMove));
					break;
				}
				case 'k': {
					moves.merge(getKingMoves(currState, pieceToMove));
					break;
				}
				default:
					break;
				}
			}
		}
	}

	return moves;
}

/// Given the current state and the current black pawn to move. All possible states are calculated and returned.
inline std::list<ChessState> ChessRules::getBlackPawnMoves(ChessState &currState, int *pawnToMove) {
	std::list <ChessState> moves = std::list<ChessState>();
	int moveTo[2];

	char movingPiece = currState.boardState[pawnToMove[0]][pawnToMove[1]];

	if (currState.boardState[pawnToMove[0]][pawnToMove[1] + 1] == '_') {
		moves.push_back(createState(currState, pawnToMove, *PAWN_BLACK_MOVES));
	}

	// Checks if the pawn is in the first position.
	if (pawnToMove[1] = BLACK_PAWN_START_ROW) {
		moves.push_back(createState(currState, pawnToMove, *PAWN_BLACK_MOVES + 2));
	}

	// Checks if either of the pawn offensive moves are viable.
	for (int i = 0; i < PAWN_MOVES; i++) {
		moveTo[0] = pawnToMove[0] + (PAWN_ATTACK_MOVES_BLACK[i][0]);
		moveTo[1] = pawnToMove[1] + (PAWN_ATTACK_MOVES_BLACK[i][1]);

		if (inRange(moveTo)) {
			if (currState.boardState[moveTo[0]][moveTo[1]] <= 90)
				moves.push_back(createState(currState, pawnToMove, moveTo));
		}
	}
}

/// Given the current state and the current white pawn to move. All possible states are calculated and returned.
inline std::list<ChessState> ChessRules::getWhitePawnMoves(ChessState &currState, int *pawnToMove) {
	std::list <ChessState> moves = std::list<ChessState>();
	int moveTo[2];

	char movingPiece = currState.boardState[pawnToMove[0]][pawnToMove[1]];

	if (currState.boardState[pawnToMove[0]][pawnToMove[1] + 1] == '_') {
		moves.push_back(createState(currState, pawnToMove, *PAWN_WHITE_MOVES));
	}

	// Checks if the pawn is in the first position.
	if (pawnToMove[1] = WHITE_PAWN_START_ROW) {
		moves.push_back(createState(currState, pawnToMove, *PAWN_WHITE_MOVES + 2));
	}

	// Checks if either of the pawn offensive moves are viable.
	for (int i = 0; i < PAWN_MOVES; i++) {
		moveTo[0] = pawnToMove[0] + (PAWN_ATTACK_MOVES_WHITE[i][0]);
		moveTo[1] = pawnToMove[1] + (PAWN_ATTACK_MOVES_WHITE[i][1]);

		if (inRange(moveTo)) {
			if (currState.boardState[moveTo[0]][moveTo[1]] >= 97)
				moves.push_back(createState(currState, pawnToMove, moveTo));
		}
	}
}

/// Given the current state and the current rook to move. All possible states are calculated and returned.
inline std::list<ChessState> ChessRules::getRookMoves(ChessState &currState, int *rookToMove)
{
	std::list<ChessState> moves = std::list<ChessState>();
	int moveTo[2];
	int multipler;

	char movingPiece = currState.boardState[rookToMove[0]][rookToMove[1]];
	char movingTo;

	/// Checks all possible straight moves
	for (int i = 0; i < STRAIGHT_ARRAY_LENGTH; i++) {
		multipler = 1;

		moveTo[0] = rookToMove[0] + (STRAIGHT_MOVES[i][0] * multipler);
		moveTo[1] = rookToMove[1] + (STRAIGHT_MOVES[i][1] * multipler);

		while (inRange(moveTo)) {
			movingTo = currState.boardState[moveTo[0]][moveTo[1]];
			// Checks if the square been moved to is free or if the pieces involved are different case.
			if (movingTo == '_') {
				moves.push_back(createState(currState, rookToMove, moveTo));
			}
			else if ((isupper(movingTo) ^ isupper(movingPiece))) {
				moves.push_back(createState(currState, rookToMove, moveTo));

				break;
			}
			else
				break;

			multipler++;

			moveTo[0] = rookToMove[0] + (STRAIGHT_MOVES[i][0] * multipler);
			moveTo[1] = rookToMove[1] + (STRAIGHT_MOVES[i][1] * multipler);
		}
	}

	return moves;
}

/// Given the current state and the current kinght to move. All possible states are calculated and returned.
inline std::list<ChessState> ChessRules::getKnightMoves(ChessState &currState, int *knightToMove)
{
	std::list<ChessState> moves = std::list<ChessState>();
	int moveTo[2];

	char movingPiece = currState.boardState[knightToMove[0]][knightToMove[1]];
	char movingTo;

	for (int i = 0; i < KNIGHT_ARRAY_LENGTH; i++) {
		moveTo[0] = knightToMove[0] + KINGHT_MOVES[i][0];
		moveTo[1] = knightToMove[1] + KINGHT_MOVES[i][1];

		if (inRange(moveTo)) {
			movingTo = currState.boardState[moveTo[0]][moveTo[1]];
			// Checks if the square been moved to is free or if the pieces involved are different case.
			if (movingTo == '_' ||
				(isupper(movingTo)^ isupper(movingPiece))) {
				moves.push_back(createState(currState, knightToMove, moveTo));
			}
		}
	}

	return moves;
}

/// Given the current state and the current bishop to move. All possible states are calculated and returned.
inline std::list<ChessState> ChessRules::getBishopMoves(ChessState &currState, int *bishopToMove)
{
	std::list<ChessState> moves = std::list<ChessState>();
	int moveTo[2];
	int multipler;

	char movingPiece = currState.boardState[bishopToMove[0]][bishopToMove[1]];
	char movingTo;

	/// Checks all possible straight moves
	for (int i = 0; i < DIAGONAL_ARRAY_LENGTH; i++) {
		multipler = 1;

		moveTo[0] = bishopToMove[0] + (DIAGONAL_MOVES[i][0] * multipler);
		moveTo[1] = bishopToMove[1] + (DIAGONAL_MOVES[i][1] * multipler);

		while (inRange(moveTo)) {
			movingTo = currState.boardState[moveTo[0]][moveTo[1]];
			// Checks if the square been moved to is free or if the pieces involved are different case.
			if (movingTo == '_') {
				moves.push_back(createState(currState, bishopToMove, moveTo));
			}
			else if ((isupper(movingTo) ^ isupper(movingPiece))) {
				moves.push_back(createState(currState, bishopToMove, moveTo));

				break;
			}
			else
				break;

			multipler++;

			moveTo[0] = bishopToMove[0] + (DIAGONAL_MOVES[i][0] * multipler);
			moveTo[1] = bishopToMove[1] + (DIAGONAL_MOVES[i][1] * multipler);
		}
	}

	return moves;
}

/// Returns all the possible moves for a Queen
inline std::list<ChessState> ChessRules::getQueenMoves(ChessState &currState, int *queenToMove)
{
	std::list<ChessState> moves = std::list<ChessState>();
	int moveTo[2];
	int multipler;

	char movingPiece = currState.boardState[queenToMove[0]][queenToMove[1]];
	char movingTo;

	/// Checks all possible stright and diagonal moves
	for (int i = 0; i < DIA_STRI_ARRAY_LENGTH; i++) {
		multipler = 1;

		moveTo[0] = queenToMove[0] + (DIA_STRI_MOVES[i][0] * multipler);
		moveTo[1] = queenToMove[1] + (DIA_STRI_MOVES[i][1] * multipler);

		while (inRange(moveTo)) {
			movingTo = currState.boardState[moveTo[0]][moveTo[1]];
			// Checks if the square been moved to is free or if the pieces involved are different case.
			if (movingTo == '_') {
				moves.push_back(createState(currState, queenToMove, moveTo));
			}
			// Checks if the pieces are not the same color
			else if ((isupper(movingTo) ^ isupper(movingPiece))) {
				moves.push_back(createState(currState, queenToMove, moveTo));

				break;
			}
			else
				break;

			multipler++;

			moveTo[0] = queenToMove[0] + (DIA_STRI_MOVES[i][0] * multipler);
			moveTo[1] = queenToMove[1] + (DIA_STRI_MOVES[i][1] * multipler);
		}
	}

	return moves;
}

/// Finds all the possible moves a king can make that are not illegal
inline std::list<ChessState> ChessRules::getKingMoves(ChessState &currState, int *kingToMove)
{
	std::list<ChessState> moves = std::list<ChessState>();

	// Piece to compare to multiple condition
	char comparePiece;
	// Holds the board location that are been checked for oppenent moves to.
	int moveToCheck[2];
	// Holds board location for multipler moves
	int moveTo[2];
	// Moves distance multipler
	int multipler;

	bool next;

	/// Checks all 8 possible moves around the king to make sure hes not moving into check.
	for (int i = 0; i < DIA_STRI_ARRAY_LENGTH; i++) {
		moveToCheck[0] = kingToMove[0] + (DIA_STRI_MOVES[i][0]);
		moveToCheck[1] = kingToMove[1] + (DIA_STRI_MOVES[i][1]);

		if (inRange(moveToCheck)) {
			next = false;

			/// Black moves
			if (currState.movePlayer == 'B') {
				// Stop checking this square if the piece occuping it is the same color.
				// And not the king itself.
				if ((currState.boardState[moveToCheck[0]][moveToCheck[1]] < 96) &&
						currState.boardState[moveToCheck[0]][moveToCheck[1]] != 'k')
					continue;
				
				if (isBlackInCheck(currState, moveToCheck))
					continue;
			} 
			/// White moves
			else { 
				// Stop checking this square if the piece occuping it is the same color. 
				// And not the king itself.
				if (currState.boardState[moveToCheck[0]][moveToCheck[1]] > 91)
					continue;

				if (isWhiteInCheck(currState, moveToCheck))
					continue;
			}

			// Creates and adds the move to the new move array.
			moves.push_back(createState(currState, kingToMove, moveToCheck));
		}
	}

	return moves;
}

// Checks if the white king is in a state of Check
inline bool ChessRules::isWhiteInCheck(ChessState &currState, int *kingToCheck) {
	int moveTo[2];
	int multipler;

	char comparePiece;

	/// Every possible move to these squares must be checked to make 
	/// sure the king isn't moving into check.
	// Pawn check.
	if (currState.boardState[kingToCheck[0] + PAWN_ATTACK_MOVES_BLACK[0][0]]
		[kingToCheck[1] + PAWN_ATTACK_MOVES_BLACK[0][1]] == 'p' ||
		currState.boardState[kingToCheck[0] + PAWN_ATTACK_MOVES_BLACK[1][0]]
		[kingToCheck[1] + PAWN_ATTACK_MOVES_BLACK[1][1]] == 'p')
		return true;

	// Knight check
	for (int j = 0; j < KNIGHT_ARRAY_LENGTH; j++) {
		if (currState.boardState[kingToCheck[0] + KINGHT_MOVES[j][0]]
			[kingToCheck[1] + KINGHT_MOVES[j][1]] == 'n') {
			return true;
		}
	}

	// King, Queen and Bishop check
	for (int j = 0; j < DIAGONAL_ARRAY_LENGTH; j++) {
		multipler = 1;

		moveTo[0] = kingToCheck[0] + (DIAGONAL_MOVES[j][0] * multipler);
		moveTo[1] = kingToCheck[1] + (DIAGONAL_MOVES[j][1] * multipler);

		while (inRange(moveTo)) {
			comparePiece = currState.boardState[moveTo[0]][moveTo[1]];

			if (comparePiece == 'q' || comparePiece == 'b' ||
				(multipler == 1 && comparePiece == 'k')) {
				return true;
			}

			multipler++;

			moveTo[0] = kingToCheck[0] + (DIAGONAL_MOVES[j][0] * multipler);
			moveTo[1] = kingToCheck[1] + (DIAGONAL_MOVES[j][1] * multipler);
		}
	}

	// King, Queen and Rook check
	for (int j = 0; j < STRAIGHT_ARRAY_LENGTH; j++) {
		multipler = 1;

		moveTo[0] = kingToCheck[0] + (STRAIGHT_MOVES[j][0] * multipler);
		moveTo[1] = kingToCheck[1] + (STRAIGHT_MOVES[j][1] * multipler);

		while (inRange(moveTo)) {
			comparePiece = currState.boardState[moveTo[0]][moveTo[1]];

			if (comparePiece == 'q' || comparePiece == 'r' ||
				(multipler == 1 && comparePiece == 'k')) {
				return true;
			}
		}
	}

	return false;
}

// Checks if the black king is in a state of Check
inline bool ChessRules::isBlackInCheck(ChessState &currState, int *kingToCheck) {
	int moveTo[2];
	int multipler;

	char comparePiece;

	/// Every possible move to these squares must be checked to make 
	/// sure the king isn't moving into check.
	// Pawn check.
	if (currState.boardState[kingToCheck[0] + PAWN_ATTACK_MOVES_WHITE[0][0]]
		[kingToCheck[1] + PAWN_ATTACK_MOVES_WHITE[0][1]] == 'P' ||
		currState.boardState[kingToCheck[0] + PAWN_ATTACK_MOVES_WHITE[1][0]]
		[kingToCheck[1] + PAWN_ATTACK_MOVES_WHITE[1][1]] == 'P')
		return true;

	// Knight check
	for (int j = 0; j < KNIGHT_ARRAY_LENGTH; j++) {
		if (currState.boardState[kingToCheck[0] + KINGHT_MOVES[j][0]]
			[kingToCheck[1] + KINGHT_MOVES[j][1]] == 'N') {
			return true;
		}
	}

	// King, Queen and Bishop check
	for (int j = 0; j < DIAGONAL_ARRAY_LENGTH; j++) {
		multipler = 1;

		moveTo[0] = kingToCheck[0] + (DIAGONAL_MOVES[j][0] * multipler);
		moveTo[1] = kingToCheck[1] + (DIAGONAL_MOVES[j][1] * multipler);

		while (inRange(moveTo)) {
			comparePiece = currState.boardState[moveTo[0]][moveTo[1]];

			if (comparePiece == 'Q' || comparePiece == 'B' ||
				(multipler == 1 && comparePiece == 'K')) {
				return true;
			}

			multipler++;

			moveTo[0] = kingToCheck[0] + (DIAGONAL_MOVES[j][0] * multipler);
			moveTo[1] = kingToCheck[1] + (DIAGONAL_MOVES[j][1] * multipler);
		}
	}

	// King, Queen and Rook check
	for (int j = 0; j < STRAIGHT_ARRAY_LENGTH; j++) {
		multipler = 1;

		moveTo[0] = kingToCheck[0] + (STRAIGHT_MOVES[j][0] * multipler);
		moveTo[1] = kingToCheck[1] + (STRAIGHT_MOVES[j][1] * multipler);

		while (inRange(moveTo)) {
			comparePiece = currState.boardState[moveTo[0]][moveTo[1]];

			if (comparePiece == 'Q' || comparePiece == 'R' ||
				(multipler == 1 && comparePiece == 'K')) {
				return true;
			}
		}
	}

	return false;
}

/// Creates a new state given a board state and a move to make then returns it.
inline ChessState ChessRules::createState(ChessState &state, int* pieceToMove, int* move) {
	// Creates and adds the move to the new move array.
	int lastMove[2][2] = { { pieceToMove[0], pieceToMove[1] },
	{ move[0], move[1] } };

	ChessState newState = ChessState(*state.boardState, *lastMove);
	makeMove(newState, state.heuristicVal, state.maxPlayer, state.movePlayer);

	return newState;
}

/// Given a newly created state with the move to be made set this executes said move.
inline void ChessRules::makeMove(ChessState &state, int heurisVal, bool maxPlayer, char movePlay) {
	char takenPiece = state.boardState[state.lastMove[1][0]][state.lastMove[1][1]];

	char movePiece = state.boardState[state.lastMove[0][0]][state.lastMove[0][1]];
	state.boardState[state.lastMove[1][0]][state.lastMove[1][1]] = movePiece;

	heurisVal += maxPlayer ? PIECE_VALUES[takenPiece] : -PIECE_VALUES[takenPiece];
	maxPlayer = !maxPlayer;
	state.movePlayer = movePlay == 'W' ? 'B' : 'W';
}

// Gets a pieces location
inline int* getPieceLoc(ChessState &currState, char pieceToFind) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (&currState, )
		}
	}
}

// Checks if a position to move to is in range
inline bool ChessRules::inRange(int * pos)
{
	if (pos[0] < 8 && pos[0] >= 0
		&& pos[1] < 8 && pos[1] >= 0) {
		return true;
	}

	return false;
}