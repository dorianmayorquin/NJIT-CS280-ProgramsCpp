#include "tokens.h"

Token getNextToken(istream &in, int& linenumber)
{
	char ch;
	string escape = "";
	string lexeme = "";

	while(in.peek())
	{
		if(in.eof())
				{
					Token tk(DONE,lexeme,linenumber);
					return tk;
				}

		ch = in.peek();

		if(ch == '\n')
		{
			ch = in.get();
			lexeme = ch;
			linenumber++;
			Token nl(NL,lexeme,linenumber);
			return nl;
		}
		else if (isspace(ch))
		{
			while(isspace(in.peek()) && in.peek() != '\n')
			{
				ch = in.get();
			}
			continue;
		}
		else if(ch == '\"')
		{
			ch = in.get();
			while(in.peek())
			{	
				if(in.peek() != '\"' && in.peek() != '\\')
				{		
					ch = in.get();			
					lexeme += ch;


					if(ch == '\n')
					{
						lexeme = "\"" + lexeme;
						linenumber++;
						Token tk(ERR,lexeme,linenumber);
						return tk;
					}
				}
				else if(in.peek() == '\\')
					{
						escape = in.get();
						if(in.peek() == 'n')
						{
							lexeme += '\n';
							in.get();
							continue;
						}
						lexeme += in.get();
						continue;

					}
				else if(in.peek() == '\"')
				{
					in.get();
					break;
				}
			}
			
			Token tk(SCONST,lexeme,linenumber);
			return tk;
		}


		else if(isalpha(ch))
		{
					while(in.peek())
					{
						if(isalpha(in.peek()) || isdigit(in.peek()))
						{
							ch = in.get();
							lexeme += ch;
						}
						else
				 			break;
					}
					if(lexeme == "if")
					{
						Token tk(IF,lexeme,linenumber);		
						return tk;
					}
					if(lexeme == "print")
					{
						Token tk(PRINT,lexeme,linenumber);		
						return tk;
					}
					if(lexeme == "set")
					{
						Token tk(SET,lexeme,linenumber);		
						return tk;
					}
					if(lexeme == "loop")
					{
						Token tk(LOOP,lexeme,linenumber);		
						return tk;
					}
					if(lexeme == "begin")
					{
						Token tk(BEGIN,lexeme,linenumber);		
						return tk;
					}
					if(lexeme == "end")
					{
						Token tk(END,lexeme,linenumber);		
						return tk;
					}
				Token tk(ID,lexeme,linenumber);
				return tk;

		}
		else if(ch == '#')
		{
			while(in.peek() != '\n')
			{
				ch = in.get();
			}
			continue;
		}
		else if(ch == '+')
				{
					ch = in.get();
					lexeme = ch;
					Token tk(PLUS,lexeme,linenumber);
					return tk;
				}
		else if(ch == '-')
				{
					ch = in.get();
					lexeme = ch;
					Token tk(MINUS,lexeme,linenumber);
					return tk;
				}
		else if(ch == '*')
				{
					ch = in.get();
					lexeme = ch;
					Token tk(STAR,lexeme,linenumber);
					return tk;
				}
		else if(ch == '/')
				{
					ch = in.get();
					lexeme = ch;
					Token tk(SLASH,lexeme,linenumber);
					return tk;
				}
		else if(ch == '(')
				{
					ch = in.get();
					lexeme = ch;
					Token tk(LPAREN,lexeme,linenumber);
					return tk;
				}
		else if(ch == ')')
				{
					ch = in.get();
					lexeme = ch;
					Token tk(RPAREN,lexeme,linenumber);
					return tk;
 				}
 		else if(ch == ';')
				{
					ch = in.get();
					lexeme = ch;
					Token tk(SC,lexeme,linenumber);
					return tk;
				}		

				
		else if(isdigit(ch))
				{
					while(in.peek())
					{
						if(isdigit(in.peek()))
						{
							ch = in.get();
							lexeme += ch;
						}
						else if(isalpha(in.peek()))
						{
							lexeme += in.get();
							linenumber++;
							Token tk(ERR,lexeme,linenumber);
							return tk;	
						}
						else
				 			break;
					}
					Token tk(ICONST,lexeme,linenumber);
					return tk;
				}
		else
		{
			lexeme = ch;
			linenumber++;
			Token tk(ERR,lexeme,linenumber);
			return tk;
		}


	}

	Token tk(DONE,lexeme,linenumber);
	return tk;

}

ostream& operator<<(ostream& out, Token& tok)
{
	if(tok.GetTokenType() == PRINT)
	{
		out << "PRINT ";
	}
	else if(tok.GetTokenType() == SET)
	{
		out << "SET";
	}
	else if(tok.GetTokenType() == IF)
	{
		out << "IF";
	}
	else if(tok.GetTokenType() == LOOP)
	{
		out << "LOOP";
	}
	else if(tok.GetTokenType() == BEGIN)
	{
		out << "BEGIN";
	}
	else if(tok.GetTokenType() == END)
	{
		out << "END";
	}
	else if(tok.GetTokenType() == ID)
	{
		out << "ID("<<tok.GetLexeme()<<")";
	}
	else if(tok.GetTokenType() == ICONST)
	{
		out << "ICONST("<<tok.GetLexeme()<<")";
	}
	else if(tok.GetTokenType() == SCONST)
	{
		out << "SCONST("<<tok.GetLexeme()<<")";
	}
	else if(tok.GetTokenType() == NL)
	{
		out << "NL";
	}
	else if(tok.GetTokenType() == PLUS)
	{
		out << "PLUS";
	}
	else if(tok.GetTokenType() == MINUS)
	{
		out << "MINUS";
	}
	else if(tok.GetTokenType() == STAR)
	{
		out << "STAR";
	}
	else if(tok.GetTokenType() == SLASH)
	{
		out << "SLASH";
	}
	else if(tok.GetTokenType() == LPAREN)
	{
		out << "LPAREN";
	}
	else if(tok.GetTokenType() == RPAREN)
	{
		out << "RPAREN";
	}
	else if(tok.GetTokenType() == SC)
	{
		out << "SC";
	}
	else if(tok.GetTokenType() == ERR)
	{
		out << "Error on line " <<tok.GetLinenum()<<" ("<<tok.GetLexeme()<<")";
	}



	return out;
}



