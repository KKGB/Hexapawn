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
/// 헥사폰 게임 턴 진행 함수
/// </summary>
/// <returns></returns>
void Manager::Game()
{
	cout << "Welcome to Hexapawn game!!!" << endl << endl;

	while (1)
	{
		try {
			gametree = new gameTree();		// minimax Tree 생성
			gameTreeNode* newNode = new gameTreeNode();		// 노드 생성
			gametree->setRoot(newNode);
			gametree->set_pCur(newNode);

			char buf[20] = { 0 };
			int turn = 0;
			int eval = 0;

			// 1) pawn 색깔 선택
			cout << "Type ""WHITE"" or ""BLACK"": ";
			cin >> buf;

			if (strcmp(buf, "WHITE") != 0 && strcmp(buf, "BLACK") != 0)
			{
				throw invalid_argument("제대로 입력해주세요.\n");
			}

			else
			{
				// User : 흰, Com : 검
				if (strcmp(buf, "WHITE") == 0)
				{
					cout << "WHITE : USER / BLACK : COMPUTER" << endl;
					set_user_color('W');
					gametree->getRoot()->set_com_color('B');
				}

				// User : 검, Com : 흰
				else
				{
					cout << "BLACK : USER / WHITE : COMPUTER" << endl;
					set_user_color('B');
					gametree->getRoot()->set_com_color('W');
				}

				cout << endl;
			}



			// 2) 선공 후공 선택
			cout << "WHITE first (1) BLACK first (2): ";
			cin >> turn;

			if (turn != 1 && turn != 2)
			{
				throw invalid_argument("제대로 입력해주세요.\n");
			}

			else
			{
				// 유저 선공
				if ((turn == 1 && strcmp(buf, "WHITE") == 0) || (turn == 2 && strcmp(buf, "BLACK") == 0))
				{
					cout << "User first!!!" << endl;
					if (turn == 1) set_user_turn(1);
					else set_user_turn(2);
				}

				// 컴퓨터 선공
				else
				{
					cout << "Computer first!!!" << endl;
					if (turn == 1) set_user_turn(1);
					else set_user_turn(2);
				}

				cout << endl;
			}

			// 3) 초기 보드 상태 설정
			memset(buf, 0, sizeof(buf));
			cout << "Input file name (default board=0): ";
			cin >> buf;
			cout << endl;

			if (InitialSetting(gametree, buf))
			{
				print_state(gametree);
				char com_color = gametree->getRoot()->get_com_color();

				cout << endl << endl;

				// 4-1) 유저 선공
				if ((get_user_color() == 'W' && get_user_turn() == 1) || ((get_user_color() == 'B') && get_user_turn() == 2))
				{
					while (eval != 100 && eval != -100)
					{
						//유저 차례
						eval = Move_User_pawn(gametree);		//유저 말 이동
						cout << endl;

						cout << "===========USER============" << endl;
						print_state(gametree);					//보드 출력
						cout << "===========================" << endl << endl;

						if (eval == 100 || eval == -100)		//종료 조건
							break;
						

						//컴퓨터 차례
						eval = Move_Com_pawn(gametree);			//컴퓨터 말 이동
						gametree->getRoot()->set_com_color(com_color);	//컴퓨터의 원래 진영 색 설정

						cout << "=========COMPUTER==========" << endl;
						print_state(gametree);					//보드 출력
						cout << "===========================" << endl << endl;

						if (eval == 100 || eval == -100)		//종료 조건
							break;
					}
				}

				// 4-2) 컴퓨터 선공
				else
				{
					while (eval != 100 && eval != -100)
					{
						//컴퓨터 차례
						eval = Move_Com_pawn(gametree);			//컴퓨터 말 이동
						gametree->getRoot()->set_com_color(com_color);	//컴퓨터의 원래 진영 색 설정

						cout << "=========COMPUTER==========" << endl;
						print_state(gametree);					//보드 출력
						cout << "===========================" << endl << endl;

						if (eval == 100 || eval == -100)		//종료 조건
							break;


						//유저 차례
						eval = Move_User_pawn(gametree);		//유저 말 이동
						cout << endl;

						cout << "===========USER============" << endl;
						print_state(gametree);					//보드 출력
						cout << "===========================" << endl << endl;

						if (eval == 100 || eval == -100)		//종료 조건
							break;
					}

				}


				cout << "게임종료 -- ";


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
				else
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
						delete gametree;		//1을 선택 시 게임 다시 진행
						system("cls");
						break;
					}

					else if (again == 2)
					{
						delete gametree;		//2를 선택 시 게임 종료
						return;
					}

					else
					{
						cout << "다시 입력해주시기 바랍니다.\n" << endl;		//그 이외 선택 시에도 게임 종료
					}
				}
			}
		}
		catch (const invalid_argument& e) {
			cout << e.what() << endl;

		}
		catch (const exception& e) {
			cout << e.what() << endl;
		}
	}
	
	
	return;
}

/// <summary>
/// 유저 턴에서 진행 함수
/// </summary>
/// <param name="pawn"></param>
/// <returns></returns>
int Manager::Move_User_pawn(gameTree* pawn)
{
	gameTreeNode* pc_Root = pawn->getRoot();

	int turn = 0;
	int term_value = 0;
	char startPos[10];
	char endPos[10];
	char* row = NULL;
	char* column = NULL;
	char board[3][3];

	memcpy(board, pc_Root->getState(), static_cast<size_t>(3) * 3);

	term_value = pawn->Term(pawn->getRoot());		//초기 상태에 이길 수 밖에 없는 파일을 읽어올 때 예외 처리

	if (term_value == -100)
	{
		cout << "BLACK이 이길 수 밖에 없는 상태입니다." << endl;
		return term_value;
	}

	if (term_value == 100)
	{
		cout << "WHITE가 이길 수 밖에 없는 상태입니다." << endl;
		return term_value;
	}

	cout << "당신의 순서입니다!" << endl;
	cout << "당신의 말을 골라주세요!!" << endl;

	while (1)
	{
		cout << "ex) 1행 1열 -> 1,1" << endl;
		cin >> startPos;
		row = strtok(startPos, ",");
		column = strtok(NULL, " ");
		
		if (!IsYourPawn(&board[0][0], startPos))	//내 pawn이 아닌 경우
		{
			cout << endl;
			cout << startPos[0] << "행 " << startPos[2] << "열에 있는 pawn은 당신의 말이 아닙니다." << endl;
			cout << "다시 골라주세요!!" << endl;
		}

		else
		{
			cout << endl;
			cout << "pawn을 어디다 두실건가요?" << endl;
			cout << "ex) 2행 1열 -> 2,1" << endl;
			cin >> endPos;
			row = strtok(endPos, ",");
			column = strtok(NULL, " ");

			if (!IsMovable(&board[0][0], startPos, endPos))		//원하는 곳으로 움직일 수 없는 경우
			{
				cout << endl;
				cout << endPos[0] << "행 " << endPos[2] << "열로 움직일 수 없습니다." << endl << endl;
				cout << "다시 골라주세요!!" << endl;
			}

			else
				break;
		}
	}

	term_value = pawn->Term(pawn->getRoot());
	return term_value;
}

/// <summary>
/// 컴퓨터 턴에서 진행 함수
/// </summary>
/// <param name="pawn"></param>
/// <returns></returns>
int Manager::Move_Com_pawn(gameTree* pawn)
{
	int term_value = 0;

	term_value = pawn->Term(pawn->getRoot());			//초기 상태에 이길 수 밖에 없는 파일을 읽어올 때 예외 처리

	if (term_value == -100)
	{
		cout << "BLACK이 이길 수 밖에 없는 상태입니다." << endl;
		return term_value;
	}

	if (term_value == 100)
	{
		cout << "WHITE가 이길 수 밖에 없는 상태입니다." << endl;
		return term_value;
	}

	if (get_user_color() == 'B')
		term_value = pawn->Max_Value(pawn->getRoot(), -200, 200);
	else
		term_value = pawn->Min_Value(pawn->getRoot(), -200, 200);

	pawn->setRoot(pawn->get_pCur());
	pawn->getRoot()->setLevel(0);

	term_value = pawn->Term(pawn->getRoot());
	return term_value;
}

/// <summary>
/// 선택한 폰이 내 폰이 맞는지 확인하는 함수
/// </summary>
/// <param name="board"></param>
/// <param name="search_buf"></param>
/// <returns></returns>
bool Manager::IsYourPawn(char* board, char* search_buf)
{
	char buf[3][3];
	memcpy(buf, board, static_cast<size_t>(3) * 3);

	int i = *(search_buf + 0) - 49;
	int j = *(search_buf + 2) - 49;

	// 보드판 안에 존재하고 내가 선택한 색깔일 때
	if (i < 3 && j < 3 && i >= 0 && j >= 0 && buf[i][j] == get_user_color())
		return true;

	return false;
}

/// <summary>
/// 선택한 폰을 움직일 수 있는지 확인하는 함수
/// </summary>
/// <param name="board"></param>
/// <param name="start"></param>
/// <param name="end"></param>
/// <returns></returns>
bool Manager::IsMovable(char* board, char* start, char* end)
{
	char buf[3][3];
	memcpy(buf, board, static_cast<size_t>(3) * 3);

	int rowStart = *(start + 0) - 49;
	int colStart = *(start + 2) - 49;		//이동 전 위치값

	int rowEnd = *(end + 0) - 49;
	int colEnd = *(end + 2) - 49;			//이동 후 위치값

	// 보드판 안에 존재하고 이동거리가 1일 때
	if (rowEnd < 3 && colEnd < 3 && rowEnd >= 0 && colEnd >= 0 && abs(colEnd - colStart) + abs(rowEnd - rowStart) <= 2)
	{
		if (get_user_color() == 'B')	//유저 == BLACK
		{
			if (buf[rowStart][colStart] == 'B' && (buf[rowEnd][colEnd] == '0' || buf[rowEnd][colEnd] == 'W'))	//빈 공간 이동 or 흰 돌을 잡을 때
			{
				if (rowEnd - rowStart == -1 && colEnd - colStart == 0 && buf[rowEnd][colEnd] == 'W')				//앞으로 가려고 할 때 흰 돌이 앞에 있는 경우 제외
					return false;

				if (rowStart - rowEnd == 0 && buf[rowEnd][colEnd] == 'W')											//양 옆으로 이동하려고 할 때 흰 돌이 양옆에 있는 경우 제외
					return false;

				if (rowStart < rowEnd)																				//뒤로 가는 경우 제외
					return false;

				if (rowEnd - rowStart == -1 && (colEnd - colStart == 1 || colEnd - colStart == -1) && buf[rowEnd][colEnd] == '0')	//대각선 빈공간 이동 제외
					return false;

				buf[rowStart][colStart] = '0';	//Start 위치 -> 빈공간
				buf[rowEnd][colEnd] = 'B';		//End 위치 -> Pawn

				gametree->getRoot()->setState(&buf[0][0]);	//Root에 State 저장
				return true;
			}

			else
				return false;
		}

		else							//유저 == WHITE
		{
			if (buf[rowStart][colStart] == 'W' && (buf[rowEnd][colEnd] == '0' || buf[rowEnd][colEnd] == 'B'))	//빈 공간 이동 or 검은 돌을 잡을 때
			{
				if (rowStart - rowEnd == -1 && colEnd - colStart == 0 && buf[rowEnd][colEnd] == 'B')				//앞으로 가려고 할 때 흰 돌이 앞에 있는 경우 제외
					return false;

				if (rowStart - rowEnd == 0 && buf[rowEnd][colEnd] == 'B')											//양 옆으로 이동하려고 할 때 흰 돌이 양옆에 있는 경우 제외
					return false;

				if (rowStart > rowEnd)																				//뒤로 가는 경우 제외
					return false;

				if (rowStart - rowEnd == -1 && (colEnd - colStart == 1 || colEnd - colStart == -1) && buf[rowEnd][colEnd] == '0')	//대각선 빈공간 이동 제외
					return false;

				buf[rowStart][colStart] = '0';	//Start 위치 -> 빈공간
				buf[rowEnd][colEnd] = 'W';		//End 위치 -> Pawn

				gametree->getRoot()->setState(&buf[0][0]);	//Root에 State 저장
				return true;
			}

			else
				return false;
		}
	}

	else
		return false;

	
}

/// <summary>
/// 맵 초기 설정 관련 함수
/// </summary>
/// <param name="pawn"></param>
/// <param name="file_name"></param>
/// <returns></returns>
bool Manager::InitialSetting(gameTree* pawn, char* file_name)
{
	FILE* fp = fopen(file_name, "r");
	char buf[3][3]{};
	
	// 기본 맵
	if (strcmp(file_name, "0") == 0)
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

	// 커스텀 맵
	else
	{
		if (fp == NULL)
			throw exception("파일이 존재하지 않습니다.\n");

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				char change = fgetc(fp);	//pawn
				if (change == '1')
					buf[i][j] = 'W';
				else if (change == '2')		//파일이 존재할 때 파일에서 초기 state 읽어옴
					buf[i][j] = 'B';
				else
					buf[i][j] = '0';
				fgetc(fp);					//space 처리
			}
		}
	}


	pawn->getRoot()->setState(&buf[0][0]);		//위 보드 상태로 state 설정

	if (fp) fclose(fp);
	return true;
}

/// <summary>
/// CLI에 상태 출력 관련 함수
/// </summary>
/// <param name="pawn"></param>
void Manager::print_state(gameTree* pawn)
{
	char buf[3][3]{};

	memcpy(buf, pawn->getRoot()->getState(), static_cast<size_t>(3) * 3);		//root 노드에 있는 state 복사

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (buf[i][j] != '0')
				cout << "[ " << buf[i][j] << " ]";		//보드 출력
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