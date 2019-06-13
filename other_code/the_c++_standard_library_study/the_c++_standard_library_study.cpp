#include <iostream>


int main()
{
	system("pause");
	return 0;
}

#if 0
迭代器看到  467页
算法看到534    回头看迭代器

	int array[] = { 1, 2, 3, 4, 5 };
	long sum = 0;
	for (int x : array) {
		sum += x;
	}
	for (auto elem : { sum, sum * 2, sum * 4 }) {
		std::cout << elem << std::endl;
	}


#endif