#include <iostream>
#include <vector>
#include <climits>
#include <cstdint>
#include <type_traits>
#include <utility>

template<class ...Args>
void printer(Args&&... args) {
	(std::cout << ... << args) << '\n';
	//(I op ... op E)
	//((((I op E1) op E2) op ...) op EN)
}

template<class T, class... Args>
void push_back_vec(std::vector<T>& v, Args&&... args)
{
	static_assert((std::is_constructible_v<T, Args&> && ...));
	(v.push_back(args), ...);
	//
	//
}

// 基于 http://stackoverflow.com/a/36937049 的编译时端序交换 
template<class T, std::size_t... N>
constexpr T bswap_impl(T i, std::index_sequence<N...>) {
	return (((i >> N * CHAR_BIT & std::uint8_t(-1)) << (sizeof(T) - 1 - N)*CHAR_BIT) | ...);
}
template<class T, class U = std::make_unsigned_t<T>>
constexpr U bswap(T i) {
	return bswap_impl<U>(i, std::make_index_sequence<sizeof(T)>{});
}

int main()
{
	printer(1, 2, 3, "abc");

	std::vector<int> v;
	push_back_vec(v, 6, 2, 45, 12);
	push_back_vec(v, 1, 2, 9);
	for (int i : v) std::cout << i << ' ';

	static_assert(bswap<std::uint16_t>(0x1234u) == 0x3412u);
	static_assert(bswap<std::uint64_t>(0x0123456789abcdefULL) == 0xefcdab8967452301ULL);

	system("pause");
	return 0;
}


#if 0
#include <iostream>

template<typename... Args>
bool all(Args... args) { return (... && args); }

int main()
{

	system("pause");
	return 0;
}


bool b = all(true, true, true, false);
// 在 all() 中，一元左折叠展开成
//  return ((true && true) && true) && false;
// b 为 false
std::cout << b << std::endl;


#include <boost/hana.hpp>
#include <boost/any.hpp>
#include <cassert>
#include <string>
#include <typeindex>
#include <typeinfo>
#include <utility>
namespace hana = boost::hana;
//! [cases]
template <typename T>
auto case_ = [](auto f) {
	return hana::make_pair(hana::type_c<T>, f);
};
struct default_t;
auto default_ = case_<default_t>;
//! [cases]
//! [process]
template <typename Any, typename Default>
auto process(Any&, std::type_index const&, Default& default_) {
	return default_();
}
template <typename Any, typename Default, typename Case, typename ...Rest>
auto process(Any& a, std::type_index const& t, Default& default_,
	Case& case_, Rest& ...rest)
{
	using T = typename decltype(+hana::first(case_))::type;
	return t == typeid(T) ? hana::second(case_)(*boost::unsafe_any_cast<T>(&a))
		: process(a, t, default_, rest...);
}
//! [process]
//! [switch_]
template <typename Any>
auto switch_(Any& a) {
	return [&a](auto ...cases_) {
		auto cases = hana::make_tuple(cases_...);
		auto default_ = hana::find_if(cases, [](auto const& c) {
			return hana::first(c) == hana::type_c<default_t>;
		});
		static_assert(default_ != hana::nothing,
			"switch is missing a default_ case");
		auto rest = hana::filter(cases, [](auto const& c) {
			return hana::first(c) != hana::type_c<default_t>;
		});
		return hana::unpack(rest, [&](auto& ...rest) {
			return process(a, a.type(), hana::second(*default_), rest...);
		});
	};
}
//! [switch_]





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

