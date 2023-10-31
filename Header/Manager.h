#include "gameTree.h"
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <cmath>

class Manager
{
private:
	char user_color;	//������ pawn ����
	char user_turn;		//White�� ���� �����Ұ��� BLACK�� ���� �����Ұ��� �����ϴ� value

public:
	Manager();
	~Manager();

	void Game();			//������ ����

	int Move_User_pawn(gameTree* pawn);	//������ pawn�� �̵�
	int Move_Com_pawn(gameTree* pawn);	//��ǻ���� pawn�� minmax �˰��� ������� �̵�

	bool IsYourPawn(char* board, char* search_buf);		//�� pawn���� Ȯ��
	bool IsMovable(char* c_board, char* start, char* end);	//������ �� �ִ� �������� Ȯ��
	bool initialSetting(gameTree* pawn, char* file_name);	//�ʱ� ��Ʈ ���� load�Ұ��� default�� ����Ͽ� setting�ϴ��� ����

	void print_state(gameTree* pawn);		//���� ��忡 ���ؼ� state ���

	void set_user_color(char user_color);
	char get_user_color();
	void set_user_turn(int user_turn);
	int get_user_turn();

	gameTree* gametree;
};

