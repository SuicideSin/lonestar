#ifndef CLI_HPP
#define CLI_HPP

#include <stdexcept>
#include <string>
#include <map>

typedef std::map<std::string,std::string> cli_t;

inline cli_t parse_cli(int argc,char* argv[])
{
	cli_t pairs;

	for(int ii=1;ii<argc;++ii)
	{
		std::string key=argv[ii];

		if(key.size()>1&&key[0]=='-'&&key[1]=='-')
		{
			key=key.substr(2,key.size()-2);
			std::string value="true";

			if(ii+1<argc)
			{
				std::string temp=argv[ii+1];

				if(!(temp.size()>1&&temp[0]=='-'&&temp[1]=='-'))
				{
					value=temp;
					++ii;
				}
			}

			pairs[key]=value;
		}
		else
		{
			throw std::runtime_error("Unrecognized cli argument \""+std::string(argv[ii])+"\".\n");
		}
	}

	return pairs;
}
#endif
