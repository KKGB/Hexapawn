#include "gameTreeNode.h"
#include <iostream>
#include <cstring>
#include <stdlib.h>

using namespace std;

class gameTree
{
private:
	gameTreeNode* Root;			//current state pointer
	gameTreeNode* pCur;			//next state pointer

public:
	gameTree();
	~gameTree();

	int Max_Value(gameTreeNode* pTemp, int alpha, int beta);	//minimax algorithm에 사용하는 max값 함수
	int Min_Value(gameTreeNode* pTemp, int alpha, int beta);	//minimax algorithm에 사용하는 min값 함수
	int Term(gameTreeNode* pTemp);	//terminal condition을 고려하여 eval 값을 return하는 함수
	int Evaluation(gameTreeNode* pTemp);		//evaluation value를 구하는 함수

	void setRoot(gameTreeNode* Root);
	gameTreeNode* getRoot();
	void set_pCur(gameTreeNode* pCur);
	gameTreeNode* get_pCur();
};

