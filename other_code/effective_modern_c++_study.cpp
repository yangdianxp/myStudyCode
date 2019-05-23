#include <iostream>

template<typename T>
void f(T& param)
{

}

int main()
{
	int x = 27;
	const int cx = x;
	const int& rx = x;

	f(x);
	f(cx);
	f(rx);
	system("pause");
}



#if 0
19


#endif