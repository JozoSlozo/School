#include <iostream>
#include <stack>
using std::cout, std::endl, std::stack, std::string;

string PopPush(stack<string>& s){
    string x = s.top();
    s.pop();
    return x;
}

bool CheckHtmlTags(string text){
    stack<string> S;
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (text[i] == '<')
        {
            string tag;
            int a = 0;//lenght of tag
            for (int l = i; text[l] != '>'; l++){a++;}
            tag = text.substr(i+1, a-1);
            if (tag[0] == '/' && PopPush(S) != tag.substr(1))//if tag is closing and top of stack is different
            {
                return false;
            }
            else if (tag[0] != '/'){//if opening tag
                S.push(tag);
            }
            
        }
    }
    if(!S.empty()){
        return false;
    }
    return true;
}

int main(){
    string pes = "pespes";
    cout << CheckHtmlTags("<ass><pes>pespes</pes></ass>") << endl;
    return 0; 
}