#include "gameTreeNode.h"
#include <iostream>
#include <cstring>
#include <stdlib.h>

using namespace std;

class gameTree
{
private:
	gameTreeNode* Root;			// 
	gameTreeNode* pCur;			//next state pointer

public:
	gameTree();
	~gameTree();

	int Max_Value(gameTreeNode* pTemp, int alpha, int beta);
	int Min_Value(gameTreeNode* pTemp, int alpha, int beta);
	int Term(gameTreeNode* pTemp);
	int Evaluation(gameTreeNode* pTemp);

	void setRoot(gameTreeNode* Root);
	gameTreeNode* getRoot();
	void set_pCur(gameTreeNode* pCur);
	gameTreeNode* get_pCur();
};

