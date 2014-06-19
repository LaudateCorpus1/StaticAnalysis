/* plugin:   (StaticAnalysis) for x64dbg <http://www.x64dbg.com>
 * author:   tr4ceflow@gmail.com <http://blog.traceflow.com>
 * license:  GLPv3
 */
#include "ApiDB.h"
#include "pluginsdk/bridgemain.h"
#include "pluginmain.h"
#include <fstream>
#include <sstream>
#include <vector>

// http://stackoverflow.com/a/22923239/1392416
std::vector<std::string> split(const std::string& string, const char* del) {
	size_t first = 0, second = 0; 
	size_t end = string.size();
	size_t len = strlen(del);
	std::vector<std::string> tokens;
	while ((second = string.find(del,first)) != (std::string::npos)) {
		size_t dif = second - first;
		if (dif) {
			tokens.push_back(string.substr(first,dif));
		}
		first = second + len;
	}
	if (first != end) {
		tokens.push_back(string.substr(first));
	}
	return tokens;
}

ApiDB::ApiDB(void)
{
	unsigned int i=0;
	mValid = true;

	std::ifstream helpFile;
	std::string rawLine;
	helpFile.open("api.dat");
	if(!helpFile){
		_plugin_logputs("[StaticAnalysis] api help file not found ...");
	}else{
		_plugin_logputs("[StaticAnalysis] load api help file  ...");
		while(!helpFile.eof())
		{
			helpFile >> rawLine;
			std::vector<std::string> tokens = split(rawLine,";");
			
			if(tokens.size() >3){
				APIFunction f;
				f.DLLName = tokens.at(0);
				f.ReturnType = tokens.at(1);
				f.Name = tokens.at(2);

				for (int j = 3;j<tokens.size()-1;j+=2)
				{
					APIArgument a;
					a.Type = tokens.at(j);
					a.Name = tokens.at(j+1);
					f.Arguments.push_back(a);
				}


				mInfo.push_back(f);

				i++;
			}
			

			
		}


	}
	
	_plugin_logprintf("[StaticAnalysis] loaded %i functions signatures from helpfile\n",i);
	helpFile.close();
}





ApiDB::~ApiDB(void)
{
}

APIFunction ApiDB::find( std::string name )
{
	APIFunction f;
	f.invalid = true;
	

	std::list<APIFunction>::iterator it = mInfo.begin();

	while(it!=mInfo.end()){
		if(it->Name == name){
			f = *it;
			f.invalid = false;
			break;
		}
		
		it++;
	}



	return f;
}

const bool ApiDB::ok() const
{
	return mValid;
}
