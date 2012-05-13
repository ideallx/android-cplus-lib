#include <string>
#include <iostream>
#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>
#include <stdio.h>

using namespace std;
using namespace boost::program_options;
using namespace boost::filesystem;

typedef recursive_directory_iterator rd_iterator;

void PrintFiles(string strPath, string strName, string strAppend);

int main(int argc, char** argv)
{
	options_description opts("print files.");
	opts.add_options()
	("help,h", "show this msg")
	("path,p", value<string>(), "search path")
	("name,n", value<string>(), "extend file name")
	("append,a", value<string>(), "append string")
	;

	variables_map vm;
	store(parse_command_line(argc, argv, opts), vm);

	if(vm.count("help")){
		cout<<opts<<endl;
		return 0;
	}
	
	if(vm.count("name") && vm.count("append") && vm.count("path")){
		string strPath = vm["path"].as<string>();
		string strName = vm["name"].as<string>();	
		string strAppend = vm["append"].as<string>();
		
		PrintFiles(strPath, strName, strAppend);
	}else{
		cout<<opts<<endl;
		return 0;
	}

	return 0;	
}

void PrintFiles(string strPath, string strName, string strAppend)
{
	if(!is_directory(strPath)){
		cout<<"Error! Path: "<<strPath<<"is not a path!"<<endl;
		return;
	}
	rd_iterator end;		
	for(rd_iterator pos(strPath); pos!=end; ++pos){
		if(pos.level() == 0 && is_regular_file(*pos)){
			string strExt = pos->path().extension().c_str();
			if(strExt == strName){
				printf("%s %s\n", pos->path().filename().c_str(), strAppend.c_str());
			}
			//printf("%s level:%d extension: %s\n", pos->path().filename().c_str(), pos.level(), pos->path().extension().c_str());
		}	
	}
}
