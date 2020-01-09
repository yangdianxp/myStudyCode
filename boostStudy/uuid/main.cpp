#include <iostream>
#include <string>
#include <algorithm>

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/name_generator.hpp>

using namespace std;
using namespace boost::uuids;

int main()
{
	for (int i = 0; i < 10; ++i)
	{
		boost::uuids::random_generator gen;
		boost::uuids::uuid id = gen();

		std::string id_str = to_string(id);
		id_str.erase(std::remove(id_str.begin(), id_str.end(), '-'), id_str.end());
		std::cout << id_str << std::endl;
	}
	
	return 0;
}

#if 0

// random_generator
for (int i = 0; i < 10; ++i)
{
	boost::uuids::random_generator gen;
	boost::uuids::uuid id = gen();
	std::cout << id << std::endl;
}

// name_generator
boost::uuids::name_generator_latest gen(boost::uuids::ns::dns());
boost::uuids::uuid id = gen("boost.org1");
std::string id_str = to_string(id);
id_str.erase(std::remove(id_str.begin(), id_str.end(), '-'), id_str.end());
std::cout << id_str << std::endl;

#endif