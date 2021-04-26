#include "BTL_Header.h"

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

int targetY[3];
int targetX[3];
int targetFlag[3];
char basket[4][4] = {  '*',' ',' ','*',
					'*',' ',' ','*',
					'*',' ',' ','*',
					'*','*','*','*' };

int basketPos = WIN_WIDTH/2;
int score = 0;
int hp;
string name="";
int highscore=0;

void gotoxy(int x, int y)
{
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}

void setcursor(bool visible, DWORD size)
{
	if(size == 0)
		size = 20;

	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(console,&lpCursor);
}

void drawBorder()
{
	for(int i=0; i<SCREEN_HEIGHT; i++)
    {
		for(int j=0; j<17; j++)
		{
			gotoxy(0+j,i); cout<<"¤";
			//gotoxy(WIN_WIDTH-j,i); cout<<"¤";
		}
	}
	for(int i=0; i<SCREEN_HEIGHT; i++)
	{
		gotoxy(WIN_WIDTH-16,i); cout<<"¤";
		gotoxy(SCREEN_WIDTH,i); cout<<"¤";
	}
}

void genTarget(int ind)
{
	targetX[ind] = 17 + rand()%(33);
}

void drawTarget(int ind)
{
	if( targetFlag[ind] == true )
    {
		gotoxy(targetX[ind], targetY[ind]);   cout<<" ** ";
		gotoxy(targetX[ind], targetY[ind]+1); cout<<"****";
		gotoxy(targetX[ind], targetY[ind]+2); cout<<"****";
		gotoxy(targetX[ind], targetY[ind]+3); cout<<" ** ";
	}
}

void eraseTarget(int ind)
{
	if( targetFlag[ind] == true )
    {
		gotoxy(targetX[ind], targetY[ind]);   cout<<"    ";
		gotoxy(targetX[ind], targetY[ind]+1); cout<<"    ";
		gotoxy(targetX[ind], targetY[ind]+2); cout<<"    ";
		gotoxy(targetX[ind], targetY[ind]+3); cout<<"    ";
	}
}

void resetTarget(int ind)
{
	eraseTarget(ind);
	targetY[ind] = 1;
	genTarget(ind);
}
void drawBasket()
{
	for(int i=0; i<4; i++)
    {
		for(int j=0; j<4; j++)
		{
			gotoxy(j+basketPos, i+22); cout<<basket[i][j];
		}
	}
}

void eraseBasket()
{
	for(int i=0; i<4; i++)
    {
		for(int j=0; j<4; j++)
		{
			gotoxy(j+basketPos, i+22); cout<<" ";
		}
	}
}

bool collision()
{
	if( targetY[0]+4 >= 23 )
    {
		if( targetX[0] + 4 - basketPos >= 0 && targetX[0] + 4 - basketPos < 9  )
		{
			return true;
		}
	}
	return false;
}

void gameover()
{
	system("cls");
	gotoxy(10,5);   cout<<" -------------------------- ";
    gotoxy(10,6);   cout<<" |        Game Over       | ";
    gotoxy(10,7);   cout<<" --------------------------";
	gotoxy(10,9);   cout<<"Press any key to go back to menu.";
	getch();
}

void updateScore()
{
	gotoxy(WIN_WIDTH +1, 5);cout<<"Score: "<<score<<endl;
}

void instructions()
{
	system("cls");
	gotoxy(10,5);   cout<<" -------------------------- ";
    gotoxy(10,6);   cout<<" |      Instructions      | ";
    gotoxy(10,7);   cout<<" --------------------------";
    gotoxy(13,9);   cout<<"+. Introduces: ";
    gotoxy(16,10);  cout<<"Move the basket to catch the falling eggs";
    gotoxy(13,11);  cout<<"+. How to play: ";
    gotoxy(16,12);  cout<<"Press 'a' to move left";
    gotoxy(16,13);  cout<<"Press 'd' to move right";
    gotoxy(16,14);  cout<<"Press 'escape' to exit";
    gotoxy(14,15);  cout<<"Press any key to go back to menu";
	getch();
}

void gameStatus()
{
    gotoxy(WIN_WIDTH - 1, 2);cout<<"Falling Egg";
	gotoxy(WIN_WIDTH , 4);cout<<"----------";
	gotoxy(WIN_WIDTH , 6);cout<<"----------";
    gotoxy(WIN_WIDTH , 8);cout<<"----------";
    gotoxy(WIN_WIDTH , 10);cout<<"----------";
	gotoxy(WIN_WIDTH + 1, 15);cout<<"Control ";
	gotoxy(WIN_WIDTH + 1, 16);cout<<"-------- ";
	gotoxy(WIN_WIDTH -4, 17);cout<<" A Key - Left";
	gotoxy(WIN_WIDTH - 4, 18);cout<<" D Key - Right";
}

void startGame()
{
    gotoxy(18, 5);cout<<"Press any key to start";
	getch();
	gotoxy(18, 5);cout<<"                      ";
}

void play(int hard)
{
    int speed;
    if (hard==8)
        speed=70;
    else if (hard==6)
        speed=50;
    else if (hard==4)
        speed=35;
	basketPos = -1 + WIN_WIDTH/2;
	score = 0;
	hp=hard;
	targetFlag[0] = 1;
	targetY[0] = targetY[1] = 1;

	system("cls");
	drawBorder();
	updateScore();
	updateHp();
	copyright();
	updateHighScore();
	updateName();
	genTarget(0);

	gameStatus();
	startGame();

	while(1)
    {
		if(kbhit())
		{
			char ch = getch();
			if( ch=='a' || ch=='A' )
			{
				if( basketPos > 18 )
					basketPos -= 4;
			}
			if( ch=='d' || ch=='D' )
			{
				if( basketPos < 50 )
					basketPos += 4;
			}
			if(ch==27)
			{
				break;
			}
		}

		drawBasket();
		drawTarget(0);
		if( collision() )
        {
			score=score+1;
			if (score>highscore)
                highscore=score;
			updateScore();
			updateHighScore();
			resetTarget(0);
		}

		Sleep(speed);
		eraseBasket();
		eraseTarget(0);

		if( targetY[0] == 10 )
			if( targetFlag[1] == 0 )
				targetFlag[1] = 1;

		if( targetFlag[0] == 1 )
			targetY[0] += 1;

		if( targetFlag[1] == 1 )
			targetY[1] += 1;

		if( targetY[0] > SCREEN_HEIGHT-4 )
        {
			resetTarget(0);
			hp--;
			clearHp();
			updateHp();
		}
		if (hp==0)
        {
            gameover();
            outputName();
            outputScore();
            return;
        }
        if (score %20==0&&score!=0&&speed>20)
        {
            speed=speed-10;
            if (score %40==0)
            {
                hp=hp+1;
                clearHp();
                updateHp();
            }
            score=score+1;
            //gotoxy(WIN_WIDTH + 7, 11);  cout<<"Faster !";
        }

	}
}

void startMenu()
{
    gotoxy(10,5);   cout<<" -------------------------- ";
    gotoxy(10,6);   cout<<" |      Falling Eggs      | ";
    gotoxy(10,7);   cout<<" --------------------------";
    gotoxy(15,9);   cout<<"1. Start Game";
    gotoxy(15,10);  cout<<"2. Instructions";
    gotoxy(15,11);  cout<<"3. LeaderBoard";
    gotoxy(15,12);  cout<<"4. Quit";
    gotoxy(10,14);  cout<<"Select option: ";
}

void chonDoKho()
{
    gotoxy(10,5);   cout<<" -------------------------- ";
    gotoxy(10,6);   cout<<" |       Game Mode        | ";
    gotoxy(10,7);   cout<<" --------------------------";
    gotoxy(15,9);   cout<<"1. Easy";
    gotoxy(15,10);  cout<<"2. Medium";
    gotoxy(15,11);  cout<<"3. Hard";
    gotoxy(15,12);  cout<<"4. Exit";
    gotoxy(10,14);  cout<<"Select option: ";
}

void updateHp()
{

    gotoxy(WIN_WIDTH + 1, 7);   cout<<"Heart: "<<hp<<endl;
}

void clearHp()
{
    gotoxy(WIN_WIDTH + 8, 7);   cout<<"     "<<endl;
}

void updateHighScore()
{

    gotoxy(WIN_WIDTH + 1,9);    cout<<"Record: "<<highscore;
}

void getName()
{
    system("cls");
    gotoxy(10,5);   cout<<" -------------------------- ";
    gotoxy(10,6);   cout<<" |     Enter your name    | ";
    gotoxy(10,7);   cout<<" --------------------------";
    gotoxy(10,12);  cout<<"Note: Turn off 'Vietkey' to play easier !!!";
    gotoxy(12,9);   cout<<"Your name: ";
    getline(cin,name);

}

void updateName()
{
    gotoxy(WIN_WIDTH -3,11);   cout<<"Name: "<<name;
}

void outputScore()
{
    ofstream scoreOutput;
    scoreOutput.open("data/score.txt",ios::app);
    scoreOutput<<score<<endl;
    scoreOutput.close();
}

void outputName()
{
    ofstream nameOutput;
    nameOutput.open("data/name.txt",ios::app);
    nameOutput<<name<<endl;
    nameOutput.close();
}

void leaderboard()
{
    int listPlayer=0;
    int temp=0;
    gotoxy(10,5);   cout<<" -------------------------- ";
    gotoxy(10,6);   cout<<" |      LeaderBoards      | ";
    gotoxy(10,7);   cout<<" --------------------------";
    ifstream nameInput("data/name.txt");
    if (nameInput.fail())
    {
        gotoxy(12,9);   cout<<"Can't find 'name.txt'!";
    }
    else
        temp=1;
    ifstream scoreInput("data/score.txt");
    if (scoreInput.fail())
    {
        gotoxy(12,10);   cout<<"Can't find 'score.txt'!" ;
    }
    else
        temp=1;
    vector<int>ScoreIN;
    vector<string>NameIN;
    if (temp==1)
    {
        while (!scoreInput.eof())
        {
            int scoreIn;
            scoreInput>>scoreIn;
            ScoreIN.push_back(scoreIn);
            string nameIn;
            getline(nameInput,nameIn);
            NameIN.push_back(nameIn);
            listPlayer=listPlayer+1;
        }
        int temp=1;
        gotoxy(16,9+listPlayer);  cout<<"Press any key to go back to menu";
        while (temp!=listPlayer)
        {
            int dele=0;
            int maxScore=-1;
            for (int i=0;i<ScoreIN.size();i++)
            {
                if (ScoreIN[i]>=maxScore)
                {
                    maxScore=ScoreIN[i];
                    dele=i;
                }
            }
            gotoxy(13,8+temp);  cout<<"Top: "<<temp<<" Name: "<<NameIN[dele]<<" - Score: "<<ScoreIN[dele]<<endl;
            ScoreIN.erase(ScoreIN.begin()+dele);
            NameIN.erase(NameIN.begin()+dele);
            temp=temp+1;
            Sleep(50);
        }
        getch();
    }
    else
    {
        gotoxy(12,11);  cout<<"Please read 'Readme.txt' and setting to use this feature";
        gotoxy(10,12);  cout<<"Press any key to go back to menu";
        getch();
    }
}

void loadingAnimation()
{
    system("cls");
    char load={'#'};
    gotoxy(1,10);    cout<<"Loading..."<<endl;
    for (int i=1;i<=100;i++)
    {
        gotoxy(0+i,9);  cout<<load;
        Sleep(5);
        gotoxy(11,10);   cout<<i<<"%";
    }
}

void copyright()
{
    gotoxy(WIN_WIDTH-3,24); cout<<"Dinh Duy Manh";
    gotoxy(WIN_WIDTH-1,25); cout<<"20020438";
}


