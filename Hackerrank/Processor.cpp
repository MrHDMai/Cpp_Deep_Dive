/* Macros are instruction within the program declared by the # symbol, the compiler will first assesed these
directive before composition - the compiler will then process these directive before running the rest 
of the program. Consider the code snippet and include the macro in order to compiler the code*/

/*we shall place the macro here
*/
#define toStr(x) #x //the has variable stringize the variable
#define io(v) cin >> v
#define INF 10000000
#define foreach(v,i) for (int i = 0; i < v.size(); i++)
#define FUNCTION(name,op) void name(int& a, int b) {if(b op a) a = b;}
#include<iostream>
#include<vector>
using namespace std;

#if !defined toStr || !defined io || !defined FUNCTION || !defined INF
#error Missing preprocessor definitions
#endif 

FUNCTION(minimum, <)
FUNCTION(maximum, >)

int main(){
	int n; cin >> n;
	vector<int> v(n);
	foreach(v, i) {
		io(v)[i];
	}
	int mn = INF;
	int mx = -INF;
	foreach(v, i) {
		minimum(mn, v[i]);
		maximum(mx, v[i]);
	}
	int ans = mx - mn;
	cout << toStr(Result =) <<' '<< ans;
	return 0;

}