//  Copyright Joel de Guzman 2002-2004. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//  Hello World Example from the tutorial
//  [Joel de Guzman 10/9/2002]

#include <boost/python/module.hpp>
#include <boost/python/def.hpp>
#include <boost/python/wrapper.hpp>
#include <boost/python.hpp>
#include <boost/operators.hpp>
#include <boost/python/class.hpp>
#include <boost/python/operators.hpp>
#include <string>
#include <iostream>

using namespace std;
using namespace boost::python;

#if 0

// 类的运算符/特殊函数

class FilePos
{
public:
	FilePos() :len(0) {}
	operator double()const { return len; };//重载类型转换符
	int len;
};

// operator 方法

FilePos operator+(FilePos pos, int a)
{
	pos.len = pos.len + a;

	return pos; //返回的是副本

}

FilePos operator+(int a, FilePos pos)
{
	pos.len = pos.len + a;

	return pos; //返回的是副本

}


int operator-(FilePos pos1, FilePos pos2)
{

	return (pos1.len - pos2.len);

}

FilePos operator-(FilePos pos, int a)
{
	pos.len = pos.len - a;
	return pos;
}

FilePos &operator+=(FilePos & pos, int a)
{
	pos.len = pos.len + a;
	return pos;
}

FilePos &operator-=(FilePos & pos, int a)
{
	pos.len = pos.len - a;
	return pos;
}

bool operator<(FilePos  pos1, FilePos pos2)
{
	if (pos1.len < pos2.len)
		return true;
	return false;
}


//特殊的方法

FilePos pow(FilePos pos1, FilePos pos2)
{
	FilePos res;
	res.len = std::pow(pos1.len, pos2.len);
	return res;

}
FilePos abs(FilePos pos)
{
	FilePos res;
	res.len = std::abs(pos.len);

	return res;
}

ostream& operator<<(ostream& out, FilePos pos)
{
	out << pos.len;
	return out;
}

BOOST_PYTHON_MODULE(hello_operator)
{
	class_<FilePos>("FilePos")
		.def_readwrite("len", &FilePos::len)
		.def(self + int())
		.def(int() + self)
		.def(self - self)
		.def(self - int())
		.def(self += int())
		.def(self -= other<int>())
		.def(self < self)
		.def(float_(self))//特殊方法 ,     __float__
		.def(pow(self, other<FilePos>()))  // __pow__
		.def(abs(self));         //  __abs__
		//.def(str(self));                //  __str__ for ostream


}

#endif

#if 0

/*
 类的虚函数，实现的功能是：可以编写Python类，来继承C++类
*/

struct Base
{
	virtual ~Base() {}
	virtual int f() { return 0; };
};


struct BaseWrap : Base, wrapper<Base>
{
	int f()
	{
		if (override f = this->get_override("f"))
			return f(); //如果函数进行重载了，则返回重载的
		return Base::f(); //否则返回基类
	}
	int default_f() { return this->Base::f(); }
};

BOOST_PYTHON_MODULE(hello_virtual)
{
	class_<BaseWrap, boost::noncopyable>("Base")
		.def("f", &Base::f, &BaseWrap::default_f);


}

#endif

#if 0

struct Base {
	virtual ~Base() {};
	virtual string getName() { return "Base"; }

	string str;
};

struct Derived : Base {

	string getName() { return "Derived"; }

};


void b(Base *base) { cout << base->getName() << endl; };

void d(Derived *derived) { cout << derived->getName() << endl; };

Base * factory() { return new Derived; }

//namespace boost
//{
//	template <>
//	Base const volatile * get_pointer<class Base const volatile >(
//		class Base const volatile *c)
//	{
//		return c;
//	}
//}

BOOST_PYTHON_MODULE(hello_derived)
{
	class_<Base>("Base")
		.def("getName", &Base::getName)
		.def_readwrite("str", &Base::str);


	class_<Derived, bases<Base> >("Derived")
		.def("getName", &Derived::getName)
		.def_readwrite("str", &Derived::str);


	def("b", b);
	def("d", d);

	def("factory", factory,
		return_value_policy<manage_new_object>());//

}

#endif

#if 0

struct Num
{
	Num() {}
	float get() const { return val; }
	void set(float val) { this->val = val; }
	float val;

};

BOOST_PYTHON_MODULE(hello_num)
{
	class_<Num>("Num")
		.add_property("rovalue", &Num::get) // 对外：只读
		.add_property("value", &Num::get, &Num::set);// 对外读写 .value值会改变.rovalue值，存储着同样的数据。

}

#endif

#if 0

struct Base { virtual ~Base(); };
struct Derived : Base {};
void b(Base*)
{
}
void d(Derived*)
{
}
Base* factory() { return new Derived; }

#endif 

#if 0

struct Num
{
    Num();
    float get() const { return m_value; }
    void set(float value) { m_value = value; }
    float m_value;
};

BOOST_PYTHON_MODULE(hello)
{
	class_<Num>("Num")
		.add_property("rovalue", &Num::get)
		.add_property("value", &Num::get, &Num::set);
}

#endif

#if 0

struct Var
{
    Var(std::string name) : name(name), value() {}
    std::string const name;
    float value;
};

BOOST_PYTHON_MODULE(hello)
{
	class_<Var>("Var", init<std::string>())
		.def_readonly("name", &Var::name)
		.def_readwrite("value", &Var::value);
}

#endif

#if 0

struct World
{
    World(std::string msg): msg(msg) {} // added constructor
    void set(std::string msg) { this->msg = msg; }
    std::string greet() { return msg; }
    std::string msg;
};

BOOST_PYTHON_MODULE(hello)
{
    class_<World>("World", init<std::string>())
        .def("greet", &World::greet)
        .def("set", &World::set)
    ;
}

#endif

#if 0
struct World
{
    void set(std::string msg) { this->msg = msg; }
    std::string greet() { return msg; }
    std::string msg;
};

BOOST_PYTHON_MODULE(hello)
{
    class_<World>("World")
        .def("greet", &World::greet)
        .def("set", &World::set)
    ;
}
#endif

#if 0
char const* greet()
{
   return "hello, world";
}

BOOST_PYTHON_MODULE(hello_ext)
{
    using namespace boost::python;
    def("greet", greet);
}
#endif

