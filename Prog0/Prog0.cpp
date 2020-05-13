#include <iostream>
#include <cctype>
#include <cstring>


using namespace std;

////////////////////////////////////////////////////////////Functions////////////////////////////////////////////////////////////
string reverse(string arg)
{
	int len = arg.length() - 1; //String Length
	string value = "";

	while(len >= 0)
	{
		value = value + arg[len];
		len--;
	}

	return value;
}

string upper(string arg)
{
	int i = 0;

	while(arg[i])
	{
		arg[i] = toupper(arg[i]);
		i++;
	}


	return arg;

}

string noVowel(string arg)
{
	int i = 0;
	string newstr = "";

	while(arg[i])
	{
		if(arg[i] != 'a' && arg[i] != 'e' && arg[i] != 'i' && arg[i] != 'o' && arg[i] != 'u'
			&& arg[i] != 'A'&& arg[i] != 'E'&& arg[i] != 'I'&& arg[i] != 'O'&& arg[i] != 'U')
			newstr = newstr + arg[i];
		i++;
	}

	return newstr;
}



///////////////////////////////////////////// Main Program ///////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{
	int i = 1;
	string val = "";
	int length = 0;
	bool Reon = false; //Reverse on/off Toggle
	bool Upon = false; //Upper on/off Toggle
	bool Voon = false; //noVowel on/off 


	while(argv[i]) //This Processes All Arguments
	{
		val = argv[i];
		length = strlen(argv[i]);
		
		if(length%2 == 0) // Toggle Reverse
		{
			Reon = !Reon; //Toggle
		}
		if(length%3 == 0) // Toggle Upper
		{
			Upon = !Upon;
		}
		if(length%5 == 0) // Toggle NoVowel
		{
			Voon = !Voon;
		}

			if(Reon) //Apply Reverse  if true
			{
				val = reverse(argv[i]);

			}
				if(Upon) //Apply Upper  if true
			{
				val = upper(val);

			}
			if(Voon) //Apply Upper  if true
			{
				val = noVowel(val);
			}

			cout << val << endl;
			i++;



	}
	

	return 0;

}

