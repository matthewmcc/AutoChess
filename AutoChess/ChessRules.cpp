#include "stdafx.h"
#include "ChessRules.h"

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

	// If the game is in a terminal state the returned list will be empty
	std::list<ChessState> ChessRules::getMoves(ChessState &currentState)
	{
		std::list<ChessState> moves;

		if (currentState.getWhichPlayersTurn() == BLACK_PLAYER) {
			// If the king is a check state then after all the possible moves have been generated...
			// ...any where the king is still in a check state must be removed.
			moves = getBlackMoves(currentState);

			if (isBlackInCheck(currentState))
				removeBlackCheckStates(moves);
		}
		else {
			moves = getWhiteMoves(currentState);

			if (isWhiteInCheck(currentState))
				removeWhiteCheckStates(moves);
		}

		return moves;
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
						moves.splice(moves.begin(), pawnMoves.getWhitePawnMoves());
						break;
					}
					case WHITE_ROOK: {
						RookMoves rookMoves = RookMoves(currentState, pieceToMove);
						moves.splice(moves.begin(), rookMoves.getWhiteRookMoves());
						break;
					}
					case WHITE_KNIGHT: {
						KnightMoves knightMoves = KnightMoves(currentState, pieceToMove);
						moves.splice(moves.begin(), knightMoves.getWhiteKnightMoves());
						break;
					}
					case WHITE_BISHOP: {
						BishopMoves bishopMoves = BishopMoves(currentState, pieceToMove);
						moves.splice(moves.begin(), bishopMoves.getWhiteBishopMoves());
						break;
					}
					case WHITE_QUEEN: {
						QueenMoves queenMoves = QueenMoves(currentState, pieceToMove);
						moves.splice(moves.begin(), queenMoves.getWhiteQueenMoves());
						break;
					}
					case WHITE_KING: {
						KingMoves kingMoves = KingMoves(currentState, pieceToMove);
						moves.splice(moves.begin(), kingMoves.getWhiteKingMoves());
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
						moves.splice(moves.begin(), pawnMoves.getBlackPawnMoves());
						break;
					}
					case BLACK_ROOK: {
						RookMoves rookMoves = RookMoves(currentState, pieceToMove);
						moves.splice(moves.begin(), rookMoves.getBlackRookMoves());
						break;
					}
					case BLACK_KNIGHT: {
						KnightMoves knightMoves = KnightMoves(currentState, pieceToMove);
						moves.splice(moves.begin(), knightMoves.getBlackKnightMoves());
						break;
					}
					case BLACK_BISHOP: {
						BishopMoves bishopMoves = BishopMoves(currentState, pieceToMove);
						moves.splice(moves.begin(), bishopMoves.getBlackBishopMoves());
						break;
					}
					case BLACK_QUEEN: {
						QueenMoves queenMoves = QueenMoves(currentState, pieceToMove);
						moves.splice(moves.begin(), queenMoves.getBlackQueenMoves());
						break;
					}
					case BLACK_KING: {
						KingMoves kingMoves = KingMoves(currentState, pieceToMove);
						moves.splice(moves.begin(), kingMoves.getBlackKingMoves());
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

	// Removes any state from the list where the passed king is in a state of check.
	// Only to be used when the king was in check the previous turn.
	std::list<ChessState> ChessRules::removeBlackCheckStates(std::list<ChessState> &moves) {
		std::list<ChessState>::iterator movesIterator = moves.begin();

		while (movesIterator != moves.end()) {
			if (isBlackInCheck(*movesIterator)) 
				movesIterator = moves.erase(movesIterator);
			else 
				movesIterator++;
		}

		return moves;
	}

	bool ChessRules::isBlackInCheck(ChessState &stateToTest) {
		ChessTile kingToCheck = stateToTest.getBlackKingLocation();
		BlackKingCheckStatus blackKingChecker = BlackKingCheckStatus(stateToTest, kingToCheck);

		return blackKingChecker.isBlackKingInCheck();
	}

	// Removes any state from the list where the passed king is in a state of check.
	// Only to be used when the king was in check the previous turn.
	std::list<ChessState> ChessRules::removeWhiteCheckStates(std::list<ChessState> &moves) {
		std::list<ChessState>::iterator movesIterator = moves.begin();

		while (movesIterator != moves.end()) {
			if (isWhiteInCheck(*movesIterator))
				movesIterator = moves.erase(movesIterator);
			else
				movesIterator++;
		}

		return moves;
	}

	bool ChessRules::isWhiteInCheck(ChessState &stateToTest) {
		ChessTile kingToCheck = stateToTest.getWhiteKingLocation();
		WhiteKingCheckStatus whiteKingChecker = WhiteKingCheckStatus(stateToTest, kingToCheck);

		return whiteKingChecker.isWhiteKingInCheck();
	}
}