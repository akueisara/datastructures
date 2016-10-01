#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::string;
using std::vector;
using std::cin;

struct Query {
    string type, s;
    size_t ind;
};

class QueryProcessor {
    long long bucket_count;
    // store all strings in one vector
    vector<string> elems;
	vector<vector<string> > hashTable;
    size_t hash_func(const string& s) const {
		static const size_t multiplier = 263;
		static const size_t prime = 1000000007;
        unsigned long long hash = 0;
        for (long long i = static_cast<long long> (s.size()) - 1; i >= 0; --i)
            hash = (hash * multiplier + s[i]) % prime;
        return hash % bucket_count;
    }

public:
    explicit QueryProcessor(long long bucket_count): bucket_count(bucket_count) {
		hashTable = vector<vector<string>>(bucket_count);
	}

    Query readQuery() const {
        Query query;
        cin >> query.type;
        if (query.type != "check")
            cin >> query.s;
        else
            cin >> query.ind;
        return query;
    }

    void writeSearchResult(bool was_found) const {
        std::cout << (was_found ? "yes\n" : "no\n");
    }

    void processQuery_naive(const Query& query) {
        if (query.type == "check") {
            // use reverse order, because we append strings to the end
            for (long long i = static_cast<long long>(elems.size()) - 1; i >= 0; --i)
                if (hash_func(elems[i]) == query.ind)
                    std::cout << elems[i] << " ";
            std::cout << "\n";
        } else {
            vector<string>::iterator it = std::find(elems.begin(), elems.end(), query.s);
            if (query.type == "find")
                writeSearchResult(it != elems.end());
            else if (query.type == "add") {
                if (it == elems.end())
                    elems.push_back(query.s);
            } else if (query.type == "del") {
                if (it != elems.end())
                    elems.erase(it);
            }
        }
    }

    void processQuery(const Query& query) {
        if (query.type == "check") {
            for (long long i = static_cast<long long>(hashTable[query.ind].size()) - 1; i >= 0; --i)
                if (hash_func(hashTable[query.ind][i]) == query.ind)
                    std::cout << hashTable[query.ind][i] << " ";
            std::cout << "\n";
        } else {
            vector<string>::iterator it = std::find(hashTable[hash_func(query.s)].begin(), hashTable[hash_func(query.s)].end(), query.s);
            if (query.type == "find")
                writeSearchResult(it != hashTable[hash_func(query.s)].end());
            else if (query.type == "add") {
                if (it == hashTable[hash_func(query.s)].end())
                    hashTable[hash_func(query.s)].push_back(query.s);
            } else if (query.type == "del") {
                if (it != hashTable[hash_func(query.s)].end())
                    hashTable[hash_func(query.s)].erase(it);
            }
        }
    }

    void processQueries() {
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i)
            processQuery(readQuery());
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    long long bucket_count;
    cin >> bucket_count;
    QueryProcessor proc(bucket_count);
    proc.processQueries();
    return 0;
}
