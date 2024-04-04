using namespace std;
#include <iostream>

#pragma region Client
class Client
{
    private:
        static int objetsCount;
        int code;
        string name;
    public:
        static int GetObjectsCount();
        Client(int c, string n);
        int GetCode();
        string GetName();
};
Client::Client(int c, string n){
    this->code = c;
    this->name = n;
    Client::objetsCount++;
}
Client::~Client(){
    Client::objetsCount--;
}
int Client::GetObjectsCount(){
    return Client::objetsCount;
}
int Client::GetCode(){
    return this->code;
}
string Client::GetName(){
    return this->name;
}
#pragma endregion

class StaticValue
{
private:
    static int value;
    StaticValue();
public:
    static void IncValue();
    static int GetValue();
};

int StaticValue::value = 0;

void StaticValue::IncValue(){
    StaticValue::value++;
}
int StaticValue::GetValue(){
    return StaticValue::value;
}
int main(){
    cout << StaticValue::GetValue() << endl;
    StaticValue::IncValue();
    cout << StaticValue::GetValue() << endl;

    //StaticValue *sv = new StaticValue();
    //cout << sv->GetValue() << endl;

    return 0;
}