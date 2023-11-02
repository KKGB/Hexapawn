#include <iostream>
#include <stdlib.h>
#include <string.h>

class gameTreeNode
{
private:
	int level;				// gameTree���� Level�� ��Ÿ��
	int eval;				// ���Լ� �����
	char com_color;			// �ΰ������� �� ����
	char state[3][3];		// gameTree���� ����� state
	

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

