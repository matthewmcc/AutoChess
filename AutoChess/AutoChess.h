
#pragma once  

#ifdef AUTO_CHESS_EXPORTS  
#define AUTO_CHESS_API __declspec(dllexport)   
#else  
#define AUTO_CHESS_API __declspec(dllimport)   
#endif 

#include "AlphaBetaSearch.h"
#include "ChessRules.h"
#include "ChessState.h"