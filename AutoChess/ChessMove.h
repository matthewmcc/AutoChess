#pragma once
namespace AutoChess {
	struct ChessTile
	{
	private:
		int X;
		int Y;

	public:
		ChessTile(int x, int y) {
			setX(x);
			setY(y);
		}

		int getX() { return X; };
		int getY() { return Y; };
		void setX(int x) { X = x; };
		void setY(int y) { Y = y; };
	};

	struct ChessMove
	{
	private:
		ChessTile MoveFromTile;
		ChessTile MoveToTile;

		ChessMove();

	public:
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