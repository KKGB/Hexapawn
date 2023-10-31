#include <iostream>
#include <stdlib.h>
#include <string.h>

class gameTreeNode
{
private:
	int level;				//Ʈ������ level�� ��Ÿ��
	int eval;				//�򰡰��� �ǹ�
	char com_color;			//��ǻ���� pawn ����
	char state[3][3];		//Ʈ������ ����� state
	

public:
	gameTreeNode();
	~gameTreeNode();

	void setLevel(int level);
	int getLevel();
	void setEval(int eval);
	int getEval();
	void set_com_color(char com_color);
	char get_com_color();
	void setState(char* state);
	char* getState();
	
};

