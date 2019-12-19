#ifndef __NGXEXCEPTION_H__
#define __NGXEXCEPTION_H__
#include <string>
#include <boost/exception/all.hpp>

class NgxException final : public virtual std::exception,
	public virtual boost::exception
{
public:
	typedef boost::string_ref string_ref_type;
private:
	std::string m_msg;
};

#endif
