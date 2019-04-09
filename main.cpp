#include <iostream>
#include "TBitField.h"
#include "TSieve.h"
#include <fstream>


using namespace std;

int main()
{
	int n;

	cout << "Enter N value: " << endl;
	cin >> n;

	//������� ���� �� ����� ������������ ������
	BitField IdentityBF(n);
	IdentityBF.load_AllBits();

	//������� ���� � ������, ������������ ��������� ������� �����
	BitField primes = sieve(IdentityBF);
	ofstream Output("Output.txt");

	for (int i = 0; i < primes.size(); ++i)
	{
		if (primes[i]) {
			Output << i << ", ";
		}

		cout << "pos " << i << " = " << primes[i] << endl;
	}

	cout << "Primal numbers amount: " << primes.nonzero_count() << endl;
	Output.close();

	system("pause");
	return 0;
	//_getch();

}