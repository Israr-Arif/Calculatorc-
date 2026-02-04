// #include <iostream>
// #include <vector>
// #include <stack>
// #include <string>
// #include <cctype>
// #include <cmath>
// using namespace std;


// const double PI = acos(-1.0);
// // ---------- Operator Precedence and Associativity ----------
// int prec(string c){
//     if( c=="sin" || c=="cos" || c=="tan" || c=="sqrt") return 4;
//     if(c=="^") return 3;
//     if(c=="*" || c=="/") return 2;
//     if(c=="+" || c=="-") return 1;
//     return -1;
// }

// bool isRightAssociative(char c){
//     return c=='^';
// }
// bool isFunction(const string &s){
//     return (s=="sin" || s=="cos" || s=="tan" || s=="sqrt");
// }
// bool isOperator(const string &s){
//     return (s=="+" || s=="-" || s=="*" || s=="/" || s=="^");
// }

// // ---------- Tokenize (numbers/operators/brackets) ----------
// vector<string> tokenize(string s){
//     vector<string> tokens;
//     int n =(int)s.size();

//     for(int i=0;i<n;i++){
//         if(s[i]==' ') continue;

//         // number (integer or decimal)
//         if(isdigit(s[i]) || s[i]=='.'){
//             string num="";
//             while(i<n && (isdigit(s[i]) || s[i]=='.')){
//                 num += s[i];
//                 i++;
//             }
//             i--;
//             tokens.push_back(num);
//         }
//         else if(isalpha(s[i])){
//             string word="";
//             while(i<n && isalpha(s[i])){
//                 word += s[i];
//                 i++;
//             }
//             i--;
//             tokens.push_back(word);
//         }
//         else{
//             string op(1, s[i]);
//             tokens.push_back(op);
//         }
//     }
//     return tokens;
// }

// // ---------- Infix to Postfix ----------
// vector<string> infixToPostfix(string infix){
//     vector<string> tokens = tokenize(infix);

//     stack<string> st;
//     vector<string> post;

//     for(int i=0;i<(int)tokens.size();i++){
//         string tk = tokens[i];

//         // number
//         if(isdigit(tk[0]) || (tk.size()>1 && tk[0]=='.') ){
//             post.push_back(tk);
//         } // constant pi
//         else if(tk == "pi"){
//             post.push_back(to_string(PI));
//         } // function
//         else if(isFunction(tk)){
//             st.push(tk);
//         }
//         // '('
//         else if(tk == "("){
//             st.push(tk);
//         }
//         // ')'
//         else if(tk == ")"){
//             while(!st.empty() && st.top() != "("){
//                 post.push_back(st.top());
//                 st.pop();
//             }
//             if(!st.empty()) st.pop(); // remove '('
//         }
//         // operator
//         else{
//             // ✅ unary minus handle
//             if(tk=="-" && (i==0 || tokens[i-1]=="(" || tokens[i-1]=="+" || tokens[i-1]=="-" ||
//                            tokens[i-1]=="*" || tokens[i-1]=="/" || tokens[i-1]=="^")){
//                 // treat unary minus as 0 - x
//                 post.push_back("0");
//             }

//             while(!st.empty() && st.top()!="("){
//                 string topOp = st.top();
//                 string curOp = tk;

//                 if(prec(topOp) > prec(curOp) ||
//                   (prec(topOp) == prec(curOp) && !isRightAssociative(curOp))){
//                     post.push_back(st.top());
//                     st.pop();
//                 }else break;
//             }
//             st.push(tk);
//         }
//     }

//     while(!st.empty()){
//         post.push_back(st.top());
//         st.pop();
//     }

//     return post;
// }

// // ---------- Evaluate Postfix ----------
// double evaluatePostfix(vector<string> post){
//     stack<double> st;

//     for(string tk : post){
//         // number
//         if(isdigit(tk[0]) || (tk.size()>1 && (isdigit(tk[1]) || tk[1]=='.')) || tk[0]=='.'){
//             st.push(stod(tk));
//         }
//         else{
//             double val1 = st.top(); st.pop();
//             double val2 = st.top(); st.pop();

//             double res = 0;
//             char op = tk[0];

//             if(op=='+') res = val2 + val1;
//             else if(op=='-') res = val2 - val1;
//             else if(op=='*') res = val2 * val1;
//             else if(op=='/') res = val2 / val1;
//             else if(op=='^') res = pow(val2, val1);

//             st.push(res);
//         }
//     }
//     return st.top();
// }

// // int main(){
// //     cout << "Enter expression: ";
// //     string infix;
// //     getline(cin, infix);

// //     vector<string> postfix = infixToPostfix(infix);

// //     cout << "Postfix: ";
// //     for(auto &x: postfix) cout << x << " ";
// //     cout << "\n";

// //     double ans = evaluatePostfix(postfix);
// //     cout << "Answer: " << ans << "\n";

// //     return 0;
// // }
// int main(){
//     string infix;
//     getline(cin, infix);

//     vector<string> postfix = infixToPostfix(infix);

//     // for(auto &x: postfix) cout << x << " ";
//     // cout << "\n";

//     double ans = evaluatePostfix(postfix);
//     cout << ans << "\n";

//     return 0;
// }
#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <cctype>
#include <cmath>

using namespace std;

const double PI = acos(-1.0);

int prec(const string &c){
    if(c=="sin" || c=="cos" || c=="tan" || c=="sqrt") return 4;
    if(c=="^") return 3;
    if(c=="*" || c=="/") return 2;
    if(c=="+" || c=="-") return 1;
    return -1;
}

bool isRightAssociative(const string &c){
    return c=="^";
}

bool isFunction(const string &s){
    return (s=="sin" || s=="cos" || s=="tan" || s=="sqrt");
}

bool isOperator(const string &s){
    return (s=="+" || s=="-" || s=="*" || s=="/" || s=="^");
}

// ---------- Tokenize ----------
vector<string> tokenize(string s){
    vector<string> tokens;
    int n = (int)s.size();

    for(int i=0;i<n;i++){
        if(s[i]==' ') continue;

        // number (integer/decimal)
        if(isdigit(s[i]) || s[i]=='.'){
            string num="";
            while(i<n && (isdigit(s[i]) || s[i]=='.')){
                num += s[i];
                i++;
            }
            i--;
            tokens.push_back(num);
        }
        // function names or constants like pi
        else if(isalpha(s[i])){
            string word="";
            while(i<n && isalpha(s[i])){
                word += s[i];
                i++;
            }
            i--;
            tokens.push_back(word);
        }
        // operators / brackets
        else{
            string op(1, s[i]);
            tokens.push_back(op);
        }
    }
    return tokens;
}

// ---------- Infix to Postfix ----------
vector<string> infixToPostfix(string infix){
    vector<string> tokens = tokenize(infix);

    stack<string> st;
    vector<string> post;

    for(int i=0;i<(int)tokens.size();i++){
        string tk = tokens[i];

        // number
        if(isdigit(tk[0]) || tk[0]=='.'){
            post.push_back(tk);
        }
        // constant pi
        else if(tk == "pi"){
            post.push_back(to_string(PI));
        }
        // function
        else if(isFunction(tk)){
            st.push(tk);
        }
        // '('
        else if(tk == "("){
            st.push(tk);
        }
        // ')'
        else if(tk == ")"){
            while(!st.empty() && st.top() != "("){
                post.push_back(st.top());
                st.pop();
            }
            if(!st.empty()) st.pop(); // pop '('

            // if there is a function on top, pop it too
            if(!st.empty() && isFunction(st.top())){
                post.push_back(st.top());
                st.pop();
            }
        }
        // operator
        else if(isOperator(tk)){

            // unary minus handling: -x => 0 - x
            if(tk=="-" && (i==0 || tokens[i-1]=="(" || isOperator(tokens[i-1]) || isFunction(tokens[i-1]))){
                post.push_back("0");
            }

            while(!st.empty() && st.top()!="("){
                string topOp = st.top();
                string curOp = tk;

                if(prec(topOp) > prec(curOp) ||
                  (prec(topOp) == prec(curOp) && !isRightAssociative(curOp))){
                    post.push_back(st.top());
                    st.pop();
                }else break;
            }
            st.push(tk);
        }
    }

    while(!st.empty()){
        post.push_back(st.top());
        st.pop();
    }

    return post;
}

double degToRad(double deg){
    return deg * (PI / 180.0);
}

// ---------- Evaluate Postfix ----------
double evaluatePostfix(vector<string> post){
    stack<double> st;

    for(string tk : post){

        // number
        if((tk.size()>=1 && (isdigit(tk[0]) || tk[0]=='.'))){
            st.push(stod(tk));
        }
        // function
        else if(isFunction(tk)){
            double x = st.top(); st.pop();
            double res = 0;

            if(tk=="sin") res = sin(degToRad(x));
            else if(tk=="cos") res = cos(degToRad(x));
            else if(tk=="tan") res = tan(degToRad(x));
            else if(tk=="sqrt") res = sqrt(x);

            st.push(res);
        }
        // operator
        else{
            double val1 = st.top(); st.pop();
            double val2 = st.top(); st.pop();

            double res = 0;
            if(tk=="+") res = val2 + val1;
            else if(tk=="-") res = val2 - val1;
            else if(tk=="*") res = val2 * val1;
            else if(tk=="/") res = val2 / val1;
            else if(tk=="^") res = pow(val2, val1);

            st.push(res);
        }
    }
    return st.top();
}

int main(){
    string infix;
    getline(cin, infix);

    vector<string> postfix = infixToPostfix(infix);
    double ans = evaluatePostfix(postfix);

    cout << ans << "\n";
    return 0;
}
