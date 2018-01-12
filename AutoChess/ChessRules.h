
#pragma once  

#include "stdafx.h"

#include "ChessState.h"
#include "ChessMove.h"
#include "PawnMoves.h"
#include "RookMoves.h"
#include "BishopMoves.h"
#include "KnightMoves.h"
#include "QueenMoves.h"
#include "KingMoves.h"
#include "BlackKingCheckStatus.h"
#include "WhiteKingCheckStatus.h"

#include <list>
#include <map>

namespace AutoChess {
	class ChessRules
	{
	public:
		static ChessRules& getInstance();

		// If this returns zero moves if the game is in an terminal state.
		std::list<ChessState> getMoves(ChessState &);

	private:
		// Singleton functions
		ChessRules();
		~ChessRules();
		ChessRules(const ChessRules &);
		const ChessRules & operator = (const ChessRules &);

		/// These functions are divided by piece color for effiency.
		inline std::list<ChessState> getBlackMoves(ChessState &);
		inline std::list<ChessState> getWhiteMoves(ChessState &);

		std::list<ChessState> removeBlackCheckStates(std::list<ChessState> &moves);
		bool isBlackInCheck(ChessState &stateToTest);

		std::list<ChessState> removeWhiteCheckStates(std::list<ChessState> &moves);
		bool isWhiteInCheck(ChessState &stateToTest);
	};
}
