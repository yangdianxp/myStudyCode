#include <iostream>
#include <typeinfo>
#include <string>
#include <vector>
#include <mutex>
#include <unordered_map>
#include <algorithm>
#include <array>
#include <atomic>
#include <boost/type_index.hpp>
using namespace std;


int main()
{
	
	system("pause");
}



#if 0
108
class Widget {
public:
	int magicValue() const
	{
		std::lock_guard<std::mutex> guard(m);
		if (cachedValue) return cachedValue;
		else {
		
		}
	}
private:
	mutable std::mutex m;
	mutable int cachedValue;
	mutable bool cacheValid;
};
class Point {
public:
	double distanceFromOrigin() const noexcept
	{
		++callCount;
		return std::sqrt((x*x) + (y*y));
	}

private:
	mutable std::atomic<unsigned> callCount{ 0 };
	double x, y;
};
class Polynomial {
public:
	using RootsType = std::vector<double>;

	RootsType roots() const
	{
		std::lock_guard<std::mutex> g(m);
		if (!rootsAreValid) {
			rootsAreValid = true;
		}
		return rootVals;
	}
private:
	mutable std::mutex m;
	mutable bool rootsAreValid{ false };
	mutable RootsType rootVals{};
};
	constexpr auto numConds = 5;
	array<int, pow(3, numConds)> results;
constexpr
int pow(int base, int exp) noexcept
{
	int result = 1;
	for (int i = 0; i < exp; ++i)
	{
		result *= base;
	}
	return result;
}
	constexpr auto arraySize2 = 10;
	std::array<int, arraySize2> data2;
	vector<int> values{ 1983 };
	findAndInsert(values, 1983, 1998);
	for_each(values.begin(), values.end(), [](auto& v) {cout << v << endl; });
template <class C>
auto cbegin(const C& container)->decltype(std::begin(container))
{
	return std::begin(container);
}

template<typename C, typename V>
void findAndInsert(C& container, const V& targetVal, const V& insertVal)
{
	using std::cbegin;
	using std::cend;
	auto it = std::find(cbegin(container), cend(container), targetVal);
	container.insert(it, insertVal);
}
	vector<int> values{ 1983 };
	vector<int>::iterator it =
		find(values.begin(), values.end(), 1983);
	values.insert(it, 1998);
	for_each(values.begin(), values.end(), [](auto& v) {cout << v << endl; });
class Base {
public:
	virtual void mf1() const
	{

	}
	virtual void mf2(int x)
	{

	}
	virtual void mf3()&
	{

	}
	virtual void mf4() const
	{

	}
};
class Derived : public Base {
public:
	virtual void mf1() const override
	{

	}
	virtual void mf2(int x) override
	{

	}
	virtual void mf3() & override
	{
	}
	void mf4() const override;
};
	Widget w;
	w.doWork();
	makeWidget().doWork();

class Widget {
public:
	void doWork() &
	{
		cout << "doWork &" << endl;
	}

	void doWork() &&
	{
		cout << "doWork &&" << endl;
	}
};

Widget makeWidget()
{
	return Widget();
}


	std::unique_ptr<Base> upb = make_unique<Derived>();
	upb->doWork();
class Base {
public:
	virtual void doWork()
	{
		cout << "Base doWork" << endl;
	}
};

class Derived : public Base {
public:
	virtual void doWork()
	{
		cout << "Derived doWork" << endl;
	}
};
class Widget {
public:
	template<typename T>
	void processPointer(T* ptr)
	{

	}
};

template<>
void Widget::processPointer<void>(void*) = delete;
	enum class Color { black, white, red };

	auto white = false;

	Color c = Color::white;
	MyAllocList<Widget> lw;
using UptrMapSS = std::unique_ptr<std::unordered_map<std::string, std::string>>;
using FP = void(*)(int, const std::string&);
template<typename T>
using MyAllocList = std::list<T>;

class Widget {
private:
	int x{ 0 };
	int y = 0;
};
	auto result3 = lockAndCall(f3, f2m, nullptr);

std::mutex f1m, f2m, f3m;
template<typename FuncType,
		typename MuxType,
		typename PtrType>
	decltype(auto) lockAndCall(FuncType func,
		MuxType& mutex, PtrType ptr)
{
	lock_guard<MuxType> g(mutex);
	return func(ptr);
}

class Widget {
private:
	int x{ 0 };
	int y = 0;
};

int f1(std::shared_ptr<Widget> spw)
{
	return 0;
}

double f2(std::unique_ptr<Widget> upw)
{
	return 0.0;
}

bool f3(Widget* pw)
{
	return true;
}
	std::vector<int> v{ 1, 3, 5 };
template<typename T>

class Widget {
private:
	int x{ 0 };
	int y = 0;
};


	f(Widget());
void f(const T& param)
{
	using boost::typeindex::type_id_with_cvr;
	cout << "T = "
		<< type_id_with_cvr<T>().pretty_name()
		<< '\n';

	cout << "param = "
		<< type_id_with_cvr<decltype(param)>().pretty_name()
		<< '\n';
}

class Widget
{

};

template<typename T>
void f(const T& param)
{
	using std::cout;
	cout << "T = " << typeid(T).name() << '\n';
	cout << "param = " << typeid(param).name() << '\n';
}



template<typename T>
class TD;

const int theAnswer = 42;
auto x = theAnswer;
auto y = &theAnswer;
TD<decltype(x)> xType;
TD<decltype(y)> yType;


template<typename Container, typename Index>
decltype(auto) authAndAccess(Container&& c, Index i)
{
	return std::forward<Container>(c)[i];
}

template<typename Container, typename Index>
decltype(auto)
authAndAccess(Container& c, Index i)
{
	return c[i];
}



Widget w;
const Widget& cw = w;
auto myWidget1 = cw;

decltype(auto) myWidget2 = cw;


template<typename Container, typename Index>
auto authAndAccess(Container& c, Index i)->decltype(c[i])
{
	return c[i];
}


auto x1 = 27;
auto x2(27);
auto x3 = { 27 };
auto x4{ 27 };

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