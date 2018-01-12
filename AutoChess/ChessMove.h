#include "stdafx.h"

#pragma once
namespace AutoChess {
	class ChessTile
	{
	private:
		int X;
		int Y;

	public:
		ChessTile() {};

		ChessTile(int x, int y) {
			setX(x);
			setY(y);
		}

		int getX() { return X; };
		int getY() { return Y; };
		void setX(int x) { X = x; };
		void setY(int y) { Y = y; };

		// Checks this tile is in range of the game board.
		bool isInBoardBounds() {
			return  (X < 8 && X >= 0 && Y < 8 && Y >= 0);
		};
	};

	class ChessMove
	{
	private:
		ChessTile MoveFromTile;
		ChessTile MoveToTile;

	public:
		ChessMove() {};

		static ChessMove CreateMove(ChessTile &moveFromTile, ChessTile &moveToTile)
		{
			ChessMove chessMove = ChessMove();

			chessMove.MoveFromTile = moveFromTile;
			chessMove.MoveToTile = moveToTile;

			return chessMove;
		};

		int getMoveFromTileX() { return MoveFromTile.getX(); };
		int getMoveFromTileY() { return MoveFromTile.getY(); };
		int getMoveToTileX() { return MoveToTile.getX(); };
		int getMoveToTileY() { return MoveToTile.getY(); };

		ChessTile getMoveFromTile() { return MoveFromTile; };
		ChessTile getMoveToTile() { return MoveToTile; };

		void setMoveFromTile(ChessTile moveFromTile) { MoveFromTile = moveFromTile; };
		void setMoveToTile(ChessTile moveToTile) { MoveToTile = moveToTile; };

		void setMoveFromTile(int moveFromTileX, int moveFromTileY) {
			MoveFromTile = ChessTile(moveFromTileX, moveFromTileY);
		};

		void setMoveToTile(int moveToTileX, int moveToTileY) {
			MoveToTile = ChessTile(moveToTileX, moveToTileY);
		};
	};
}