#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <algorithm>
#include <set>
#include <map>
#include <math.h>
#include <cmath>
#include <queue>
#include <iomanip>
#include <bitset>
#include <unordered_map>
#include <stack>
#include <memory.h>
#include <list>
#include <numeric>
#include <functional>
#include <complex>
#include <cassert>
#include <climits>

#define ll long long
#define ld long double
#pragma comment (linker, "/STACK:5000000000")
#define ull unsigned ll
#define all(x) (x).begin(),(x).end()
#define rall(x) (x).rbegin(),(x).rend()
#define pii pair<int,int>
#define vi vector<int>
#define vpii vector<pii>
#define vvi vector<vector<int>>
#define forn(it,from,to) for(int (it)=from; (it)<to; (it)++)
int  Inf = 2e9;
ll LINF = (ll)4e18;
ll mod = 1e9 + 7;


#define M_PI 3.14159265358979323846 

using namespace std;

map<char, int> operatorPriority;
void initPriority() {
    operatorPriority['^'] = 4;
    operatorPriority['~'] = 3;
    operatorPriority['*'] = 2;
    operatorPriority['/'] = 2;
    operatorPriority['+'] = 1;
    operatorPriority['-'] = 1;
    operatorPriority['('] = 0;
}

int getPriority(char opr_char){
    return operatorPriority[opr_char];
}

string buildReversePolishNotation(string inputString){
    string ans = "";
    char flg = 1;
    stack<char> st;
    for(int i=0; i < inputString.size(); i++){
        if (inputString[i]>='0' && inputString[i]<='9'){
            ans = ans+ inputString[i];
            flg = 0;
        } else{
            if(flg == 0){
                ans += ' ';
            }
            flg = 1;
            if (inputString[i]!=' '){
                if (inputString[i]!=')' && inputString[i]!='('){
                int prio = getPriority(inputString[i]);
                if (prio<3){
                   
                    while (!st.empty() && prio<=getPriority(char(st.top()))){
                        char c = st.top();
                        ans = ans + c + ' ';
                        st.pop();
                    }
                    st.push(inputString[i]);
                } else{
                    while (!st.empty() && prio<getPriority(char(st.top()))){
                        char c = st.top();
                        ans = ans + c + ' ';
                        st.pop();
                    }
                    st.push(inputString[i]);
                }
                } else{
                    if (inputString[i]=='('){
                        st.push(inputString[i]);
                    } else{
                        char c = st.top();
                        while(c!='('){
                            
                            ans = ans + c + ' ';
                            st.pop();
                            c = st.top();
                        }
                        st.pop();
                    }
                }
                
            }
        }
    }
    while (!st.empty()) {
        char c = st.top();
        if (ans.back()!=' ') ans+=' ';
        ans = ans + c + ' ';
        st.pop();
    }
    return ans;
}

pair<ll, char>add(ld x, ld y){
    if ((x+y)>LLONG_MAX || (x+y)<LLONG_MIN){
        return {-1, 0};
    } else{
        return {(ll)(x+y), 1};
    }
}
pair<ll, char>sub(ld x, ld y){
    if (x-y>LLONG_MAX || x-y<LLONG_MIN)
        return {-1, 0};
    else{
        return {(ll)(x-y), 1};
    }
}

pair<ll, char> mul(ld x, ld y){
    if (x*y>LLONG_MAX || x*y<LLONG_MIN)
        return {-1, 0};
    return {x*y, 1};
}

pair<ll, char> step(ld x, ld y){
    
    pair<ll, char> q = {1,1};
    for(int i=1; i<=y; i++){
        q = mul(q.first, x);
        if (q.second == 0){
            return {-1, 0};
        }
    }
    return q;
}

int main(int argc, const char * argv[])
{    for(int i = 0; i < argc; i++){
        if((string)argv[i] == "_DEBUG"){
            freopen("input.txt", "r", stdin);freopen("output.txt", "w", stdout);
        }
    }
    freopen("input.txt", "r", stdin);freopen("output.txt", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    string str;
    getline(cin, str);
    initPriority();
    char flg = 0;
    string ans = buildReversePolishNotation(str);
    int i = 0;
    
    cout << ans<<endl;
    stack<ll> st1;
    
    char zn = 0;
    i = 0;
    ll digit = 0;
    flg = 0;
    while (i < ans.size()) {
        
        if (ans[i] >= '0' && ans[i] <= '9') {
            flg = 1;
            ll lst = digit;
            digit = digit*10 + ans[i] - '0';
            if (lst>digit){
                cout<<"Error"<<endl;
                return 0;
            }
            
        }
        else {
            if (flg == 1) {
                
                st1.push(digit);
                
                flg = 0;
                zn = 0;
                digit = 0;
            }
            if (ans[i] != ' ') {
                zn = 0;
                flg = 0;
                digit = 0;
                if (ans[i] == '~') {
                    ll k = st1.top();
                    st1.pop();
                    st1.push(-k);
                }
                if (ans[i] == '-') {
                    ll x,  y;
                    y = st1.top();
                    st1.pop();
                    x = st1.top();
                    st1.pop();
                    pair<ll, char> q = sub(x, y);
                    if (q.second==0) {
                        cout<<"Error"<<endl;
                        return 0;
                    } else st1.push(q.first);
                }
                if (ans[i] == '+') {
                    ll x,  y;
                    y = st1.top();
                    st1.pop();
                    x = st1.top();
                    st1.pop();
                
                    pair<ll, char> q = add(x, y);
                    if (q.second==0) {
                        cout<<"Error"<<endl;
                        return 0;
                    } else st1.push(q.first);
                }
                if (ans[i] == '*') {
                    ll x,  y;
                    y = st1.top();
                    st1.pop();
                    x = st1.top();
                    st1.pop();
                    pair<ll, char> q = mul(x, y);
                    if (q.second==0) {
                        cout<<"Error"<<endl;
                        return 0;
                    } else st1.push(q.first);
                    
                }
                if (ans[i] == '/') {
                    ll x,  y;
                    y = st1.top();
                    st1.pop();
                    x = st1.top();
                    st1.pop();
                    if (y == 0) {
                        cout << "Error" << endl;
                        return 0;
                    }
                    st1.push(x/y);
                }
                if (ans[i] == '^') {
                    ll x, y;
                    y = st1.top();
                    st1.pop();
                    x = st1.top();
                    st1.pop();
                    if (y < 0) {
                        if (x==1){
                             st1.push(1);
                        }else{
                             st1.push(0);
                        }
                    }else{
                        if (x==1)st1.push(1); else{
                        pair<ll, char> q = step(x, y);
                        if (q.second==0) {
                            cout<<"Error"<<endl;
                            return 0;
                        } else st1.push(q.first);
                            
                        }
                    }
                }
            }
            
            
        }
        i++;
    }
    cout << st1.top();
    return 0;
}