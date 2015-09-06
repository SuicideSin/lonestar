#ifndef STRING_HPP
#define STRING_HPP

#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

typedef std::vector<std::string> list_t;

inline list_t comma_split(std::string list)
{
	list+=',';
	list_t values;
	std::string temp;

	for(auto ii:list)
	{
		if(ii==',')
		{
			values.push_back(temp);
			temp="";
		}
		else
		{
			temp+=ii;
		}
	}

	return values;
}

inline std::string to_hex_string(const std::string& str)
{
	std::ostringstream ostr;

	for(auto ii:str)
		ostr<<std::hex<<std::setw(2)<<std::setfill('0')<<((int)ii&0x000000ff);

	return ostr.str();
}

#endif
