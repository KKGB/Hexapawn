#include "../Header/gameTreeNode.h"

gameTreeNode::gameTreeNode()
{
	level = 0;
	eval = 0;
    com_color = NULL;
    memset(state[0], 0, 3);
    memset(state[1], 0, 3);
    memset(state[2], 0, 3);
}

gameTreeNode::~gameTreeNode() {}

// gameTree에서 노드의 Level 관련 함수
void gameTreeNode::setLevel(int level)
{
	this->level = level;
}
int gameTreeNode::getLevel()
{
	return level;
}

// gameTree에서 노드의 평가함수 결과값 관련 함수
void gameTreeNode::setEval(int eval)
{
	this->eval = eval;
}
int gameTreeNode::getEval()
{
	return eval;
}

// 인공지능의 폰 색깔 관련 함수
void gameTreeNode::set_com_color(char com_color)
{
	this->com_color = com_color;
}
char gameTreeNode::get_com_color()
{
	return com_color;
}

// gameTree에서 노드의 상태 관련 함수
void gameTreeNode::setState(char* state)
{
	memcpy(this->state, state, static_cast<size_t>(3) * 3);
}
char* gameTreeNode::getState()
{
	return &state[0][0];
}





