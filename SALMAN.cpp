#include<bits/stdc++.h>
using namespace std;

#define ll long long int
#define FIO ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0)
#define mod 1000000007
#define SIZE 100001
#define MAX 262143 // Why? :D

ll salary[SIZE],id[SIZE],s[SIZE],e[SIZE]; // for dfs part
vector<ll> v[SIZE];

ll seg1[MAX],seg2[MAX],lazy[MAX],newID; // for lazy segtree part seg1 for sum tree , seg2 for min tree..


// DFS function
void dfs(ll oldID){

    id[newID]=oldID;
    s[oldID]=newID;

    for(ll i=0;i<v[oldID].size();i++){
        newID++;
        dfs(v[oldID][i]);
    }

    e[oldID]=newID;

}


struct segResult{
ll mini;
ll sum;
}result;



void buildSegtree(ll index, ll start , ll end){

    lazy[index]=0;

    if(start==end){
        seg1[index]=seg2[index]=salary[id[start]];
        return;
    }

    ll mid=(start+end)/2;

    buildSegtree(index*2+1,start,mid);
    buildSegtree(index*2+2,mid+1,end);

    seg1[index]=seg1[index*2+1]+seg1[index*2+2];
    seg2[index]=(ll)min(seg2[index*2+1],seg2[index*2+2]);

}





// segtree range sum and min query function
void query(ll index, ll start , ll end , ll rangeStart , ll rangeEnd ){

    if(start>rangeEnd || end<rangeStart){// out of range
        return ;
    }

    if(lazy[index]!=0){

        seg1[index]+=(end-start+1)*lazy[index];
        seg2[index]+=lazy[index];

        if(start!=end){
            lazy[index*2+1]+=lazy[index];
            lazy[index*2+2]+=lazy[index];
        }
        lazy[index]=0;
    }

    if(start>=rangeStart && end<=rangeEnd){ // fully within range
        result.sum+=seg1[index];
        result.mini=(ll)min(result.mini,seg2[index]);
        return;
    }

    ll mid=(start+end)/2;

    query(index*2+1,start,mid,rangeStart,rangeEnd);
    query(index*2+2,mid+1,end,rangeStart,rangeEnd);

}

// segtree range update query..
void update(ll index, ll start , ll end , ll rangeStart , ll rangeEnd ,ll val){

    if(lazy[index]!=0){

        seg1[index]+=(end-start+1)*lazy[index];
        seg2[index]+=lazy[index];

        if(start!=end){
            lazy[index*2+1]+=lazy[index];
            lazy[index*2+2]+=lazy[index];
        }

        lazy[index]=0;
    }

    if(start>rangeEnd || end<rangeStart){// out of range
        return ;
    }


    if(start>=rangeStart && end<=rangeEnd){ // fully within range
        seg1[index]+=(end-start+1)*val;
        seg2[index]+=val;

        if(start!=end){
            lazy[index*2+1]+=val;
            lazy[index*2+2]+=val;
        }

        return;
    }

    ll mid=(start+end)/2;

    update(index*2+1,start,mid,rangeStart,rangeEnd,val);
    update(index*2+2,mid+1,end,rangeStart,rangeEnd,val);

    seg1[index]=seg1[index*2+1]+seg1[index*2+2];
    seg2[index]=(ll)min(seg2[index*2+1],seg2[index*2+2]);

}


int main(){
    FIO;
    ll t,n,q,k,i,j,m;
    cin >> t;
    for(m=1;m<=t;m++){
        cout << "Case " << m << ":\n";
        cin >> n >> q;

        for(i=1;i<=n;i++){
            cin >> j >> salary[i];
            v[j].push_back(i);
        }

        newID=1;

        dfs(1); // starting dfs with managing director...

        buildSegtree(0,1,n);

        while(q--){
            cin >> j >> k;
            result.sum=0;
            result.mini=LLONG_MAX;
            query(0,1,n,s[k],e[k]);

            if(j==1)
                cout << result.sum << endl;
            else
                update(0,1,n,s[k],e[k],(ll)min(result.mini,(ll)1000));

        }

        if(m!=t)
        for(i=0;i<=n;i++)
            v[i].clear();
    }
	return 0;
}
