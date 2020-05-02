#include "tools/Scanner.h"

void Scanner::consume()
{
    if (lookahead() != '\0')
        ++position;
}

void Scanner::consumeWS()
{
    char ch;
    while (lookahead(&ch) && isWhitespace(ch))
        consume();
}

char Scanner::lookahead()
{
    if (position >= length)
        return 0;

    return input[position];
}

bool Scanner::lookahead(char* dest)
{
    if (dest == 0)
        return false;

    if (position >= length)
        return false;

    *dest = input[position];
    return (*dest != '\0');
}

bool Scanner::isDigit(char ch)
{
   return (((unsigned)ch > 47) && ((unsigned)ch < 58));
}

bool Scanner::isWhitespace(char ch)
{
   return ((unsigned)ch == 32);
}

bool Scanner::isOp(char ch){
	return ((ch == 37) || (ch == 42) || (ch == 43) || (ch == 45) || (ch == 47));
}

bool Scanner :: isChar(char ch){

	//für Adressen weil diese in Hexa
	 return (((ch >= 97) && (ch <= 102)) || (ch == 120) || (ch == ' '));
}

void Scanner::init(char* input)
{
    this->input = input;
    position = 0;
    length = 0;
    for (; *input != 0; ++input)
        ++length;
}
