#ifndef HANDLER_HPP
#define HANDLER_HPP

#include <iostream>
#include <string>

#include "database.hpp"
#include "hash.hpp"
#include "mongoose/mongoose.h"
#include "uri.hpp"

inline void mg_send(mg_connection* connection,const std::string& data,const std::string& mime)
{
	mg_printf(connection,"HTTP/1.1 200 OK\r\nContent-Type: %s\r\nContent-Length: %ld\r\n\r\n%s",
		mime.c_str(),data.size(),data.c_str());
}

inline void mg_send_status(mg_connection* connection,const std::string& status)
{
	mg_printf(connection,"HTTP/1.1 %s\r\nContent-Length: 0\r\n\r\n\r\n\r\n",status.c_str());
}

inline bool handle_read(mg_connection* connection,const bool authenticated,const std::string& request,
	const std::string& query)
{
	std::string comma_list=get_query(connection,"read");

	if(comma_list.size()>0)
	{
		auto& database=get_database(connection);
		std::cout<<"\tReading \""<<comma_list<<"\"..."<<std::flush;

		if((database.permissions&P_READ)!=0||(authenticated&&database.allow_authentication()))
		{
			mg_send(connection,database.read(comma_list),"application/json");
			std::cout<<"done."<<std::endl;
		}
		else
		{
			mg_send_status(connection,"401 UNAUTHORIZED");
			std::cout<<"denied."<<std::endl;
		}

		return true;
	}

	return false;
}

inline bool handle_write(mg_connection* connection,const bool authenticated,const std::string& request,
	const std::string& query,const std::string& post_data)
{
	std::string comma_list=get_query(connection,"write");

	if(comma_list.size()>0)
	{
		auto& database=get_database(connection);
		std::cout<<"\tWriting \""<<comma_list<<"\"..."<<std::flush;

		if((database.permissions&P_WRITE)!=0||(authenticated&&database.allow_authentication()))
		{
			if(!database.write(comma_list,post_data))
			{
				mg_send_status(connection,"400 BAD REQUEST");
				std::cout<<"malformed."<<std::endl;
			}
			else
			{
				std::cout<<"done."<<std::endl;
			}
		}
		else
		{
			mg_send_status(connection,"401 UNAUTHORIZED");
			std::cout<<"denied."<<std::endl;
		}

		return true;
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

		std::string method=(connection->request_method);
		std::string request(connection->uri);
		std::string post_data;

		if(method=="POST")
			post_data=std::string(connection->content,connection->content_len);

		std::string query;
		if(connection->query_string!=nullptr)
			query=connection->query_string;

		auto& database=get_database(connection);
		bool authenticated=false;
		std::string auth=get_query(connection,"auth");
		if(auth.size()>0)
		{
				std::string query_no_auth=replace_all(query,"&auth="+auth,"");
				query_no_auth=replace_all(query_no_auth,"auth="+auth,"");
				authenticated=database.authenticate(query_no_auth+post_data,auth);
		}

		std::cout<<client;
		if(client==std::string(connection->remote_ip))
			std::cout<<" NOLOOKUP";
		else
			std::cout<<" LOOKUP  ";
		if(!authenticated)
			std::cout<<" NOAUTH";
		else
			std::cout<<" AUTH  ";
		std::cout<<" "<<method<<" "<<request<<"."<<std::endl;
		std::cout<<"\tQuery:  \""<<query<<"\""<<std::endl;

		bool wrote=false;

		if(method=="POST")
		{
			std::cout<<"\tPost:  \""<<post_data<<"\""<<std::endl;
			wrote=handle_write(connection,authenticated,request,query,post_data);
		}

		bool read=handle_read(connection,authenticated,request,query);

		if(wrote||read)
			return MG_TRUE;
	}

	return MG_FALSE;
}

#endif
