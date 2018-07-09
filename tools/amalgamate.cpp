#include<bits/stdc++.h>
using namespace std;

vector<string> dirs = {
	"."
};




unordered_set<string> included;
vector<string> path_stack;

void parse(istream& is);


string g_indent;

int output_line(const string& line) {
	cout << g_indent << line << endl;
	return 0;
}

bool include(string filename) {

	// add path stack
	{
		string new_filename;
		for(auto& e : path_stack) {
			new_filename += e;
		}
		new_filename += filename;
		filename = std::move(new_filename);
	}


	if(included.find(filename) != included.end()) {
		return true;
	}
	
	
	ifstream is;

	for(auto& dir : dirs) {
		string fn = dir + filename;
		is.open( fn.c_str() );

		if(is.good()) break;
	}

	if(!is.good()) return false;

	included.insert(filename);

	output_line("");
	output_line("////////////////////////////////////////////////////////////////////////////////");
	output_line("// AMALGAMATE: \""s + filename + "\" BEGINS HERE");
	output_line("//");


	auto pos = filename.rfind('/');
	path_stack.push_back( filename.substr(0,pos+1) );


	auto old_indent = g_indent;
	g_indent += '\t';

	parse(is);

	g_indent = old_indent;


	path_stack.pop_back();

	output_line("");
	output_line("//");
	output_line("// AMALGAMATE: \""s + filename + "\" ENDS HERE");
	output_line("////////////////////////////////////////////////////////////////////////////////");
	output_line("");

	return true;
}

int process(const string& source_line) {

	int fst = 0;
	while(fst < (int)source_line.size() && source_line[fst] <= ' ') ++fst;

	auto indent = source_line.substr(0,fst);
	auto line = source_line.substr(fst);

	if(line.substr(0,8) == "#include") {
		string s = line.substr(8);

		int i;
		for(i = 0; i < (int)s.size() && s[i] != '"'; ++i);
		if(i == (int)s.size()) return output_line(source_line);

		s = s.substr(i+1);
		for(i = 0; i < (int)s.size() && s[i] != '"'; ++i);
		if(i == 0 || i==(int)s.size()) return output_line(source_line);

		s = s.substr(0,i);

		g_indent += indent;
		bool r = include(s);
		g_indent.resize( g_indent.size() - indent.size() );

		if(!r) return output_line(source_line + " // AMALGAMATE: INCLUDE FAILED!");
	}
	else if(line.substr(0,12) == "#pragma once")	// todo: can have some more whitespace
	{
		return 0;	// don't rewrite
	}
	else return output_line(source_line);

	return 0;	// never
}


void parse(istream& is) {
	string line;
	getline(is,line);

	for(;;) {
		process(line);

		getline(is,line);

		if(!is.good() && line.empty()) break;
	}
}


int main(int argc, char*[])
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	if(argc != 1)
	{
		cout << "Arguments not supported!\n";
		return 1;
	}

	// add trailing slashes
	for(auto& dir : dirs) {
		if(dir.back() != '/') dir.push_back('/');
	}

	parse(cin);

	return 0;
}

