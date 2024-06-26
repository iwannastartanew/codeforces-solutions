#include <bits/stdc++.h>
using namespace std;

long long lcm(long long a, long long b) {
    return (a * b) / __gcd(a, b);
}

int ceilDiv(int a, int b) {
    return (a + b - 1) / b;
}

template <typename T>
class myDict {
private:
    unsigned int RANDOM;
    function<T()> defaultFunc;
    unordered_map<unsigned int, T> dict;

public:
    myDict(function<T()> func) : RANDOM(rand()), defaultFunc(func) {}

    T& operator[](unsigned int key) {
        unsigned int myKey = RANDOM ^ key;
        if (dict.find(myKey) == dict.end()) {
            dict[myKey] = defaultFunc();
        }
        return dict[myKey];
    }

    void insert(unsigned int key, const T& value) {
        unsigned int myKey = RANDOM ^ key;
        dict[myKey] = value;
    }

    bool contains(unsigned int key) {
        return dict.find(RANDOM ^ key) != dict.end();
    }

    vector<pair<unsigned int, T>> items() {
        vector<pair<unsigned int, T>> result;
        for (auto& item : dict) {
            result.emplace_back(item.first ^ RANDOM, item.second);
        }
        return result;
    }
};

class mySet {
private:
    unsigned int RANDOM;
    unordered_set<unsigned int> set;

public:
    mySet() : RANDOM(rand()) {}

    void add(unsigned int key) {
        set.insert(key ^ RANDOM);
    }

    void remove(unsigned int key) {
        set.erase(key ^ RANDOM);
    }

    bool contains(unsigned int key) {
        return set.find(key ^ RANDOM) != set.end();
    }

    int size() {
        return set.size();
    }

    vector<unsigned int> elements() {
        vector<unsigned int> result;
        for (auto& item : set) {
            result.push_back(item ^ RANDOM);
        }
        return result;
    }
};

const int BUFSIZE = 8192;
class FastIO {
public:
    FastIO() {
        cin.tie(nullptr)->sync_with_stdio(false);
    }
};
FastIO fastio;

int main()
{
    int mod = 1e9 + 7;
    int T;
    cin >> T;
    while (T--) {
        int n, k;
        cin >> n >> k;
        vector<pair<int, int>> l(n);
        for (int i = 0; i < n; ++i) {
            cin >> l[i].first >> l[i].second;
        }
        sort(l.begin(), l.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
            return a.second < b.second;
        });

        int ans = 0;
        for (int i = 0; i < n; ++i) {
            int val = -l[i].second;
            priority_queue<int> pq;
            for (int j = i; j < n; ++j) {
                if (val + l[j].first + l[j].second <= k) {
                    pq.push(l[j].first);
                    val += l[j].first;
                } else {
                    while (!pq.empty() && pq.top() > l[j].first) {
                        val -= pq.top();
                        pq.pop();
                        if (val + l[j].first + l[j].second <= k) {
                            pq.push(l[j].first);
                            val += l[j].first;
                            break;
                        }
                    }
                }
                if (val + l[j].second <= k) {
                    ans = max(ans, (int)pq.size());
                }
            }
        }
        cout << ans << "\n";
    }
    return 0;
}
