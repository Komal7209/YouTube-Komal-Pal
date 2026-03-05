//Here cmp must be a type, not a function. That is why we write:
struct cmp {
    bool operator()(pair<int,int> a, pair<int,int> b) {
        return a.second > b.second;
    }
};
//This creates a callable object.

priority_queue<pair<int,int>, vector<pair<int,int>>, cmp> pq;
// priority_queue does not take a function pointer directly in the same way sort does.
//Instead it expects a type for the comparator.

// Here operator():
/*

operator() is called the function call operator in C++.
It allows an object of a class or struct to behave like a function.
In simple words, it lets you call an object using parentheses.

*/
// eg:
#include <iostream>
using namespace std;

struct Add {
    int operator()(int a, int b) {
        return a + b;
    }
};

int main() {
    Add add;
    cout << add(3, 4);
}

// same required for following ds:
// priority_queue
// set
// map
// multiset
// multimap