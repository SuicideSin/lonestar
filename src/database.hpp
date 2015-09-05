#ifndef DATABASE_HPP
#define DATABASE_HPP

#include "permissions.hpp"

class database_t
{
	public:
		permissions_t permissions;

		database_t(const permissions_t& permissions):permissions(permissions)
		{}

	private:
};

inline database_t get_database(mg_connection* connection)
{
	if(connection->server_param==nullptr)
		throw std::runtime_error("Invalid database object passed to server.");

	return *(database_t*)connection->server_param;
}

#endif