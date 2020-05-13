/*
 * parsetree.h
 */

#ifndef TREE_H_
#define TREE_H_

#include <vector>
#include <map>
#include <string>
#include "value.h"
using std::vector;
using std::map;
using std::string;

// NodeType represents all possible types
enum NodeType { ERRTYPE, INTTYPE, STRTYPE };

// a "forward declaration" for a class to hold values

static map<string,Value> tablelookup;


class ParseTree {


public:

	int		linenum;
	ParseTree	*left;
	ParseTree	*right;

	virtual Value Eval() const = 0;


	ParseTree(int linenum, ParseTree *l = 0, ParseTree *r = 0)
		: linenum(linenum), left(l), right(r) {}

	virtual ~ParseTree() {
		delete left;
		delete right;
	}

	int GetLinenum() const { return linenum; }
	ParseTree *GetLeft() const { return left; }
	ParseTree *GetRight() const { return right; }

	int NodeCount() const {
		int nc = 0;
		if( left ) nc += left->NodeCount();
		if( right ) nc += right->NodeCount();
		return nc + 1;
	}


	virtual bool IsString() const { return false; }

	virtual bool IsIdent() const {return false;}

	virtual bool IsInt() const {return false;}


};

class StmtList : public ParseTree {

public:
	StmtList(ParseTree *l, ParseTree *r) : ParseTree(0, l, r) {}
	Value Eval() const 
	{
		if(left){left->Eval();}
		if(right){right->Eval();}

		return Value();
	}

};

class IfStatement : public ParseTree {
public:
	IfStatement(int line, ParseTree *ex, ParseTree *stmt) : ParseTree(line, ex, stmt) {}
	Value Eval() const 
	{
		if(!left->Eval().isInt())
		{
			throw std::logic_error("RUNTIME ERROR Conditional is not an integer");
		}

		if(left->Eval().GetInt())
			{
				right->Eval();
			}

		return Value();

	}
};

class SetStatement : public ParseTree {
	string id;

public:
	SetStatement(int line, string id, ParseTree *expr) : ParseTree(line, expr), id(id) {}
	Value Eval() const 
	{
		tablelookup[id] = left->Eval();

		return Value(0);
	}
};

class PrintStatement : public ParseTree {
public:
	PrintStatement(int line, ParseTree *e) : ParseTree(line, e) {}
	Value Eval() const 
	{
		cout << left->Eval();
		return Value(0);
	}

};

class LoopStatement : public ParseTree {
public:
	LoopStatement(int line, ParseTree *ex, ParseTree *stmt) : ParseTree(line, ex, stmt) {}
	Value Eval() const 
	{
		while(left->Eval().GetInt() != 0)
		{
			right->Eval();
		}

		return Value();
	}
};

class Addition : public ParseTree {
public:
	Addition(int line, ParseTree *l, ParseTree *r) : ParseTree(line,l,r) {}

	Value Eval() const 
	{
		auto a1 = left->Eval();
		auto a2 = right->Eval();

		return a1 + a2;
	}
};

class Subtraction : public ParseTree {
public:
	Subtraction(int line, ParseTree *l, ParseTree *r) : ParseTree(line,l,r) {}
	Value Eval() const 
	{
		auto a1 = left->Eval();
		auto a2 = right->Eval();

		return a1 - a2;
	}
};

class Multiplication : public ParseTree {
public:
	Multiplication(int line, ParseTree *l, ParseTree *r) : ParseTree(line,l,r) {}
	Value Eval() const 
	{
		auto a1 = left->Eval();
		auto a2 = right->Eval();

		return a1 * a2;
	}
};

class Division : public ParseTree {
public:
	Division(int line, ParseTree *l, ParseTree *r) : ParseTree(line,l,r) {}
	Value Eval() const 
	{
		auto a1 = left->Eval();
		auto a2 = right->Eval();

		int num = right->Eval().GetInt();

		if(num == 0)
		{
			throw std::logic_error("RUNTIME ERROR Divide by zero error");
		}

		return a1 / a2;
	}
};
class Empty : public ParseTree{

	public:
		Empty() : ParseTree(1){

		}
	Value Eval() const {return Value();}


};

class IConst : public ParseTree {
	int val;

public:
	IConst(Token& t) : ParseTree(t.GetLinenum()) {
		val = stoi(t.GetLexeme());
	}

	bool IsInt() const {return true;}
	Value Eval() const {return Value(val);}
};

class SConst : public ParseTree {
	string val;

public:
	SConst(Token& t) : ParseTree(t.GetLinenum()) {
		val = t.GetLexeme();
	}

	bool IsString() const { return true; }
	Value Eval() const {return Value(val);}
};

class Ident : public ParseTree {
	

public:
	string id;
	Ident(Token& t) : ParseTree(t.GetLinenum()), id(t.GetLexeme()) {
	}

	string GetID() const {return id;}

	bool IsIdent() const { return true; }
	Value Eval() const 
	{
		if(tablelookup.find(id) == tablelookup.end())
		{
			throw std::runtime_error(id);
		}
		return Value(tablelookup[id]);
	}

};


#endif /* TREE_H_ */
