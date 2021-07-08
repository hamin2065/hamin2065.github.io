#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdlib.h>
using namespace std;

int prime(int n){
   if((n == 0)||(n == 1))
      return 0;
   for(int i = 2;i*i<=n;i++){
         if(n%i == 0){
         return 0;
      }
   }
   return 1;
}

int main(string str) {
   vector <int> v;
   vector <string> m;
   vector <int> n;
   for (int i = 0; str[i] != '\0'; i++){ 
         v.push_back(str[i]-'0');
   }
    sort(v.begin(),v.end());
   vector <int> ind;
   for(int j = 1;j<=v.size();j++){
         ind.erase(ind.begin(), ind.end());
         for(int k = 0;k<j;k++){
         ind.push_back(1);
      }
      for(int k = 0;k<v.size()-j;k++){
      ind.push_back(0);
   }
   string s1;
   do{
            s1 = "";
            for (int i = 0; i < v.size(); i++)
            {
            if(ind[i]==1){
                  s1 += v[i]+'0';
                  }
            }
             m.push_back(s1);
   }while (next_permutation(v.begin(), v.end()));
}
   int a;
   for (int i = 0; i < m.size(); i++) {
         a = stoi(m[i]);
         n.push_back(a);
   }

   sort(n.begin(), n.end());
   n.erase(unique(n.begin(),n.end()),n.end());
   int count = 0;
   for(int i = 0;i<n.size();i++){  
         if(prime(n[i])==1){
             count +=1;
         }
   }
   cout << count;
}