#include <bits/stdc++.h>
using namespace std;

int main() {
    long n;
    cin >> n;
    long a[n];
    map<long, long> mp;
    for(int i = 0; i < n; i++){
        cin >> a[i];
        mp[a[i]]++;
    }
    for(int i = 0; i < n; i++){
        if(mp[a[i]] > 1){
            cout << "0\n";
            mp[a[i]] = 0;
        }
        else if(mp[a[i]] == 1) cout << "0\n";
        else cout << "1\n";
    }
    return 0;
}
