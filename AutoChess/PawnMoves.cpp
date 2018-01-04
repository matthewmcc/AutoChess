#include "stdafx.h"
#include "PawnMoves.h"

namespace AutoChess {
	// Given the current state and the current black pawn to move. All possible states are calculated and returned.
	inline std::list<ChessState> PawnMoves::getBlackPawnMoves()
	{
		blackStraightMoves();
		blackOffensiveMoves();

		return PossibleMoves;
	}

	// Given the current state and the current white pawn to move. All possible states are calculated and returned.
	inline std::list<ChessState> PawnMoves::getWhitePawnMoves()
	{
		whiteStraightMoves();
		whiteOffensiveMoves();

		return PossibleMoves;
	}

	void PawnMoves::blackStraightMoves() {
		// Checks first possible pawn move
		ChessTile moveToTile = ChessTile(PawnToMove.getX(), PawnToMove.getY() + 1);
		if (CurrentState.isTileEmpty(moveToTile))
		{
			ChessMove moveToMake = ChessMove::CreateMove(PawnToMove, moveToTile);
			PossibleMoves.push_back(CurrentState.CreateNextState(moveToMake));

			// Checks if the pawn is in the first position.
			if (PawnToMove.getY() == BLACK_PAWN_START_ROW) {
				blackTwoTileStraightMove();
			}
		}
	}

	void PawnMoves::blackTwoTileStraightMove() {
		ChessTile moveToTile = ChessTile(PawnToMove.getX(), PawnToMove.getY() + 2);
		if (CurrentState.isTileEmpty(moveToTile))
		{
			ChessMove moveToMake = ChessMove::CreateMove(PawnToMove, moveToTile);
			PossibleMoves.push_back(CurrentState.CreateNextState(moveToMake));
		}
	}

	void PawnMoves::blackOffensiveMoves() {
		// Checks if either of the pawn offensive moves are viable.
		for (int i = 0; i < PAWN_MOVES_ARRAY_LENGTH; i++)
		{
			ChessTile moveToTile = ChessTile(PawnToMove.getX() + (BLACK_PAWNS_ATTACK_MOVES[i][0]),
				PawnToMove.getY() + (BLACK_PAWNS_ATTACK_MOVES[i][1]));

			blackAddLegalMove(moveToTile);
		}
	}

	void PawnMoves::blackAddLegalMove(ChessTile &moveToTile) {
		if (moveToTile.isInBoardBounds()) {
			if (CurrentState.isTilesPieceWhite(moveToTile)) {
				ChessMove moveToMake = ChessMove::CreateMove(PawnToMove, moveToTile);
				PossibleMoves.push_back(CurrentState.CreateNextState(moveToMake));
			}
		}
	};


	void PawnMoves::whiteStraightMoves() {
		// Checks first possible pawn move
		ChessTile moveToTile = ChessTile(PawnToMove.getX(), PawnToMove.getY() - 1);
		if (CurrentState.isTileEmpty(moveToTile))
		{
			ChessMove moveToMake = ChessMove::CreateMove(PawnToMove, moveToTile);
			PossibleMoves.push_back(CurrentState.CreateNextState(moveToMake));

			// Checks if the pawn is in the first position.
			if (PawnToMove.getY() == WHITE_PAWN_START_ROW) {
				whiteTwoTileStraightMove();
			}
		}
	}

	void PawnMoves::whiteTwoTileStraightMove() {
		ChessTile moveToTile = ChessTile(PawnToMove.getX(), PawnToMove.getY() - 2);
		if (CurrentState.isTileEmpty(moveToTile))
		{
			ChessMove moveToMake = ChessMove::CreateMove(PawnToMove, moveToTile);
			PossibleMoves.push_back(CurrentState.CreateNextState(moveToMake));
		}
	}

	void PawnMoves::whiteOffensiveMoves() {
		// Checks if either of the pawn offensive moves are viable.
		for (int i = 0; i < PAWN_MOVES_ARRAY_LENGTH; i++)
		{
			ChessTile moveToTile = ChessTile(PawnToMove.getX() + (WHITE_PAWNS_ATTACK_MOVES[i][0]),
				PawnToMove.getY() + (WHITE_PAWNS_ATTACK_MOVES[i][1]));

			whiteAddLegalMove(moveToTile);
		}
	}

	void PawnMoves::whiteAddLegalMove(ChessTile &moveToTile) {
		if (moveToTile.isInBoardBounds()) {
			if (CurrentState.isTilesPieceWhite(moveToTile)) {
				ChessMove moveToMake = ChessMove::CreateMove(PawnToMove, moveToTile);
				PossibleMoves.push_back(CurrentState.CreateNextState(moveToMake));
			}
		}
	};
}