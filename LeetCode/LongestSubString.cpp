class solution{
public:
    int longeststring(string s){
        unorder_map<char,char> lastindex;
        int maxlength = 0;
        int left = 0;

        for(int right = 0; right < s.length(); right++){
            char c = s[right];

            if(lastindex.find(c) != lastindex.end() && lastindex[c] >=left){
                left = lastindex[c] + 1;
            }
            lastindex[c] = right;
            maxlength = max(maxlength, right-left+1);
        }
    }
    retun maxlenght;
}