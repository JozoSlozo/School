#include <iostream>
#include <string>
using namespace std;

const int StackSize = 100;

struct Stack
{
    char Items[StackSize];
    int StackPointer;
};

void Init(Stack& S){
    S.StackPointer = 0;
}
void Push(Stack& S, const char x){
    S.Items[S.StackPointer] = x;
    S.StackPointer += 1;
}
char Pop(Stack& S){
    S.StackPointer -= 1;
    return S.Items[S.StackPointer];
}
char Top(const Stack& S){
    return S.Items[S.StackPointer-1];
}
bool IsEmpty(const Stack& S){
    return S.StackPointer == 0;
}
bool IsFull(const Stack& S){
    return S.StackPointer == StackSize;
}
void clear(Stack& S){
    S.StackPointer = 0;
}
void Test(Stack& S){
    string pes = "asdasdasdasdasd";
    for (int i = 0; i < 10; i++)
    {
        Push(S, pes[i]);
    }
    cout << Pop(S) << endl;
}
bool CheckParantheses(string text){
    Stack stack;
    Init(stack);
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (text[i] == '(')
        {
            Push(stack, '(');
        }
        else if(text[i] == ')' && Pop(stack) != '('){
            return false;
        }
        else if (text[i] == '{')
        {
            Push(stack, '{');
        }
        else if(text[i] == '}' && Pop(stack) != '{'){
            return false;
        }  
        else if (text[i] == '[')
        {
            Push(stack, '[');
        }
        
        else if(text[i] == ']' && Pop(stack) != '['){
            return false;
        }     
    }
    if (!IsEmpty(stack))
    {   
        return false;
    }
    return true;
}
int main()
{
    Stack stack;
    Init(stack);
    cout << CheckParantheses("()") << endl;
    return 0;
}