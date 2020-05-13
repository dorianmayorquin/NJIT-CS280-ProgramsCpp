#include <iostream>
#include <fstream>
#include "tokens.h"
#include "parse.h"
#include "tree.h"

using namespace std;

void Use(ParseTree *tree)
{
}

int main(int argc, char* argv[])
{
	int line = 0;

	if(argc > 2)
	{
		cout << "TOO MANY FILENAMES"<<endl;
		return 0;
	}

	ifstream file;
	istream *input;
	file.open(argv[argc-1]);

	if(!file.is_open())
	{
		cout << "COULD NOT OPEN "<<argv[argc-1]<<endl;
		return 0;
	}

	if(argc == 1)
	{
		input = &cin;
	}
	else
	{
		input = &file;
	}

	try
	{
		ParseTree *tree = Prog(*input,line);
		if(errcount() == 0)
			tree->Eval();
		Use(tree);
	}
	catch(std::logic_error& e)
	{
		cout<<e.what()<<endl;
	}
	catch(std::runtime_error& e)
	{
		cout << "RUNTIME ERROR Symbol "<<e.what()<< " not defined"<<endl;
	}







	return 0;	
}









