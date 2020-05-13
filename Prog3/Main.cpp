#include <iostream>
#include <fstream>
#include "tokens.h"
#include "parse.h"
#include "tree.h"

using namespace std;

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

	ParseTree *tree = Prog(*input,line);


	if(tree != 0)
	{
		cout << "NODE COUNT: "<< tree->NodeCount() <<endl;
		cout << "INTERIOR COUNT: "<< tree->NodeCount() - leaves() <<endl;
		if(ops() > 0)
			cout << "OPS COUNT: "<< ops()<<endl;
		if(strgs() > 0)
			cout << "STRING COUNT: "<< strgs()<<endl;
		cout << "MAX DEPTH: "<< depth(tree)<<endl;
	}



	return 0;	
}









