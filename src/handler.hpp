#ifndef HANDLER_HPP
#define HANDLER_HPP

#include <iostream>
#include <string>

#include "database.hpp"
#include "mongoose/mongoose.h"
#include "uri.hpp"

inline void mg_send(mg_connection* connection,const std::string& data,const std::string& mime)
{
	mg_printf(connection,"HTTP/1.1 200 OK\r\nContent-Type: %s\r\nContent-Length: %ld\r\n\r\n%s",
		mime.c_str(),data.size(),data.c_str());
}

inline bool handle_read(mg_connection* connection,const std::string& request,const std::string& query)
{
	std::string value=get_query(connection,"read");

	if(value.size()>0)
	{
		auto database=get_database(connection);
		std::cout<<"\tReading \""<<value<<"\"..."<<std::flush;

		if((database.permissions&P_READ)!=0)
		{
			mg_send(connection,database.read(value),"application/json");
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
	std::string value=get_query(connection,"write");

	if(value.size()>0)
	{
		auto database=get_database(connection);
		std::cout<<"\tWriting \""<<value<<"\"..."<<std::flush;

		if((database.permissions&P_WRITE)!=0)
		{
			//mg_send(connection,database.read(value),"application/json");
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
			std::cout<<" \""<<query<<"\"."<<std::endl;

		bool read=handle_read(connection,request,query);
		bool wrote=handle_write(connection,request,query);

		if(read|wrote)
			return MG_TRUE;
	}

	return MG_FALSE;
}

#endif
