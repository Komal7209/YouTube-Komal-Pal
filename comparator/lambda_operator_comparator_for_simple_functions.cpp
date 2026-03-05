// for int:
sort(v.begin(), v.end(), [](int a, int b) {
    return a < b;
});

// For pair:

sort(v.begin(), v.end(), [](auto &a, auto &b) {
    return a.second < b.second;
});