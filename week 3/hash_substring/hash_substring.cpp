#include <iostream>
#include <string>
#include <vector>

using std::string;
typedef unsigned long long ull;

struct Data {
	string pattern, text;
};

Data read_input() {
	Data data;
	std::cin >> data.pattern >> data.text;
	return data;
}

void print_occurrences(const std::vector<int>& output) {
	for (size_t i = 0; i < output.size(); ++i)
		std::cout << output[i] << " ";
	std::cout << "\n";
}

std::vector<int> get_occurrences_naive(const Data& input) {
	const string& s = input.pattern, t = input.text;
	std::vector<int> ans;
	for (size_t i = 0; i + s.size() <= t.size(); ++i) {
		if (t.substr(i, s.size()) == s)
			ans.push_back(i);
	}
	return ans;
}

long long polyHash(const string& s, int prime, int x) {
	unsigned long long hash = 0;
	for (long long i = static_cast<long long> (s.size()) - 1; i >= 0; --i)
		hash = (hash * x + s[i]) % prime;
	return hash;
}

std::vector<long long> preComputeHashes(string text, int pLength, int p, int x) {
	int tLength = text.size();
	std::vector<long long> H(tLength - pLength + 1);
	string s = text.substr(tLength - pLength, pLength);
	H[tLength - pLength] = polyHash(s, p, x);
	long long y = 1;
	for (int i = 1; i <= pLength; ++i)
		y = y * x % p;
	for (int i = tLength - pLength - 1; i >= 0; --i) {
		long long preHash = x * H[i + 1] + text[i] - y * text[i + pLength];
		while (preHash < 0) {
			preHash += p;
		}
		H[i] = preHash % p;
	}
	return H;
}

bool areEqual(string s1, string s2){
	if (s1.size() != s2.size())
		return false;
	for (int i = 0; i < s1.size(); ++i) {
		if (s1[i] != s2[i])
			return false;
	}
	return true;
}

std::vector<int> get_occurrences(const Data& input) {
	int p = 1000000007;
	int x = rand() % (p-1) + 1;
	const string& s = input.pattern, t = input.text;
	std::vector<int> ans;

	long long pHash = polyHash(input.pattern, p, x);
	std::vector<long long> H = preComputeHashes(t, s.size(), p, x);
	for (size_t i = 0; i + s.size() <= t.size(); ++i) {
		if (pHash != H[i])
			continue;
		if (areEqual(t.substr(i, s.size()), s))
			ans.push_back(i);
	}
	return ans;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	print_occurrences(get_occurrences(read_input()));
	return 0;
}
