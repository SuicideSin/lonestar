#ifndef VALIDATE_HPP
#define VALIDATE_HPP

#include <stdexcept>
#include <string>
#include <vector>

#include "permissions.hpp"

inline void validate_ip(const std::string& ip)
{
	std::vector<std::string> octets;
	octets.resize(4);
	size_t counter=0;

	std::string error_rest="ip \""+ip+"\" (should be X.X.X.X, where X is in range 0-255).";

	for(auto ii:ip)
		if(counter>3)
			throw std::runtime_error("Invalid "+error_rest);
		else if(ii=='.')
			++counter;
		else if(ii>='0'&&ii<='9')
			octets[counter]+=ii;
		else
			throw std::runtime_error("Invalid symbol in "+error_rest);

	for(auto ii:octets)
	{
		if(ii.size()>0)
		{
			int octet=std::stoi(ii);

			if(octet>=0&&octet<=255)
				continue;
		}

		throw std::runtime_error("Invalid "+error_rest);
	}
}

inline void validate_port(const std::string& port)
{
	int port_number=std::stoi(port);

	if(port_number<0||port_number>65535)
		throw std::runtime_error("Invalid port \""+port+"\" (should be in range 0-65535).");
}

inline void validate_permissions(const std::string& permissions)
{
	permissions_t permissions_number=std::stoi(permissions);

	if(permissions_number<0||permissions_number>7)
		throw std::runtime_error("Invalid permissions \""+permissions+"\" (bit field:  4=read, 2=write, and 1=exec).");
}

#endif
