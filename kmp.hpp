#pragma once



auto kmp_table(const string& pattern) {
	vector<int> result( pattern.size() + 1 );

	result[0] = -1;
	int longest_prefix = -1;

	for(int i=1; i<(int)result.size(); ++i) {

		while(longest_prefix != -1  &&  pattern[i-1] != pattern[longest_prefix]) longest_prefix = result[longest_prefix];
		++longest_prefix;

		if(i == (int)pattern.size()  ||  pattern[longest_prefix] != pattern[i]) {
			result[i] = longest_prefix;
		}
		else {
			result[i] = result[ longest_prefix ];
		}
	}

	return result;
}



/* from wiki - is it faster?
auto kmp_table(const string& pattern) {
	vector<int> result( pattern.size() + 1 );

	result[0] = -1;
	int longest_prefix = 0;

	for(int i=1; i<(int)result.size(); ++i) {

		if(pattern[i] == pattern[longest_prefix]) {
			result[i] = result[longest_prefix];
			++longest_prefix;
		}
		else {
			result[i] = longest_prefix;

			longest_prefix = result[longest_prefix];

			while(longest_prefix >= 0 && pattern[i] != pattern[longest_prefix]) {
				longest_prefix = result[longest_prefix];
			}

			++longest_prefix;
		}
	}

	result[ pattern.size() ] = longest_prefix;

	return result;
}
*/



