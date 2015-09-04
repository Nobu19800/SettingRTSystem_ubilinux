#include <coil/File.h>

#include "CompSearch.h"


using namespace RTC;
using namespace std;




void WriteString(string a, ofstream &ofs)
{
	int s = a.size()+1;
	ofs.write( (char*)&s, sizeof(s) );
	ofs.write( a.c_str(), s );
}

string ReadString(ifstream &ifs)
{
	string a;
	int s;
	ifs.read( (char*)&s, sizeof(s) );

	char *st = new char[s];
	ifs.read( st, s );

	a = st;

	delete st;

	return a;
}


PathList::PathList(std::string path)
{
	fname = coil::basename(path.c_str());
	std::vector<std::string> sl = coil::split(fname,".");
	name = sl[0];
	
	if(sl.size() > 1)
	{
		cxt = sl[1];
	}
	else
	{
		cxt = "";
	}
	
	char* repath = const_cast<char*>(path.c_str());
	dname = coil::dirname(repath);
}