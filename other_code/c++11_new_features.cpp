#include <iostream>
#include <iterator>
#include <string>
#include <regex>

int main()
{
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

	system("pause");
}

#if 0
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