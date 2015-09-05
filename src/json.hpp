#ifndef JSON_HPP
#define JSON_HPP

#include "jsoncpp/json.h"
#include <sstream>
#include <string>

typedef Json::Value json_t;

inline std::string serialize(const json_t& json)
{
	Json::FastWriter writer;
	std::string stringified=writer.write(json);

	while(stringified.size()>0&&isspace(stringified[stringified.size()-1])!=0)
		stringified.pop_back();

	return stringified;
}

inline json_t deserialize(const std::string& stringified)
{
	std::istringstream istr(stringified);
	json_t json;
	istr>>json;
	return json;
}

#endif