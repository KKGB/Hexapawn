#include "gameTree.h"
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <cmath>

class Manager
{
private:
	char user_color;	//유저의 pawn 색깔
	char user_turn;		//턴을 결정하는 value

public:
	Manager();
	~Manager();

	void Game();

	int Move_User_pawn(gameTree* pawn);
	int Move_Com_pawn(gameTree* pawn);

	bool IsYourPawn(char* board, char* search_buf);
	bool IsMovable(char* c_board, char* start, char* end);
	bool InitialSetting(gameTree* pawn, char* file_name);

	void print_state(gameTree* pawn);

	void set_user_color(char user_color);
	char get_user_color();
	void set_user_turn(int user_turn);
	int get_user_turn();

	gameTree* gametree;
};

