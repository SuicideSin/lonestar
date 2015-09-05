#include <iostream>
#include <stdexcept>
#include <string>

#include "cli.hpp"
#include "handler.hpp"
#include "mongoose/mongoose.h"
#include "permissions.hpp"
#include "validate.hpp"

int main(int argc,char* argv[])
{
	try
	{
		auto cli=parse_cli(argc,argv);
		std::string ip="0.0.0.0";
		std::string port="8080";
		std::string permissions_string="4";

		if(cli.count("ip")>0)
			ip=cli["ip"];
		if(cli.count("port")>0)
			port=cli["port"];
		if(cli.count("permissions")>0)
			permissions_string=cli["permissions"];

		validate_ip(ip);
		validate_port(port);
		validate_permissions(permissions_string);

		permissions_t permissions=(permissions_t)std::stoi(permissions_string);

		mg_server* server=mg_create_server(&permissions,client_handler);

		if(server==nullptr)
		{
			std::cout<<"Server failed to start (Out of ram? Out of disk space?)."<<std::endl;
			return 0;
		}

		std::string address=ip+":"+port;

		if(mg_set_option(server,"listening_port",address.c_str())!=0)
		{
			std::cout<<"Failed to open port "<<mg_get_option(server,"listening_port")<<
				" (Is something running on this port? Do you have permissions?)."<<std::endl;
			return 0;
		}

		mg_set_option(server,"document_root","web");

		std::cout<<"Server started on "<<mg_get_option(server,"listening_port")<<" with ";
		if((permissions&P_READ)<=0&&(permissions&P_WRITE)<=0)
			std::cout<<"no";
		if((permissions&P_READ)>0)
			std::cout<<"read";
		if((permissions&P_READ)>0&&(permissions&P_WRITE)>0)
			std::cout<<"/";
		if((permissions&P_WRITE)>0)
			std::cout<<"write";
		std::cout<<" permissions."<<std::endl;

		while(mg_poll_server(server,1000))
		{}

		mg_destroy_server(&server);
	}
	catch(std::exception& exception)
	{
		std::cout<<exception.what()<<std::endl;
		return 1;
	}

	return 0;
}
