#pragma warning (disable:4996)
#include "../Header/Manager.h"

using namespace std;

Manager::Manager()
{
	gametree = NULL;
	user_color = NULL;
	user_turn = 0;
}

Manager::~Manager(){}

/// <summary>
/// ������ ���� ���� �Լ�
/// </summary>
/// <returns></returns>
void Manager::Game()
{
	while (1)
	{
		gametree = new gameTree();		// minimax Tree ����
		gameTreeNode* newNode = new gameTreeNode();		// ��� ����
		gametree->setRoot(newNode);
		gametree->set_pCur(newNode);

		char buf[20] = { 0 };
		int turn = 0;
		int eval = 0;

		cout << "Welcome to Hexapawn game!!!" << endl << endl;

		// 1) pawn ���� ����
		cout << "Type ""WHITE"" or ""BLACK"": ";
		cin >> buf;

		if (strcmp(buf, "WHITE") != 0 && strcmp(buf, "BLACK") != 0)
		{
			cout << "������ ����� �������� �ʾҽ��ϴ�. ���α׷� �����մϴ�." << endl;
			return;
		}

		else
		{
			// User : ��, Com : ��
			if (strcmp(buf, "WHITE") == 0)
			{
				cout << "WHITE : USER / BLACK : COMPUTER" << endl;
				set_user_color('W');
				gametree->getRoot()->set_com_color('B');
			}

			// User : ��, Com : ��
			else
			{
				cout << "BLACK : USER / WHITE : COMPUTER" << endl;
				set_user_color('B');
				gametree->getRoot()->set_com_color('W');
			}

			cout << endl;
		}



		// 2) ���� �İ� ����
		cout << "WHITE first (1) BLACK first (2): ";
		cin >> turn;

		if (turn != 1 && turn != 2)
		{
			cout << "������ ����� �������� �ʾҽ��ϴ�. ���α׷��� �����մϴ�." << endl;
			return;
		}

		else
		{
			// ���� ����
			if ((turn == 1 && strcmp(buf, "WHITE") == 0) || (turn == 2 && strcmp(buf, "BLACK") == 0))
			{
				cout << "User first!!!" << endl;
				if (turn == 1) set_user_turn(1);
				else set_user_turn(2);
			}

			// ��ǻ�� ����
			else
			{
				cout << "Computer first!!!" << endl;
				if (turn == 1) set_user_turn(1);
				else set_user_turn(2);
			}

			cout << endl;
		}

		// 3) �ʱ� ���� ���� ����
		memset(buf, 0, sizeof(buf));
		cout << "Input file name (default board=0): ";
		cin >> buf;

		if (!initialSetting(gametree, buf))
		{
			cout << "������ �������� �ʽ��ϴ�. ���α׷��� �����մϴ�." << endl;
			return;
		}

		print_state(gametree);
		char com_color = gametree->getRoot()->get_com_color();		//���� ���� �� computer�� �����̰� ���� computer�� ���� ���� ���߱� ����

		cout << endl << endl;

		// 4-1) ���� ����
		if ((get_user_color() == 'W' && get_user_turn() == 1) || ((get_user_color() == 'B') && get_user_turn() == 2))
		{
			while (eval != 100 && eval != -100)
			{
				//���� ����
				eval = Move_User_pawn(gametree);		//���� �� �̵�

				cout << "=========================" << endl;
				cout << "USER" << endl;
				print_state(gametree);					//���� ���

				if (eval == 100 || eval == -100)		//���� ����
					break;
				cout << "=========================" << endl << endl;

				//��ǻ�� ����
				cout << "==========================" << endl;
				cout << "COMPUTER" << endl;

				eval = Move_Com_pawn(gametree);			//��ǻ�� �� �̵�
				gametree->getRoot()->set_com_color(com_color);	//��ǻ���� ���� ���� �� ����
				print_state(gametree);					//���� ���

				if (eval == 100 || eval == -100)		//���� ����
					break;
				cout << "=========================" << endl << endl;
			}
		}

		// 4-2) ��ǻ�� ����
		else
		{
			while (eval != 100 && eval != -100)
			{
				//��ǻ�� ����
				cout << "===================================================" << endl;
				cout << "COMPUTER" << endl;

				eval = Move_Com_pawn(gametree);			//��ǻ�� �� �̵�
				gametree->getRoot()->set_com_color(com_color);	//��ǻ���� ���� ���� �� ����
				print_state(gametree);					//���� ���

				if (eval == 100 || eval == -100)		//���� ����
					break;

				cout << "===================================================" << endl << endl;


				//���� ����
				eval = Move_User_pawn(gametree);		//���� �� �̵�

				cout << "===================================================" << endl;
				cout << "USER" << endl;
				print_state(gametree);					//���� ���

				if (eval == 100 || eval == -100)		//���� ����
					break;
				cout << "===================================================" << endl << endl;
			}

		}


		cout << "�������� -- ";


		if (eval == 100)
		{
			if (get_user_color() == 'B')
			{
				cout << "HUMAN LOSS" << endl;

			}
			else
			{
				cout << "HUMAN WIN" << endl;
			}
		}
		else	//eval == -100
		{
			if (get_user_color() == 'B')
			{
				cout << "HUMAN WIN" << endl;
			}
			else
			{
				cout << "HUMAN LOSE" << endl;
			}
		}


		while (1)
		{
			int again = 0;
			cout << "Play more (1), Exit (2) : ";
			cin >> again;

			if (again == 1)
			{
				delete gametree;		//1�� ���� �� ���� �ٽ� ����
				system("cls");
				break;
			}

			else if (again == 2)
			{
				delete gametree;		//2�� ���� �� ���� ����
				return;
			}

			else
			{
				cout << "�߸� �Է��߱� ������ ���� �����ϰڽ��ϴ�." << endl;		//�� �̿� ���� �ÿ��� ���� ����
				delete gametree;
				return;
			}
		}

	}
	
	return;
}

int Manager::Move_User_pawn(gameTree* pawn)
{
	gameTreeNode* pc_Root = pawn->getRoot();			//current Node

	int turn = 0;
	int term_value = 0;
	char startPos[10];
	char endPos[10];
	char board[3][3];

	memcpy(board, pc_Root->getState(), 3 * 3);

	term_value = pawn->Term(pawn->getRoot());		//�ʱ� ���¿� �̱� �� �ۿ� ���� ������ �о�� �� ���� ó��

	if (term_value == -100)
	{
		cout << "BLACK�� �̱� �� �ۿ� ���� �����Դϴ�." << endl;
		return term_value;
	}

	if (term_value == 100)
	{
		cout << "WHITE�� �̱� �� �ۿ� ���� �����Դϴ�." << endl;
		return term_value;
	}

	cout << "����� �����Դϴ�!" << endl;
	cout << "����� ���� ����ּ���!!" << endl;

	while (1)
	{
		cout << "ex) 1�� 1�� -> 1,1 " << endl;
		cin >> startPos;

		if (!IsYourPawn(&board[0][0], startPos))	//�� pawn�� �ƴ� ���
		{
			cout << endl;
			cout << startPos[0] << "�� " << startPos[2] << "���� �ִ� pawn�� ����� ���� �ƴմϴ�." << endl;
			cout << "�ٽ� ����ּ���!!" << endl;
		}

		else
		{
			cout << endl;
			cout << "pawn�� ���� �νǰǰ���?" << endl;
			cout << "ex) 2�� 1�� -> 2,1 " << endl;
			cin >> endPos;

			if (!IsMovable(&board[0][0], startPos, endPos))		//���ϴ� ������ ������ �� ���� ���
			{
				cout << endl;
				cout << endPos[0] << "�� " << endPos[2] << "���� ������ �� �����ϴ�." << endl << endl;
				cout << "�ٽ� ����ּ���!!" << endl;
			}

			else
				break;
		}
	}

	term_value = pawn->Term(pawn->getRoot());
	return term_value;
}

int Manager::Move_Com_pawn(gameTree* pawn)
{
	int term_value = 0;

	term_value = pawn->Term(pawn->getRoot());			//�ʱ� ���¿� �̱� �� �ۿ� ���� ������ �о�� �� ���� ó��

	if (term_value == -100)
	{
		cout << "BLACK�� �̱� �� �ۿ� ���� �����Դϴ�." << endl;
		return term_value;
	}

	if (term_value == 100)
	{
		cout << "WHITE�� �̱� �� �ۿ� ���� �����Դϴ�." << endl;
		return term_value;
	}

	//move computer pawn
	if (get_user_color() == 'B')
		term_value = pawn->Max_Value(pawn->getRoot(), -200, 200);
	else
		term_value = pawn->Min_Value(pawn->getRoot(), -200, 200);

	pawn->setRoot(pawn->get_pCur());
	pawn->getRoot()->setLevel(0);
	//term_value 100 is white win, -100 is black win

	term_value = pawn->Term(pawn->getRoot());
	return term_value;
}

bool Manager::IsYourPawn(char* board, char* search_buf)
{
	char buf[3][3];
	memcpy(buf, board, 3 * 3);

	int i = *(search_buf + 0) - 49;
	int j = *(search_buf + 2) - 49;

	if (i > 3 || j > 3 || i < 0 || j < 0 || buf[i][j] != get_user_color())		//�� ������ ����ų� ������ ����� �ٸ� ���(�� pawn�� �ƴ� ���)
		return false;

	return true;
}

bool Manager::IsMovable(char* board, char* start, char* end)
{
	char buf[3][3];
	memcpy(buf, board, 3 * 3);

	int rowStart = *(start + 0) - 49;
	int colStart = *(start + 2) - 49;		//�̵� �� ��ġ��

	int rowEnd = *(end + 0) - 49;
	int colEnd = *(end + 2) - 49;			//�̵� �� ��ġ��

	if (rowEnd > 3 || colEnd > 3 || rowEnd < 0 || colEnd < 0 || abs(colEnd - colStart) > 1 || abs(rowEnd - rowStart) > 1)	// ��ĭ �̻� �����̰ų� ���� ��� ��
		return false;


	if (get_user_color() == 'B')	//���� == BLACK
	{
		if (buf[rowStart][colStart] == 'B' && (buf[rowEnd][colEnd] == '0' || buf[rowEnd][colEnd] == 'W'))	//�� ���� �̵� or �� ���� ���� ��
		{
			if (rowEnd - rowStart == -1 && colEnd - colStart == 0 && buf[rowEnd][colEnd] == 'W')				//������ ������ �� �� �� ���� �տ� �ִ� ��� ����
				return false;

			if (rowStart - rowEnd == 0 && buf[rowEnd][colEnd] == 'W')											//�� ������ �̵��Ϸ��� �� �� �� ���� �翷�� �ִ� ��� ����
				return false;

			if (rowStart < rowEnd)																				//�ڷ� ���� ��� ����
				return false;

			if (rowEnd - rowStart == -1 && (colEnd - colStart == 1 || colEnd - colStart == -1) && buf[rowEnd][colEnd] == '0')	//�밢�� ����� �̵� ����
				return false;

			buf[rowStart][colStart] = '0';	//Start ��ġ -> �����
			buf[rowEnd][colEnd] = 'B';		//End ��ġ -> Pawn

			gametree->getRoot()->setState(&buf[0][0]);	//Root�� State ����
			return true;
		}

		else
			return false;
	}

	else							//���� == WHITE
	{
		if (buf[rowStart][colStart] == 'W' && (buf[rowEnd][colEnd] == '0' || buf[rowEnd][colEnd] == 'B'))	//�� ���� �̵� or ���� ���� ���� ��
		{
			if (rowStart - rowEnd == -1 && colEnd - colStart == 0 && buf[rowEnd][colEnd] == 'B')				//������ ������ �� �� �� ���� �տ� �ִ� ��� ����
				return false;

			if (rowStart - rowEnd == 0 && buf[rowEnd][colEnd] == 'B')											//�� ������ �̵��Ϸ��� �� �� �� ���� �翷�� �ִ� ��� ����
				return false;

			if (rowStart > rowEnd)																				//�ڷ� ���� ��� ����
				return false;

			if (rowStart - rowEnd == -1 && (colEnd - colStart == 1 || colEnd - colStart == -1) && buf[rowEnd][colEnd] == '0')	//�밢�� ����� �̵� ����
				return false;

			buf[rowStart][colStart] = '0';	//Start ��ġ -> �����
			buf[rowEnd][colEnd] = 'W';		//End ��ġ -> Pawn

			gametree->getRoot()->setState(&buf[0][0]);	//Root�� State ����
			return true;
		}

		else
			return false;
	}
}

bool Manager::initialSetting(gameTree* pawn, char* file_name)
{
	FILE* fp = fopen(file_name, "r");
	char buf[3][3];


	if (strcmp(file_name, "0") == 0)	//default 0�� ������ �� default�� �ʱ� state ����
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (i == 0)
					buf[i][j] = 'W';
				else if (i == 2)
					buf[i][j] = 'B';
				else
					buf[i][j] = '0';
			}
		}
	}

	else
	{
		if (fp == NULL) return false;	//������ ���� X

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				char change = fgetc(fp);	//pawn
				if (change == '1')
					buf[i][j] = 'W';
				else if (change == '2')		//������ ������ �� ���Ͽ��� �ʱ� state �о��
					buf[i][j] = 'B';
				else
					buf[i][j] = '0';
				fgetc(fp);					//space ó��
			}
		}
	}


	pawn->getRoot()->setState(&buf[0][0]);		//�� ���� ���·� state ����

	if (fp) fclose(fp);
	return true;
}

void Manager::print_state(gameTree* pawn)
{
	char buf[3][3];

	memcpy(buf, pawn->getRoot()->getState(), 3 * 3);		//root ��忡 �ִ� state ����

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (buf[i][j] != '0')
				cout << "[ " << buf[i][j] << " ]";		//���� ���
			else
				cout << "[   ]";

		}

		cout << endl;
	}
}

void Manager::set_user_color(char user_color)
{
	this->user_color = user_color;
}

char Manager::get_user_color()
{
	return user_color;
}

void Manager::set_user_turn(int user_turn)
{
	this->user_turn = user_turn;
}

int Manager::get_user_turn()
{
	return user_turn;
}