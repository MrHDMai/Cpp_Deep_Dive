#include<iostream>
#include<vector>
using namespace std;

class addingNum{
public: 
    vector<int> addnum(vector<int>& num, int target){
        for(int i = 0; i < num.size(); i++){
            for(int j = i + 1; j < num.size(); j++){
                if(num[i] + num[j] == target){
                    return {i,j};
                }
            }
        }
        return {};
    }
};

int main(){
    int target = 11;
    vector<int> v{2,3,5,6,7,8,1,3,4,6};
    addingNum ad;
    vector<int> result = ad.addnum(v,target);
    int index1 = result[0];
    int index2 = result[1];
    int* val1 = &v[index1];
    int* val2 = &v[index2];

    cout << result[0]<<":"<< *val1<<" "<<result[1]<<":" <<*val2;

} 