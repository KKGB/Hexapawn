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

	int Max_Value(gameTreeNode* pTemp, int alpha, int beta);	//minimax algorithm�� ����ϴ� max�� �Լ�
	int Min_Value(gameTreeNode* pTemp, int alpha, int beta);	//minimax algorithm�� ����ϴ� min�� �Լ�
	int Term(gameTreeNode* pTemp);	//terminal condition�� ����Ͽ� eval ���� return�ϴ� �Լ�
	int Evaluation(gameTreeNode* pTemp);		//evaluation value�� ���ϴ� �Լ�

	void setRoot(gameTreeNode* Root);
	gameTreeNode* getRoot();
	void set_pCur(gameTreeNode* pCur);
	gameTreeNode* get_pCur();
};

