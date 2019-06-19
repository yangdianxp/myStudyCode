#include <iostream>
#include <unordered_set>

using namespace std;

class Customer
{

};

std::size_t customer_hash_func(const Customer& c)
{
	return 0;
}

int main()
{
	unordered_set<Customer, std::size_t(*)(const Customer&)>
		custset(20, customer_hash_func);

	system("pause");
	return 0;
}

#if 0
正则表达式    720


	int array[] = { 1, 2, 3, 4, 5 };
	long sum = 0;
	for (int x : array) {
		sum += x;
	}
	for (auto elem : { sum, sum * 2, sum * 4 }) {
		std::cout << elem << std::endl;
	}


#endif