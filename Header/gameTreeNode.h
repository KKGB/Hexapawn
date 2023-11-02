#include <iostream>
#include <stdlib.h>
#include <string.h>

class gameTreeNode
{
private:
	int level;				// gameTree에서 Level을 나타냄
	int eval;				// 평가함수 결과값
	char com_color;			// 인공지능의 폰 색깔
	char state[3][3];		// gameTree에서 노드의 state
	

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

