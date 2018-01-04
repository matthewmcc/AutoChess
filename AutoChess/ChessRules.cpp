#include "stdafx.h"
#include "ChessRules.h"
#include "ChessMove.h"
#include "PawnMoves.h"

#include <algorithm>
#include <list>

namespace AutoChess {
	ChessRules::ChessRules() {}
	ChessRules::~ChessRules() {}

	// Function to insure class is only used as singleton.
	ChessRules& ChessRules::getInstance()
	{
		static ChessRules instance;
		return instance;
	}

	std::list<ChessState> ChessRules::getMoves(ChessState &currState)
	{
		std::list<ChessState> moves;

		bool kingInCheck;
		int* currKingLoc;

		if (currState.getWhichPlayersTurn() == BLACK_PLAYER) {
			// If the king is a check state then after all the possible moves have been generated...
			// ...any where the king is still in a check state must be removed.
			currKingLoc = getPieceLoc(currState, BLACK_KING);
			kingInCheck = isCurrPlayerInCheck(currState, currKingLoc);
			moves = getBlackMoves(currState);

			if (kingInCheck)
				removeCheckStates(moves, currKingLoc, BLACK_PLAYER);
		}
		else {
			currKingLoc = getPieceLoc(currState, WHITE_KING);
			kingInCheck = isCurrPlayerInCheck(currState, currKingLoc);
			moves = getWhiteMoves(currState);

			if (kingInCheck)
				removeCheckStates(moves, currKingLoc, 'W');
		}

		return moves;
	}

	/// Is the king in check?
	///		If not can another piece on that team move?
	///	else
	///		can the king move.
	///			No? can a piece block the check?
	///
	bool ChessRules::isCurrPlayerInCheck(ChessState &currState, int* kingLoc)
	{
		/// Checks whos in check
		if (currState.getWhichPlayersTurn() == BLACK_PLAYER)
			return isBlackInCheck(currState, kingLoc);
		else
			return isWhiteInCheck(currState, kingLoc);
	}

	std::list<ChessState> ChessRules::getWhiteMoves(ChessState &currentState)
	{
		char pieceType;
		std::list<ChessState> moves = std::list<ChessState>();

		// Checks every place on the board for black pieces and then
		for (int i = 0; i < 8; i++) 
		{
			for (int j = 0; j < 8; j++) 
			{
				pieceType = currentState.getBoardTile(i, j);
				if (pieceType <= 90) {
					ChessTile pieceToMove = ChessTile(i, j);

					// Calls the correct move function given the piece to move.
					switch (pieceType)
					{
					case WHITE_PAWN: {
						PawnMoves pawnMoves = PawnMoves(currentState, pieceToMove);
						moves.merge(pawnMoves.getWhitePawnMoves());
						break;
					}
					case WHITE_ROOK: {
						getRookMoves(moves, currState, pieceToMove);
						break;
					}
					case WHITE_KNIGHT: {
						getKnightMoves(moves, currState, pieceToMove);
						break;
					}
					case WHITE_BISHOP: {
						getBishopMoves(moves, currState, pieceToMove);
						break;
					}
					case WHITE_QUEEN: {
						getQueenMoves(moves, currState, pieceToMove);
						break;
					}
					case WHITE_KING: {
						getKingMoves(moves, currState, pieceToMove);
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

	std::list<ChessState> ChessRules::getBlackMoves(ChessState &currentState)
	{
		char pieceType;
		std::list<ChessState> moves = std::list<ChessState>();

		// Checks every place on the board for black pieces and then
		for (int i = 0; i < 8; i++) 
		{
			for (int j = 0; j < 8; j++) 
			{
				pieceType = currentState.getBoardTile(i, j);
				if (pieceType >= 97) {
					ChessTile pieceToMove = ChessTile(i, j);				

					// Calls the correct move funciton given the piece to move.
					switch (pieceType)
					{
					case BLACK_PAWN: {
						PawnMoves pawnMoves = PawnMoves(currentState, pieceToMove);
						moves.merge(pawnMoves.getBlackPawnMoves());
						break;
					}
					case BLACK_ROOK: {
						getRookMoves(moves, currState, pieceToMove);
						break;
					}
					case BLACK_KNIGHT: {
						getKnightMoves(moves, currState, pieceToMove);
						break;
					}
					case BLACK_BISHOP: {
						getBishopMoves(moves, currState, pieceToMove);
						break;
					}
					case BLACK_QUEEN: {
						getQueenMoves(moves, currState, pieceToMove);
						break;
					}
					case BLACK_KING: {
						getKingMoves(moves, currState, pieceToMove);
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

	/// Given the current state and the current rook to move. All possible states are calculated and returned.
	inline void ChessRules::getRookMoves(std::list<ChessState> &moves, ChessState &currState, int *rookToMove)
	{

	}

	/// Given the current state and the current kinght to move. All possible states are calculated and returned.
	inline void ChessRules::getKnightMoves(std::list<ChessState> &moves, ChessState &currState, int *knightToMove)
	{
		int moveTo[2];

		char movingPiece = currState.getBoardTile(knightToMove[0], knightToMove[1]);
		char movingTo;

		for (int i = 0; i < KNIGHT_ARRAY_LENGTH; i++) 
		{
			moveTo[0] = knightToMove[0] + KNIGHT_MOVES[i][0];
			moveTo[1] = knightToMove[1] + KNIGHT_MOVES[i][1];

			if (inRange(moveTo)) {
				movingTo = currState.getBoardTile(moveTo[0], moveTo[1]);
				// Checks if the square been moved to is free or if the pieces involved are different case.
				if (movingTo == EMPTY_TILE ||
					(isupper(movingTo) ^ isupper(movingPiece))) {
					moves.push_back(createState(currState, knightToMove, moveTo));
				}
			}
		}
	}

	/// Given the current state and the current bishop to move. All possible states are calculated and returned.
	inline void ChessRules::getBishopMoves(std::list<ChessState> &moves, ChessState &currState, int *bishopToMove)
	{
		int moveTo[2];
		int multipler;

		char movingPiece = currState.getBoardTile(bishopToMove[0], bishopToMove[1]);
		char movingTo;

		/// Checks all possible straight moves
		for (int i = 0; i < DIAGONAL_ARRAY_LENGTH; i++) 
		{
			multipler = 1;

			moveTo[0] = bishopToMove[0] + (DIAGONAL_MOVES[i][0] * multipler);
			moveTo[1] = bishopToMove[1] + (DIAGONAL_MOVES[i][1] * multipler);

			while (inRange(moveTo)) 
			{
				movingTo = currState.getBoardTile(moveTo[0], moveTo[1]);
				// Checks if the square been moved to is free or if the pieces involved are different case.
				if (movingTo == EMPTY_TILE) {
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
	}

	/// Returns all the possible moves for a Queen
	inline void ChessRules::getQueenMoves(std::list<ChessState> &moves, ChessState &currState, int *queenToMove)
	{
		int moveTo[2];
		int multipler;

		char movingPiece = currState.getBoardTile(queenToMove[0], queenToMove[1]);
		char movingTo;

		/// Checks all possible stright and diagonal moves
		for (int i = 0; i < DIA_STRI_ARRAY_LENGTH; i++) 
		{
			multipler = 1;

			moveTo[0] = queenToMove[0] + (DIA_STRI_MOVES[i][0] * multipler);
			moveTo[1] = queenToMove[1] + (DIA_STRI_MOVES[i][1] * multipler);

			while (inRange(moveTo)) 
			{
				movingTo = currState.getBoardTile(moveTo[0], moveTo[1]);
				// Checks if the square been moved to is free or if the pieces involved are different case.
				if (movingTo == EMPTY_TILE) {
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
	}

	/// Finds all the possible moves a king can make that are not illegal
	inline void ChessRules::getKingMoves(std::list<ChessState> &moves, ChessState &currState, int *kingToMove)
	{
		// Holds the board location that are been checked for oppenent moves to.
		int moveToCheck[2];

		bool next;

		/// Checks all 8 possible moves around the king to make sure hes not moving into check.
		for (int i = 0; i < DIA_STRI_ARRAY_LENGTH; i++) 
		{
			moveToCheck[0] = kingToMove[0] + (DIA_STRI_MOVES[i][0]);
			moveToCheck[1] = kingToMove[1] + (DIA_STRI_MOVES[i][1]);

			if (inRange(moveToCheck)) {
				next = false;

				/// Black moves
				if (currState.getWhichPlayersTurn() == BLACK_PLAYER) {
					// Stop checking this square if the piece occuping it is the same color.
					// And not the king itself.
					if ((currState.getBoardTile(moveToCheck[0], moveToCheck[1]) < 96) &&
						currState.getBoardTile(moveToCheck[0], moveToCheck[1]) != BLACK_KING)
						continue;

					if (isBlackInCheck(currState, moveToCheck))
						continue;
				}
				/// White moves
				else {
					// Stop checking this square if the piece occuping it is the same color. 
					// And not the king itself.
					if (currState.getBoardTile(moveToCheck[0], moveToCheck[1]) > 91)
						continue;

					if (isWhiteInCheck(currState, moveToCheck))
						continue;
				}

				// Creates and adds the move to the new move array.
				moves.push_back(createState(currState, kingToMove, moveToCheck));
			}
		}
	}

	// Checks if the white king is in a state of Check
	inline bool ChessRules::isWhiteInCheck(ChessState &currState, int *kingToCheck) {
		int moveTo[2];
		int multipler;

		char comparePiece;

		/// Every possible move to these squares must be checked to make 
		/// sure the king isn't moving into check.
		// Pawn check.
		if (currState.getBoardTile(kingToCheck[0] + PAWN_ATTACK_MOVES_BLACK[0][0],
				kingToCheck[1] + PAWN_ATTACK_MOVES_BLACK[0][1]) == BLACK_PAWN ||
			currState.getBoardTile(kingToCheck[0] + PAWN_ATTACK_MOVES_BLACK[1][0],
				kingToCheck[1] + PAWN_ATTACK_MOVES_BLACK[1][1]) == BLACK_PAWN)
			return true;

		// Knight check
		for (int j = 0; j < KNIGHT_ARRAY_LENGTH; j++) 
		{
			if (currState.getBoardTile(kingToCheck[0] + KNIGHT_MOVES[j][0],
					kingToCheck[1] + KNIGHT_MOVES[j][1]) == BLACK_KNIGHT) {
				return true;
			}
		}

		// King, Queen and Bishop check
		for (int j = 0; j < DIAGONAL_ARRAY_LENGTH; j++) 
		{
			multipler = 1;

			moveTo[0] = kingToCheck[0] + (DIAGONAL_MOVES[j][0] * multipler);
			moveTo[1] = kingToCheck[1] + (DIAGONAL_MOVES[j][1] * multipler);

			while (inRange(moveTo)) 
			{
				comparePiece = currState.getBoardTile(moveTo[0], moveTo[1]);

				if (comparePiece == BLACK_QUEEN || comparePiece == BLACK_BISHOP ||
					(multipler == 1 && comparePiece == BLACK_KING)) {
					return true;
				}

				multipler++;

				moveTo[0] = kingToCheck[0] + (DIAGONAL_MOVES[j][0] * multipler);
				moveTo[1] = kingToCheck[1] + (DIAGONAL_MOVES[j][1] * multipler);
			}
		}

		// King, Queen and Rook check
		for (int j = 0; j < STRAIGHT_ARRAY_LENGTH; j++) 
		{
			multipler = 1;

			moveTo[0] = kingToCheck[0] + (STRAIGHT_MOVES[j][0] * multipler);
			moveTo[1] = kingToCheck[1] + (STRAIGHT_MOVES[j][1] * multipler);

			while (inRange(moveTo)) {
				comparePiece = currState.getBoardTile(moveTo[0], moveTo[1]);

				if (comparePiece == BLACK_QUEEN || comparePiece == BLACK_ROOK ||
					(multipler == 1 && comparePiece == BLACK_KING)) {
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
		if (currState.getBoardTile(kingToCheck[0] + PAWN_ATTACK_MOVES_WHITE[0][0],
				kingToCheck[1] + PAWN_ATTACK_MOVES_WHITE[0][1]) == WHITE_PAWN ||
			currState.getBoardTile(kingToCheck[0] + PAWN_ATTACK_MOVES_WHITE[1][0],
				kingToCheck[1] + PAWN_ATTACK_MOVES_WHITE[1][1]) == WHITE_PAWN)
			return true;

		// Knight check
		for (int j = 0; j < KNIGHT_ARRAY_LENGTH; j++) {
			if (currState.getBoardTile(kingToCheck[0] + KNIGHT_MOVES[j][0],
					kingToCheck[1] + KNIGHT_MOVES[j][1]) == WHITE_KNIGHT) {
				return true;
			}
		}

		// King, Queen and Bishop check
		for (int j = 0; j < DIAGONAL_ARRAY_LENGTH; j++) 
		{
			multipler = 1;

			moveTo[0] = kingToCheck[0] + (DIAGONAL_MOVES[j][0] * multipler);
			moveTo[1] = kingToCheck[1] + (DIAGONAL_MOVES[j][1] * multipler);

			while (inRange(moveTo)) {
				comparePiece = currState.getBoardTile(moveTo[0], moveTo[1]);

				if (comparePiece == WHITE_QUEEN || comparePiece == WHITE_BISHOP ||
					(multipler == 1 && comparePiece == WHITE_KING)) {
					return true;
				}

				multipler++;

				moveTo[0] = kingToCheck[0] + (DIAGONAL_MOVES[j][0] * multipler);
				moveTo[1] = kingToCheck[1] + (DIAGONAL_MOVES[j][1] * multipler);
			}
		}

		// King, Queen and Rook check
		for (int j = 0; j < STRAIGHT_ARRAY_LENGTH; j++) 
		{
			multipler = 1;

			moveTo[0] = kingToCheck[0] + (STRAIGHT_MOVES[j][0] * multipler);
			moveTo[1] = kingToCheck[1] + (STRAIGHT_MOVES[j][1] * multipler);

			while (inRange(moveTo)) 
			{
				comparePiece = currState.getBoardTile(moveTo[0], moveTo[1]);

				if (comparePiece == WHITE_QUEEN || comparePiece == WHITE_ROOK ||
					(multipler == 1 && comparePiece == WHITE_KING)) {
					return true;
				}
			}
		}

		return false;
	}

	/// Creates a new state given a board state and a move to make then returns it.
	inline ChessState ChessRules::createState(ChessState &state, ChessMove moveToMake) {
		ChessState newState = state.CreateNextState(moveToMake);

		return newState;
	}

	inline int calculateNewHeuristic(ChessState &state, ChessMove moveToBeMade) {
		char takenPiece = state.getBoardTile(moveToBeMade.getMoveToTile());

		
	}


	// Removes any state from the list where the passed king is in a state of check.
	// Only to be used when the king was in check the previous turn.
	void ChessRules::removeCheckStates(std::list<ChessState> &moves, int* kingToCheck, char typeOfKing) {
		std::list<ChessState>::iterator iterMoves = moves.begin();

		int tempKingLoc[2];

		if (typeOfKing == 'W') {
			while (iterMoves != moves.end()) {
				// If the king was moved last the temp King Loc must be used.
				if ((*iterMoves).lastMove[0][0] == kingToCheck[0] &&
					(*iterMoves).lastMove[0][1] == kingToCheck[1]) {
					// Sets tempKingLoc to the new location of the king.
					tempKingLoc[0] = (*iterMoves).lastMove[1][0];
					tempKingLoc[1] = (*iterMoves).lastMove[1][1];

					if (isBlackInCheck((*iterMoves), tempKingLoc))
						iterMoves = moves.erase(iterMoves);
					else
						iterMoves++;
				}
				else {
					if (isBlackInCheck((*iterMoves), kingToCheck))
						iterMoves = moves.erase(iterMoves);
					else
						iterMoves++;
				}
			}
		}
		else {
			while (iterMoves != moves.end()) {
				// If the king was moved last the temp King Loc must be used.
				if ((*iterMoves).lastMove[0][0] == kingToCheck[0] &&
					(*iterMoves).lastMove[0][1] == kingToCheck[1]) {
					// Sets tempKingLoc to the new location of the king.
					tempKingLoc[0] = (*iterMoves).lastMove[1][0];
					tempKingLoc[1] = (*iterMoves).lastMove[1][1];

					if (isWhiteInCheck((*iterMoves), tempKingLoc))
						iterMoves = moves.erase(iterMoves);
					else
						iterMoves++;
				}
				else {
					if (isWhiteInCheck((*iterMoves), kingToCheck))
						iterMoves = moves.erase(iterMoves);
					else
						iterMoves++;
				}
			}
		}
	}

	// Gets a pieces location.
	inline int* ChessRules::getPieceLoc(ChessState &currState, char pieceToFind) {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (currState.getBoardTile(i, j) == pieceToFind)
					return new int[2]{ i, j };
			}
		}

		return nullptr;
	}
}