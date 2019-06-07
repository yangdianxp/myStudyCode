#include <iostream>
#include <vector>

#include "Cpp_Concurrency_In_Action_study.h"


int main()
{


	system("pause");
}


#if 0
	std::vector<int> vec;
	for (auto i = 0; i < 100000000; ++i)
	{
		vec.push_back(i);
	}
	auto result = parallel_accumulate(vec.begin(), vec.end(), 0);
	std::cout << result << std::endl;




#endif