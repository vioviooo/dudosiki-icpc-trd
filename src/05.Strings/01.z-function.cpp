// O(n)
vector<int> z_function(string s) {
    int n = s.size();
    vector<int> z(n);
    int l = 0, r = 0;
    for(int i = 1; i < n; i++) {
        if(i < r) {
            z[i] = min(r - i, z[i - l]);
        }
        while(i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            z[i]++;
        }
        if(i + z[i] > r) {
            l = i;
            r = i + z[i];
        }
    }
    return z;
}

// pattern matching: s = pattern + '$' + text
vector<int> find_pattern(string pattern, string text) {
    string s = pattern + '$' + text;
    vector<int> z = z_function(s);
    vector<int> matches;
    for(int i = pattern.size() + 1; i < s.size(); i++) {
        if(z[i] == pattern.size()) {
            matches.push_back(i - pattern.size() - 1);
        }
    }
    return matches;
}

// find all distinct substrings in O(n²)
int distinct_substrings(string s) {
    int cnt = 0;
    string current = "";
    for(char c : s) {
        current += c;
        string rev = current;
        reverse(rev.begin(), rev.end());
        vector<int> z = z_function(rev);
        int max_z = *max_element(z.begin(), z.end());
        cnt += current.size() - max_z;
    }
    return cnt;
}

bool areAnagrams(string s1, string s2) {
    if (s1.length() != s2.length()) return false;
    
    vector<int> count(26, 0);
    for (char c : s1) count[c - 'a']++;
    for (char c : s2) count[c - 'a']--;
    
    for (int i = 0; i < 26; i++) {
        if (count[i] != 0) return false;
    }
    return true;
}

string longestCommonPrefix(vector<string>& strs) {
    if (strs.empty()) return "";
    
    string prefix = strs[0];
    for (int i = 1; i < strs.size(); i++) {
        while (strs[i].find(prefix) != 0) {
            prefix = prefix.substr(0, prefix.length() - 1);
            if (prefix.empty()) return "";
        }
    }
    return prefix;
}

#include <cctype>

char c = 'A';

// Character checks
bool isAlpha = isalpha(c);    // alphabetic
bool isDigit = isdigit(c);    // digit
bool isLower = islower(c);    // lowercase
bool isUpper = isupper(c);    // uppercase
bool isSpace = isspace(c);    // whitespace
bool isAlnum = isalnum(c);    // alphanumeric

// Character conversion
char lower = tolower(c);      // to lowercase
char upper = toupper(c);      // to uppercase

#include <string>
#include <iostream>
using namespace std;

int main() {
    string s = "Hello";
    
    // Length
    int len = s.length(); // or s.size()
    
    // Access characters
    char first = s[0];
    char last = s.back();
    
    // Modification
    s += " World"; // append
    s.push_back('!'); // add single character
    s.pop_back(); // remove last character
    
    // Comparison
    string s2 = "Hello";
    if (s == s2) { /* equal */ }
    if (s < s2) { /* lexicographical comparison */ }
    
    // Substring
    string sub = s.substr(0, 5); // from index 0, length 5
    
    // Find
    size_t pos = s.find("World"); // returns string::npos if not found
    if (pos != string::npos) {
        // found at position pos
    }
    
    // Replace
    s.replace(0, 5, "Hi"); // replace 5 chars from index 0 with "Hi"
    
    return 0;
}

void solve() {
    int t;
    cin >> t;
 
    cin.ignore();
 
    int cnt = 0;
    while (t--) {
        string cmd;
        getline(cin, cmd);
 
        if (cmd.find("Set") == 0 and cmd.find("to answer") != string::npos) {
            stringstream ss(cmd);
            string set_, name, to_, answer_;
            ss >> set_ >> name >> to_ >> answer_;
            cnt += name.length();
        }
    }
 
    cout << cnt << '\n';
}
int main() {

	int n;
	vector < vector<int> > g (n, vector<int> (n));
	... чтение графа в матрицу смежности ...

	vector<int> deg (n);
	for (int i=0; i<n; ++i)
		for (int j=0; j<n; ++j)
			deg[i] += g[i][j];

	int first = 0;
	while (!deg[first])  ++first;

	int v1 = -1,  v2 = -1;
	bool bad = false;
	for (int i=0; i<n; ++i)
		if (deg[i] & 1)
			if (v1 == -1)
				v1 = i;
			else if (v2 == -1)
				v2 = i;
			else
				bad = true;

	if (v1 != -1)
		++g[v1][v2],  ++g[v2][v1];

	stack<int> st;
	st.push (first);
	vector<int> res;
	while (!st.empty())
	{
		int v = st.top();
		int i;
		for (i=0; i<n; ++i)
			if (g[v][i])
				break;
		if (i == n)
		{
			res.push_back (v);
			st.pop();
		}
		else
		{
			--g[v][i];
			--g[i][v];
			st.push (i);
		}
	}

	if (v1 != -1)
		for (size_t i=0; i+1<res.size(); ++i)
			if (res[i] == v1 && res[i+1] == v2 || res[i] == v2 && res[i+1] == v1)
			{
				vector<int> res2;
				for (size_t j=i+1; j<res.size(); ++j)
					res2.push_back (res[j]);
				for (size_t j=1; j<=i; ++j)
					res2.push_back (res[j]);
				res = res2;
				break;
			}

	for (int i=0; i<n; ++i)
		for (int j=0; j<n; ++j)
			if (g[i][j])
				bad = true;

	if (bad)
		puts ("-1");
	else
		for (size_t i=0; i<res.size(); ++i)
			printf ("%d ", res[i]+1);

}
 
