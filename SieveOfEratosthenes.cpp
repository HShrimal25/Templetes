#include <bits/stdc++.h>
using namespace std;

#define ll long long

void sieveOfEratosthenes(ll n, vector<ll>& isPrime){
    
    isPrime[0] = isPrime[1] = false;

    for(ll i=2; i*i<=n; i++){
        if(isPrime[i]){
            for(ll j=i*i; j<=n; j+=i)
               isPrime[j] = false; 
        }
    }

}

void solve() {
   ll n;
   cin>>n;

   vector<ll>isPrime(n+1, true);

   sieveOfEratosthenes(n, isPrime);

   for(ll i=1; i<=n; i++) if(isPrime[i]) cout<<i<<" ";
   cout<<endl;
   
}


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    ll t;
    cin >> t;

    for (ll i = 0; i < t; i++) {
        solve();
    }
    return 0;
}
