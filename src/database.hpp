#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <map>
#include <string>
#include <vector>

#include "hash.hpp"
#include "json.hpp"
#include "mongoose/mongoose.h"
#include "permissions.hpp"
#include "string.hpp"

class database_t
{
	public:
		permissions_t permissions;

		database_t(const std::string& key,const permissions_t& permissions):
			permissions(permissions),key_m(key),nonce_m(0)
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
					{
						std::string value=json[(int)ii].asString();

						if(value=="")
							data_m.erase(list[ii]);
						else
							data_m[list[ii]]=value;
					}

					return true;
				}
			}
			catch(...)
			{}

			return false;
		}

		bool authenticate(const std::string& plain,const std::string& challenge)
		{
			bool authenticated=(to_hex_string(hmac_sha3_512(key_m,plain+std::to_string(nonce_m)))==challenge);

			if(authenticated)
				++nonce_m;

			return authenticated;
		}

		bool allow_authentication() const
		{
			return key_m.size()>0;
		}

		uint32_t get_nonce() const
		{
			return nonce_m;
		}

	private:
		std::map<std::string,std::string> data_m;
		const std::string key_m;
		uint32_t nonce_m;
};

inline database_t& get_database(mg_connection* connection)
{
	if(connection->server_param==nullptr)
		throw std::runtime_error("Invalid database object passed to server.");

	return *(database_t*)connection->server_param;
}

#endif
