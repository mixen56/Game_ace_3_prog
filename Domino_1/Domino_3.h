//#pragma once
#ifndef Domino_3
#define Domino_3
#include <iostream>
namespace Prog_3_3
{
	struct Bone
	{
		int a;
		int b;
		Bone(int a0 = -1, int b0 = -1) : a(a0), b(b0) {}
	};

	class Domino
	{
	private:
		int n;
		static const int QUOTA = 7;
		int size;
		Bone *arr;
	public:
		Domino() :n(0), arr(new Bone[QUOTA]), size(7) {};//+
		Domino(int n);//+
		Domino(int n, Domino des);
		Domino(int a, int b);//+
		Domino(const Domino&);//+
		Domino &operator =(const Domino &);//+
		~Domino() { delete[] arr; } // деструктор
		Domino push(Bone);//+
		int del(Bone);//+
		int GetN() { return n; }//+
		int GetS() { return size; }//+
		int GetBone_A(int i) const { return arr[i - 1].a; }//+
		int GetBone_B(int i) const { return arr[i - 1].b; }//+
		//Domino &Input();//+
		friend std::istream & operator >>(std::istream &, Domino &);
		//void Output() const;//+
		friend std::ostream & operator <<(std::ostream &, const Domino &);
		Domino &Add_bone(Domino des);//+
		//Domino & operator ++();
		//Domino &Del_bone(int a, int b);//+
		Domino & operator -=(Bone a);
		//Domino Open_bone(int num) const;//+
		Domino & operator [](int num) const;
		Domino Sort_group();//+
		Domino Pickout(int val);
		int check(int a1, int a2);
	};
}
#endif