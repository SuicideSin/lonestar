#ifndef CLI_HPP
#define CLI_HPP

#include <stdexcept>
#include <string>
#include <map>

class cli_t
{
	public:
		cli_t(int argc,char* argv[])
		{
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

					pairs_m[key]=value;
				}
				else
				{
					throw std::runtime_error("Unrecognized cli argument \""+std::string(argv[ii])+"\".");
				}
			}
		}

		void throw_unknown() const
		{
			for(auto key:pairs_m)
				throw std::runtime_error("Unrecognized cli argument \""+key.first+"\".");
		}

		size_t count(const std::string& key) const
		{
			return pairs_m.count(key);
		}

		void move(const std::string& key,std::string& destination)
		{
			if(pairs_m.count(key)>0)
			{
				destination=pairs_m[key];
				pairs_m.erase(key);
			}
		}

	private:
		std::map<std::string,std::string> pairs_m;
};

#endif
