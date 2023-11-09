// lgamal.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include<iostream>
#include<cstdlib>
#include<ctime>
#include<fstream>
#include<windows.h>

using namespace std;

int power(int a, int b, int n) // формула a^b mod n
{
	int tmp = a;
	int sum = tmp;
	for (int i = 1; i < b; i++)
	{
		for (int j = 1; j < a; j++)
		{
			sum += tmp;
			if (sum >= n)
			{
				sum -= n;
			}
		}
		tmp = sum;
	}
	return tmp;
}

int mul(int a, int b, int n) // формула a*b mod n
{
	int sum = 0;

	for (int i = 0; i < b; i++)
	{
		sum += a;

		if (sum >= n)
		{
			sum -= n;
		}
	}

	return sum;
}

void crypt(int p, int n, int x, string inFileName, string outFileName)
{
	ifstream inf(inFileName.c_str());
	ofstream outf(outFileName.c_str());

	int y = power(n, x, p);

	cout << "Открытый ключ (p,n,y)=" << "(" << p << "," << n << "," << y << ")" << endl;
	cout << "Закрытый ключ x=" << x << endl;

	cout << "\nШифруемый текст:" << endl;

	while (inf.good())
	{
		int m = inf.get();
		if (m > 0) {
			cout << (char)m;

			int k = rand() % (p - 2) + 1; // 1 < k < (p-1)
			int a = power(n, k, p);
			int b = mul(power(y, k, p), m, p);
			outf << a << " " << b << " ";
		}
	}

	cout << endl;

	inf.close();
	outf.close();
}

void decrypt(int p, int x, string inFileName, string outFileName)
{
	ifstream inf(inFileName.c_str());
	ofstream outf(outFileName.c_str());

	cout << "\nДешифрованый текст:" << endl;

	while (inf.good())
	{
		int a = 0;
		int b = 0;
		inf >> a;
		inf >> b;

		if (a != 0 && b != 0)
		{
			int deM = mul(b, power(a, p - 1 - x, p), p);// m=b*(a^x)^(-1)mod p =b*a^(p-1-x)mod p 
			char m = static_cast<char>(deM);
			outf << m;
			cout << m;
		}
	}

	cout << endl;

	inf.close();
	outf.close();
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	crypt(593, 123, 8, "in.txt", "in_crypt.txt");
	decrypt(593, 8, "in_crypt.txt", "in_decrypt.txt");

	return 0;
}

