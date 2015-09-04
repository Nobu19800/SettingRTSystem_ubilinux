#ifndef COMPSEARCH_H
#define COMPSEARCH_H

#include <stdio.h>


#include <iostream>
#include <rtm/CorbaNaming.h>
#include <rtm/RTObject.h>
#include <rtm/CorbaConsumer.h>
#include <assert.h>
#include <string>
#include <vector>

/*
*バイナリファイルに文字保存する関数
*/
void WriteString(std::string a, std::ofstream &ofs);
/*
*バイナリファイルより文字読み込みする関数
*/
std::string ReadString(std::ifstream &ifs);


class PathList
{
public:
	PathList(std::string path);
	std::string fname;
	std::string name;
	std::string cxt;
	std::string dname;
};



#endif