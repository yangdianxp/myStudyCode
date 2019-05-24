#include <iostream>
#include <typeinfo>
#include <string>
using namespace std;



int main()
{
	auto x1 = 27;
	auto x2(27);
	auto x3 = { 27 };
	auto x4{ 27 };

	system("pause");
}



#if 0
26

void someFunc(int, double)
{
}

auto x = 27;
const auto cx = x;
const auto& rx = x;
auto&& uref1 = x;
auto&& uref2 = cx;
auto&& uref3 = 27;

const char name[] = "R. N. Briggs";
auto arr1 = name;
auto& arr2 = name;

auto func1 = someFunc;
auto& func2 = someFunc;


auto x = 27;   //  x Ϊiint
const auto cx = x;
const auto& rx = x;

template<typename T, std::size_t N>
constexpr std::size_t arraySize(T(&)[N]) noexcept
{
	return N;
}

int keyVals[] = { 1, 3, 7, 9, 11, 22, 35 };
cout << arraySize(keyVals) << endl;


template<typename T>
void f(T& param)
{
	cout << sizeof(param) << endl;
}

int keyVals[] = { 1, 3, 7, 9, 11, 22, 35 };
f(keyVals);
cout << sizeof(keyVals) << endl;


template<typename T>
void f(T param)
{
}


int x = 27;
const int cx = x;
const int& rx = x;
f(x);
f(cx);
f(rx);
f(27);

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