#include "../Header/gameTree.h"

gameTree::gameTree()
{
	Root = NULL;
	pCur = NULL;

}

gameTree::~gameTree()
{
	if (Root)
	{
		delete Root;
	}
}

int gameTree::Max_Value(gameTreeNode* pTemp, int alpha, int beta)
{
	gameTreeNode* currRoot = pTemp;
	int temp = 0;
	int term_value = Term(currRoot);
	int eval_value = Evaluation(currRoot);

	//종료 상태
	if (term_value == 100 || term_value == -100)
		return term_value;

	if (currRoot->getLevel() == 3)
		return eval_value;

	char current_state[3][3];		//현재 상태를 나타낼 배열
	char next_state[3][3];			//다음 상태를 나타낼 배열

	char com_color = 'W';			//MAX이므로 양수 값을 갖는 White를 노드의 색깔로 설정
	char user_color = 'B';

	memset(current_state[0], 0, 3);
	memset(current_state[1], 0, 3);
	memset(current_state[2], 0, 3);

	memcpy(current_state, currRoot->getState(), 3 * 3);		//노드에 있는 State를 복사해옴



	//MAX == 컴퓨터가 WHITE일 경우
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (current_state[i][j] == com_color)
			{
				if ((current_state[i + 1][j - 1] == user_color) && i < 2 && j > 0)			//왼쪽 대각선 아래에 유저 말 위치
				{
					gameTreeNode* newNode = new gameTreeNode();
					newNode->setState(&current_state[0][0]);
					memcpy(next_state, newNode->getState(), 3 * 3);
					next_state[i][j] = '0';	
					next_state[i + 1][j - 1] = com_color;
					newNode->setState(&next_state[0][0]);			//왼쪽 대각선 아래로 유저 말을 잡고 상태 저장
					newNode->setLevel(currRoot->getLevel() + 1);	//하나 아래 level로 이동
					newNode->set_com_color('B');					//MIN 호출 전 BLACK 설정(유저 입장에서 진행)
					temp = Min_Value(newNode, alpha, beta);			//MIN 재귀 호출

					if (temp > alpha)	//alpha update
					{
						alpha = temp;

						if (newNode->getLevel() == 1)
						{
							pCur = newNode;
						}
					}

				}

				if (current_state[i + 1][j + 1] == user_color && i < 2 && j < 2)	//오른쪽 대각선 아래 유저 말 위치
				{
					gameTreeNode* newNode = new gameTreeNode();	
					newNode->setState(&current_state[0][0]);
					memcpy(next_state, newNode->getState(), 3 * 3);
					next_state[i][j] = '0';
					next_state[i + 1][j + 1] = com_color;
					newNode->setState(&next_state[0][0]);			//오른쪽 대각선 아래로 유저 말을 잡고 상태 저장
					newNode->setLevel(currRoot->getLevel() + 1);	//하나 아래 level로 이동
					newNode->set_com_color('B');					//MIN 호출 전 BLACK 설정(유저 입장에서 진행)
					temp = Min_Value(newNode, alpha, beta);			//MIN 재귀 호출
					
					if (temp > alpha)	//alpha update
					{
						alpha = temp;

						if (newNode->getLevel() == 1)
						{
							pCur = newNode;
						}
					}
				}

				if (current_state[i + 1][j] == '0' && i < 2)						//앞쪽이 비었을 때
				{
					gameTreeNode* newNode = new gameTreeNode();
					newNode->setState(&current_state[0][0]);
					memcpy(next_state, newNode->getState(), 3 * 3);
					next_state[i][j] = '0';						
					next_state[i + 1][j] = com_color;
					newNode->setState(&next_state[0][0]);			//앞으로 이동 후 상태 저장
					newNode->setLevel(currRoot->getLevel() + 1);	//하나 아래 level로 이동
					newNode->set_com_color('B');					//MIN 호출 전 BLACK 설정(유저 입장에서 진행)
					temp = Min_Value(newNode, alpha, beta);			//MIN 재귀 호출
					
					if (temp > alpha)	//alpha update
					{
						alpha = temp;

						if (newNode->getLevel() == 1)
						{
							pCur = newNode;
						}
					}

				}

				if (current_state[i][j - 1] == '0' && j > 0)						//왼쪽이 비었을 때
				{
					gameTreeNode* newNode = new gameTreeNode();
					newNode->setState(&current_state[0][0]);
					memcpy(next_state, newNode->getState(), 3 * 3);
					next_state[i][j] = '0';						
					next_state[i][j - 1] = com_color;
					newNode->setState(&next_state[0][0]);			//왼쪽으로 이동 후 상태 저장
					newNode->setLevel(currRoot->getLevel() + 1);	//하나 아래 level로 이동
					newNode->set_com_color('B');					//MIN 호출 전 BLACK 설정(유저 입장에서 진행)
					temp = Min_Value(newNode, alpha, beta);			//MIN 재귀 호출
					
					if (temp > alpha)	//alpha update
					{
						alpha = temp;

						if (newNode->getLevel() == 1)
						{
							pCur = newNode;
						}
					}
				}

				if (current_state[i][j + 1] == '0' && j < 2)						//오른쪽이 비었을 때
				{
					gameTreeNode* newNode = new gameTreeNode();
					newNode->setState(&current_state[0][0]);
					memcpy(next_state, newNode->getState(), 3 * 3);	
					next_state[i][j] = '0';
					next_state[i][j + 1] = com_color;
					newNode->setState(&next_state[0][0]);			//오른쪽으로 이동 후 상태 저장
					newNode->setLevel(currRoot->getLevel() + 1);	//하나 아래 level로 이동 
					newNode->set_com_color('B');					//MIN 호출 전 BLACK 설정(유저 입장에서 진행)
					temp = Min_Value(newNode, alpha, beta);			////MIN 재귀 호출
					
					if (temp > alpha)	//alpha update
					{
						alpha = temp;

						if (newNode->getLevel() == 1)
						{
							pCur = newNode;
						}
					}

				}

				if (alpha >= beta)			//pruning
					return beta;
			}
		}
	}
	return alpha;
}

int gameTree::Min_Value(gameTreeNode* pTemp, int alpha, int beta)
{
	int temp = 0;

	gameTreeNode* currRoot = pTemp;
	int term_value = Term(currRoot);
	int eval_value = Evaluation(currRoot);

	//종료 상태
	if (term_value == 100 || term_value == -100)
		return term_value;
	if (currRoot->getLevel() == 3)
		return eval_value;


	char current_state[3][3];		//현재 상태를 나타낼 배열
	char next_state[3][3];			//다음 상태를 나타낼 배열

	char com_color = 'B';
	char user_color = 'W';

	memset(current_state[0], 0, 3);
	memset(current_state[1], 0, 3);
	memset(current_state[2], 0, 3);


	memcpy(current_state, currRoot->getState(), 3 * 3);
	


	//MIN == 컴퓨터가 BLACK일 경우
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (current_state[i][j] == com_color)
			{
				if (current_state[i - 1][j - 1] == user_color && i > 0 && j > 0)	//왼쪽 대각선 위에 유저 말 위치
				{
					gameTreeNode* newNode = new gameTreeNode();					
					newNode->setState(&current_state[0][0]);
					memcpy(next_state, newNode->getState(), 3 * 3);	
					next_state[i][j] = '0';						
					next_state[i - 1][j - 1] = com_color;
					newNode->setState(&next_state[0][0]);			//왼쪽 대각선 위로 이동 후 state 저장
					newNode->setLevel(currRoot->getLevel() + 1);	//아래 level로 이동
					newNode->set_com_color('W');					//MIN 호출 전 WHITE로 설정()
					temp = Max_Value(newNode, alpha, beta);			//MIN 재귀 호출
					
					if (beta > temp)	//beta update
					{
						beta = temp;

						if (newNode->getLevel() == 1)
						{
							pCur = newNode;
						}
					}
				}

				if (current_state[i - 1][j + 1] == user_color && i > 0 && j < 2)	//오른쪽 대각선 위에 유저 말 위치
				{
					gameTreeNode* newNode = new gameTreeNode();					
					newNode->setState(&current_state[0][0]);
					memcpy(next_state, newNode->getState(), 3 * 3);	
					next_state[i][j] = '0';						
					next_state[i - 1][j + 1] = com_color;
					newNode->setState(&next_state[0][0]);			//오른쪽 대각선 위로 이동 후 state 저장
					newNode->setLevel(currRoot->getLevel() + 1);	//아래 level로 이동
					newNode->set_com_color('W');					//MIN 호출 전 WHITE로 설정()
					temp = Max_Value(newNode, alpha, beta);			//MIN 재귀 호출
					
					if (beta > temp)	//beta update
					{
						beta = temp;

						if (newNode->getLevel() == 1)
						{
							pCur = newNode;
						}
					}
				}

				if (current_state[i - 1][j] == '0' && i > 0)						//앞에 비어 있는 상태
				{
					gameTreeNode* newNode = new gameTreeNode();	
					newNode->setState(&current_state[0][0]);
					memcpy(next_state, newNode->getState(), 3 * 3);	
					next_state[i][j] = '0';						
					next_state[i - 1][j] = com_color;
					newNode->setState(&next_state[0][0]);			//앞으로 이동 후 state 저장
					newNode->setLevel(currRoot->getLevel() + 1);	//아래 level로 이동
					newNode->set_com_color('W');					//MIN 호출 전 WHITE로 설정()
					temp = Max_Value(newNode, alpha, beta);			//MIN 재귀 호출
					
					if (beta > temp)	//beta update
					{
						beta = temp;

						if (newNode->getLevel() == 1)
						{
							pCur = newNode;
						}
					}
				}

				if (current_state[i][j - 1] == '0' && j > 0)						//왼쪽에 비어 있는 상태
				{
					gameTreeNode* newNode = new gameTreeNode();
					newNode->setState(&current_state[0][0]);
					memcpy(next_state, newNode->getState(), 3 * 3);
					next_state[i][j] = '0';						
					next_state[i][j - 1] = com_color;
					newNode->setState(&next_state[0][0]);			//왼쪽으로 이동 후 state 저장
					newNode->setLevel(currRoot->getLevel() + 1);	//아래 level로 이동
					newNode->set_com_color('W');					//MIN 호출 전 WHITE로 설정()
					temp = Max_Value(newNode, alpha, beta);			//MIN 재귀 호출
					
					if (beta > temp)	//beta update
					{
						beta = temp;

						if (newNode->getLevel() == 1)
						{
							pCur = newNode;
						}
					}
				}

				if (current_state[i][j + 1] == '0' && j < 2)						//오른쪽에 비어 있는 상태
				{
					gameTreeNode* newNode = new gameTreeNode();
					newNode->setState(&current_state[0][0]);
					memcpy(next_state, newNode->getState(), 3 * 3);

					next_state[i][j] = '0';
					next_state[i][j + 1] = com_color;

					newNode->setState(&next_state[0][0]);			//오른쪽으로 이동 후 state 저장
					newNode->setLevel(currRoot->getLevel() + 1);	//아래 level로 이동
					newNode->set_com_color('W');					//MIN 호출 전 WHITE로 설정()
					temp = Max_Value(newNode, alpha, beta);			//MIN 재귀 호출
					
					if (beta > temp)	//beta update
					{
						beta = temp;

						if (newNode->getLevel() == 1)
						{
							pCur = newNode;
						}
					}
				}

				if (beta <= alpha)				//pruning
					return alpha;
			}
		}
	}
	return beta;
}

int gameTree::Term(gameTreeNode* pTemp)
{
	int e_value = 0;

	char board[3][3];
	memcpy(board, pTemp->getState(), 3 * 3);

	int w_count = 0;
	int b_count = 0;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (board[i][j] == 'B') b_count++;

			if (board[i][j] == 'W') w_count++;

			//종료 조건 1 - pawn이 반대 끝에 도달하는 경우
			if (i == 0 && board[i][j] == 'B') return -100;
			if (i == 2 && board[i][j] == 'W') return 100;
		}
	}


	//종료 조건 2 - 한쪽 색의 pawn이 없는 경우
	if (w_count == 0 ) return -100;
	if (b_count == 0 ) return 100;

	//종료 조건 3 - 못 움직이는 경우
	//검은색이 이길 때
	if (w_count == 1 && (b_count == 2 || b_count == 3)) 	//흰색 말 1개 사방으로 막힐 때
	{
		if (board[1][0] == 'W' && board[1][1] == 'B' && board[2][1] == 'B')
			return -100;

		if (board[1][1] == 'B' && board[1][2] == 'W' && board[2][2] == 'B')
			return -100;

		if (board[1][0] == 'B' && board[1][1] == 'W' && board[1][2] == 'B' && board[2][1] == 'B')
			return -100;
	}

	//흰색이 이길 때
	if (b_count == 1 && (w_count == 2 || w_count == 3))	//검은색 말 1개 사방으로 막힐 때
	{
		if (board[0][0] == 'W' && board[1][0] == 'B' && board[1][1] == 'W')
			return 100;

		if (board[0][2] == 'W' && board[1][1] == 'W' && board[1][2] == 'B')
			return 100;

		if (board[0][1] == 'W' && board[1][0] == 'W' && board[1][1] == 'B' && board[1][2] == 'W')
			return 100;
	}



	e_value = Evaluation(pTemp);
	return e_value;
}

int gameTree::Evaluation(gameTreeNode* pTemp)
{
	char board[3][3];
	memcpy(board, pTemp->getState(), 3 * 3);

	int w_pawn = 0;
	int b_pawn = 0;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (i == 0)
			{
				if (board[i][j] == 'W')		//1행에서 White가 있을 때 +1
					w_pawn += 1;
			}

			else if (i == 1)
			{
				if (board[i][j] == 'W')
					w_pawn += 4;			//2행에서 White나 Black이 있을 때 +4

				else if (board[i][j] == 'B')
					b_pawn += 4;
			}

			else
			{
				if (board[i][j] == 'B')		//3행에서 Black이 있을 때 +1
					b_pawn += 1;
			}
		}
	}
	int eval = w_pawn - b_pawn;
	return eval;
}

void gameTree::setRoot(gameTreeNode* Root)
{
	this->Root = Root;
}

gameTreeNode* gameTree::getRoot()
{
	return Root;
}

void gameTree::set_pCur(gameTreeNode* pCur)
{
	this->pCur = pCur;
}

gameTreeNode* gameTree::get_pCur()
{
	return pCur;
}




