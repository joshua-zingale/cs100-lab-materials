#ifndef _INTERACTIVE_ANSI_DIRECTIVES
#define _INTERACTIVE_ANSI_DIRECTIVES
#include<iostream>
namespace ansi {
std::ostream &clearScreen(std::ostream &os);
std::ostream &clearScreenFromCursor(std::ostream &os);
std::ostream &clearLine(std::ostream &os);


std::string moveCursor(int line, int column);



std::ostream& save(std::ostream &os);
std::ostream& load(std::ostream &os);

std::string unescape(std::string&);
}
#endif