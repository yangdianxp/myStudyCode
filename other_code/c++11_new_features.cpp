#include <iostream>
#include <iterator>
#include <string>
#include <regex>

using namespace std;

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


int main()
{
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
	
	system("pause");
}

#if 0

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