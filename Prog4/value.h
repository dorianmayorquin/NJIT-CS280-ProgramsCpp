#include <stdexcept>
#include <string>
using std::string;
#include <iostream>
using std::ostream;

#ifndef _VALUE_H_
#define _VALUE_H_



class Value {
public:
    enum ValType { ERRVAL, INTVAL, STRVAL };
    
private:
    ValType        theType;
    int                 theInt;
    string            theStr;
    
public:
    Value() : theType(ERRVAL), theInt(0) {}
    Value(int i) : theType(INTVAL), theInt(i) {}
    Value(string s) : theType(STRVAL), theInt(0) , theStr(s) {}
    
    bool isInt() const { return theType == INTVAL; }
    bool isStr() const { return theType == STRVAL; }
    bool isErr() const { return theType == ERRVAL; }
    
    int GetInt() const {
        if( isInt() ) return theInt;
        throw std::logic_error("This Value is not an int");
    }
    
    string GetStr() const {
        if( isStr() ) return theStr;
        throw std::logic_error("This Value is not a string");
    }
    
    friend Value operator+(const Value& o, const Value& b) 
    {   
        if(o.isInt() && b.isInt())
        {
            return o.GetInt() + b.GetInt();
        }
        if(o.isStr() && b.isStr())
        {
            return o.GetStr() + b.GetStr();
        }
        else
        {
            throw std::logic_error("RUNTIME ERROR Type mismatch for arguments of +");
        }

    }
    friend Value operator-(const Value& o, const Value& b) 
    {
        if(!o.isInt() || !b.isInt())
        {
            throw std::logic_error("RUNTIME ERROR Type mismatch for arguments of -");
        }
        return o.GetInt() - b.GetInt();

    }
    friend Value operator*(const Value& o, const Value& b)
    {
        if(o.isInt() && b.isInt())
        {
            return o.GetInt() * b.GetInt();
        }
        if(o.isStr() && b.isInt())
        {
            if(b.GetInt() < 0)
            {
                throw std::logic_error("RUNTIME ERROR Repetition count less than 0");
            }
            string str = "";
            int num = b.GetInt();

            for(int i = 0; i<num; i++)
            {
                str += o.GetStr();
            }

            return Value(str);
        }
        if(o.isInt() && b.isStr())
        {
             if(o.GetInt() < 0)
            {
                throw std::logic_error("RUNTIME ERROR Repetition count less than 0");
            }
            string str = "";
            int num = o.GetInt();

            for(int i = 0; i<num; i++)
            {
                str += b.GetStr();
            }

            return Value(str);
        }
        else
        {
            throw std::logic_error("RUNTIME ERROR Type mismatch for arguments of *");
        }

        return Value();

    }
    friend Value operator/(const Value& o, const Value& b)
    {
        if(o.isInt() && b.isInt())
        {
            return  o.GetInt() / b.GetInt();
        }

        return Value();
    }
    
    friend ostream& operator<<(ostream& out, const Value& v) {
        switch( v.theType ) {
            case ERRVAL:
                out << "RUNTIME ERROR: " << v.theStr;
                break;
            case INTVAL:
                out << v.theInt;
                break;
            case STRVAL:
                out << v.theStr;
                break;
        }
        
        return out;
    }
};




#endif
