#include "stdafx.h"
#include "PawnMoves.h"

namespace AutoChess {
	// Given the current state and the current black pawn to move. All possible states are calculated and returned.
	std::list<ChessState> PawnMoves::getBlackPawnMoves()
	{
		blackStraightMove();
		blackOffensiveMoves();

		return PossibleMoves;
	}

	// Given the current state and the current white pawn to move. All possible states are calculated and returned.
	std::list<ChessState> PawnMoves::getWhitePawnMoves()
	{
		whiteStraightMove();
		whiteOffensiveMoves();

		return PossibleMoves;
	}

	void PawnMoves::blackStraightMove() {
		// Checks first possible pawn move
		ChessTile moveToTile = createBlackMoveTile(0);

		if (blackAddLegalMove(moveToTile)) 
		{
			if (PawnToMove.getX() == BLACK_PAWN_START_ROW)
				doubleBlackStraightMove();
		}
	}

	void PawnMoves::doubleBlackStraightMove() {
		ChessTile moveToTile = createBlackMoveTile(1);

		blackAddLegalMove(moveToTile);
	}

	void PawnMoves::blackOffensiveMoves() {
		// Checks if either of the pawn offensive moves are viable.
		for (int i = 0; i < PAWN_MOVES_ARRAY_LENGTH; i++)
		{
			ChessTile moveToTile = createBlackOffensiveMoveTile(i);

			blackAddLegalOffensiveMove(moveToTile);
		}
	}

	// Returns true if the move was added else false
	bool PawnMoves::blackAddLegalMove(ChessTile &moveToTile) {
		if (moveToTile.isInBoardBounds())
		{
			if (CurrentState.isTileEmpty(moveToTile))
			{
				addBlackPossibleMove(moveToTile);
				return true;
			}
		}

		return false;
	};


	void PawnMoves::blackAddLegalOffensiveMove(ChessTile &moveToTile) {
		if (moveToTile.isInBoardBounds())
		{
			if (CurrentState.isTilesPieceWhite(moveToTile))
			{
				addBlackPossibleMove(moveToTile);
			}
		}
	};

	void PawnMoves::addBlackPossibleMove(ChessTile &moveToAdd) {
		ChessMove moveToMake = ChessMove::CreateMove(PawnToMove, moveToAdd);
		ChessState newState = CurrentState.CreateNextState(moveToMake);

		PossibleMoves.push_front(isBlackPawnUpgrade(newState));
	}

	ChessState PawnMoves::isBlackPawnUpgrade(ChessState stateToCheck) {
		if (stateToCheck.getLastMove().getMoveToTileX() == BLACK_PAWN_END_ROW) {
			stateToCheck.setBoardTile(stateToCheck.getLastMove().getMoveToTile(), BLACK_QUEEN);

			if (stateToCheck.isMaxPlayer())
				stateToCheck.setHeuristsValue(stateToCheck.getHeuristsValue() - PAWN_UPGRADE);
			else
				stateToCheck.setHeuristsValue(stateToCheck.getHeuristsValue() - PAWN_UPGRADE);
		}

		return stateToCheck;
	}

	ChessTile PawnMoves::createBlackMoveTile(int moveArrayIndex) {
		int tileXValue = PawnToMove.getX() + (BLACK_PAWNS_MOVES[moveArrayIndex][0]);
		int tileYValue = PawnToMove.getY() + (BLACK_PAWNS_MOVES[moveArrayIndex][1]);

		return ChessTile(tileXValue, tileYValue);
	}

	ChessTile PawnMoves::createBlackOffensiveMoveTile(int moveArrayIndex) {
		int tileXValue = PawnToMove.getX() + (BLACK_PAWNS_ATTACK_MOVES[moveArrayIndex][0]);
		int tileYValue = PawnToMove.getY() + (BLACK_PAWNS_ATTACK_MOVES[moveArrayIndex][1]);

		return ChessTile(tileXValue, tileYValue);
	}

	void PawnMoves::whiteStraightMove() {
		// Checks first possible pawn move
		ChessTile moveToTile = createWhiteMoveTile(0);

		if (whiteAddLegalMove(moveToTile))
		{
			if (PawnToMove.getX() == WHITE_PAWN_START_ROW)
				doubleWhiteStraightMove();
		}
	}

	void PawnMoves::doubleWhiteStraightMove() {
		ChessTile moveToTile = createWhiteMoveTile(1);

		whiteAddLegalMove(moveToTile);
	}

	void PawnMoves::whiteOffensiveMoves() {
		// Checks if either of the pawn offensive moves are viable.
		for (int i = 0; i < PAWN_MOVES_ARRAY_LENGTH; i++)
		{
			ChessTile moveToTile = createWhiteOffensiveMoveTile(i);

			whiteAddLegalOffensiveMove(moveToTile);
		}
	}

	// Returns true if the move was added else false
	bool PawnMoves::whiteAddLegalMove(ChessTile &moveToTile) {
		if (moveToTile.isInBoardBounds())
		{
			if (CurrentState.isTileEmpty(moveToTile))
			{
				addWhitePossibleMove(moveToTile);
				return true;
			}
		}

		return false;
	};

	void PawnMoves::whiteAddLegalOffensiveMove(ChessTile &moveToTile) {
		if (moveToTile.isInBoardBounds()) 
		{
			if (CurrentState.isTilesPieceBlack(moveToTile)) 
			{
				addWhitePossibleMove(moveToTile);
			}
		}
	};

	ChessTile PawnMoves::createWhiteMoveTile(int moveArrayIndex) {
		int tileXValue = PawnToMove.getX() + (WHITE_PAWNS_MOVES[moveArrayIndex][0]);
		int tileYValue = PawnToMove.getY() + (WHITE_PAWNS_MOVES[moveArrayIndex][1]);

		return ChessTile(tileXValue, tileYValue);
	}

	ChessTile PawnMoves::createWhiteOffensiveMoveTile(int moveArrayIndex) {
		int tileXValue = PawnToMove.getX() + (WHITE_PAWNS_ATTACK_MOVES[moveArrayIndex][0]);
		int tileYValue = PawnToMove.getY() + (WHITE_PAWNS_ATTACK_MOVES[moveArrayIndex][1]);

		return ChessTile(tileXValue, tileYValue);
	}

	void PawnMoves::addWhitePossibleMove(ChessTile &moveToAdd) {
		ChessMove moveToMake = ChessMove::CreateMove(PawnToMove, moveToAdd);
		ChessState newState = CurrentState.CreateNextState(moveToMake);

		PossibleMoves.push_front(isWhitePawnUpgrade(newState));
	}

	ChessState PawnMoves::isWhitePawnUpgrade(ChessState stateToCheck) {
		if (stateToCheck.getLastMove().getMoveToTileX() == WHITE_PAWN_END_ROW) {
			stateToCheck.setBoardTile(stateToCheck.getLastMove().getMoveToTile(), WHITE_QUEEN);
			
			if (stateToCheck.isMaxPlayer())
				stateToCheck.setHeuristsValue(stateToCheck.getHeuristsValue() - PAWN_UPGRADE);
			else 
				stateToCheck.setHeuristsValue(stateToCheck.getHeuristsValue() - PAWN_UPGRADE);
		}

		return stateToCheck;
	}
}