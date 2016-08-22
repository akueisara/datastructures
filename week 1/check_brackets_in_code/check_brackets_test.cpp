#include <iostream>
#include <stack>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>

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

std::string getFileString(std::string filename) {
	std::ifstream inFile;
    inFile.open(filename);// Open the input file
 
    std::stringstream strStream;
    strStream << inFile.rdbuf();// Read the file
    std::string text = strStream.str();// string holds the content of the file
	return text;
}

int IsBalanced(std::string text) {
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
				return error_pos;
			}
			Bracket top = opening_brackets_stack.top();
			opening_brackets_stack.pop();
			if(!top.Matchc(next)) {
				error_pos = position + 1;
				return error_pos;
			}
        }
    }

    // Printing answer, write your code here
	if(error_pos==0 && opening_brackets_stack.empty())
		return 0;
	else {
		if(error_pos == 0) {
			while(opening_brackets_stack.size()>1)
				opening_brackets_stack.pop();
			error_pos = opening_brackets_stack.top().position;
		}
		return error_pos;
	}
}

int main() {
    std::string text;
	std::string result_text;
	for(int i=1;i<55;i++) {
		std::string name = "";
		if(i<10)
			name = "./tests/0";
		else
			name = "./tests/";
		text = getFileString(name + std::to_string(i));
		result_text = getFileString(name + std::to_string(i) + ".a");
		if (result_text.compare(0,7,"Success") == 0)
			result_text = "0";
		else
			result_text.erase(result_text.end()-2, result_text.end());
		int result = IsBalanced(text);
		if(result_text.compare(std::to_string(result)) == 0)
			std::cout << i << " Pass" << std::endl;
		else
			std::cout << i << " Not Pass " << result_text << " " << std::to_string(result) << std::endl;
	}
	
    return 0;
}