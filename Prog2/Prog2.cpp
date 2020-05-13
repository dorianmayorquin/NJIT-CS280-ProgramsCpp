//Currently on mix2, trying to read from standard in

#include <iostream>
#include <fstream>
#include <cstdio>
#include <map>
#include "tokens.h"
#include "Functions.h"

using namespace std;

int main(int argc, char* argv[])
{
//////////////////////////////////////Input Handling/////////////////////////////////////////////////
	ifstream file;
	string filename;
	static bool v,s,idf,stdin = false;
	int i = 1;

	while(argv[i])
	{
		string flag = argv[i];

		if(flag[0] == '-')
		{
			if(flag == "-v")
			{
				v = true;
			}
			else if(flag == "-strings")
			{
				s = true;
			}
			else if(flag == "-ids")
			{
				idf = true;
			}
			else
			{
				cout << "UNRECOGNIZED FLAG " << flag <<endl;
				return 0;
			}

			i++;
		}
			else if(argv[i+1] || argc > 5)
		{
			cout << "ONLY ONE FILE NAME ALLOWED" <<endl;
			return 0;
		}
		else
		{
			break;
		}

	}


	filename = argv[argc-1]; //Last Argument, Presumed Filename
	
	if(filename[0] != '-')
	{
		file.open(filename);

		if(!file.is_open())
		{
			cout << "CANNOT OPEN " << filename <<endl;
			return 0;
		}
	}
	else
	{
		stdin = true;
	}


//////////////////////////////////////////////////////////////////////////////////////////////////

	int lines = 0;
	int tokens = 0;
	int idnum = 0;
	int strcount = 0;
	Token tok;
	map<string,int> str;
	map<string,int> ids;


	file.peek(); // If File is empty the loop doesn't execute

		while(tok.GetTokenType() != DONE)	// Create Map of Tokens for easier alphabetic sorting w -string -ids
		{	
			if(stdin || argc == 1)
			{
				tok = getNextToken(cin,lines);
			}
			else
			{
				tok = getNextToken(file,lines);
			}
			if(tok.GetTokenType() == ERR)
			{
				cout<<tok<<endl;
				return 0;
			}
			else if(tok.GetTokenType() != DONE)
			{
				if(v)
					{cout << tok <<endl;}
				tokens++;
				if(tok.GetTokenType() == SCONST)
				{
					str[tok.GetLexeme()];
					strcount++;
				}
				if(tok.GetTokenType() == ID)
				{
					if(ids.find(tok.GetLexeme()) == ids.end())
					{
						ids[tok.GetLexeme()];
						idnum++;
					}
					
				}
			}

		}

		if(s && strcount > 0)
		{
			map<string,int>::iterator it;
			cout<<"STRINGS:"<<endl;
			for( it = str.begin();it != str.end(); it++ )
	     	cout << it->first << endl;
	 	}

	 	
	 	if(idf && idnum > 0)
	 	{
	 		map<string,int>::iterator idit;
	 		cout<<"IDENTIFIERS: ";
			for( idit = ids.begin();idit != ids.end(); idit++ )
			{
	     	 	cout << idit->first;
	     	 	idnum--;
	     	 	if(idnum != 0)
	     	 	{
	     	 		cout <<", ";
	     	 	}
	     	 }

	     		cout << endl;
	 	}





	cout << "Total lines: " << lines <<endl;
	if(tokens >= 1)
	cout << "Total tokens: " << tokens <<endl;
	file.close();


	return 0;
}