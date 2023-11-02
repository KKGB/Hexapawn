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

/// <summary>
/// �ִ� �ּ� �˰��򿡼� �ִ� ���� �Լ�
/// </summary>
/// <param name="pTemp"></param>
/// <param name="alpha"></param>
/// <param name="beta"></param>
/// <returns></returns>
int gameTree::Max_Value(gameTreeNode* pTemp, int alpha, int beta)
{
	gameTreeNode* currRoot = pTemp;
	int temp = 0;
	int term_value = Term(currRoot);
	int eval_value = Evaluation(currRoot);

	//���� ����
	if (term_value == 100 || term_value == -100)
		return term_value;

	if (currRoot->getLevel() == 3)
		return eval_value;

	char current_state[3][3]{};		//���� ���¸� ��Ÿ�� �迭
	char next_state[3][3]{};			//���� ���¸� ��Ÿ�� �迭

	char com_color = 'W';			//MAX�̹Ƿ� ��� ���� ���� White�� ����� ����� ����
	char user_color = 'B';

	memcpy(current_state, currRoot->getState(), static_cast<size_t>(3) * 3);		//��忡 �ִ� State�� �����ؿ�

	//MAX == ��ǻ�Ͱ� WHITE�� ���
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (current_state[i][j] == com_color)
			{
				if (i < 2 && j > 0 && current_state[i + 1][j - 1] == user_color)			//���� �밢�� �Ʒ��� ���� �� ��ġ
				{
					gameTreeNode* newNode = new gameTreeNode();
					newNode->setState(&current_state[0][0]);
					memcpy(next_state, newNode->getState(), static_cast<size_t>(3) * 3);
					next_state[i][j] = '0';	
					next_state[i + 1][j - 1] = com_color;
					newNode->setState(&next_state[0][0]);			//���� �밢�� �Ʒ��� ���� ���� ��� ���� ����
					newNode->setLevel(currRoot->getLevel() + 1);	//�ϳ� �Ʒ� level�� �̵�
					newNode->set_com_color('B');					//MIN ȣ�� �� BLACK ����(���� ���忡�� ����)
					temp = Min_Value(newNode, alpha, beta);			//MIN ��� ȣ��

					if (temp > alpha)	//alpha update
					{
						alpha = temp;

						if (newNode->getLevel() == 1)
						{
							pCur = newNode;
						}
					}

				}

				if (i < 2 && j < 2 && current_state[i + 1][j + 1] == user_color)	//������ �밢�� �Ʒ� ���� �� ��ġ
				{
					gameTreeNode* newNode = new gameTreeNode();	
					newNode->setState(&current_state[0][0]);
					memcpy(next_state, newNode->getState(), static_cast<size_t>(3) * 3);
					next_state[i][j] = '0';
					next_state[i + 1][j + 1] = com_color;
					newNode->setState(&next_state[0][0]);			//������ �밢�� �Ʒ��� ���� ���� ��� ���� ����
					newNode->setLevel(currRoot->getLevel() + 1);	//�ϳ� �Ʒ� level�� �̵�
					newNode->set_com_color('B');					//MIN ȣ�� �� BLACK ����(���� ���忡�� ����)
					temp = Min_Value(newNode, alpha, beta);			//MIN ��� ȣ��
					
					if (temp > alpha)	//alpha update
					{
						alpha = temp;

						if (newNode->getLevel() == 1)
						{
							pCur = newNode;
						}
					}
				}

				if (i < 2 && current_state[i + 1][j] == '0')						//������ ����� ��
				{
					gameTreeNode* newNode = new gameTreeNode();
					newNode->setState(&current_state[0][0]);
					memcpy(next_state, newNode->getState(), static_cast<size_t>(3) * 3);
					next_state[i][j] = '0';						
					next_state[i + 1][j] = com_color;
					newNode->setState(&next_state[0][0]);			//������ �̵� �� ���� ����
					newNode->setLevel(currRoot->getLevel() + 1);	//�ϳ� �Ʒ� level�� �̵�
					newNode->set_com_color('B');					//MIN ȣ�� �� BLACK ����(���� ���忡�� ����)
					temp = Min_Value(newNode, alpha, beta);			//MIN ��� ȣ��
					
					if (temp > alpha)	//alpha update
					{
						alpha = temp;

						if (newNode->getLevel() == 1)
						{
							pCur = newNode;
						}
					}

				}

				if (j > 0 && current_state[i][j - 1] == '0')						//������ ����� ��
				{
					gameTreeNode* newNode = new gameTreeNode();
					newNode->setState(&current_state[0][0]);
					memcpy(next_state, newNode->getState(), static_cast<size_t>(3) * 3);
					next_state[i][j] = '0';						
					next_state[i][j - 1] = com_color;
					newNode->setState(&next_state[0][0]);			//�������� �̵� �� ���� ����
					newNode->setLevel(currRoot->getLevel() + 1);	//�ϳ� �Ʒ� level�� �̵�
					newNode->set_com_color('B');					//MIN ȣ�� �� BLACK ����(���� ���忡�� ����)
					temp = Min_Value(newNode, alpha, beta);			//MIN ��� ȣ��
					
					if (temp > alpha)	//alpha update
					{
						alpha = temp;

						if (newNode->getLevel() == 1)
						{
							pCur = newNode;
						}
					}
				}

				if (j < 2 && current_state[i][j + 1] == '0')						//�������� ����� ��
				{
					gameTreeNode* newNode = new gameTreeNode();
					newNode->setState(&current_state[0][0]);
					memcpy(next_state, newNode->getState(), static_cast<size_t>(3) * 3);
					next_state[i][j] = '0';
					next_state[i][j + 1] = com_color;
					newNode->setState(&next_state[0][0]);			//���������� �̵� �� ���� ����
					newNode->setLevel(currRoot->getLevel() + 1);	//�ϳ� �Ʒ� level�� �̵� 
					newNode->set_com_color('B');					//MIN ȣ�� �� BLACK ����(���� ���忡�� ����)
					temp = Min_Value(newNode, alpha, beta);			////MIN ��� ȣ��
					
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

/// <summary>
/// �ִ� �ּ� �˰��򿡼� �ּڰ� ���� �Լ�
/// </summary>
/// <param name="pTemp"></param>
/// <param name="alpha"></param>
/// <param name="beta"></param>
/// <returns></returns>
int gameTree::Min_Value(gameTreeNode* pTemp, int alpha, int beta)
{
	int temp = 0;

	gameTreeNode* currRoot = pTemp;
	int term_value = Term(currRoot);
	int eval_value = Evaluation(currRoot);

	//���� ����
	if (term_value == 100 || term_value == -100)
		return term_value;
	if (currRoot->getLevel() == 3)
		return eval_value;


	char current_state[3][3]{};		//���� ���¸� ��Ÿ�� �迭
	char next_state[3][3]{};			//���� ���¸� ��Ÿ�� �迭

	char com_color = 'B';
	char user_color = 'W';

	memcpy(current_state, currRoot->getState(), static_cast<size_t>(3) * 3);
	
	//MIN == ��ǻ�Ͱ� BLACK�� ���
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (current_state[i][j] == com_color)
			{
				if (i > 0 && j > 0 && current_state[i - 1][j - 1] == user_color)	//���� �밢�� ���� ���� �� ��ġ
				{
					gameTreeNode* newNode = new gameTreeNode();					
					newNode->setState(&current_state[0][0]);
					memcpy(next_state, newNode->getState(), static_cast<size_t>(3) * 3);
					next_state[i][j] = '0';						
					next_state[i - 1][j - 1] = com_color;
					newNode->setState(&next_state[0][0]);			//���� �밢�� ���� �̵� �� state ����
					newNode->setLevel(currRoot->getLevel() + 1);	//�Ʒ� level�� �̵�
					newNode->set_com_color('W');					//MIN ȣ�� �� WHITE�� ����()
					temp = Max_Value(newNode, alpha, beta);			//MIN ��� ȣ��
					
					if (beta > temp)	//beta update
					{
						beta = temp;

						if (newNode->getLevel() == 1)
						{
							pCur = newNode;
						}
					}
				}

				if (i > 0 && j < 2 && current_state[i - 1][j + 1] == user_color)	//������ �밢�� ���� ���� �� ��ġ
				{
					gameTreeNode* newNode = new gameTreeNode();					
					newNode->setState(&current_state[0][0]);
					memcpy(next_state, newNode->getState(), static_cast<size_t>(3) * 3);
					next_state[i][j] = '0';						
					next_state[i - 1][j + 1] = com_color;
					newNode->setState(&next_state[0][0]);			//������ �밢�� ���� �̵� �� state ����
					newNode->setLevel(currRoot->getLevel() + 1);	//�Ʒ� level�� �̵�
					newNode->set_com_color('W');					//MIN ȣ�� �� WHITE�� ����()
					temp = Max_Value(newNode, alpha, beta);			//MIN ��� ȣ��
					
					if (beta > temp)	//beta update
					{
						beta = temp;

						if (newNode->getLevel() == 1)
						{
							pCur = newNode;
						}
					}
				}

				if (i > 0 && current_state[i - 1][j] == '0')						//�տ� ��� �ִ� ����
				{
					gameTreeNode* newNode = new gameTreeNode();	
					newNode->setState(&current_state[0][0]);
					memcpy(next_state, newNode->getState(), static_cast<size_t>(3) * 3);
					next_state[i][j] = '0';						
					next_state[i - 1][j] = com_color;
					newNode->setState(&next_state[0][0]);			//������ �̵� �� state ����
					newNode->setLevel(currRoot->getLevel() + 1);	//�Ʒ� level�� �̵�
					newNode->set_com_color('W');					//MIN ȣ�� �� WHITE�� ����()
					temp = Max_Value(newNode, alpha, beta);			//MIN ��� ȣ��
					
					if (beta > temp)	//beta update
					{
						beta = temp;

						if (newNode->getLevel() == 1)
						{
							pCur = newNode;
						}
					}
				}

				if (j > 0 && current_state[i][j - 1] == '0')						//���ʿ� ��� �ִ� ����
				{
					gameTreeNode* newNode = new gameTreeNode();
					newNode->setState(&current_state[0][0]);
					memcpy(next_state, newNode->getState(), static_cast<size_t>(3) * 3);
					next_state[i][j] = '0';						
					next_state[i][j - 1] = com_color;
					newNode->setState(&next_state[0][0]);			//�������� �̵� �� state ����
					newNode->setLevel(currRoot->getLevel() + 1);	//�Ʒ� level�� �̵�
					newNode->set_com_color('W');					//MIN ȣ�� �� WHITE�� ����()
					temp = Max_Value(newNode, alpha, beta);			//MIN ��� ȣ��
					
					if (beta > temp)	//beta update
					{
						beta = temp;

						if (newNode->getLevel() == 1)
						{
							pCur = newNode;
						}
					}
				}

				if (j < 2 && current_state[i][j + 1] == '0')						//�����ʿ� ��� �ִ� ����
				{
					gameTreeNode* newNode = new gameTreeNode();
					newNode->setState(&current_state[0][0]);
					memcpy(next_state, newNode->getState(), static_cast<size_t>(3) * 3);

					next_state[i][j] = '0';
					next_state[i][j + 1] = com_color;

					newNode->setState(&next_state[0][0]);			//���������� �̵� �� state ����
					newNode->setLevel(currRoot->getLevel() + 1);	//�Ʒ� level�� �̵�
					newNode->set_com_color('W');					//MIN ȣ�� �� WHITE�� ����()
					temp = Max_Value(newNode, alpha, beta);			//MIN ��� ȣ��
					
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

/// <summary>
/// ���� �ܰ踦 ����Ͽ� �� �Լ��� ����� ����ϴ� �Լ�
/// </summary>
/// <param name="pTemp"></param>
/// <returns></returns>
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

			//���� ���� 1 - pawn�� �ݴ� ���� �����ϴ� ���
			if (i == 0 && board[i][j] == 'B') return -100;
			if (i == 2 && board[i][j] == 'W') return 100;
		}
	}


	//���� ���� 2 - ���� ���� pawn�� ���� ���
	if (w_count == 0 ) return -100;
	if (b_count == 0 ) return 100;

	//���� ���� 3 - �� �����̴� ���
	//�������� �̱� ��
	if (w_count == 1 && (b_count == 2 || b_count == 3)) 	//��� �� 1�� ������� ���� ��
	{
		if (board[1][0] == 'W' && board[1][1] == 'B' && board[2][1] == 'B')
			return -100;

		if (board[1][1] == 'B' && board[1][2] == 'W' && board[2][2] == 'B')
			return -100;

		if (board[1][0] == 'B' && board[1][1] == 'W' && board[1][2] == 'B' && board[2][1] == 'B')
			return -100;
	}

	//����� �̱� ��
	if (b_count == 1 && (w_count == 2 || w_count == 3))	//������ �� 1�� ������� ���� ��
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

/// <summary>
/// ������ ����ϴ� �� �Լ�
/// </summary>
/// <param name="pTemp"></param>
/// <returns></returns>
int gameTree::Evaluation(gameTreeNode* pTemp)
{
	char board[3][3];
	memcpy(board, pTemp->getState(), static_cast<size_t>(3) * 3);

	int w_pawn = 0;
	int b_pawn = 0;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (i == 0)
			{
				if (board[i][j] == 'W')		//1�࿡�� White�� ���� �� +1
					w_pawn += 1;
			}

			else if (i == 1)
			{
				if (board[i][j] == 'W')
					w_pawn += 4;			//2�࿡�� White�� Black�� ���� �� +4

				else if (board[i][j] == 'B')
					b_pawn += 4;
			}

			else
			{
				if (board[i][j] == 'B')		//3�࿡�� Black�� ���� �� +1
					b_pawn += 1;
			}
		}
	}
	int eval = w_pawn - b_pawn;
	return eval;
}

// gameTree�� Root�� ���� �Լ�
void gameTree::setRoot(gameTreeNode* Root)
{
	this->Root = Root;
}
gameTreeNode* gameTree::getRoot()
{
	return Root;
}

// gameTree�� ���� ��忡 ���õ� �Լ�
void gameTree::set_pCur(gameTreeNode* pCur)
{
	this->pCur = pCur;
}
gameTreeNode* gameTree::get_pCur()
{
	return pCur;
}




