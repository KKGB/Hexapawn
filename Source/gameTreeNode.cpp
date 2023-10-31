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

void gameTreeNode::setLevel(int level)
{
	this->level = level;
}
int gameTreeNode::getLevel()
{
	return level;
}

void gameTreeNode::setEval(int eval)
{
	this->eval = eval;
}
int gameTreeNode::getEval()
{
	return eval;
}

void gameTreeNode::set_com_color(char com_color)
{
	this->com_color = com_color;
}
char gameTreeNode::get_com_color()
{
	return com_color;
}

void gameTreeNode::setState(char* state)
{
	memcpy(this->state, state, 3 * 3);
}
char* gameTreeNode::getState()
{
	return &state[0][0];
}





