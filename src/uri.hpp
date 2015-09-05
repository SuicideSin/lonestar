#ifndef URI_HPP
#define URI_HPP

#include <string>
#include <utility>

#include "mongoose/mongoose.h"

inline std::string get_query(const mg_connection* connection,const std::string& var)
{
	std::string temp;
	temp.resize(32767);
	int size=mg_get_var(connection,var.c_str(),(char*)temp.data(),temp.size());
	temp.resize(std::max(0,size));
	return temp;
}

#endif
