#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>
#include <iostream>
#include <cmath>
using namespace std;
//===----------------------------------------------------------------------===//
// Lexer
//===----------------------------------------------------------------------===//
// The lexer returns tokens [0-255] if it is an unknown character, otherwise one
// of these for known things.
enum Token
{
    tok_eof = -1,
    // commands
    tok_def = -2,
    tok_extern = -3,
    // primary
    tok_identifier = -4,
    tok_number = -5
};
static std::string IdentifierStr; // Filled in if tok_identifier
static double NumVal;             // Filled in if tok_number
                                  /// gettok - Return the next token from standard input.
static int gettok()
{
    static int LastChar = ' ';
    // eat the input chars as it recognizes them and stores the last character read, but not processed, in LastChar. Skip any whitespace.
    while (isspace(LastChar))
        LastChar = getchar();

    if (isalpha(LastChar))
    { // check if is an identifier: [a-zA-Z][a-zA-Z0-9]*

        string test;
        IdentifierStr = LastChar;
        while (!isspace(LastChar))
        {
            IdentifierStr = LastChar;
            LastChar = getchar();
            test = test + IdentifierStr;
        }
        IdentifierStr = test;
        // std::cout << "cout << " << IdentifierStr << std::endl;

        // fill in the code here
        return tok_identifier;
    }
    if (isdigit(LastChar) || LastChar == '.')
    { // check if is a number: [0-9.]+
        // fill in the code here
        // NumVal = LastChar;
        // LastChar = getchar();
        // int PrevVal = LastChar - 1;
        double test = 0;
        double PrevVal = 0;
        while (isdigit(LastChar))
        {
            int place = 1;
            int secondplace = 0;
            NumVal = LastChar - 48;
            if (PrevVal != 0)
            {

                test = NumVal * pow(10, secondplace) + PrevVal * pow(10, place);
                // test = test + PrevVal;
                place++;
                secondplace++;
            }
            // std::cout << "cout << " << LastChar <<" - 48 -->"<<NumVal<<" * 10 + "<<PrevVal<<" = "<<test<< std::endl;
            if (PrevVal == 0)
                PrevVal = NumVal;
            else
                PrevVal = test;
            LastChar = getchar();
        }
        if (test > 9)
            NumVal = test;
      //std::cout << "cout << " << NumVal << std::endl;

        return tok_number;
    }
    if (LastChar == '#')
    { // check if is a comment which starts with '#' and ends until end of line.
        // fill in the code here
        while (LastChar != '\n')
            LastChar = getchar();
    }
    // Check for end of file. Don't eat the EOF.
    if (LastChar == EOF)
        return tok_eof;
    // Otherwise, it is unknown, just return the character as its ascii value.
    int ThisChar = LastChar;
    LastChar = getchar();
    return ThisChar;
}

// //===----------------------------------------------------------------------===//
// // Main driver to test your lexer.
// //===----------------------------------------------------------------------===//
int main()
{
    // Prime the first token.
    fprintf(stderr, "ready> ");
    int tok_typ = gettok();
    // // use ctrl + d to send the EOF signal and end this program
    while (true)
    {
        fprintf(stderr, "token type> %d\n", tok_typ);
        switch (tok_typ)
        {
        case tok_eof:
            return 0;
        default:
            tok_typ = gettok();
            break;
        }
    }
}