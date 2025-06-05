#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include <functional>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;
    int n = s.size();

    // Count the number of question marks in the pattern.
    int m = 0;
    for (char c : s) {
        if(c == '?')
            m++;
    }
    
    // Read the costs for each "?" in the order of appearance.
    vector<long long> a(m), b(m);
    for (int i = 0; i < m; i++){
         cin >> a[i] >> b[i];
    }
    
    // Initial total cost: assume every '?' becomes ')'
    long long totalCost = 0;
    // We will build the answer in this string.
    string ans = s;
    
    // Priority queue (min-heap) to hold candidates.
    // Each candidate is a pair: {delta, index} where
    // delta = a[i] - b[i], the extra cost to flip a '?' (which was set as ')' by default)
    // to '('.
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    
    int questionIndex = 0; // index into cost arrays for each '?'
    int balance = 0;       // current balance = (# of '(') - (# of ')')
    
    // Process every character in order.
    for (int i = 0; i < n; i++){
         if(s[i] == '(') {
             balance++;
         }
         else if(s[i] == ')') {
             balance--;
         }
         else { // character is '?'
              // Initially, assume replacement as ')':
              totalCost += b[questionIndex];
              ans[i] = ')';
              balance--;            
              // Save candidate: flipping from ')' to '(' will cost (a - b)
              pq.push({a[questionIndex] - b[questionIndex], i});
              questionIndex++;
         }
         // If balance falls below 0, fix it by flipping some earlier '?'
         while(balance < 0 && !pq.empty()){
              auto candidate = pq.top();
              pq.pop();
              // Flip that candidate: change from ')' to '('.
              ans[candidate.second] = '(';
              // Add the extra cost (which can be negative – a saving)
              totalCost += candidate.first;
              // This flip changes the balance by +2 (instead of -1, it becomes +1).
              balance += 2;
         }
         // If balance is negative and we have no candidate, no valid sequence exists.
         if(balance < 0) { 
             cout << -1;
             return 0;
         }
    }
    
    // At the end, the balance must be 0 for a correct bracket sequence.
    if(balance != 0){
         cout << -1;
         return 0;
    }
    
    cout << totalCost << "\n" << ans;
    return 0;
}
