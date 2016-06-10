#include "stdafx.h"
#include "Application.h"

using namespace std;

Application::Application(string file)
{
}


Application::~Application()
{
}

void Application::setupData(string file)
{
	string line;
	ifstream streetFile(file);
	if (streetFile.is_open())
	{
		while (getline(streetFile, line))
		{
			cout << line << '\n';
		}
		streetFile.close();
	}
	else {
		cout << "file not open";
	}
}
