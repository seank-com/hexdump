#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

char GetHexValue(char ch)
{
    if (ch >= '0' && ch <= '9') return ch - '0';
    if (ch >= 'a' && ch <= 'f') return (ch - 'a') + 10;
    if (ch >= 'A' && ch <= 'F') return (ch - 'A') + 10;
    return -1;
}

char GetHexChar(char val)
{
    if (val >= 0 && val <= 9) return val + '0';
    if (val >= 10 && val <= 15) return (val - 10) + 'A';
    return '?';
}

char GetCommentChar(char ch)
{
    if (ch < 32) return '?';
    if (ch > 126) return '?';
    return ch;
}

int HexDump(const char* filein, const char* fileout)
{
    ifstream input(filein, ios_base::in | ios_base::binary);
    ofstream output(fileout, ios_base::out);
    int count = 0;
    char ch;
    string comment;
    while (input.get(ch))
    {
        unsigned char byte = static_cast<unsigned char>(ch);
        output << GetHexChar(byte >> 4) << GetHexChar(byte & 0xf) << ' ';
        comment.push_back(GetCommentChar(ch));

        count++;
        if (count % 20 == 0)
        {
            output << "; " << comment << endl;
            comment.clear();
        }
    }
    output << "; " << comment << endl;

    cout << count << " bytes from " << filein << " converted to hex and save as " << fileout << endl;
    return 0;
}

int ReverseHexDump(const char* filein, const char* fileout)
{
    ifstream input(filein, ios_base::in);
    ofstream output(fileout, ios_base::out | ios_base::binary);
    int count = 0;
    int state = 0;
    char ch;
    char high = 0;
    char low = 0;
    while (input.get(ch))
    {
        switch (state)
        {
        case 0: // looking for first hex digit or comment mark ignoring whitepase
            {
                high = GetHexValue(ch);
                if (high != -1)
                {
                    state = 1;    
                } 
                else if (ch == ';')
                {
                    state = 2;
                }
                else if (ch != ' ' && ch != '\t' && ch != '\r' && ch != '\n')
                {
                    cerr << "Bad file format, aborting (state 1)" << endl;
                    return 1;
                }
            }
            break;
        case 1: // looking for second hex digit
            {
                low = GetHexValue(ch);
                if (low == -1)
                {
                    cerr << "Bad file format, aborting (state 2)" << endl;
                    return 1;
                }

                unsigned char byte = static_cast<unsigned char>(high << 4) | static_cast<unsigned char>(low & 0xf);
                output << byte;
                count++;
                state = 0;
            }
            break;
        case 2: // looking for newline
            {
                if (ch == '\n')
                {
                    state = 0;
                }
            }
        }
    }
    
    if (state == 1)
    {
        cerr << "Bad file format, aborting (bad finish state)" << endl;
        return 1;
    }

    cout << count << " bytes from " << filein << " converted to hex and save as " << fileout << endl;
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc == 4)
    {
        string param(argv[1]);
        if (param == "-r")
        {
            return ReverseHexDump(argv[2], argv[3]);
        }
    }
    else if (argc == 3)
    {
        return HexDump(argv[1], argv[2]);
    }

    cerr << "Usage:" << endl << endl << 
    argv[0] << " [-r] filein fileout" << endl << endl <<
    "\tTakes a binary file and produces a hexdump" << endl << endl <<
    "-r\tTakes a hexdump and produces a binary file" << endl;
    return 1;
}
