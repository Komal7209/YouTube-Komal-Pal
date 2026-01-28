//Q1:  There is a string and substr.some question marks are given in string, whcih need to be replaced by substr characters. If we cannot get that substr then we ned to return -1 else return smallest possible substr.
//Q2: there is a n*4 matrix given, where userId, no.ofshares, biddingprice, timestamp. and totalShares are given. On the basis of highest bidding price we need to allocate shares. If bidding price is same then on the basis of smallest timestamp, we need to allocate share. Then we need to return useriuds in ascending order for those who have not been allocated with any shares.
//[[1,2,3,0], [2,3,4,1]]


auto cmp=[&](vector<vector<int>>a, vector<vector<int>>b){
    if(a[2]==b[2])return a[3]<b[3];
    return a[2] > b[2];
}

sort(a.begin(),a.end(), cmp);

//q1:

#include <bits/stdc++.h>
using namespace std;

string smallestStringWithSubstring(string s, string sub) {
    int n = s.size();
    int m = sub.size();
    string answer = "";

    for (int i = 0; i + m <= n; i++) {
        bool canPlace = true;

        // Check if sub can be placed at index i
        for (int j = 0; j < m; j++) {
            if (s[i + j] != '?' && s[i + j] != sub[j]) {
                canPlace = false;
                break;
            }
        }

        if (!canPlace) continue;

        // Create a candidate string
        string temp = s;

        // Place sub
        for (int j = 0; j < m; j++) {
            temp[i + j] = sub[j];
        }

        // Replace remaining '?' with 'a'
        for (char &c : temp) {
            if (c == '?') c = 'a';
        }

        // Update lexicographically smallest answer
        if (answer.empty() || temp < answer) {
            answer = temp;
        }
    }

    return answer.empty() ? "-1" : answer;
}

int main() {
    string s, sub;
    cin >> s >> sub;
    cout << smallestStringWithSubstring(s, sub);
    return 0;
}


// q2:

#include <bits/stdc++.h>
using namespace std;

vector<int> getUnallocatedUsers(vector<vector<int>>& bids, int totalShares) {
    // bids[i] = {userId, shares, price, timestamp}

    // Sort by:
    // 1. Higher bidding price
    // 2. Smaller timestamp
    sort(bids.begin(), bids.end(), [](auto &a, auto &b) {
        if (a[2] != b[2])
            return a[2] > b[2];     // higher price first
        return a[3] < b[3];         // earlier timestamp first
    });

    unordered_map<int, int> allocated; // userId -> allocated shares

    for (auto &bid : bids) {
        if (totalShares == 0) break;

        int userId = bid[0];
        int requested = bid[1];

        int give = min(requested, totalShares);
        allocated[userId] += give;
        totalShares -= give;
    }

    vector<int> result;

    for (auto &bid : bids) {
        int userId = bid[0];
        if (allocated[userId] == 0) {
            result.push_back(userId);
        }
    }

    sort(result.begin(), result.end());
    return result;
}
