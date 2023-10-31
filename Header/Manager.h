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
	char user_turn;		//White가 먼저 시작할건지 BLACK이 먼저 시작할건지 결정하는 value

public:
	Manager();
	~Manager();

	void Game();			//게임을 시작

	int Move_User_pawn(gameTree* pawn);	//유저의 pawn을 이동
	int Move_Com_pawn(gameTree* pawn);	//컴퓨터의 pawn을 minmax 알고리즘 기반으로 이동

	bool IsYourPawn(char* board, char* search_buf);		//내 pawn인지 확인
	bool IsMovable(char* c_board, char* start, char* end);	//움직일 수 있는 상태인지 확인
	bool initialSetting(gameTree* pawn, char* file_name);	//초기 보트 판을 load할건지 default를 사용하여 setting하는지 결정

	void print_state(gameTree* pawn);		//현재 노드에 대해서 state 출력

	void set_user_color(char user_color);
	char get_user_color();
	void set_user_turn(int user_turn);
	int get_user_turn();

	gameTree* gametree;
};

