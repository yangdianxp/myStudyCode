#include <iostream>

namespace my_space
{
	template<typename... Args>
	void printf(const std::string &str, Args... args)
	{
		std::cout << str << std::endl;
		std::cout << sizeof...(args) << std::endl;
	}
}


int main()
{
	my_space::printf("aaaaa", 1, 2, 3, 4);
	system("pause");
	return 0;
}

#if 0
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