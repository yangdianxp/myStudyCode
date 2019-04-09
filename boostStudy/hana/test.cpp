#include <cassert>
#include <iostream>
#include <string>

#include <boost/hana.hpp>
namespace hana = boost::hana;
using namespace hana::literals;

struct Fish { std::string name; };
struct Cat { std::string name; };
struct Dog { std::string name; };

int main()
{
	boost::any a = 'x';
	std::string r = switch_(a)(
		case_<int>([](auto i) { return "int: "s + std::to_string(i); }),
		case_<char>([](auto c) { return "char: "s + std::string{ c }; }),
		default_([] { return "unknown"s; })
		);
	assert(r == "char: x"s);


	system("pause");
	return 0;
}


#if 0
auto animals = hana::make_tuple(Fish{ "Nemo" }, Cat{ "Garfield" }, Dog{ "Snoopy" });
// Access tuple elements with operator[] instead of std::get.
Cat garfield = animals[1_c];

// Perform high level algorithms on tuples (this is like std::transform)
auto names = hana::transform(animals, [](auto a) {
	return a.name;
});

assert(hana::reverse(names) == hana::make_tuple("Snoopy", "Garfield", "Nemo"));

std::cout << animals[0_c].name << std::endl;
std::cout << animals[1_c].name << std::endl;
std::cout << animals[2_c].name << std::endl;

auto animal_types = hana::make_tuple(hana::type_c<Fish*>, hana::type_c<Cat&>, hana::type_c<Dog>);
auto no_pointers = hana::remove_if(animal_types, [](auto a) {
	return hana::traits::is_pointer(a);
});
static_assert(no_pointers == hana::make_tuple(hana::type_c<Cat&>, hana::type_c<Dog>), "");

auto has_name = hana::is_valid([](auto&& x) -> decltype((void)x.name) {});
static_assert(has_name(garfield), "");
static_assert(!has_name(1), "");

std::cout << has_name(garfield) << std::endl;
std::cout << has_name(1) << std::endl;

// 1. Give introspection capabilities to 'Person'
/*struct Person {
	BOOST_HANA_DEFINE_STRUCT(Person,
		(std::string, name),
		(int, age)
	);
};*/
struct Person {
	std::string name;
	int age;
};
// 2. Write a generic serializer (bear with std::ostream for the example)
auto serialize = [](std::ostream& os, auto const& object) {
	hana::for_each(hana::members(object), [&](auto member) {
		os << member << std::endl;
	});
};
// 3. Use it
Person john{};

serialize(std::cout, john);
// output:
// John
// 30

#endif

