#include <iostream>
#include <typeinfo>
using namespace std;

template<typename T>
void f(T param)
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
	f(27);


	system("pause");
}



#if 0
21


template<typename T>
void f(T&& param)
{
	cout << typeid(T).name() << endl;
	cout << typeid(param).name() << endl;
	cout << param << endl;
}


template<typename T>
void f(T& param)
{

}


int x = 27;
const int cx = x;
const int& rx = x;

f(x);
f(cx);
f(rx);


#endif