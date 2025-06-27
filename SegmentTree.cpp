#include <bits/stdc++.h>
using namespace std;

#define ll long long

class SGTree{
    vector<ll>seg;

public :     

    SGTree(ll n){
        seg.resize(4 * n + 1);
    }

    void build(ll ind, ll low, ll high, vector<ll>& arr){
        if(low==high){
            seg[ind] = arr[low];
            return; 
        }
        
        ll mid = (low+high) / 2; 
        build(2*ind+1, low, mid, arr);
        build(2*ind+2, mid+1, high, arr);

        seg[ind] = min(seg[2*ind+1], seg[2*ind+2]);
    }

    ll query(ll ind, ll low, ll high, ll l, ll r){
        // No overlap 
        // [low high] [l r] | [l r] [low high]

        if(high < l || r < low){
            return INT_MAX;
        }

        // Complete Overlap 
        // [l low high r]

        if(l<=low && high<=r){
            return seg[ind];
        }

        // partial Overlap 
        ll mid = (low+high) / 2;

        ll left = query(2*ind+1, low, mid, l, r);
        ll right = query(2*ind+2, mid+1, high, l, r);

        return min(left, right);
    }

    void update(ll ind, ll low, ll high, ll i, ll val){
        if(low==high){
            seg[ind] = val;
            return;
        } 

        ll mid = (low+high)/2;
        if(i <= mid)
            update(2*ind+1, low, mid, i, val);
        else    
            update(2*ind+2, mid+1, high, i, val);

        seg[ind] = min(seg[2*ind+1], seg[2*ind+2]);    
    }
};



void solve() {

    ll n1;
    cin>>n1;

    vector<ll>arr1(n1);
    SGTree sg1(n1);

    for(ll i=0; i<n1; i++) 
        cin>>arr1[i];
    
    sg1.build(0, 0, n1-1, arr1);

    ll n2;
    cin>>n2;

    vector<ll>arr2(n2);
    SGTree sg2(n2);

    for(ll i=0; i<n2; i++) 
        cin>>arr2[i];
    
    sg2.build(0, 0, n2-1, arr2);
    
    ll q;
    cin>>q;
    
    while(q--){
        ll type; 
        cin>>type;

        if(type==1){
            ll l1,r1,l2,r2;
            cin>>l1>>r1>>l2>>r2;

            ll mn1 = sg1.query(0, 0, n1-1, l1, r1);
            ll mn2 = sg2.query(0, 0, n2-1, l2, r2);

            cout<<min(mn1, mn2)<<endl;
        }

        else{
           ll arrno,i,val;
           cin>>arrno>>i>>val;
           
            if(arrno == 1){
               sg1.update(0, 0, n1-1, i, val);
               arr1[i] = val;
            }

            else{
               sg2.update(0, 0, n2-1, i, val);
               arr2[i] = val;
            }

        }
    }
}


int main() {
    // ios_base::sync_with_stdio(0);
    // cin.tie(0);
    // cout.tie(0);
    ll t;
    cout<<"Test Cases : ";
    cin >> t;

    for (ll i = 0; i < t; i++) {
        solve();
    }
    return 0;
}