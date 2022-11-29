#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void problema1();

void problema2();

int main(int argc , char** argv) {
    int c;
    cin >> c;
    if (c==1) {
        problema1();
    }
    if (c==2) {
        problema2();
    }
    return 0;
}

void problema1(){
    vector<int> vec(0);

    int k1;
    int vec_size=0;
    int sol_size=0;
    int cont_size=0;
    int res=0;
    int conta=0;
    
    while(1){
        cin >> k1;
        vec.push_back(k1);
        vec_size++;
        if(cin.get()=='\n'){
            break;
        }
    }
    int sol[vec_size];
    int cont[vec_size];

    for(int i=0; i < vec_size ; i++){
        sol[i]=1;
        sol_size++;
        cont[i]=1;
        cont_size++;
    }
    
   
    for (int i=1;i < vec_size ; i++){
        for (int j=0 ; j<i ; j++){
            if(vec[j]<vec[i]){
                if(sol[j]+1 > sol[i]){
                    sol[i]= sol[j] +1;
                    cont[i] = cont[j];
                }
                else if (sol[j]+1 == sol[i]){
                    cont[i]+=cont[j];
                }
            }
        }
    }
    for(int i=0 ; i < sol_size ;i++){
        if (sol[i] > res ){
            res = sol[i];
        }
    }
    for (int i=0 ;i <vec_size ; i++){
        if (sol[i] == res ){
            conta = conta + cont[i];
        }
    }
    cout << res << ' ' << conta << endl ;
  
}


void problema2(){
    vector<int> vec1(0);
    vector<int> vec2(0);
    vector<int> sorted(0);
    int k1;
    int k2;
    int vec1_size=0;
    int vec2_size=0;
    int sorted_size=0; 
    int res=0;

    while (1) {
        cin >> k1;
        vec1.push_back(k1);
        sorted.push_back(k1);
        vec1_size++;
        sorted_size++; 

        if (cin.get()=='\n') {
            break;
        }
    }
    sort(sorted.begin(), sorted.end());
    while (1) {
        cin >> k2;
        if (binary_search(sorted.begin() , sorted.end() ,k2) ){
            vec2.push_back(k2);
            vec2_size++;
        }
        if (cin.get()=='\n') {
            break;
        }
    }
    
    int aux[vec2_size];
    for (int k=0 ; k<vec2_size ; k++) {
        aux[k]=0;
    }

    for (int i=0; i<vec1_size ; i++) {
        int cur=0;
        for (int j=0 ; j<vec2_size ; j++) {
            if (vec1[i]==vec2[j]) {
                aux[j]=max(aux[j],cur+1);
            }
            if (vec1[i]>vec2[j]) {
                cur=max(cur,aux[j]);
            }
        }
    }

    for (int p=0 ; p<vec2_size ; p++) {
        res=max(res,aux[p]);
    }

    cout << res << endl;
}