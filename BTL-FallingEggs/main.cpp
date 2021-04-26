#include "BTL_Header.h"

using namespace std;

int main()
{
	setcursor(0,0);
	srand( (unsigned)time(NULL));


	do{
		system("cls");
		startMenu();
		char op = getche();
		if( op=='1')
        {
            getName();
            do
            {

                system("cls");
                chonDoKho();

                char lv = getche();

                if (lv=='1'||lv=='2'||lv=='3')
                {
                    loadingAnimation();
                    if (lv=='1')
                    {
                        play(8);
                    }
                    else if (lv=='2')
                        play(6);
                    else
                        play(4);
                }
                else if (lv=='4')
                    break;
            }
            while (1);
        }
		else if( op=='2')
        {
            loadingAnimation();
            instructions();
        }
		else if (op=='3')
        {
            loadingAnimation();
            system("cls");
            leaderboard();
        }
		else if( op=='4')   exit(0);

	}while(1);

	return 0;
}
