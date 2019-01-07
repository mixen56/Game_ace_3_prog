#include <stdexcept>
#include "Domino_3.h"
#include <iostream>
#include <time.h>
#include <limits>


namespace Prog_3_3
{
	void zero()
	{
		std::cout << "|   |" << std::endl;
		std::cout << "|   |" << std::endl;
		std::cout << "|   |" << std::endl;
	}

	void one()
	{
		std::cout << "|   |" << std::endl;
		std::cout << "| * |" << std::endl;
		std::cout << "|   |" << std::endl;
	}

	void two()
	{
		std::cout << "| * |" << std::endl;
		std::cout << "|   |" << std::endl;
		std::cout << "| * |" << std::endl;
	}

	void three()
	{
		std::cout << "| * |" << std::endl;
		std::cout << "| * |" << std::endl;
		std::cout << "| * |" << std::endl;
	}

	void four()
	{
		std::cout << "|* *|" << std::endl;
		std::cout << "|   |" << std::endl;
		std::cout << "|* *|" << std::endl;
	}

	void five()
	{
		std::cout << "|* *|" << std::endl;
		std::cout << "| * |" << std::endl;
		std::cout << "|* *|" << std::endl;
	}

	void six()
	{
		std::cout << "|* *|" << std::endl;
		std::cout << "|* *|" << std::endl;
		std::cout << "|* *|" << std::endl;
	}

	void(*fptr[7])() = { zero, one, two, three, four, five , six };

	int Domino::check(int a1, int a2)
	{
		int fl = -1;
		for (int i = 0; i < n; i++)
			if (((arr[i].a == a1) && (arr[i].b == a2)) || ((arr[i].a == a2) && (arr[i].b == a1)))
			{
				//std::cout << "this bone exists " << std::endl;
				fl = i;
			}
		return fl;
	}

	Domino::Domino(int n_ent, Domino des)
	{
		n = 0;
		srand(time(0));
		for (int i = 0; i < n_ent; i++)
		{
			int r1, r2;
			do
			{
				r1 = rand() % 7;
				r2 = rand() % 7;
			} while ((check(r1, r2) != (-1)) || (des.check(r1,r2) != (-1)));
			Bone k(r1, r2);
			push(k);
		}
	}

	Domino::Domino(const Domino &st) :n(st.n), size(st.size)
	{
		arr = new Bone[size];
		for (int i = 0; i < n; ++i)
			arr[i] = st.arr[i];
	}

	Domino & Domino::operator =(const Domino &st)
	{
		if (this != &st) 
		{
			n = st.n;
			size = st.size;
			delete[] arr;
			arr = new Bone[size];
			for (int i = 0; i < n; ++i)
				arr[i] = st.arr[i];
		}
		return *this;
	}

	Domino Domino::push(Bone b)
	{
		if (n >= size) 
		{
			size += QUOTA;
			Bone *old = arr;
			arr = new Bone[size];
			for (int i = 0; i < n; ++i)
				arr[i] = old[i];
			delete[] old;
		}
		arr[n++] = b;
		return *this;
	}

	int Domino::del(Bone b)
	{
		n--;
		if (n <= (size-QUOTA))
		{
			size -= QUOTA;
			Bone *old = arr;
			arr = new Bone[size];
			for (int i = 0; i < n; ++i)
				arr[i] = old[i];
			delete[] old;
		}
		return 1;
	}

	Domino::Domino(int n_ent)
	{
		//if (n>28 || n<1)
		//	throw std::exception("invalid number of bones, min = 1, max = 28");
		n = 0;
		srand(time(0));
		for (int i = 0; i < n_ent; i++)
		{
			int r1, r2;
			if (i == 0)
			{
				r1 = rand() % 7;
				r2 = rand() % 7;
			}
			else
			{
				do
				{
					r1 = rand() % 7;
					r2 = rand() % 7;
				} while (check(r1, r2) != (-1));
			}
			Bone k(r1, r2);
			push(k);
		}
	}

	Domino::Domino(int a1, int a2)
	{
		if ((a1 > 6 || a1 < 0) || (a2 > 6 || a2 < 0))
			throw std::exception("invalid number of bone's part, min = 0, max = 6");
		Bone k(a1, a2);
		push(k);
	}

	//Domino &Domino::Input();
	std::istream & operator >> (std::istream &s, Domino &st)
	{
		int m = 0, r1, r2, fl;
		//n = 0;
		const char* emrg = "";
		while ((m < 1) || (m > 28))
		{
			std::cout << emrg << std::endl;
			std::cout << "enter number of bones" << std::endl;
			std::cin >> m;
			fl = std::cin.good();
			if (fl == 0)
			{
				std::cin.clear();
				std::cin.ignore();
			}
			emrg = "repeat enter, min = 1, max = 28";
		}

		for (int i = 0; i < m; i++)
		{
			do
			{
				r1 = -2;
				r2 = -2;
				emrg = "";
				while (r1 < 0 || r1 > 6)
				{
					std::cout << emrg << std::endl;
					std::cout << "enter the first part of bone " << i + 1 << std::endl;
					std::cin >> r1;
					emrg = "repeat enter, min = 0, max = 6";
				}
				emrg = "";
				while (r2 < 0 || r2 > 6)
				{
					std::cout << emrg << std::endl;
					std::cout << "enter the second part of bone " << i + 1 << std::endl;
					std::cin >> r2;
					emrg = "repeat enter, min = 0, max = 6";
				}
			} while (st.check(r1, r2) != (-1));
			Bone k(r1, r2);
			st.push(k);
		}
		return s;
	}

	std::ostream & operator <<(std::ostream &s, const Domino &st)
	{
		if (st.n == 0)
			std::cout << "group is empty" << std::endl;
		else
			for (int i = 0; i < st.n; i++)
			{
				//std::cout << "bone " << i + 1 << "--> " << fptr[st.arr[i].a - 1] << " ; " << fptr[st.arr[i].b - 1] << "\n";
				std::cout << "bone " << i + 1 << "--> " << std::endl;
				fptr[st.GetBone_A(i + 1)](); 
				//std::cout << std::endl;
				fptr[st.GetBone_B(i + 1)]();
			}
		return s;
	}

	Domino &Domino::Add_bone(Domino des)
	{
		int r1, r2;
		srand(time(0));
		if (n < 28)
		{
			do
			{
				r1 = rand() % 7;
				r2 = rand() % 7;
			} while ((check(r1, r2) != (-1)) || (des.check(r1, r2) != (-1)));
			Bone k(r1, r2);
			push(k);
		}
		else
			std::cout << "Group is full" << std::endl;
		return *this;
	}

	Domino &Domino::operator -=(Bone a1)
	{
		Bone zam;
		int ch = check(a1.a, a1.b);
		if (ch != (-1))
		{
			zam = arr[ch];
			arr[ch] = arr[n - 1];
			arr[n - 1] = zam;
			n--;
			if (n <= (size - QUOTA))
			{
				size -= QUOTA;
				Bone *old = arr;
				arr = new Bone[size];
				for (int i = 0; i < n; ++i)
					arr[i] = old[i];
				delete[] old;
			}
		}
		else
			std::cout << "\ndeleting is impossible, bone don't exist\n" << std::endl;
		return *this;
	}

	Domino &Domino::operator [](int num) const
	{
		int h1, h2;
		h1 = arr[num].a;
		h2 = arr[num].b;
		if ((h1 < 7) && (h1 >= 0))
		{
			Domino opened(h1, h2);
			std::cout << opened << std::endl;
			return opened;
		}
		else
		{
			Domino opened;
			std::cout << "bone don't exist with this number" << std::endl;
			return opened;
		}
		//return opened;
	}

	Domino Domino::Sort_group()//сортировка вставками
	{
		int i;
		Bone key;
		for (int j = 1; j < n; j++)
		{
			key = arr[j];
			i = j - 1;
			while ((i >= 0) && ((arr[i].a + arr[i].b) > (key.a + key.b)))
			{
				arr[i + 1] = arr[i];
				i--;
				arr[i + 1] = key;
			}
		}
		return *this;
	}

	Domino Domino::Pickout(int val)
	{
		if ((val > 6) || (val < 0))
			throw std::exception("invalid number of bone's part, min = 0, max = 6");
		Domino out;
		//out.n = 0;
		for (int i = 0; i < n; i++)
		{
			if ((arr[i].a == val) || (arr[i].b == val))
			{
				out.arr[out.n] = arr[i];
				out.n++;
			}
		}
		std::cout << out << std::endl;
		return out;
	}
}