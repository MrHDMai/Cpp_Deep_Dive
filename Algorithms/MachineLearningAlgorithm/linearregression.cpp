#include<iostream>
#include<vector>

using namespace std;

pair<double, double> linearregression(const vector<double>& x, const vector<double>& y){
    if(x.size() != y.size()){
        throw invalid_argument("x and y vector must be the same length");
    }
    int n = x.size();
    double sumx = 0, sumy = 0, sumxy = 0, sumx2 = 0;
    for(int i = 0; i < n; i++){
        sumx +=x[i];
        sumy +=y[i];
        sumxy +=x[i] * y[i];
        sumx2 += x[i]*x[i];
    }
    double m = (n*sumxy-sumx*sumy)/(n*sumx2-sumx-sumx);
    double b = (sumy-m*sumx)/n;
    return {m,b};
}

double predict(double x, double m, double b){
    return m*x+b;
}

int main(){
    vector<double>x = {1,2,3,4,5};
    vector<double>y = {2,4,5,4,5};

    try{
        auto[m,b] = linearregression(x,y);
        cout <<"Fitted line: y = " << m << "x + " << b << endl;
        double x_test;
        cout<<"Enter x value to predict y: ";
        cin >> x_test;
        cout << "Predict y = " << predict(x_test,m,b) << endl;
    }
    catch(const exception& e){
        cerr << "Error: " << e.what() << endl;
    }
}