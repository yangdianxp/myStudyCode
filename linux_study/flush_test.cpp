#include <unistd.h>

#include <iostream>
#include <fstream>
#include <sstream> 

using namespace std;

int main()
{
	ofstream fout("./mytest.txt");
	if (!fout)
	{
		cout << "�ļ����ܴ�" << endl;
	}
	else
	{
		// ����������ļ�
		for (int i = 0; i < 10000; ++i)
		{
			fout << i << "==>" << "Learning C++ is very useful.\n";
			sleep(1);
		}
	}
	while (true)
	{
		sleep(2);
	}
	return 0;
}