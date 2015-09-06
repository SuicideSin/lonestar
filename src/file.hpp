#ifndef FILE_HPP
#define FILE_HPP

#include <fstream>
#include <stdexcept>
#include <string>

std::string read_file(const std::string& filename)
{
	std::string file;
	char buffer;
	std::ifstream istr(filename.c_str(),std::ios_base::in|std::ios_base::binary);
	istr.unsetf(std::ios_base::skipws);

	if(!istr)
		throw std::runtime_error("Could not open file \""+filename+"\".");

	file="";

	while(istr>>buffer)
		file+=buffer;

	istr.close();
	return file;
}

#endif