#ifndef PERMISSIONS_HPP
#define PERMISSIONS_HPP

#include "mongoose/mongoose.h"

typedef int permissions_t;

#define P_NONE 0
#define P_WRITE 2
#define P_READ 4

//Octal Permissions(Bits are RWX)
inline permissions_t get_permissions(mg_connection* connection)
{
	if(connection->server_param!=nullptr)
		return *(permissions_t*)connection->server_param;

	return P_NONE;
}

#endif
