#include "litera.h"
#include <iostream>

Litera::TypeData Litera::GetLit(char symbol)
{
    value = symbol;
	if (IsLetter(symbol))
		return synterm = LETTER; 

	if (IsDigit(symbol))
		return synterm = DIGIT; 

	if (IsSpace(symbol))
		return synterm = SPACE; 

	if (IsEnd(symbol))
		return synterm = ENDFILE;

	return synterm = UNKNOWU;
}

Litera::TypeData Litera::GetSynterm() const
{
    return synterm;
}

char Litera::GetSymbol() const
{
    return value;
}

bool Litera::IsLetter(char symbol)
{
	if ((symbol >= 'a' && symbol <= 'z') || (symbol >= 'A' && symbol <= 'Z'))
		return true;

	return false;
}

bool Litera::IsDigit(char symbol)
{
	if (symbol >= '0' && symbol <= '9')
		return true;

	return false;
}

bool Litera::IsSpace(char symbol)
{
	switch (symbol)
	{
	case ' ':
	case '\t':
	case '\r':
	case '\n':
		return true;
	default:
		return false;
	}
}

bool Litera::IsEnd(char symbol)
{
	if (symbol == '\0')
		return true;

	return false;
}

Litera::Litera(){}
Litera::~Litera(){}
