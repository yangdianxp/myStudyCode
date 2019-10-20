// 例
#include <boost/type_traits/function_traits.hpp>
#include <iostream>

using namespace std;

#define mp_data typedef			// 元数据定义

int main() {
	mp_data void(mdata1)(int, std::string);
	static_assert(is_function<mdata1>::value);

	const size_t n = boost::function_traits<mdata1>::arity;  // 获得函数参数数量
	static_assert(n == 2);

	mp_data boost::function_traits<mdata1>::result_type rtype; // 函数的返回类型
	static_assert(is_void<rtype>::value);

	mp_data boost::function_traits<mdata1>::arg2_type a2type;  // 第二个参数的类型
	static_assert(is_same<a2type, std::string>::value);

	return 0;
}


//// 例
//#include <iostream>
//#include <type_traits>
//using namespace std;
//#define mp_eval(Func) Func::value		// 获取元函数返回值
//
//
//int main()
//{
//	cout << mp_eval(has_greater<int>) << endl;
//
//	system("pause");
//}


#if 0
struct my_err {};  //某个自定义的异常类，未使用boost::exception

try
{
	//使用enable_error_info包装自定义异常
	throw enable_error_info(my_err()) << errinfo_errno(101)
		<< errinfo_api_function("fopen");
}
catch (boost::exception& e) //这里必须使用boost::exception来捕获
{
	cout << diagnostic_information(e) << endl;
}
try
{
	BOOST_THROW_EXCEPTION(std::logic_error("logic"));//必须是标准异常
}
catch (boost::exception& e)
{
	cout << diagnostic_information(e) << endl;
}

#endif

#if 0
boost::uuids::uuid u;
u = boost::uuids::random_generator()();
std::string s = boost::lexical_cast<std::string>(u);
std::cout << s << std::endl;
std::cout << to_string(u) << std::endl;


std::cout << std::boolalpha;

// any 类型
std::any a = 1;
std::cout << a.type().name() << ": " << std::any_cast<int>(a) << '\n';
a = 3.14;
std::cout << a.type().name() << ": " << std::any_cast<double>(a) << '\n';
a = true;
std::cout << a.type().name() << ": " << std::any_cast<bool>(a) << '\n';

// 有误的转型
try
{
	a = 1;
	std::cout << std::any_cast<float>(a) << '\n';
}
catch (const std::bad_any_cast& e)
{
	std::cout << e.what() << '\n';
}

// 拥有值
a = 1;
if (a.has_value())
{
	std::cout << a.type().name() << '\n';
}

// 重置
a.reset();
if (!a.has_value())
{
	std::cout << "no value\n";
}

// 指向所含数据的指针
a = 1;
int* i = std::any_cast<int>(&a);
std::cout << *i << "\n";



std::mutex mtx;
std::condition_variable_any cv;

int cargo = 0;
bool shipment_available() { return cargo != 0; }

void consume(int n) {
	for (int i = 0; i < n; ++i) {
		mtx.lock();
		cv.wait(mtx, shipment_available);
		std::cout << cargo << '\n';
		cargo = 0;
		mtx.unlock();
	}
}



	std::thread consumer_thread(consume, 10);

	for (int i = 0; i < 10; ++i) {
		while (shipment_available()) std::this_thread::yield();
		mtx.lock();
		cargo = i + 1;
		cv.notify_one();
		mtx.unlock();
	}
	consumer_thread.join();


condition_variable cv;
mutex mtx;

void thread_1()
{
	unique_lock<mutex> ulock(mtx);
	cv.wait(ulock);
	cout << "hello from thread_1" << endl;
}

thread t1(thread_1);
cout << "main" << endl;
this_thread::sleep_for(chrono::seconds(1));
cv.notify_one();
t1.join();

	thread threads[10];

	for (int i = 0; i < 10; ++i)
		threads[i] = thread(test);

	for (auto& th : threads)
		th.join();

class object
{
public:
	static class object* pObject;

	static object* create_new_object()
	{
		std::call_once(oc, [&]() {pObject = new object(); });
		return pObject;
	}
	
	void print_num()
	{
		cout << m_num << endl;
	}

private:
	static std::once_flag oc;
	static std::atomic<int> m_a_num;
	int m_num = 0;
	object() 
	{ 
		m_num = m_a_num; 
		m_a_num++; 
		std::cout << "object()" << std::endl; 
	}
	~object() {}
};
std::once_flag object::oc;
std::atomic<int> object::m_a_num{ 100 };
class object* object::pObject = nullptr;

void test()
{
	object* pGlobal = object::create_new_object();
	pGlobal->print_num();
}



timed_mutex mtx;
void fireworks() {
	while (!mtx.try_lock_for(std::chrono::microseconds(200))) {
		cout << "_";
	}
	this_thread::sleep_for(std::chrono::microseconds(1000));
	cout << "\n";
	mtx.unlock();
}

class thread_c
{
public:
	void thread_1(int a)
	{
		cout << "hello from class member function:" << a << endl;
	}
};

thread_c a;
thread t1(&thread_c::thread_1, a, 1);
t1.join();
this_thread::sleep_for(chrono::seconds(2));



	vector<std::thread> threads;
	for (int i = 0; i < 5; ++i) {
		threads.push_back(std::thread([]() {cout << "Hello from thread" << std::this_thread::get_id() << std::endl; }));
	}
	for (auto& thread : threads) {
		thread.join();
	}


	thread_c c;
	thread t(c);
	this_thread::sleep_for(chrono::seconds(1));


	std::thread t1(hello, 1);
class thread_c
{
public:
	void operator()()
	{
		cout << "hello from class member function" << endl;
	}
};
	t1.join();

void hello(int i) {
	cout << "Hello from thread:" << i << endl;
}



	filters.emplace_back([](int value) {return value % 5 == 0; });
using FilterContainer = std::vector<std::function<bool(int)>>;
FilterContainer filters;
	cout << R"(hello, \n
			world)" << endl;
char utf8[] = u8"\u4F60\u597D\u554A";
char16_t utf16[] = u"hello";
char32_t utf32[] = U"hello equals \u4F60\u597D\u554A";

cout << utf8 << endl;
cout << utf16 << endl;
cout << utf32 << endl;

/*char32_t u2[] = u"hello";
char u3[] = U"hello";
char16_t u4 = u8"hello";*/


struct alignas(32) ColorVector
{
	double r;
	double g;
	double b;
	double a;
};

cout << "alignof(ColorVector): " << alignof(ColorVector) << endl;

struct HowManyBytes {
	char a;
	int b;
};

cout << "sizeof(char): " << sizeof(char) << endl;
cout << "sizeof(int): " << sizeof(int) << endl;
cout << "sizeof(HowManyBytes): " << sizeof(HowManyBytes) << endl;

cout << endl;
cout << "offset of char a: " << offsetof(HowManyBytes, a) << endl;
cout << "offset of int b: " << offsetof(HowManyBytes, b) << endl;

void Stat(vector<int> &v) {
	int errors;
	int score;
	auto print = [&] {
		cout << "Errors: " << errors << endl
			<< "Score: " << score << endl;
	};
	errors = accumulate(v.begin(), v.end(), 0);
	score = accumulate(v.begin(), v.end(), 100, minus<int>());
	print();

	errors = 0;
	score = 100;

	for_each(v.begin(), v.end(), [&](int i) {
		errors += i;
		score -= i;
	});
	print();
}

vector<int> v(10);
generate(v.begin(), v.end(), [] {
	return rand() % 10;
});
Stat(v);

vector<int> nums;

void Add(const int val) {
	auto print = [&] {
		for (auto s : nums) {
			cout << s << '\t';
		}
		cout << endl;
	};
	for (auto i = nums.begin(); i != nums.end(); ++i) {
		*i = *i + val;
	}
	print();

	for_each(nums.begin(), nums.end(), bind2nd(plus<int>(), val));
	print();

	transform(nums.begin(), nums.end(), nums.begin(), bind2nd(plus<int>(), val));
	print();

	for_each(nums.begin(), nums.end(), [=](int &i) {
		i += val;
	});
	print();
}

for (int i = 0; i < 10; i++) {
	nums.push_back(i);
}
Add(10);


vector<int> nums;

void OneCond(int val) {
	for (auto i = nums.begin(); i != nums.end(); i++)
		if (*i == val) break;
	find_if(nums.begin(), nums.end(), bind2nd(equal_to<int>(), val));

	find_if(nums.begin(), nums.end(), [=](int i) {
		return i == val;
	});
}

OneCond(1);

vector<int> nums;
vector<int> largeNums;

const int ubound = 10;

inline void LargeNumsPunc(int i) {
	if (i > ubound)
		largeNums.push_back(i);
}

void Above() {
	for (auto itr = nums.begin(); itr != nums.end(); ++itr) {
		if (*itr >= ubound)
			largeNums.push_back(*itr);
	}

	for_each(nums.begin(), nums.end(), LargeNumsPunc);

	for_each(nums.begin(), nums.end(), [=](int i) {
		if (i > ubound)
			largeNums.push_back(i);
	});
}
Above();


int girls = 3, boys = 4;
auto totalChild = [](int x, int y)->int { return x + y; };
typedef int(*allChild)(int x, int y);
typedef int(*oneChild)(int x);
allChild p;
p = totalChild;

//oneChild q;
//q = totalChild;

decltype(totalChild) allPeople = totalChild;
decltype(totalChild) totalPeople = p;

int j = 12;
auto by_val_lambda = [=] { return j + 1; };
auto by_ref_lambda = [&] { return j + 1; };
cout << "by_val_lambda: " << by_val_lambda() << endl;
cout << "by_ref_lambda: " << by_ref_lambda() << endl;

j++;
cout << "by_val_lambda: " << by_val_lambda() << endl;
cout << "by_ref_lambda: " << by_ref_lambda() << endl;

int a = 1;
int b = 2;
auto func = [=]() {return a + b; };

int boys = 4, girls = 3;
auto totalChild = [girls, &boys]()->int { return girls + boys; };
cout << totalChild() << endl;

int girls = 3, boys = 4;
auto totalChild = [](int x, int y)->int { return x + y; };
cout << totalChild(3, 4) << endl;

class NoHeapAlloc {
public:
	void * operator new(std::size_t) = delete;
};

NoHeapAlloc nha;
NoHeapAlloc * pnha = new NoHeapAlloc;

class ConvType {
public:
	ConvType(int i) {};
	ConvType(char c) = delete;
};

void Func(ConvType ct) {}

Func(3);
Func('a');

ConvType ci(3);
ConvType cc('a');

class DefaultedOptr {
public:
	DefaultedOptr() = default;
	DefaultedOptr & operator = (const DefaultedOptr &);
};

inline DefaultedOptr &
DefaultedOptr::operator= (const DefaultedOptr &) = default;

class NoCopyCstor {
public:
	NoCopyCstor() = default;

	NoCopyCstor(const NoCopyCstor &) = delete;
};

NoCopyCstor a;
NoCopyCstor b(a);

class TwoCstor {
public:
	TwoCstor() = default;
	TwoCstor(int i) : data(i) {}

private:
	int data;
};

cout << is_pod<TwoCstor>::value << endl;

char * cp = nullptr;

nullptr_t nptr = nullptr;
if (nptr == nullptr)
cout << "nullptr_t nptr == nullptr" << endl;
else
cout << "nullptr_t nptr != nullptr" << endl;

if (nptr < nullptr)
	cout << "nullptr_t nptr < nullptr" << endl;
else
cout << "nullptr_t nptr !< nullptr" << endl;

sizeof(nullptr);
typeid(nullptr);
throw(nullptr);


struct A { ~A() { cout << "Destruct A. " << endl; } };

void closeDevice() { cout << "device is closed." << endl; }


A a;
at_quick_exit(closeDevice);
quick_exit(0);

void print_terminate()
{
	cout << "terminate" << endl;
}

set_terminate(print_terminate);
char* p = NULL;
*p = 'c';

atomic<int> a;
atomic<int> b;

int Thread1(int) {
	int t = 1;
	a.store(t, memory_order_relaxed);
	b.store(2, memory_order_release);
	return 0;
}

int Thread2(int) {
	while (b.load(memory_order_acquire) != 2);
	cout << a.load(memory_order_relaxed) << endl;
	return 0;
}

thread t1(Thread1, 0);
thread t2(Thread2, 0);

t1.join();
t2.join();
cout << "Got (" << a << ", " << b << ")" << endl;

atomic<int> a{ 0 };
atomic<int> b{ 0 };

int ValueSet(int) {
	int t = 1;
	a.store(t/*, memory_order_relaxed*/);
	b.store(2/*, memory_order_acquire*/);
	return 0;
}

int Observer(int) {
	cout << "(" << a << ", " << b << ")" << endl;
	return 0;
}

thread t1(ValueSet, 0);
thread t2(Observer, 0);

t1.join();
t2.join();
cout << "Got (" << a << ", " << b << ")" << endl;

atomic<int> a{ 0 };
atomic<int> b{ 0 };

int ValueSet(int) {
	int t = 1;
	a = t;
	b = 2;
	return 0;
}

int Observer(int) {
	cout << "(" << a << ", " << b << ")" << endl;
	return 0;
}

thread t1(ValueSet, 0);
thread t2(Observer, 0);

t1.join();
t2.join();

std::atomic_flag lock = ATOMIC_FLAG_INIT;

void f(int n) {
	while (lock.test_and_set(std::memory_order_acquire))
		cout << "Waiting from thread " << n << endl;
	cout << "Thread " << n << " starts working" << endl;
}

void g(int n) {
	cout << "Thread " << n << " is going to start." << endl;
	lock.clear();
	cout << "Thread " << n << " starts working" << endl;
}

lock.test_and_set();

thread t1(f, 1);
thread t2(g, 2);

t1.join();
Sleep(1);
t2.join();

class my_class {
public:
	void add()
	{
		num++;
	}
	void print()
	{
		cout << num << endl;
	}
private:
	long long num = 0;
};

atomic<my_class> value;


void func(int) {
	for (long long i = 0; i < 100000000LL; ++i) {
		value.operator my_class
	}
}


thread t1(func, 0);
thread t2(func, 0);

t1.join();
t2.join();

atomic_llong total{ 0 };

total += i;


cout << total << endl;

using my_type = vector<tuple<int, string, const char*>>;

my_type a;
a.push_back(make_tuple(1, "aaa", "111"));
a.push_back(make_tuple(2, "bbb", "222"));
for_each(a.begin(), a.end(), [](tuple<int, string, const char*>& t)
{
	cout << get<int>(t) << '\t' << get<string>(t) << '\t' << get<const char*>(t) << endl;
});

template<typename A, typename B> struct S {};

template<
	template<typename... > class T, typename... TArgs,
	template<typename... > class U, typename... UArgs
>

S<int, float> p;
//S<std::tuple<int, char>, std::tuple<float>> s;

template<typename I, template<typename> class... B> struct Container {};

template<typename I, template<typename> class A, template<typename> class... B>
struct Container<I, A, B...> {
	A<I> a;
	Container<I, B...> b;
};

template<typename I> struct Container<I> {};

template<class...A> void Print(A...arg) {
	assert(false);
}

void Print(int a1, int a2, int a3, int a4, int a5, int a6) {
	cout << a1 << ", " << a2 << ", " << a3 << ", "
		<< a4 << ", " << a5 << ", " << a6 << endl;
}

template<typename ... T> void DummyWrapper(T... t) {
	cout << "DummyWrapper" << endl;
}

template<typename T> T pr(T t) {
	cout << t;
	return t;
}

template<typename... A>
void VTPrint(A... a) {
	DummyWrapper(pr(a)...);
}


VTPrint(1, ", ", 1.2, ", abc\n");


void Printf(const char* s) {
	while (*s) {
		if (*s == '%' && *++s != '%')
			throw runtime_error("invalid format string: missing arguments");
		cout << *s++;
	}
}

template<typename T, typename... Args>
void Printf(const char* s, T value, Args... args) {
	while (*s) {
		if (*s == '%' && *++s != '%') {
			cout << value;
			return Printf(++s, args...);
		}
		cout << *s++;
	}
	throw runtime_error("extra arguments provided to Printf");
}

Printf("hello %s.\n", string("world"));


template <long... nums> struct Multiply;

template <long first, long... last>
struct Multiply<first, last...> {
	static const long val = first * Multiply<last...>::val;
};

template<>
struct Multiply<> {
	static const long val = 1;
};

cout << Multiply<2, 3, 4, 5>::val << endl;
cout << Multiply<22, 44, 66, 88, 9>::val << endl;

template<typename T1, typename T2> class B {};
template<typename... A> class Template : private B<A...> {};
Template<int, double> xy;

struct Date {
	constexpr Date(int y, int m, int d) :
		year(y), month(m), day(d) {}

	constexpr int GetYear() { return year; }
	constexpr int GetMonth() { return month; }
	constexpr int GetDay() { return day; }
private:
	int year;
	int month;
	int day;
};

constexpr Date PRCfound{ 1949, 10, 1 };
const int foundmonth = PRCfound.GetMonth();

//cout << foundmonth << endl;
	//cout << PRCfound.GetMonth() << endl;

struct MyType {
	constexpr MyType(int x) : i(x) {}
	int i;
};
constexpr MyType mt = { 0 };

int *p = new int;
declare_reachable(p);
int *q = (int *)((long long)p ^ 2012);
q = undeclare_reachable<int>((int*)((long long)q ^ 2012));
*q = 10;

pointer_safety safety = get_pointer_safety();
if (safety == pointer_safety::relaxed)
{
	cout << "safety == pointer_safety::relaxed" << endl;
}
else if (safety == pointer_safety::preferred)
{
	cout << "safety == pointer_safety::preferred" << endl;
}
else if (safety == pointer_safety::strict)
{
	cout << "safety == pointer_safety::strict" << endl;
}

void Check(weak_ptr<int> & wp) {
	shared_ptr<int> sp = wp.lock();
	if (sp != nullptr)
		cout << "still " << *sp << endl;
	else
		cout << "pointer is invalid." << endl;
}

shared_ptr<int> sp1(new int(22));
shared_ptr<int> sp2 = sp1;
weak_ptr<int> wp = sp1;

cout << *sp1 << endl;
cout << *sp2 << endl;
Check(wp);

sp1.reset();
cout << *sp2 << endl;
Check(wp);

sp2.reset();
Check(wp);

enum class Type { General, Light, Medium, Heavy };   //强类型枚举
enum class Type { General = 1, Pistol, , MachineGun, Cannon };

Type t = Type::Light;
//t = General;

using nullptr_t = decltype(nullptr);
cout << typeid(nullptr).name() << endl;

int i;
decltype(i) j = 0;
cout << typeid(j).name() << endl;

float a;
double b;
decltype(a + b) c;
cout << typeid(c).name() << endl;

class White {};
class Black {};

White a;
Black b;

cout << typeid(a).name() << endl;
cout << typeid(b).name() << endl;

White c;

bool a_b_sametype = (typeid(a).hash_code() == typeid(b).hash_code());
bool a_c_sametype = (typeid(a).hash_code() == typeid(c).hash_code());

cout << "ab:" << a_b_sametype << "  ac:" << a_c_sametype << endl;

cout << typeid(int).name() << endl;

double foo() { return double(); }
float * bar() { return nullptr; }

const auto a = foo();
cout << is_same<decltype(a), const double>::value << endl;
const auto & b = foo();
cout << is_same<decltype(a), const double>::value << endl;

template<typename T1, typename T2>
double Sum(T1 & t1, T2 & t2) {
	auto s = t1 + t2;
	return s;
}

int a = 3;
long b = 5;
float c = 1.0f, d = 2.3f;
auto e = Sum<int, long>(a, b);
auto f = Sum<float, float>(c, d);

class PI {
public:
	double operator* (float v) {
		return (double)val * v;
	}
	const float val = 3.1415927f;
};

float radius{ 1.7e10 };
PI pi;
auto circumference = 2 * (pi * radius);
cout << circumference << endl;

auto name = "world.\n";
cout << "hello, " << name;

template<typename T> using MapString = std::map<T, string>;
MapString<int> numberedString;

template<typename T> using MapInt = std::map<T, int>;

MapInt<char> mymap;

// first insert function version (single parameter):
mymap.insert(std::pair<char, int>('a', 100));
mymap.insert(std::pair<char, int>('z', 200));

numberedString.insert(make_pair(1, "aaaa"));

using uint = unsigned int;
typedef unsigned int UINT;
using sint = int;

cout << is_same<uint, UINT>::value << endl;

struct Trivial1 {};
struct Trivial2 {
public:
	int a;
private:
	int b;
};

struct Trivial3 {
	Trivial1 a;
	Trivial2 b;
};

struct Trivial4 {
	Trivial2 a[23];
};

struct Trivial5 {
	int x;
	static int y;
};

struct NonTrivial1 {
	NonTrivial1() : z(42) {}
	int z;
};

struct NonTrivial2 {
	NonTrivial2();
	int w;
};
NonTrivial2::NonTrivial2() = default;

struct NonTrivial3 {
	Trivial5 c;
	virtual void f();
};

cout << is_trivial<Trivial1>::value << endl;
cout << is_trivial<Trivial2>::value << endl;
cout << is_trivial<Trivial3>::value << endl;
cout << is_trivial<Trivial4>::value << endl;
cout << is_trivial<Trivial5>::value << endl;
cout << is_trivial<NonTrivial1>::value << endl;
cout << is_trivial<NonTrivial2>::value << endl;
cout << is_trivial<NonTrivial3>::value << endl;

vector<int> Func() { return { 1, 3 }; }


vector<int> v = Func();
for_each(v.begin(), v.end(), [](int i) { cout << i << endl; });

class Mydata {
public:
	Mydata & operator [] (initializer_list<int> l)
	{
		for (auto i = l.begin(); i != l.end(); ++i)
			idx.push_back(*i);
		return *this;
	}
	Mydata & operator = (int v)
	{
		if (idx.empty() != true) {
			for (auto i = idx.begin(); i != idx.end(); ++i) {
				d.resize((static_cast<size_t>(*i) > d.size()) ? *i : d.size());
				d[*i - 1] = v;
			}
			idx.clear();
		}
		return *this;
	}
	void Print() {
		for (auto i = d.begin(); i != d.end(); ++i)
			cout << *i << " ";
		cout << endl;
	}

private:
	vector<int> idx;
	vector<int> d;
};

Mydata d;
d[{2, 3, 5}] = 7;
d[{1, 4, 5, 8}] = 4;
d.Print();

void Fun(initializer_list<int> iv) {}

Fun({ 1, 2 });
Fun({});

enum Gender { boy, girl };
class People {
public:
	People(initializer_list<pair<string, Gender>> li) {
		auto i = li.begin();
		for (; i != li.end(); ++i)
			data.push_back(*i);
	}

private:
	vector<pair<string, Gender>> data;
};

People ship2012 = { {"Garfield", boy}, {"HelloKitty", girl} };

int a[] = { 1, 3, 5 };
int b[]{ 2, 4, 5 };
vector<int> c{ 1, 3, 5 };
map<int, float> d =
{ {1, 1.0f}, {2, 2.0f}, {5, 3.2f} };

template <typename T>
class Ptr {
public:
	Ptr(T* p) : _p(p) {}
	operator bool() const {
		if (_p != 0)
			return true;
		else
			return false;
	}
private:
	T* _p;
};

int a;
Ptr<int> p(&a);

if (p)
cout << "valid pointer." << endl;
else
cout << "invalid pointer." << endl;

Ptr<double> pd(0);
cout << p + pd << endl;

//void RunCode(int m) { cout << "lvalue" << endl; }
void RunCode(int && m) { cout << "rvalue ref" << endl; }
void RunCode(int & m) { cout << "lvalue ref" << endl; }
void RunCode(const int && m) { cout << "const rvalue ref" << endl; }
void RunCode(const int & m) { cout << "const lvalue ref" << endl; }

template <typename T>
void PerfectForward(T && t) { RunCode(forward<T>(t)); }

int a;
int b;
const int c = 1;
const int d = 0;

PerfectForward(a);
PerfectForward(move(b));
PerfectForward(c);
PerfectForward(move(d));

template <typename T>
void IamForwording(T && t) {
	IrunCodeActually(static_cast<T &&>(t));
}

struct Maythrow {
	Maythrow() {}
	Maythrow(const Maythrow&) {
		std::cout << "Maythrow copy constructor." << endl;
	}
	Maythrow(Maythrow&&) {
		std::cout << "Maythrow move constructor." << endl;
	}
};

struct Nothrow {
	Nothrow() {}
	Nothrow(Nothrow&&) noexcept {
		std::cout << "Nothrow move constructor." << endl;
	}
	Nothrow(const Nothrow&) {
		std::cout << "Nothrow copy constructor." << endl;
	}
};

{
	Maythrow m;
	Nothrow n;
	Maythrow mt = move_if_noexcept(m);
	Nothrow nt = move_if_noexcept(n);
}

class HugeMem {
public:
	HugeMem(int size) : sz(size > 0 ? size : 1) {
		c = new int[sz];
	}
	~HugeMem() { delete[] c; }
	HugeMem(HugeMem && hm) : sz(hm.sz), c(hm.c) {
		hm.c = nullptr;
	}
	int* c;
	int sz;
};
class Moveable {
public:
	Moveable() :i(new int(3)), h(1024) {}
	~Moveable() { delete i; }
	Moveable(Moveable && m) :
		i(m.i), h(move(m.h)) {
		m.i = nullptr;
	}

	int* i;
	HugeMem h;
};
Moveable GetTemp() {
	Moveable tmp = Moveable();
	cout << hex << "Huge Mem from " << __func__
		<< "@" << tmp.h.c << endl;
	return tmp;
}

{
	Moveable a(GetTemp());
	cout << hex << "Huge Mem from " << __func__
		<< "@" << a.h.c << endl;
}

class Moveable {
public:
	Moveable() : i(new int(3)) { }
	~Moveable() { delete i; }
	Moveable(const Moveable & m) : i(new int(*m.i)) {}
	Moveable(Moveable && m) : i(m.i) {
		m.i = nullptr;
	}
	int* i;
};

Moveable a;
Moveable c(move(a));
cout << *a.i << endl;

class my_class {
public:
	int a = 5;
};

void func_a(my_class&& c)
{
	cout << "func_a:" << c.a << endl;
}

func_a(my_class());

class HasPtrMem {
public:
	HasPtrMem() : d(new int{ 3 }) {
		cout << "Construct: " << ++n_cstr << endl;
		cout << "*d = " << *d << endl;
	}
	HasPtrMem(const HasPtrMem & h) : d(new int(*h.d)) {
		cout << "Copy construct: " << ++n_cstr << endl;
	}
	HasPtrMem(HasPtrMem && h) : d(h.d) {
		h.d = nullptr;
		cout << "Move construct: " << ++n_mvtr << endl;
	}
	~HasPtrMem() {
		std::cout << "d = " << d << endl;
		delete d;
		cout << "Destruct: " << ++n_dstr << endl;
	}
	int * d;
	static int n_cstr;
	static int n_dstr;
	static int n_cptr;
	static int n_mvtr;
};

int HasPtrMem::n_cstr = 0;
int HasPtrMem::n_dstr = 0;
int HasPtrMem::n_cptr = 0;
int HasPtrMem::n_mvtr = 0;

HasPtrMem GetTemp() {
	HasPtrMem h;
	cout << "Resource from " << __func__ << ": " << hex << h.d << endl;
	return h;
}

{
	HasPtrMem a = GetTemp();
	cout << "Resource from " << __func__ << ": " << hex << a.d << endl;
}

class HasPtrMem {
public:
	HasPtrMem() : d(new int{ 0 }) {
		cout << "Construct: " << ++n_cstr << endl;
	}
	HasPtrMem(const HasPtrMem & h) : d(new int(*h.d)) {
		cout << "Copy construct: " << ++n_cstr << endl;
	}
	~HasPtrMem() {
		cout << "Destruct: " << ++n_dstr << endl;
	}
	int * d;
	static int n_cstr;
	static int n_dstr;
	static int n_cptr;
};

int HasPtrMem::n_cstr = 0;
int HasPtrMem::n_dstr = 0;
int HasPtrMem::n_cptr = 0;

HasPtrMem GetTemp() { return HasPtrMem(); }

{
	HasPtrMem a = GetTemp();
}

class DCExcept {
public:
	DCExcept(double d)
		try : DCExcept(1, d) {

	}
	catch (...) {
		cout << "caught exception." << endl;
	}
private:
	DCExcept(int i, double d) {
		cout << "going to throw!" << endl;
		throw 0;
	}
	int type;
	double data;
};

DCExcept a(1.2);

class TDConstructed {
	template<class T> TDConstructed(T first, T last) :
		l(first, last) {}
	list<int> l;

public:
	TDConstructed(vector<short> & v) :
		TDConstructed(v.begin(), v.end()) {}
	TDConstructed(deque<int> & d) :
		TDConstructed(d.begin(), d.end()) {}
	void print()
	{
		for_each(l.begin(), l.end(), [](int i) {cout << i << "\t"; });
		std::cout << endl;
	}
};

vector<short> v{ 1, 2, 3, 4 };
TDConstructed t(v);
t.print();
deque<int> d{ 100, 300, 500, 700 };
TDConstructed t1(d);
t1.print();

class Info {
public:
	Info() : Info(1) {}
	Info(int i) : Info(i, 'a') {}
	Info(char e) : Info(1, e) {}

private:
	Info(int i, char e) : type(i), name(e) {}
	int type{ 1 };
	char name{ 'a' };
};

Info i(1);
Info i1('c');

class Info {
public:
	Info() : Info(1, 'a') {}
	Info(int i) : Info(i, 'a') {}
	Info(char e) : Info(1, e) {}

private:
	Info(int i, char e) : type(i), name(e) {}
	int type{ 1 };
	char name{ 'a' };
};

class Info {
public:
	Info() { InitRest(); }
	Info(int i) : Info() { type = i; }
	Info(char e) : Info() { name = e; }

private:
	void InitRest() {}
	int type{ 1 };
	char name{ 'a' };
};



struct A {
	A(int i) {}
	A(double d, int i) {}
	A(float f, int i, const char* c) {}
};

struct B : A {
	using A::A;
	virtual void ExtraInterface() {}
};

B b(1);
b.ExtraInterface();

TempFun(1);
TempFun("1");

template <typename T> void TempFun(T a) {
	cout << a << endl;
}

template <typename T> class DefenderT {
public:
	friend T;
	void Defence(int x, int y) {}
	void Tackle(int x, int y) {}
private:
	int pos_x = 15;
	int pos_y = 0;
	int speed = 2;
	int stamina = 120;
};

template <typename T> class AttackerT {
public:
	friend T;
	void Move(int x, int y) {}
	void SpeedUp(float ratio) {}
private:
	int pos_x = 0;
	int pos_y = -30;
	int speed = 3;
	int stamina = 100;
};

using Defender = DefenderT<int>;
using Attacker = AttackerT<int>;

#define UNIT_TEST
#ifdef UNIT_TEST

class Validator;
using DefenderTest = DefenderT<Validator>;
using AttackerTest = AttackerT<Validator>;

class Validator {
public:
	void Validate(int x, int y, DefenderTest & d) {}
	void Validate(int x, int y, AttackerTest & a) {}
};

DefenderTest d;
AttackerTest a;
a.Move(15, 30);
d.Defence(15, 30);
a.SpeedUp(1.5f);
d.Defence(15, 30);
Validator v;
v.Validate(7, 0, d);
v.Validate(1, -10, a);

#endif

class Mem {
public:
	Mem(int i) : m(i) {}

private:
	int m;
};

class Group {
public:
	Group() {}
	Group(int a) : data(a) {}
	Group(Mem m) : mem(m) {}
	Group(int a, Mem m, string n) : data(a), mem(m), name(n) {}

private:
	int data = 1;
	Mem mem{ 0 };
	string name{ "Group" };
};

struct Mem {
	Mem() { cout << "Mem default, num: " << num << endl; }
	Mem(int i) : num(i) { cout << "Mem, num: " << num << endl; }

	int num = 2;
};

class Group {
public:
	Group() { cout << "Group default. val: " << val << endl; }
	Group(int i) : val('G'), a(i) { cout << "Group. val:" << val << endl; }
	void NumOfA() { cout << "number of A: " << a.num << endl; }
	void NumOfB() { cout << "number of B: " << b.num << endl; }

private:
	char val{ 'g' };
	Mem a;
	Mem b{ 19 };
};


Mem member;

Group group;
group.NumOfA();
group.NumOfB();

Group group2(7);
group2.NumOfA();
group2.NumOfB();

#define LOG(...) {\
	fprintf(stderr, "%s: Line %d:\t", __FILE__, __LINE__);\
	fprintf(stderr, __VA_ARGS__);\
	fprintf(stderr, "\n");\
 }

int x = 3;
LOG("x = %d", x);

struct TestStruct {
	TestStruct() : name(__func__) {}
	const char *name;
};

TestStruct ts;
cout << ts.name << endl;


const char* hello() { return __func__; }
const char* world() { return __func__; }

cout << hello() << ", " << world() << endl;

void f(int && a)
{
	cout << a << endl;
}

template<typename T>
void f1(T&& param)
{
	cout << param << endl;
}

int&& f2(void)
{
	int a = 10;
	cout << &a << endl;
	return std::move(a);
}

int&& f3(void)
{
	int&& a = f2();
	cout << &a << endl;
	int b = 10;
	return std::move(a);
}

int&& a = f3();
cout << &a << endl;

/*f(10);
int a = 8;
f(std::move(a));
a = 6;
f(std::move(a));*/
/*f1(10);
int a = 8;
f1(std::move(a));*/

template <typename T>
void f(T&&) {
	cout << boolalpha;
	cout << "is int ? : " << is_same<int, T>::value << endl;
	cout << "is int& ? : " << is_same<int&, T>::value << endl;
	cout << "is int&& ? : " << is_same<int&&, T>::value << endl;
	cout << endl;
}

int i = 0;
int &ri = i;
int &&rri = 4;
f(i);     //左值
f(ri);    // 左值引用
f(0);      //右值
f(std::move(i)); // 匿名的右值引用， 正确识别
f(rri);       //实际上 f 收到的是左值引用, 右值引用只能绑定到 右值 上，而不能绑定到另一个右值引用上， 左值引用却可以绑定到另一个右值引用或者另一个左值引用或者左值上


void f(int&& a)
{
	std::cout << std::is_same<int&&, decltype(a)>::value << std::endl;
}

int a = 5;
f(std::move(a));

// 简单正则表达式匹配
std::string fnames[] = { "foo.txt", "bar.txt", "baz.dat", "zoidberg" };
std::regex txt_regex("[a-z]+\\.txt");

for (const auto &fname : fnames) {
	std::cout << fname << ": " << std::regex_match(fname, txt_regex) << '\n';
}

// 提取子匹配
std::regex base_regex("([a-z]+)\\.txt");
std::smatch base_match;

for (const auto &fname : fnames) {
	if (std::regex_match(fname, base_match, base_regex)) {
		// 首个 sub_match 是整个字符串；下个
		// sub_match 是首个有括号表达式。
		if (base_match.size() == 2) {
			std::ssub_match base_sub_match = base_match[1];
			std::string base = base_sub_match.str();
			std::cout << fname << " has a base of " << base << '\n';
		}
	}
}

// 提取几个子匹配
std::regex pieces_regex("([a-z]+)\\.([a-z]+)");
std::smatch pieces_match;

for (const auto &fname : fnames) {
	if (std::regex_match(fname, pieces_match, pieces_regex)) {
		std::cout << fname << '\n';
		for (size_t i = 0; i < pieces_match.size(); ++i) {
			std::ssub_match sub_match = pieces_match[i];
			std::string piece = sub_match.str();
			std::cout << "  submatch " << i << ": " << piece << '\n';
		}
	}
}


const std::string s = "Quick brown fox.";

std::regex words_regex("[^\\s]+");
auto words_begin =
std::sregex_iterator(s.begin(), s.end(), words_regex);
auto words_end = std::sregex_iterator();

std::cout << "Found "
<< std::distance(words_begin, words_end)
<< " words:\n";

for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
	std::smatch match = *i;
	std::string match_str = match.str();
	std::cout << match_str << '\n';
}

std::string text = "Quick brown fox";
std::regex vowel_re("a|e|i|o|u");

// 写结果到输出迭代器
std::regex_replace(std::ostreambuf_iterator<char>(std::cout),
	text.begin(), text.end(), vowel_re, "*");

// 构造保有结果的字符串
std::cout << '\n' << std::regex_replace(text, vowel_re, "[$&]") << '\n';


std::string s = "Some people, when confronted with a problem, think "
"\"I know, I'll use regular expressions.\" "
"Now they have two problems.";

std::regex self_regex("REGULAR EXPRESSIONS",
	std::regex_constants::ECMAScript | std::regex_constants::icase);
if (std::regex_search(s, self_regex)) {
	std::cout << "Text contains the phrase 'regular expressions'\n";
}

std::regex word_regex("(\\S+)");
auto words_begin =
std::sregex_iterator(s.begin(), s.end(), word_regex);
auto words_end = std::sregex_iterator();

std::cout << "Found "
<< std::distance(words_begin, words_end)
<< " words\n";

const int N = 6;
std::cout << "Words longer than " << N << " characters:\n";
for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
	std::smatch match = *i;
	std::string match_str = match.str();
	if (match_str.size() > N) {
		std::cout << "  " << match_str << '\n';
	}
}

std::regex long_word_regex("(\\w{7,})");
std::string new_s = std::regex_replace(s, long_word_regex, "[$&]");
std::cout << new_s << '\n';



#include <iostream>
#include <regex>

using namespace std;

int main()
{
	{
		regex reg1("\\w+day");
		string s1 = "saturday";
		string s2 = "saturday and sunday";
		smatch rr1;
		smatch rr2;
		cout << boolalpha << regex_search(s1, rr1, reg1) << endl;
		cout << "s1匹配结果：" << rr1.str() << endl;
		cout << boolalpha << regex_search(s2, rr2, reg1) << endl;
		cout << "s1匹配结果：" << rr2.str() << endl;
		cout << endl;
	}

	{
		regex reg1("\\w+day");
		string s1 = "saturday";
		string s2 = "saturday and sunday";
		smatch r1;
		smatch r2;
		cout << boolalpha << regex_match(s1, r1, reg1) << endl;
		cout << boolalpha << regex_match(s2, r2, reg1) << endl;
		cout << "s1匹配结果：" << r1.str() << endl;
		cout << "s2匹配结果：" << r2.str() << endl;
		cout << endl;
	}

	system("pause");
	return 0;
}

namespace my_space
{
	template<typename... Args>
	void printf(const std::string &str, Args... args)
	{
		std::cout << str << std::endl;
		std::cout << sizeof...(args) << std::endl;
	}
}

my_space::printf("aaaaa", 1, 2, 3, 4);


#include <iostream>
#include <vector>

class MyNumber
{
public:
	MyNumber(const std::initializer_list<int> &v) {
		for (auto itm : v) {
			mVec.push_back(itm);
		}
	}

	void print() {
		for (auto itm : mVec) {
			std::cout << itm << " ";
		}
	}
private:
	std::vector<int> mVec;
};

int main()
{
	MyNumber m = { 1, 2, 3, 4 };
	m.print();  // 1 2 3 4

	system("pause");
	return 0;
}

#endif