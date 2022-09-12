#pragma once

class Litera
{
    public:

        Litera();
        ~Litera();
        /*
        * Типы входных сигналов автомата
        * (синтермы литер сканируемого текста)
        */
        enum TypeData
        {
            LETTER,
		    DIGIT,
		    SPACE,
		    ENDFILE,
		    UNKNOWU
        };
        TypeData GetLit(char symbol);
        TypeData GetSynterm() const;
        char GetSymbol() const;

    private:
        char value; // значение литеры
        TypeData synterm; //значение синтермы

        bool IsLetter(char c);
        bool IsDigit(char c);
        bool IsSpace(char c);
        bool IsEnd(char c);

};