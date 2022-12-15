//
//  main.cpp
//  ISLab14
//
//  Created by Snow Lukin on 15.12.2022.
//

#include <iostream>

//#include <bits/stdc++.h>
using namespace std;
#define ld long long

ld ModInv(ld b, ld n){
  ld r1=n,r2=b,t1=0,t2=1;
  while(r2>0){
    ld q=r1/r2;
    ld r=r1-q*r2;
    r1=r2;r2=r;
    ld t=t1-q*t2;
    t1=t2;t2=t;
  }
  if(t1<0)t1+=n;
  return t1;
}

ld powerLL(ld x, ld n, ld MOD) {
    ld result = 1;
    while (n) {
        if (n&1)
            result = result * x % MOD;
        n = n / 2;
        x = x * x % MOD;
    }
    return result;
}

ld powerStrings(string sa, string sb, ld MOD) {

    ld a = 0, b = 0;
    for (int i = 0; i < sa.length(); i++)
        a = (a * 10 + (sa[i] - '0')) % MOD;

    for (int i = 0; i < sb.length(); i++)
        b = (b * 10 + (sb[i] - '0')) % (MOD - 1);
    return powerLL(a, b, MOD);
}

ld mod(string num, ld a) {
    ld res = 0;

    // One by one process all digits of 'num'
    for (int i = 0; i < num.length(); i++)
        res = (res*10 + (int)num[i] - '0') %a;

    return res;
}




int main(int argc, const char * argv[]){
  ld p=709,q=59,e0,d=14,r=13,hm=100;
  // cin>>p>>q>>e0>>d>>hm>>r;
  ld a,b,t,e1,e2,s1,s2,v;
  
  // for(int i=1;i<=708;i++){
    e0=187;
  e1=powerStrings(to_string(e0),to_string((p-1)/q),p);if(e1<0)e1+=p;
  e2=powerStrings(to_string(e1),to_string(d),p);if(e2<0)e2+=p;
  
  s1=powerStrings(to_string(e1),to_string(r),p);if(s1<0)s1+=p;
  s1=s1%q;
  
  s2=(((hm%q+(d*s1)%q)%q)*ModInv(r,q))%q;
  
  //////////// V
  a=powerStrings(to_string(e1),to_string(hm*ModInv(s2,q)),p);
  b=powerStrings(to_string(e2),to_string(s1*ModInv(s2,q)),p);
  v=(a*b)%q;
  
  
  // if(s1==v)cout<<e0<<"\n";
  
  cout<<"e1="<<e1<<"\n";
  cout<<"e2="<<e2<<"\n";
  cout<<"s1="<<s1<<"\n";
  cout<<"s2="<<s2<<"\n";
  cout<<"v="<<v<<"\n";
  // }
}
