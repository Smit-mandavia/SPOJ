#include<bits/stdc++.h>
using namespace std;
 
#define ll long long int
#define FIO ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0)
#define mod 1000000007

int main() {

    FIO; // for fast input output
    
    int temp=1,temp2=1,n,v,i;
    bool flag;
    char t;
    string s;
    
    stack <char> str;  // for formula
    stack <int> val;  // for value
    
    val.push(0);  // push before doing anything
    
    cin >> s;  
    n=(int)s.length(); // cheking size of input string
    
    for(i=0;i<n;i++){
        
	if(s[i]==')'){     
            
	    if(i+1<n && s[i+1]>'1' && s[i+1]<='9')
                temp=s[++i]-'0';
            else
                temp=1;
            
            do{
                flag=true;
                
                t=str.top();
                str.pop();
                
                switch(t){
                    case '(': 
                                v=val.top();
                                val.pop();
                                v=(v*temp)+val.top();
                                break; 
                    case 'C':
                                v=val.top();
                                v+=12*temp2;
                                break;
                    case 'H':  
                                v=val.top();
                                v+=1*temp2;
                                break;
                    case 'O':
                                v=val.top();
                                v+=16*temp2;
                                break;
                    default :
                                flag=false; // make it false if t is a number
                                temp2=t-'0';    
                }
                
                if(flag){ // if t was not a number
                    temp2=1;
                    val.pop();
                    val.push(v);
                }
                
            }  
            while(t!='(');
            
        }
        else{  // if input is not  ')' then keep pushing it..
            str.push(s[i]);
            if(s[i]=='(')  //  if input is '(' then push a "0" to stack of value..
                val.push(0);
        }
        
    }
    
    // this loop is for elements without any bracket like "COOH"   
    // or for 'H' in "H(COOH)2"
    while(!(str.empty())){
        
        flag=true;
        t=str.top();
        str.pop();
        
        switch(t){ // no chance that input is a bracket.. (why ?? think... :D)
            case 'C':
                        v=val.top();
                        v+=12*temp2;
                        break;
            case 'H':  
                        v=val.top();
                        v+=1*temp2;
                        break;
            case 'O':
                        v=val.top();
                        v+=16*temp2;
                        break;
            default : // for numbers
                        flag=false;
                        temp2=t-'0';    
        }
        
        if(flag){ //same as above
                temp2=1;
                val.pop();
                val.push(v);
        }
 
    }
    
    
    cout << val.top(); // output the only number in stack which is our answer
    
    return 0;
}
