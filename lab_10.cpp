#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
using namespace std;


vector<string>  read_input_file() {
	cout << "Enter a file name: " << endl;
	string filename;
	cin >> filename;
	cout << "\n" << endl;
	
	ifstream input_file(filename);
	vector<string> lines;
	
	if (!input_file.is_open()) {
        cerr << "Error: Could not open the file\n" <<endl;
		return lines;
    }
	
	string line;
	while (getline(input_file, line)) {
		lines.push_back(line);
	}
	
	input_file.close();
	
	return lines;
}


vector<string> input_lines(vector<string> lines) {
    vector<string> cleaned;

    for (string& line : lines) {
        line.erase(remove(line.begin(), line.end(), '\r'), line.end());

        if (!line.empty())
            cleaned.push_back(line);
    }
	
	return cleaned;
}


vector<string> get_two_nums(vector<string> lines, int line_index) {
	string num1;
	string num2;
	int char_index = 0;
	vector<string> result;
	
	while (!(isspace(lines[line_index][char_index]))) {
		num1 += lines[line_index][char_index];
		char_index += 1;
	}
	
	char_index += 1;
	
	while (char_index < static_cast<int>(lines[line_index].size())) {
		num2 += lines[line_index][char_index];
		char_index += 1;
	}
	
	result.push_back(num1);
	result.push_back(num2);
	
    return result;
}


bool valid_double(const string num) {
	if (num.empty()) return false;

    int i = 0;
    if (num[i] == '+' || num[i] == '-') i++;
    if (i >= static_cast<int>(num.size())) return false;

    bool has_dot = false;
    bool digits_before = false;
    bool digits_after = false;

    for (; i < static_cast<int>(num.size()); i++) {
        char c = num[i];
        if (isdigit(c)) {
            if (!has_dot) digits_before = true;
            else digits_after = true;
        } 
        else if (c == '.') {
            if (has_dot) return false;
            has_dot = true;
        } 
        else {
            return false;
        }
    }

    if (!has_dot)
        return digits_before;
    else
        return digits_before && digits_after;
}


int main() {
	vector<string> lines = read_input_file();
	lines = input_lines(lines);
	
	vector<string> results;

	for (int i=0; i < static_cast<int>(lines.size()); i++) {
		vector<string> new_result = get_two_nums(lines, i);
		string result1 = new_result[0];
		string result2 = new_result[1];
		results.push_back(result1);
		results.push_back(result2);
	}
	
	int index = 0;
	
	while (index < static_cast<int>(results.size())) {
		string num1 = results[index];
		string num2 = results[index+1];
		bool num1_valid = valid_double(num1);
		bool num2_valid = valid_double(num2);
		
		if (num1_valid && num2_valid) {
			double num_sum = stod(num1) + stod(num2);
			cout << num1 << " + " << num2 << " = " << num_sum << endl;
		}
		
		else {
			cout << "Invalid Number(s): " << num1 << ", " << num2 << endl;
		}
		
		index += 2;
	}
	
	return 0;
}
