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
		cout << "文件不能打开" << endl;
	}
	else
	{
		// 输出到磁盘文件
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