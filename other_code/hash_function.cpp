#include <iostream>
#include <functional>
#include <unordered_set>

// 一个万用的Hash Function 如下：
#include<functional>

template<typename T>
inline void hash_combine(size_t &seed, const T& val) {
	seed ^= std::hash<T>()(val) + 0x9e3779b9 + (seed << 6) + (seed >> 2);  //0x9e3779b9
}
//auxiliary generic functions
template<typename T>
inline void hash_val(size_t &seed, const T & val) {
	hash_combine(seed, val);
}

template<typename T, typename... Types>
inline void hash_val(size_t & seed, const T& val, const Types &...args) //逐一取val改变seed（pass by reference）
{
	hash_combine(seed, val);
	hash_val(seed, args...);
}
//auxiliary generic function
template<typename... Types>
inline size_t hash_val(const Types& ...arg) //seed最终就被视为hash code
{
	size_t seed = 0;
	hash_val(seed, arg...);
	return seed;
}

struct node
{
	int a;
	int b;
	int c;
	int d;
	node(int _a, int _b, int _c, int _d) : a(_a), b(_b), c(_c), d(_d) {}
	bool operator==(const node & rhs)const
	{
		std::cout << "operator==" << std::endl;
		return a == rhs.a && b == rhs.b && c == rhs.c && d == rhs.d;
	}
};

class node_hash {
public:
	std::size_t operator ()(const node &n)const
	{
		std::cout << "node_hash" << std::endl;
		return hash_val(n.a, n.b, n.c, n.d);
	}
};

std::unordered_set<node, node_hash> node_set;


int main()
{
	node n(1, 2, 3, 4);
	node_set.insert(n);

	for (int i = 1; i < 10; i++)
	{
		node_set.insert(node(1 * i, 2 * i, 3 * i, 4 * i));
	}

	system("pause");
}