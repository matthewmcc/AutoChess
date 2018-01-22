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
#include "stdafx.h"
#include "ChessMove.h"

#pragma once
namespace AutoChess {
	class ChessState
	{
	public:
		ChessState() {};

		// Initializes the new state as the game start state
		static ChessState CreateStartState(bool isMaxPlayer);
		// Creates a new state given the current board state and a move to do.
		ChessState CreateNextState(ChessMove moveToDo);

		void copyBoardState(ChessState stateToCopy);

		bool maxPlayer;

		/// Gets and sets for memeber variables
		inline ChessMove getLastMove() { return LastMove; };

		char getBoardTile(ChessTile tile) { return BoardState[tile.getX()][tile.getY()]; };
		char getBoardTile(int x, int y) { return BoardState[x][y]; };

		void setBoardTile(ChessTile tile, char newTileState) { BoardState[tile.getX()][tile.getY()] = newTileState; };
		void setBoardTile(int x, int y, char newTileState) { BoardState[x][y] = newTileState; };

		inline char getWhichPlayersTurn() { return WhichPlayersTurn; };

		inline int getHeuristsValue() { return HeuristicVal; };
		inline void setHeuristsValue(int heuristValue) { HeuristicVal = heuristValue; };

		inline bool isMaxPlayer() { return IsMaxPlayer; };
		inline bool isTileEmpty(ChessTile tile) {
			return BoardState[tile.getX()][tile.getY()] == EMPTY_TILE;
		};

		inline bool isTilesPieceBlack(ChessTile tile) {
			return BoardState[tile.getX()][tile.getY()] >= BLACKS_LOWEST_ASCII_VALUE;
		};

		inline bool isTilesPieceWhite(ChessTile tile) {
			return BoardState[tile.getX()][tile.getY()] <= WHITES_HIGHEST_ASCII_VALUE;
		};

		ChessTile getBlackKingLocation();
		ChessTile getWhiteKingLocation();

	private:
		char BoardState[8][8];
		ChessMove LastMove;
		char WhichPlayersTurn;
		int HeuristicVal;
		bool IsMaxPlayer;

		void initNewBoard();

		static const char WHITE_PLAYER = 'W';
		static const char BLACK_PLAYER = 'B';

		void setLastMove(ChessMove lastMove) { LastMove = lastMove; };
		void makeMove(ChessMove move);

		inline void setWhichPlayersTurn(char whichPlayersTurn) { WhichPlayersTurn = whichPlayersTurn; };

		inline void setIsMaxPlayer(bool isMaxPlayer) { IsMaxPlayer = isMaxPlayer; };

		inline ChessTile getPieceLocation(char pieceToFind);

		inline void calculateHeuristicsValue(ChessState lastState, char pieceTaken);
		inline void setNextPlayer(ChessState lastState);
	};

	class PieceNotFoundException : public std::exception {
	public:
		PieceNotFoundException(ChessState currentState, char pieceNotFound) {};
	};
}