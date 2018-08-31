#include<bits/stdc++.h>
using namespace std;

vector<string> dirs = {
	".",
	"/usr/local/include"
};

bool minimize = false;

vector<pair<string,string>> mapper = {
	{"is_trivially_move_constructible_v", "_tmc"},
	{"is_trivially_copy_constructible_v", "_tcc"},
	{"is_move_constructible_v", "_mc"},
	{"is_class_v", "_icv"},
	{"friend", "F"},
	{"salgo::", "S "},
	{"_container()", "_c"},
	{"_handle()", "_h"},
	{"auto", "_a"},
	{"template", "_te"},
	{"typename", "_ty"},
	{"class", "_cl"},
	{"Const_Flag", "CF"},
	{"constexpr", "_ce"},
	{"return", "_re"},
	{"using BASE::", "_uB "},
	{"construct", "cr"},
	{"const", "_"},
	{"operator", "_op"},
	{"using", "_u"},
};


unordered_set<string> included;
vector<string> path_stack = {""};

void parse(istream& is);


string g_indent;


std::string ReplaceAll(std::string str, const std::string& from, const std::string& to) {
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
    }
    return str;
}


int output_line_raw(string line) {
	cout << line << endl;
	return 0;
}

int output_line(string line) {
	if(minimize) {
		int start = 0;
		int end = line.size();

		auto p = line.find("//");
		if(p != string::npos) end = p;

		while(start < end && line[start]<=' ') {
			++start;
		}

		while(end > start && line[end-1]<=' ') {
			--end;
		}

		line = line.substr(start, end-start);

		for(auto& m : mapper) {
			line = ReplaceAll(line, m.first, m.second);
		}

		if(start < end) cout << line << endl;
	}
	else {
		cout << g_indent << line << endl;
	}
	return 0;
}

bool include(string original_filename) {
	//cerr << endl << "including " << original_filename << endl;


	// add path stack
	string filename;
	{
		//for(auto& e : path_stack) {
			filename += path_stack.back();
		//}
		filename += original_filename;
	}


	if(included.find(filename) != included.end()
			|| included.find(original_filename) != included.end()) {
		return true;
	}


	// get rid of glog
	if(original_filename == "glog/logging.h") {
		output_line("#define CHECK_EQ(...) if(0) cerr");
		output_line("#define DCHECK_EQ(...) if(0) cerr");
		output_line("#define CHECK_GE(...) if(0) cerr");
		output_line("#define DCHECK_GE(...) if(0) cerr");
		output_line("#define CHECK_GT(...) if(0) cerr");
		output_line("#define DCHECK_GT(...) if(0) cerr");
		output_line("#define CHECK_LT(...) if(0) cerr");
		output_line("#define DCHECK_LT(...) if(0) cerr");
		output_line("#define CHECK_LE(...) if(0) cerr");
		output_line("#define DCHECK_LE(...) if(0) cerr");
		output_line("#define CHECK(...) if(0) cerr");
		output_line("#define DCHECK(...) if(0) cerr");
		output_line("#define LOG(...) if(0) cerr");
		output_line("#define DLOG(...) if(0) cerr");
		included.insert(original_filename);
		return true;
	}

	
	
	ifstream is;

	for(auto& dir : dirs) {
		string fn = dir + filename;

		//cerr << "testing " << fn << endl;

		is.open( fn.c_str() );
		if(is.good()) break;

		//fn = dir + original_filename;

		//cerr << "testing " << fn << endl;

		//is.open( fn.c_str() );
		//if(is.good()) {
		//	filename = original_filename;
		//	break;
		//}
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
		for(i = 0; i < (int)s.size() && s[i] != '"' && s[i] != '<'; ++i);
		if(i == (int)s.size()) return output_line(source_line);

		char bracket = s[i];

		s = s.substr(i+1);
		for(i = 0; i < (int)s.size() && s[i] != '"' && s[i] != '>'; ++i);
		if(i == 0 || i==(int)s.size()) return output_line(source_line);

		s = s.substr(0,i);

		if(bracket != '"' && s.substr(0,6) != "salgo/" && s != "glog/logging.h") {
			return output_line(source_line);
		}

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


int main(int argc, char* argv[])
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	for(int i=1; i<argc; ++i) {
		string arg = argv[i];
		if(arg == "--minimize") {
			minimize = true;
		}
		else {
			cerr << "unrecognized command line parameter: " << arg << endl;
			return 1;
		}
	}

	// add trailing slashes
	for(auto& dir : dirs) {
		if(dir.back() != '/') dir.push_back('/');
	}

	if(minimize) {
		for(auto& m : mapper) {
			output_line_raw("#define "s + m.second + " " + m.first);
		}
	}

	parse(cin);

	return 0;
}

