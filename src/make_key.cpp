#include <iostream>
#include <string>

#include "hash.hpp"
#include "string.hpp"

#ifdef WIN32
	#include <windows.h>
#else
	#include <termios.h>
	#include <unistd.h>
#endif

void set_echo(const bool enable)
{
	#ifdef WIN32
		HANDLE hstdin=GetStdHandle(STD_INPUT_HANDLE);
		DWORD mode;
		GetConsoleMode(hstdin,&mode);

		if(enable)
			mode|=ENABLE_ECHO_INPUT;
		else
			mode&=~ENABLE_ECHO_INPUT;

		SetConsoleMode(hstdin,mode);
	#else
		termios tty;
		tcgetattr(STDIN_FILENO,&tty);

		if(enable)
			tty.c_lflag|=ECHO;
		else
			tty.c_lflag&=~ECHO;

		tcsetattr(STDIN_FILENO,TCSANOW,&tty);
	#endif
}

int main(int argc,char* argv[])
{
	std::cerr<<"Enter key:  "<<std::flush;

	std::string key;

	set_echo(false);
	std::getline(std::cin,key);
	set_echo(true);
	std::cerr<<std::endl;

	std::cout<<to_hex_string(hash_sha3_512(key))<<std::flush;

	return 0;
}
