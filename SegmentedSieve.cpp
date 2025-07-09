#include <bits/stdc++.h>
using namespace std;

#define ll long long

const ll N = 1000000;

bool isPrime[N + 1];

void sieveOfEratosthenes(){
    
    isPrime[0] = isPrime[1] = false;
    
    for(ll i=2; i<=N; i++) isPrime[i] = true;

    for(ll i=2; i*i<=N; i++){
        if(isPrime[i]){
            for(ll j=i*i; j<=N; j+=i)
               isPrime[j] = false; 
        }
    }

}


vector<ll>GeneratePrimes(ll n){
   vector<ll>ds;
   
   for(ll i=2; i<=n; i++) if(isPrime[i]) ds.push_back(i);

   return ds;
}


void solve() {
    ll l,r;
    cin>>l>>r;

    vector<ll>primes = GeneratePrimes(sqrt(r));

    vector<bool>dummy(r-l+1, true);
    
    if(l == 1) dummy[l - 1] = false;

    for(auto i : primes){
      ll firstMultiple = (l/i) * i;

      if(firstMultiple < l) firstMultiple +=i;

      for(ll j=max(firstMultiple, i*i); j<=r; j+=i) dummy[j - l] = false;
      
    }
    
    for(ll i=l; i<=r; i++)if(dummy[i-l]) cout<<i<<endl;

    cout<<endl;
}


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    sieveOfEratosthenes();  
    ll t;
    cin >> t;

    for (ll i = 0; i < t; i++) {
        solve();
    }
    return 0;
}