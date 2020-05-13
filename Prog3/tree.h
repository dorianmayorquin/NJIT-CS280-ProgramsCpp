/*
 * parsetree.h
 */

#ifndef TREE_H_
#define TREE_H_

#include <vector>
#include <map>
#include <string>
using std::vector;
using std::map;
using std::string;

// NodeType represents all possible types
enum NodeType { ERRTYPE, INTTYPE, STRTYPE };

// a "forward declaration" for a class to hold values
class Value;

class ParseTree {

int		linenum;
ParseTree	*left;
ParseTree	*right;
	

public:


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
};

class StmtList : public ParseTree {

public:
	StmtList(ParseTree *l, ParseTree *r) : ParseTree(0, l, r) {}

};

class IfStatement : public ParseTree {
public:
	IfStatement(int line, ParseTree *ex, ParseTree *stmt) : ParseTree(line, ex, stmt) {}
};

class SetStatement : public ParseTree {
	string id;

public:
	SetStatement(int line, string id, ParseTree *expr) : ParseTree(line, expr), id(id) {}
};

class PrintStatement : public ParseTree {
public:
	PrintStatement(int line, ParseTree *e) : ParseTree(line, e) {}
};

class LoopStatement : public ParseTree {
public:
	LoopStatement(int line, ParseTree *ex, ParseTree *stmt) : ParseTree(line, ex, stmt) {}
};

class Addition : public ParseTree {
public:
	Addition(int line, ParseTree *l, ParseTree *r) : ParseTree(line,l,r) {}
};

class Subtraction : public ParseTree {
public:
	Subtraction(int line, ParseTree *l, ParseTree *r) : ParseTree(line,l,r) {}
};

class Multiplication : public ParseTree {
public:
	Multiplication(int line, ParseTree *l, ParseTree *r) : ParseTree(line,l,r) {}
};

class Division : public ParseTree {
public:
	Division(int line, ParseTree *l, ParseTree *r) : ParseTree(line,l,r) {}
};

class IConst : public ParseTree {
	int val;

public:
	IConst(Token& t) : ParseTree(t.GetLinenum()) {
		val = stoi(t.GetLexeme());
	}
};

class SConst : public ParseTree {
	string val;

public:
	SConst(Token& t) : ParseTree(t.GetLinenum()) {
		val = t.GetLexeme();
	}

	bool IsString() const { return true; }
};

class Ident : public ParseTree {
	

public:
	string id;
	Ident(Token& t) : ParseTree(t.GetLinenum()), id(t.GetLexeme()) {
	}


	bool IsIdent() const { return true; }
};

class Parens : public ParseTree{
	string val;

public:
	Parens(Token &t, ParseTree *l) : ParseTree(t.GetLinenum(),l), val(t.GetLexeme()) {}
};

#endif /* TREE_H_ */
