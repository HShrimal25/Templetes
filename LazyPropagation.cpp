#include <bits/stdc++.h>
using namespace std;

#define ll long long

class SGTree{
public : 
    vector<ll>seg;
    vector<ll>lazy;

    SGTree(ll n){
        seg.resize(4 * n + 1);
        lazy.resize(4 * n + 1);
    }

    void build(ll ind, ll low, ll high, vector<ll>& arr){
        if(low==high){
            seg[ind] = arr[low];
            return;
        }

        ll mid = (low+high) >> 1;

        build(2*ind+1, low, mid, arr);
        build(2*ind+2, mid+1, high, arr);

        seg[ind ] = seg[2 * ind + 1] + seg[2 * ind + 2];
    }

    void update(ll ind, ll low, ll high, ll l, ll r, ll val){

        if(lazy[ind] != 0){
            seg[ind] += (high - low + 1) * lazy[ind];
            
            if(low != high){
                lazy[2 * ind + 1] +=lazy[ind];
                lazy[2 * ind + 2] +=lazy[ind];
            }

            lazy[ind] = 0;
        }

        // Compelete Overlap [l low high r]
        // update the node, lazy propagate down & return

        if(l<=low && high<=r){
            seg[ind] += (high - low + 1) * val;

            if(low != high){
                lazy[2*ind+1] += val;
                lazy[2*ind+2] += val;
            }

            return;
        }

        // No Overlap [l r] [low high] or [low high] [l r]

        if(r < low || high < l)
            return;
        
        // Partial Overlap  
        ll mid = (low + high) >> 1;
        
        update(2 * ind + 1, low, mid, l, r, val);
        update(2 * ind + 2, mid+1, high, l, r, val);

        seg[ind] = seg[2 * ind + 1] + seg[2 * ind + 2];

    }

    ll query(ll ind, ll low, ll high, ll l, ll r){

        // if prev update remaining, the do it to get fresh value 
        // and Also propagate down 

        if(lazy[ind] != 0){
            seg[ind] += (high - low + 1) * lazy[ind];
            
            if(low != high){
                lazy[2 * ind + 1] +=lazy[ind];
                lazy[2 * ind + 2] +=lazy[ind];
            }

            lazy[ind] = 0;
        }

        // Compelete Overlap [l low high r]
        if(l<=low && high<=r) return seg[ind];

        // No Overlap [l r] [low high] or [low high] [l r]

        if(r < low || high < l)
            return 0;

        // Partial Overlap  
        ll mid = (low + high) >> 1;

        ll left = query(2 * ind + 1, low, mid, l, r);
        ll right = query(2 * ind + 2, mid+1, high, l, r);

        return left + right;
             
    }

};

void solve() {
    ll n;
    cin>>n;

    vector<ll>arr(n);
    
    for(ll i=0; i<n; i++)
       cin>>arr[i];

    SGTree st(n);
    st.build(0, 0, n-1, arr); 

    ll q;
    cin>>q; 

    while(q--){
        ll type; 
        cin>>type;

        if(type==1){
            ll l,r;
            cin>>l>>r;

            cout<<st.query(0, 0, n-1, l, r)<<endl;
        }

        else{
           ll l,r,val;
           cin>>l>>r>>val;

           st.update(0, 0, n-1, l, r, val);
        }
    }


}


int main() {
    // ios_base::sync_with_stdio(0);
    // cin.tie(0);
    // cout.tie(0);
    ll t;
    // cin >> t;
    t = 1;
    for (ll i = 0; i < t; i++) {
        solve();
    }
    return 0;
}