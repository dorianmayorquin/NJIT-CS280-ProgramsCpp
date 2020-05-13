#include "parse.h"
#include "gettoken.h"
#include <map>
#include "tree.h"
#include <exception>


static int error_count = 0;
static int leaf = 0;
static int str = 0;
static int op = 0;


int leaves()
{
	return leaf;
}
int errcount()
{
	return error_count;
}
int strgs()
{
	return str;
}
int ops()
{
	return op;
}
int depth(ParseTree* tree)
{
	int ln = 0,rn = 0;

	if(tree->GetLeft())
		ln = depth(tree->GetLeft());
	if(tree->GetRight())
		rn = depth(tree->GetRight());

	if(ln > rn)
	{
		return ln + 1;
	}
	else
		return rn + 1;

}

void ParseError(int line, string msg)
{
	++error_count;
	cout << line+1 << ": " << msg << endl;
}

// Prog is an Slist
ParseTree *Prog(istream& in, int& line)
{
	ParseTree *sl = Slist(in, line);
    
	if( GetToken::Get(in, line) != DONE )
	{
		ParseError(line, "Unrecognized statement");
	}

	if( sl == 0 )
		ParseError(line, "No statements in program");


	if( error_count )
		return 0;


	return sl;
}

// Ssep { Slist } | Stmt Ssep { Slist }
ParseTree *Slist(istream& in, int& line) {
	ParseTree *s = Stmt(in, line);
	if( s == 0 )
		return 0;
 
	Token t;
	if( (t = GetToken::Get(in, line)) != SC && t != NL ) {
		ParseError(line, "Missing statement separator");
		return 0;
	}


    return new StmtList(s, Slist(in,line));
}

ParseTree *Stmt(istream& in, int& line) {
	ParseTree *s = 0;

	Token t = GetToken::Get(in, line);

	switch( t.GetTokenType() ) {
	case IF:
		s = IfStmt(in, line);
		break;

	case PRINT:
		s = PrintStmt(in, line);
		break;

	case SET:
		s = SetStmt(in, line);
		break;

	case LOOP:
		s = LoopStmt(in, line);
		break;

	case ERR:
		ParseError(line, "Invalid token");
		break;

	case DONE:
		break;

	case NL:
	case SC:
		// an empty statement; get the next one
		s = Stmt(in, line);
		break;

	default:
		GetToken::PushBack(t);
		break;
	}

	return s;
}

ParseTree *IfStmt(istream& in, int& line) {

	ParseTree *exp = Expr(in,line);

	if(exp == 0)
	{
		return 0;
	}

		Token t = GetToken::Get(in,line);

		if(t.GetTokenType() != BEGIN)
		{
			ParseError(line,"Missing BEGIN after expression");
			return 0;
		}

		ParseTree *st = Slist(in,line);

		t = GetToken::Get(in,line);

		if(t.GetTokenType() != END)
		{
			ParseError(line,"Missing end identifier");
			return 0;
		}


		return new IfStatement(line,exp,st);
	
}

ParseTree *LoopStmt(istream& in, int& line) {

	ParseTree *fi = Expr(in,line);

	if(fi == 0)
		return 0;

	Token t = GetToken::Get(in,line);

	if(t.GetTokenType() != BEGIN)
		{
			ParseError(line,"Missing BEGIN after expression");
			return 0;
		}

		ParseTree *st = Slist(in,line);

		

		if(st == 0)
		{
			ParseError(line,"Missing statement list after BEGIN");
			return 0;
		}

		t = GetToken::Get(in,line);

		if(t.GetTokenType() != END)
		{
			ParseError(line,"Missing end identifier");
			return 0;
		}



		
		return new LoopStatement(line,fi,st);


	// add code to parse an if

}

ParseTree *SetStmt(istream& in, int& line) {

	Token t = GetToken::Get(in,line);

	if(t.GetTokenType() != ID)
	{
		ParseError(line,"Missing Identifier after Set");
	}

	string id = t.GetLexeme();

	ParseTree *set = Expr(in,line);


	return new SetStatement(line,t.GetLexeme(),set);
}

ParseTree *PrintStmt(istream& in, int& line) {
	
	ParseTree *nod = Expr(in,line);

	if(nod == 0)
	{
		ParseError(line,"Primary expected");
		ParseError(line,"Missing expression after print");
		return 0;
	}

	return new PrintStatement(line,nod);
}

ParseTree *Expr(istream& in, int& line) {

	ParseTree *t1 = Prod(in, line);
	if( t1 == 0 ) {
		return 0;
	}

	while ( true ) {
		Token t = GetToken::Get(in, line);

		if( t != PLUS && t != MINUS ) {
			GetToken::PushBack(t);
			return t1;
		}

		ParseTree *t2 = Prod(in, line);
		if( t2 == 0 ) {
			ParseError(line, "Missing expression after operator");
			return 0;
		}

		if( t == PLUS )
		{
			op++;
			t1 = new Addition(t.GetLinenum(), t1, t2);
		}
		else
		{
			op++;
			t1 = new Subtraction(t.GetLinenum(), t1, t2);
		}
	}
}

ParseTree *Prod(istream& in, int& line) {

	ParseTree *t1 = Primary(in, line);

	if(t1 == 0)
	{
		return 0;
	}

	while ( true ) {

		Token t = GetToken::Get(in, line);

		if( t != STAR && t != SLASH ) {
			GetToken::PushBack(t);
			return t1;
		}

		ParseTree *t2 = Primary(in, line);

		if( t2 == 0 ) {
			ParseError(line, "Missing expression after operator");
			return 0;
		}

		if( t == STAR )
		{
			op++;
			t1 = new Multiplication(t.GetLinenum(), t1, t2);
		}
		else
		{
			op++;
			t1 = new Division(t.GetLinenum(), t1, t2);
		}
	}

	// needs more...
}

ParseTree *Primary(istream& in, int& line) {

	Token t = GetToken::Get(in, line);

	if(t.GetTokenType() == ID)
	{
		leaf++;
		return new Ident(t);
	}
	if(t.GetTokenType() == ICONST)
	{
		leaf++;
		return new IConst(t);
	}
	if(t.GetTokenType() == SCONST)
	{
		leaf++;
		str++;
		return new SConst(t);
	}
	if(t.GetTokenType() == LPAREN)
	{
		ParseTree *val = Expr(in, line);

		Token t = GetToken::Get(in,line);

		if(t.GetTokenType() != RPAREN)
		{
			ParseError(line,"Missing ) after expression");
			ParseError(line,"Missing expression after if");
			return 0;
		}

		return val;
	}
	else


	return 0;
	

	// needs more...
}



