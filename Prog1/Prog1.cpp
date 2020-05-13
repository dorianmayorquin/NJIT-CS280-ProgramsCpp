
//Lost SS1
#include <iostream>
#include <cctype>
#include <cstring>
#include <fstream>
#include <string>
#include <map>

using namespace std;

////////////////////////////////////////Side Functions////////////////////////////////////////////
string subconditioner(string arg) //Applies Rules to subs
{
	string sub;
	int i = 0;

	while(arg[i] != '\0') //Removes Punctuation
	{
		if(isalpha(arg[i]) || arg[i] == '\'' || arg[i] == '-')
		{	
			sub += arg[i];
			i++;
		}
		else
		{
			i++;
		}
	}

	i=0;
	while(sub[i]) //Makes Lowercase
	{
			sub[i] = tolower(sub[i]);
			i++;
	}
	return sub;
}
//string wordconditioner(string arg)
//{

//}



////////////////////////////////////////Main Functions////////////////////////////////////////////

map<int,string> wordmapcreator(string name)
{

ifstream wfile;
wfile.open(name);

map<int,string> words; //Maps a number to a word or a space

string word;
string space;

int i = 0;

char ch = wfile.get(); //Gets the first character

while(!wfile.eof())
{
	if(!isspace(ch))
	{
		while(!isspace(ch)) // Keeps adding characters to word variable
		{
			word = word + ch;
			ch = wfile.get();
		}
		words[i] = word; 	// Stores word to value i(number) in map and number
		word = "";			// Resets word variable
		i++;
	}
	if(isspace(ch)) 	//Stores spaces to next value i(number) in map
	{

			space = space + ch;
			ch = wfile.get();

		words[i] = space;
		space = "";
		i++;
	}

}

	return words;

}

//++++++++++++++++++++++++++++++++++++Main Program++++++++++++++++++++++++++++++++++++++++++++++++++++

int main(int argc, char *argv[])
{

////////////////////////////File Input Handling//////////////////////////////////////////////////
	if(argc != 3)
	{
		cout << "TWO FILENAMES REQUIRED" <<endl;
		return 1;
	}

	ifstream file1, file2;

	file1.open(argv[1]);
	file2.open(argv[2]);

	if(!file1.is_open())
	{
		cout << "BAD FILENAME " << argv[1] <<endl;
		return 2;
	}
	else if(!file2.is_open())
	{
		cout << "BAD FILENAME " << argv[2] <<endl;
		return 2;
	}

	string str;
	file1 >> str;

	if(file1.eof()) // If subs file is empty
	{
		map<int,string> words;
		words = wordmapcreator(argv[2]);

		map<int,string>::iterator res;

		for(res = words.begin(); res != words.end(); res++)
		cout << res->second;

		return 0;
	}

	file1.close();
	file2.close();

////////////////////////////////////File Processing//////////////////////////////////////////////

ifstream subfile;

subfile.open(argv[1]);

map<int,string> words;

words = wordmapcreator(argv[2]);



//////////////////////////////Subs File Map Creation////////////////////////////////////////

map<string,string> subs; //Maps first word to second word in subs file

string key;
string sub;

subfile >> key;
subfile >> sub;
char multiple;

multiple = subfile.get();

while(!subfile.eof())
{
	if(!isalpha(sub[0]) && multiple != '\n')
	{
		subfile >> sub;
		multiple = subfile.get();
	}

	if(isspace(multiple) && multiple != '\n')
	{

			while(multiple != '\n')
			{
				multiple = subfile.get();
			}

			subfile >> key;
			subfile >> sub;
			multiple = subfile.get();

	}
	else
	{
			subs[subconditioner(key)] = subconditioner(sub);
			subfile >> key;
			subfile >> sub;
			multiple = subfile.get();
	}
}

//////////////////////////////////////Word Replacer/Comparer/////////////////////////////////////////////


map<string,string>::iterator subit;// subs map iterator
map<int,string>::iterator worit;	// word map iterator
map<int,bool> changed;				//map for changes in word


int changes = 0; 	// # of changes

for( subit = subs.begin();subit != subs.end(); subit++ )
{
	for( worit = words.begin();worit != words.end(); worit++ )
	{
		string temp;
		temp = subconditioner(worit->second);

     	if(subit->first == temp)
     	{
    

     		if(changed.find(worit->first) == changed.end()) // If word hasn't been changed before
     		{

     			if(isupper(worit->second[0])) //If first letter is Uppercase
     			{
     				if(!isalpha(worit->second[worit->second.length()-1])) // If last character in word is punctuation preserve it
     				{
	     				char punct = worit->second[worit->second.length()-1]; // Store the punctuation in last char
	     				words[worit->first] = subs[subit->first]; //Make the replacement
	     				words[worit->first] += punct;
     				}
     				else
     				{
     					words[worit->first] = subs[subit->first]; //Make the replacement
     				}
     				words[worit->first][0] = toupper(words[worit->first][0]); //Make Letter Uppercase
     				changed[worit->first] = true;
	     			changes++;
     			}
     			else
     			{
     				if(!isalpha(worit->second[worit->second.length()-1])) // If last character in word is punctuation preserve it
     				{
     					int i=1;
     					string punct = "";
     					while(!isalpha(worit->second[worit->second.length()-i]))
     					{
     						punct += worit->second[worit->second.length()-i]; // Store the punctuation in last char
     						i++;
     					}
	     				
	     				words[worit->first] = subs[subit->first]; //Make the replacement
	     				words[worit->first] += punct;

	     				
     				}
     				else
     				{
     					words[worit->first] = subs[subit->first]; //Make the replacement
     				}
     				changed[worit->first] = true;
	     			changes++;
     			}

	     	}

     	}

	}
}

////////////////////////////////////Output/////////////////////////////////////////////
map<int,string>::iterator res;

for(res = words.begin(); res != words.end(); res++)
	cout <<res->second;

if(changes!=0)
{
	cout << "NUMBER OF CHANGES: "<<changes<<endl;
}





	return 0;
}