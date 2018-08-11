#include <iostream>
#include <map>
#include <unordered_map>
#include <set>
#include <boost/bimap.hpp>
#include <boost/bimap/unordered_set_of.hpp>
#include <boost/bimap/list_of.hpp>
#include <boost/bimap/multiset_of.hpp>
#include <boost/bimap/set_of.hpp>
#include <boost/bimap/vector_of.hpp>
#include <boost/bimap/unordered_multiset_of.hpp>
#include <boost/bimap/support/lambda.hpp>

int main()
{
	std::unordered_multimap<int, double> myUnorderedMap;
	for (int i = 1; i < 10; i++)
	{
		myUnorderedMap.insert(std::make_pair(i, i * 1.1));
		myUnorderedMap.insert(std::make_pair(i, i * 2.2));
	}
	std::for_each(myUnorderedMap.begin(), myUnorderedMap.end(), 
		[](std::pair<int, double> pair) {
			std::cout << pair.first << " " << pair.second << std::endl;
		});
	std::cout << "==============================" << std::endl;
	for (auto it = myUnorderedMap.lower_bound(3), itEnd = myUnorderedMap.upper_bound(10);
		it != itEnd; ++it)
	{
		std::cout << it->first << " " << it->second << std::endl;
	}
	std::cout << "==============================" << std::endl;
	auto pairIt = myUnorderedMap.equal_range(5);
	for (auto it = pairIt.first; it != pairIt.second; ++it)
	{
		std::cout << it->first << " " << it->second << std::endl;
	}
	

	/*using namespace std;
	using namespace boost::bimaps;
	using bmType = bimap<set_of<int>, multiset_of<int>>;
	using elemType = bmType::value_type;

	bmType myBimap;
	myBimap.insert(elemType(1, 1000));
	myBimap.insert(elemType(2, 1001));

	for (auto it = myBimap.right.begin(), itEnd = myBimap.right.end(); it != itEnd; ++it)
	{
		std::cout << it->first << "  " << it->second << std::endl;
	}

	bmType::left_iterator it = myBimap.left.find(1);
	myBimap.left.modify_data(it, ++_data);
	myBimap.left.modify_data(it, ++_data);

	for (auto it = myBimap.right.begin(), itEnd = myBimap.right.end(); it != itEnd; ++it)
	{
		std::cout << it->first << "  " << it->second << std::endl;
	}*/



	/*for (auto it = myBimap.begin(), itEnd = myBimap.end(); it != itEnd; ++it)
	{
		std::cout << it->left << "  " << it->right << std::endl;
	}
	for (auto it = myBimap.left.begin(), itEnd = myBimap.left.end(); it != itEnd; ++it)
	{
		std::cout << it->first << "  " << it->second << std::endl;
	}

	for (auto it = myBimap.right.begin(), itEnd = myBimap.right.end(); it != itEnd; ++it)
	{
		std::cout << it->first << "  " << it->second << std::endl;
	}*/



	system("pause");

	return 0;
}
