#include<bits/stdc++.h>
using namespace std;
int ind;
int dx[]={1,0,0,-1};
int dy[]={0,-1,1,0};
int ans=0;
int n,cnt = 0;
vector<vector<int>> A;
vector<int> r(3);
bool check(int x,int y)
{
    if(x<0 || x>=n || y<0 || y>=n || A[x][y] == 0) return false;
    return true;
}
int random(int x,int y) {
    std::random_device rd;  
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(x, y);
    return distrib(gen);
}
void func1(int row,int col)
{
    if(A[row][col] == 0) 
        return;
    vector<pair<int,pair<int,int>>> v;
    for(int i=0;i<4;i++)
    {
        int nx=row+dx[i];
        int ny=col+dy[i];
        if(check(nx,ny)){
            v.push_back({A[nx][ny],{nx,ny}});
        }
    }
    sort(v.begin(),v.end());
    for(int i=0;i<v.size();i++) {
        if(v[i].first%r[ind]==0)
        {
            ans+=A[v[i].second.first][v[i].second.second]/r[ind];
            A[v[i].second.first][v[i].second.second]/=r[ind];
            A[row][col] = 0;
            cnt--;
            if(A[v[i].second.first][v[i].second.second]==1) 
            {
                A[v[i].second.first][v[i].second.second]=0;
                cnt--;
            }
            func1(v[i].second.first,v[i].second.second);
            return;
        }
    }
    reverse(v.begin(), v.end());
    for(int i=0;i<v.size();i++) {
        if(r[ind]%v[i].first==0)
        {
            ans+=r[ind]/A[v[i].second.first][v[i].second.second];
            A[row][col]/=A[v[i].second.first][v[i].second.second];
            A[v[i].second.first][v[i].second.second] = 0;
            cnt--;
            if(A[row][col]==1) 
            {
                A[row][col]=0;
                cnt--;
            }
            func1(row,col);
            return;
        }
    }
}
void rec()
{
    if(cnt==n*n) return;
    cout<<'\n';
    r[0]=random(2,100);
    r[1]=random(2,100);
    r[2]=random(2,100);
    cout<<r[0]<<' '<<r[1]<<' '<<r[2]<<'\n';
    cout<<"Choose any of one no. in zero indexing :";
    cin>>ind;
    cout<<'\n';
    int row,col;
    cout<<"choose row and col in zero indexing :";
    cin>>row>>col;
    cout<<'\n';
    if(A[row][col] != 0) {
        rec();
        return;
    }
    A[row][col] = r[ind];
    cnt++;
    func1(row,col);
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            cout<<A[i][j]<<' ';
        }
        cout<<'\n';
    }
    cout<<"Your current score is :"<<ans<<'\n';
    rec();
}
signed main()
{
    cout<<"enter size of grid : ";
    cin>>n;
    A.resize(n, vector<int>(n, 0));
    int row=random(0,n-1);
    int col=random(0,n-1);
    A[row][col] = random(2,100);
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            cout<<A[i][j]<<' ';
        }
        cout<<'\n';
    }
    rec();
    cout<<"ans " << ans<<'\n';
} 
