#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <map>
#include <string>
#include <vector>

#include "json.hpp"
#include "mongoose/mongoose.h"
#include "permissions.hpp"
#include "string.hpp"

class database_t
{
	public:
		permissions_t permissions;

		database_t(const permissions_t& permissions):permissions(permissions)
		{}

		std::string read(const std::string& comma_list)
		{
			auto list=comma_split(comma_list);

			std::string array="[";

			for(auto ii:list)
			{
				if(ii.size()>0)
				{
					array+="\""+ii+"\":\"";

					if(data_m.count(ii)>0)
						array+=data_m[ii];

					array+="\",";
				}
			}

			if(array.size()>0&&array[array.size()-1]==',')
				array=array.substr(0,array.size()-1);

			array+="]";

			return array;
		}

		bool write(const std::string& comma_list,const std::string& array)
		{
			try
			{
				auto list=comma_split(comma_list);
				auto json=deserialize(array);

				if(json.type()==Json::arrayValue&&list.size()==json.size())
				{
					for(size_t ii=0;ii<list.size();++ii)
						data_m[list[ii]]=json[(int)ii].asString();

					return true;
				}
			}
			catch(...)
			{}

			return false;
		}

	private:
		std::map<std::string,std::string> data_m;
};

inline database_t& get_database(mg_connection* connection)
{
	if(connection->server_param==nullptr)
		throw std::runtime_error("Invalid database object passed to server.");

	return *(database_t*)connection->server_param;
}

#endif