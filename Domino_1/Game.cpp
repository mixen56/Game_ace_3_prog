#include <iostream>
#include "Domino_3.h"

using namespace Prog_3_3;
using namespace std;

void rules()
{
	cout << " ---Welcome to game --ace-- with domino--- " << endl;
	cout << "RULES:" << endl;
	cout << "1. Winner is who has 35 points, 35 points is ace (if both players have 35 scores, it is draw" << endl;
	cout << "2. If you have less than 35 points, winner is who have more than you or 35 points (but less 36)" << endl;
	cout << "3. If you have more than 35 scores, you are looser (if both players have more than 35 points, winner is who has less points" << endl;
	cout << "4. Computer will give you three bones and can give you more bones, if you will choose appropriate variant" << endl;
	cout << "5. Max amount of bones in hand is 6" << endl;
	cout << "Ok! Let's start!" << endl;
}

int sum(Domino dom)
{
	int summa = 0;
	int n = dom.GetN();
	for (int i = 1; i <= n; i++)
	{
		summa +=(dom.GetBone_A(i) + dom.GetBone_B(i));
	}
	return summa;
}

int game(Domino *c, Domino  *y)
{
	const char* emrg= " ";
	int s1 = 0, s2 = 0, turn, fl1 = 1, fl2 = 1;
	while ((s1 <= 35) && (s2 <= 35) && (c->GetN() < 6) && (y->GetN() < 6) && (fl1 || fl2))
	{
		if (abs(sum(*c) - 35) > 6)
		{
			c->Add_bone(*y);
			s1 = sum(*c);
		}
		else
			fl1 = 0;

		if (fl2)
		{
			cout << emrg << endl;
			cout << *y;
			cout << "Sum = " << sum(*y) << endl;
			cout << "enter 1 to add a bone, other key to open bones" << endl;
			cin >> turn;
			if (turn == 1)
			{
				y->Add_bone(*c);
				s2 = sum(*y);
			}
			else
				fl2 = 0;
		}
	}

	cout << endl;
	cout << "computer's group" << endl;
	cout << *c;
	cout << "Sum = " << sum(*c) << endl << endl;
	cout << "your's group" << endl;
	cout << *y;
	cout << "Sum = " << sum(*y) << endl;
	cout << endl;
	if (s1 > 35 && s2 <= 35)//у компа перебор
	{
		cout << "You're the winner!!!" << endl;
		return 1;
	}

	if (s1 <= 35 && s2 > 35)//у игрока перебор
	{
		cout << "Computer is the winner!!!";
		return 1;
	}

	if (s1 <= 35 && s2 <= 35)//у обоих недобор
		if (s1 > s2)
		{
			cout << "Computer is the winner!!!";
			return 1;
		}
		else
			if (s2 > s1)
			{
				cout << "You're the winner!!!" << endl;
				return 1;
			}
			else
			{
				cout << "Friendship is the winner!!!" << endl;
					return 1;
			}

	if (s1 > 35 && s2 > 35)//у обоих перебор
		if (s1 < s2)
		{
			cout << "Computer is the winner!!!";
			return 1;
		}
		else
			if (s2 < s1)
			{
				cout << "You're the winner!!!" << endl;
				return 1;
			}
			else
			{
				cout << "Friendship is the winner!!!" << endl;
				return 1;
			}
}

int main()
{
	Domino c(3), y(3, c);
	rules();
	game(&c, &y);
	cout << endl;
	system("pause");
	return 1;
}
