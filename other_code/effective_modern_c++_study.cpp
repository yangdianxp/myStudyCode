#include <iostream>
#include <typeinfo>
#include <string>
#include <vector>
#include <mutex>
#include <unordered_map>
#include <algorithm>
#include <array>
#include <atomic>
#include <set>
#include <string>
#include <future>
#include <boost/type_index.hpp>

#include "effective_modern_c++_study.h"
using namespace std;
using namespace std::literals;


int main()
{
	{

		std::thread t([]() {std::cout << "thread start..." << std::endl; });
		t.detach();
	}
	std::this_thread::sleep_for(1s);

	system("pause");
}



#if 0
item33  216
template<typename F, typename... Ts>
inline std::future<typename std::result_of<F(Ts...)>::type>
reallyAsync(F&& f, Ts&&... params)
{
	return std::async(std::launch::async,
		std::forward<F>(f),
		std::forward<Ts>(params)...);
}


template<typename F, typename... Ts>
inline auto reallyAsync_2(F&& f, Ts&&... params)
{
	return std::async(std::launch::async,
		std::forward<F>(f),
		std::forward<Ts>(params)...);
}
void f()
{
	std::this_thread::sleep_for(1s);
}

	auto fut = std::async(f);
	if (fut.wait_for(0s) == std::future_status::deferred)
	{
		std::cout << "deferred" << endl;
	}
	else {
		while (fut.wait_for(100ms) !=
			std::future_status::ready);
	}

	std::cout << "end..." << std::endl;
	

	std::cout << std::this_thread::get_id() << std::endl;
	std::future<int> f1 = std::async(std::launch::async, []() {
		std::cout << std::this_thread::get_id() << std::endl;
		return 8;
	});

	std::cout << f1.get() << std::endl;

	std::future<void> f2 = std::async(std::launch::async, []() {
		std::cout << std::this_thread::get_id() << std::endl;
		std::cout << 8 << std::endl;
	});
	f2.wait();

	std::future<int> future = std::async(std::launch::async, []() {
		std::cout << std::this_thread::get_id() << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(3));
		return 8;
	});

	std::cout << "waiting...\n";

	std::future_status status;
	std::this_thread::sleep_for(std::chrono::seconds(3));
	do {
		status = future.wait_for(std::chrono::seconds(1));
		if (status == std::future_status::deferred) {
			std::cout << "deferred\n";
		}
		else if (status == std::future_status::timeout) {
			std::cout << "timeout\n";
		}
		else if (status == std::future_status::ready) {
			std::cout << "ready\n";
		}
	} while (status != std::future_status::ready);

	std::cout << "result is " << future.get() << '\n';

void normalize(int& x)
{
	cout << "normalize int&" << endl;
}

void normalize(int&& x)
{
	cout << "normalize int &&" << endl;
}

	auto f = [](auto&& x)
	{ return normalize(std::forward<decltype(x)>(x)); };
	int x = 1;
	f(1);
	f(x);
	f(move(x));
	int num = 0;
	auto func = [num = num]() {};

	auto pw = std::make_unique<Widget>();
	auto func1 = [pw = move(pw)]() {};

	auto func2 = [pw = std::make_unique<Widget>()](){};

	std::vector<double> data;
	//auto func3 = [data = std::move(data)]() {};

	data.push_back(0.22);

	auto func4 = std::bind([](std::vector<double>& data) mutable { data.push_back(0.33); }, std::move(data));
	func4();
template<typename... Ts>
void fwd(Ts&&... params)
{
f(std::forward<Ts>(params)...);
}

	logAndAdd(1);
template<typename T>
void logAndAdd(T&& name);

template<typename T>
void logAndAddImpl(T&& name, false_type)
{
	cout << "logAndAddImpl false_type" << endl;
}

string nameFromIdx(int idx)
{
	return "yangdian";
}

void logAndAddImpl(int idx, true_type)
{
	cout << "logAndAddImpl true_type" << endl;
	logAndAdd(nameFromIdx(1));
}

template<typename T>
void logAndAdd(T&& name)
{
	logAndAddImpl(forward<T>(name), is_integral<T>());
}
class Person {
public:
	template<typename T>
	explicit Person(T&& n)
		: name(std::forward<T>(n)) {}

	explicit Person(int idx)
		: name(nameFromIdx(idx)) {}
private:
	std::string name;
};
class Widget {
public:
	Widget(Widget&& rhs)
		: name(std::move(rhs.name)),
		p(std::move(rhs.p))
	{}

private:
	std::string name;
	std::shared_ptr<> p;
};
auto timeFuncInvocation = 
[](auto&& func, auto&&... params)
{
	std::forward<decltype(func)>(func)(
		std::forward<decltype(params)>(params)
		);
};
	Widget w;
	logAndProcess(w);
	logAndProcess(std::move(w));
void process(const Widget& lvalArg)
{
	cout << "process lvalArg" << endl;
}
void process(Widget&& rvalArg)
{
	cout << "process rvalArg" << endl;
}

template<typename T>
void logAndProcess(T&& param)
{
	process(std::forward<T>(param));
}
struct Widget::Impl{
	std::string name;
	std::vector<double> data;
};

Widget::Widget() : pImpl(std::make_unique<Impl>())
{}
class ReallyBigType
{};
auto pBigObj = std::make_shared<ReallyBigType>();
template<typename T, typename... Ts>
std::unique_ptr<T> make_unique(Ts&&... params)
{
	return std::unique_ptr<T>(new T(std::forward(Ts)(params)...));
}
	auto widget_ptr = fastLoadWidget(WidgetId::red);
enum class WidgetId { red };

class Widget
{};

unique_ptr<Widget> loadWidget(WidgetId id)
{
	return make_unique<Widget>();
}

std::shared_ptr<const Widget> fastLoadWidget(WidgetId id)
{
	static std::unordered_map<WidgetId,
		std::weak_ptr<const Widget>> cache;
	auto objPtr = cache[id].lock();

	if (!objPtr) {
		objPtr = loadWidget(id);
		cache[id] = objPtr;
	}
	return objPtr;
}
	auto spw = std::make_shared<Widget>();

	std::weak_ptr<Widget> wpw(spw);

	spw = nullptr;

	if (wpw.expired())
	{
		cout << "wpw.expired()" << endl;
	}
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
	std::shared_ptr<Investment> sp = makeInvestment();
	

class Investment 
{
public:
	virtual ~Investment()
	{

	}
};

class Stock: public Investment
{};

class Bond: public Investment
{};

class RealEstate: public Investment
{};

template<typename... Ts>
auto makeInvestment(Ts&&... params)
{
	auto delInvmt = [](Investment* pInvestment)
	{
		delete pInvestment; 
	};
	std::unique_ptr<Investment, decltype(delInvmt)> pInv(nullptr, delInvmt);
	int type = 0;
	if (0 == type)
	{
		pInv.reset(new Stock(std::forward<Ts>(params)...));
	}
	else if (1 == type)
	{
		pInv.reset(new Bond(std::forward<Ts>(params)...));
	}
	else if (2 == type)
	{
		pInv.reset(new RealEstate(std::forward<Ts>(params)...));
	}
	return pInv;
}


class Base {
public:
	virtual ~Base() = default;
	Base(Base&&) = default;
	Base& opperator=(Base&&) = default;

	Base(const Base&) = default;
	Base&operator=(const Base&) = default;
};
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