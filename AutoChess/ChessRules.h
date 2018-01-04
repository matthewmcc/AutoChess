
#pragma once  

#ifdef AUTO_CHESS_EXPORTS  
#define AUTO_CHESS_API __declspec(dllexport)   
#else  
#define AUTO_CHESS_API __declspec(dllimport)   
#endif 

#include "stdafx.h"
#include "ChessState.h"
#include "constAutoChess.h"

#include <list>
#include <map>

namespace AutoChess {
	class AUTO_CHESS_API ChessRules
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

		inline void getBlackPawnMoves(std::list<ChessState> &, ChessState &, ChessTile &);
		inline void getWhitePawnMoves(std::list<ChessState> &, ChessState &, int*);

		inline bool isWhiteInCheck(ChessState &, int*);
		inline bool isBlackInCheck(ChessState &, int*);

		// Get all possible moves for a piece of a certain type
		inline void getRookMoves(std::list<ChessState> &, ChessState &, int*);
		inline void getKnightMoves(std::list<ChessState> &, ChessState &, int*);
		inline void getBishopMoves(std::list<ChessState> &, ChessState &, int*);
		inline void getQueenMoves(std::list<ChessState> &, ChessState &, int*);
		inline void getKingMoves(std::list<ChessState> &, ChessState &, int*);

		inline ChessState createState(ChessState &state, ChessMove moveToMake);

		// Returns true if the current players in check.
		bool isCurrPlayerInCheck(ChessState &, int* currKingLoc);

		// Removes any state from the list where the passed king is in a state of check.
		// Only to be used when the king was in check the previous turn.
		void removeCheckStates(std::list<ChessState> &moves, int* kingToCheck, char typeOfKing);

		// Gets a pieces location
		inline int* getPieceLoc(ChessState &, char);
	};
}
