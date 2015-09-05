#ifndef STRING_HPP
#define STRING_HPP

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

#endif
