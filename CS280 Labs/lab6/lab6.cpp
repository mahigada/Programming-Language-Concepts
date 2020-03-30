/*
You are given a copy of lex.h from Programming Assignment 2 and a file called streams.cpp
DO NOT CHANGE streams.cpp
Write code to implement the operator<< overload for Tok
Use the given code to test your implementation.
*/

#include "lex.h"
#include <iostream>
#include <map>
using namespace std;
//Lex l;
map<Token, string> myMap = {
    {ERR, "ERR"},
    {DONE, "DONE"},
    {SC, "SC"},
    {PLUS, "PLUS"},
    {MINUS, "MINUS"},
    {STAR, "STAR"},
    {SLASH, "SLASH"},
    {EQ, "EQ"},
    {LPAREN, "LPAREN"},
    {RPAREN, "RPAREN"},
    {PRINT, "PRINT"},
    {PRINTLN, "PRINTLN"},
    {REPEAT, "REPEAT"},
    {BEGIN, "BEGIN"},
    {END, "END"},
    {SCONST, "SCONST"},
    {ICONST, "ICONST"},
    {IDENT, "IDENT"}
};


ostream& operator<< (ostream& out, const Tok& tok){
    Token tokenName =tok.GetToken();
    out<<myMap[tokenName];
    if (tokenName == IDENT || tokenName == ICONST || tokenName == SCONST || tokenName == ERR){
        out<<"("<<tok.GetLexeme()<<")";
    }
return out;
}