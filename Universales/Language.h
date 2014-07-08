#pragma once
//hard coded. Futuramente poderia usar arquivo
#include <vector>
#include <string>
using namespace std;

class Language
{
public:
	Language();
	~Language();
	static vector<string> base;
	static void selectLang(string lang);
	static vector<string> names;
};

