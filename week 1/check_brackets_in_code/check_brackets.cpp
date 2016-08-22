#include <iostream>
#include <stack>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

struct Bracket {
    Bracket(char type, int position):
        type(type),
        position(position)
    {}

    bool Matchc(char c) {
        if (type == '[' && c == ']')
            return true;
        if (type == '{' && c == '}')
            return true;
        if (type == '(' && c == ')')
            return true;
        return false;
    }

    char type;
    int position;
};

int main() {
    std::string text;
    getline(std::cin, text);
	
	int error_pos = 0;

    std::stack <Bracket> opening_brackets_stack;
    for (int position = 0; position < text.length(); ++position) {
        char next = text[position];

        if (next == '(' || next == '[' || next == '{') {
            // Process opening bracket, write your code here
			Bracket b(next, position+1);
			opening_brackets_stack.push(b);
        }
		
        if (next == ')' || next == ']' || next == '}') {
            // Process closing bracket, write your code here
			if(opening_brackets_stack.empty()) {
				error_pos = position + 1;
				break;
			}
			Bracket top = opening_brackets_stack.top();
			opening_brackets_stack.pop();
			if(!top.Matchc(next)) {
				error_pos = position + 1;
				break;
			}
        }
    }

    // Printing answer, write your code here
	if(error_pos==0 && opening_brackets_stack.empty())
		std::cout << "Success";
	else {
		if(error_pos == 0) {
			while(opening_brackets_stack.size()>1)
				opening_brackets_stack.pop();
			error_pos = opening_brackets_stack.top().position;
		}
		std::cout << error_pos;
	}

    return 0;
}
