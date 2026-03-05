// 1. Comparator for simple sorting
// Ascending order:

bool cmp(int a, int b) {
    return a < b;
}

// Usage:

sort(arr.begin(), arr.end(), cmp); // Because sort() accepts a normal function pointer as a comparator, thus no struct required
// Meaning: place a before b if a is smaller.

//----------------------

// Descending order:

bool cmp(int a, int b) {
    return a > b;
}

//----------------------
// 2. Comparator for pair

// Sort by second element:

bool cmp(pair<int,int> a, pair<int,int> b) {
    return a.second < b.second;
}

// Example:

// (1,5)
// (2,2)
// (3,4)

// Sorted by second:

// (2,2)
// (3,4)
// (1,5)

//----------------------
// 3. Multi condition comparator (very common)

// Sort by:
// first ascending
// second descending

bool cmp(pair<int,int> a, pair<int,int> b) {

    if (a.first == b.first)
        return a.second > b.second;

    return a.first < b.first;
}

// Logic:

// primary rule
// tie breaker