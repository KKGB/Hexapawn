#include <iostream>
#include <stdlib.h>
#include <string.h>

class gameTreeNode
{
private:
	int level;				//트리에서 level을 나타냄
	int eval;				//평가값을 의미
	char com_color;			//컴퓨터의 pawn 색깔
	char state[3][3];		//트리에서 노드의 state
	

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

