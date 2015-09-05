#ifndef HANDLER_HPP
#define HANDLER_HPP

#include <iostream>
#include <string>

#include "mongoose/mongoose.h"
#include "permissions.hpp"
#include "uri.hpp"

inline bool handle_read(mg_connection* connection,const std::string& request,const std::string& query)
{
	std::string read=get_query(connection,"read");

	if(read.size()>0)
	{
		std::cout<<"\tReading \""<<read<<"\"..."<<std::flush;

		if((get_permissions(connection)&P_READ)!=0)
		{
			std::cout<<"done."<<std::endl;
			return true;
		}
		else
		{
			std::cout<<"denied."<<std::endl;
		}
	}

	return false;
}

inline bool handle_write(mg_connection* connection,const std::string& request,const std::string& query)
{
	std::string write=get_query(connection,"write");

	if(write.size()>0)
	{
		std::cout<<"\tWriting \""<<write<<"\"..."<<std::flush;

		if((get_permissions(connection)&P_WRITE)!=0)
		{
			std::cout<<"done."<<std::endl;
			return true;
		}
		else
		{
			std::cout<<"denied."<<std::endl;
		}
	}

	return false;
}

inline int client_handler(mg_connection* connection,mg_event event)
{
	if(event==MG_AUTH)
		return MG_TRUE;

	if(event==MG_REQUEST)
	{
		std::string client(connection->remote_ip);
		for(int ii=0;ii<connection->num_headers&&client=="127.0.0.1";++ii)
			if(std::string(connection->http_headers[ii].name)=="X-Forwarded-For")
				client=connection->http_headers[ii].value;

		std::string request(connection->uri);

		std::string query;
		if(connection->query_string!=nullptr)
			query=connection->query_string;

		std::cout<<client;
		if(client==std::string(connection->remote_ip))
			std::cout<<" false";
		else
			std::cout<<" true";
		std::cout<<" GET "<<request;
		if(query.size()>0)
			std::cout<<" "<<query;
		std::cout<<std::endl;

		bool read=handle_read(connection,request,query);
		bool wrote=handle_write(connection,request,query);

		if(read|wrote)
			return MG_TRUE;
	}

	return MG_FALSE;
}

#endif
