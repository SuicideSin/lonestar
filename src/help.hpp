#ifndef HELP_HPP
#define HELP_HPP

#include <iostream>

inline void print_help()
{
	std::cout<<"NAME"<<std::endl;
	std::cout<<"        lonestar - A cross platform, simple, read/write driven, web server with adjustable permissions. Heavily influenced by superstar. This is still in development."<<std::endl;
	std::cout<<std::endl;
	std::cout<<"SYNOPSIS"<<std::endl;
	std::cout<<"        lonestar [OPTION]..."<<std::endl;
	std::cout<<std::endl;
	std::cout<<"DESCRIPTION"<<std::endl;
	std::cout<<"        --ip host_address"<<std::endl;
	std::cout<<"                Use host_address on the local machine as the host address of the connection."<<std::endl;
	std::cout<<"                Only useful on systems with more than one address."<<std::endl;
	std::cout<<"                Default is:  0.0.0.0"<<std::endl;
	std::cout<<std::endl;
	std::cout<<"        --port host_port"<<std::endl;
	std::cout<<"                Specifies the hosting port lonestar should use, subject to privilege restrictions and availability."<<std::endl;
	std::cout<<"                Default is: 8080"<<std::endl;
	std::cout<<std::endl;
	std::cout<<"        --permissions permissions"<<std::endl;
	std::cout<<"                Sets access permissions to the lonestar database. Bit field (read=4, write=2, and exec=1)."<<std::endl;
	std::cout<<"                Default is: 4"<<std::endl;
	std::cout<<std::endl;
	std::cout<<"        --web_root root"<<std::endl;
	std::cout<<"                Access web_root as \"/\" for web documents."<<std::endl;
	std::cout<<"                Default is: web"<<std::endl;
	std::cout<<std::endl;
	std::cout<<"        --help"<<std::endl;
	std::cout<<"                Show this menu."<<std::endl;
	std::cout<<std::endl;
	std::cout<<"RUNNING"<<std::endl;
	std::cout<<"        Run lonestar on localhost:8081 with web root in folder \"root\" with read/write permissions:"<<std::endl;
	std::cout<<"                ./lonestar --ip 127.0.0.1 --port 8081 --web_root root --permissions 6"<<std::endl;
	std::cout<<std::endl;
	std::cout<<"        Run lonestar on any IP on port 8080 with web root in folder \"web\" with read only permissions"<<std::endl;
	std::cout<<"        Note, this is the default option, so the two commands below are equivalent:"<<std::endl;
	std::cout<<"                ./lonestar --ip 0.0.0.0 --port 8080 --web_root web --permissions 4"<<std::endl;
	std::cout<<"                ./lonestar"<<std::endl;
	std::cout<<std::endl;
	std::cout<<"WRITING"<<std::endl;
	std::cout<<"        To write, pass a query string of \"write\" with a comma separated list of values."<<std::endl;
	std::cout<<"        Pass the values of the comma separated values in the post data as a JSON array."<<std::endl;
	std::cout<<"        Regardless of the type of objects in the array in the post data, they will be interpreted as strings."<<std::endl;
	std::cout<<"        Note, writing can only be done with POST data."<<std::endl;
	std::cout<<"        If there are no write permissions, a 401 UNAUTHORIZED error code will be returned."<<std::endl;
	std::cout<<"        If the post data is malformed, a 400 BAD REQUEST error code will be returned."<<std::endl;
	std::cout<<std::endl;
	std::cout<<"        Example:"<<std::endl;
	std::cout<<"                Request URI:  'http://127.0.0.1:8080/?write=a,b'"<<std::endl;
	std::cout<<"                Post String:  '[\"123\",\"456\"]'"<<std::endl;
	std::cout<<std::endl;
	std::cout<<"READING"<<std::endl;
	std::cout<<"        To read, pass a query string of \"read\" with a comma separated list of values."<<std::endl;
	std::cout<<"        You will then be returned a JSON array of strings."<<std::endl;
	std::cout<<"        If a value in the comma separated list does not exist, a value of "" will be returned."<<std::endl;
	std::cout<<"        If there are no read permissions, a 401 UNAUTHORIZED error code will be returned."<<std::endl;
	std::cout<<std::endl;
	std::cout<<"        Example (assuming the write example above has happened):"<<std::endl;
	std::cout<<"                Request URI:  'http://127.0.0.1:8080/?read=a,b'"<<std::endl;
	std::cout<<"                Post String:  '[\"a\":\"123\",\"b\":\"456\"]'"<<std::endl;
	std::cout<<std::endl;
	std::cout<<"        Example (assuming the write example above has not happend):"<<std::endl;
	std::cout<<"                Request URI:  'http://127.0.0.1:8080/?read=a,b'"<<std::endl;
	std::cout<<"                Post String:  '[\"a\":\"\",\"b\":\"\"]'"<<std::endl;
	std::cout<<std::endl;
	std::cout<<"BUILDING"<<std::endl;
	std::cout<<"        make"<<std::endl;
	std::cout<<"        ./lonestar"<<std::endl;
	std::cout<<std::endl;
	std::cout<<"DEPENDENCIES"<<std::endl;
	std::cout<<"        None (well...if you want to use the makefile...then a makefile runner...)."<<std::endl;
	std::cout<<std::endl;
	std::cout<<"LINKS"<<std::endl;
	std::cout<<"        Based on Superstar:        http://robotmoose.com/"<<std::endl;
	std::cout<<"        Uses Mongoose (included):  https://github.com/cesanta/mongoose"<<std::endl;
	std::cout<<"        Uses JSONCPP (included):   https://github.com/open-source-parsers/jsoncpp"<<std::endl;
}

#endif