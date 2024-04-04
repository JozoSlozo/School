#include <iostream> 
using namespace std;
class KeyValue
{
    private:
        int key;
        double value;
        KeyValue *next;
    public:
        KeyValue(int k, double v);
        ~KeyValue();
        int GetKey();
        double GetValue();
        KeyValue* GetNext();
        KeyValue* CreateNext(int k, double v);
};
int KeyValue::GetKey(){
    return this->key;
}
double KeyValue::GetValue(){
    return this->value;
}

KeyValue::KeyValue(int k, double v)
{
    this->key = k;
    this->value = v; 
    this->next = nullptr;
}
KeyValue::~KeyValue()
{
    if (this->next != nullptr)
    {
        delete this->next;
        this->next = nullptr;
    }
}
KeyValue* KeyValue::GetNext()
{
    return this->next;
}
KeyValue* KeyValue::CreateNext(int k, double v)
{
    this->next = new KeyValue(k, v);
    return this->next;
}
//----------------------------------------------------------------------
class KeyString
{
private:
    int id;
    string value;
    KeyString *left;
    KeyString *right;
public:
    KeyString(int id, string value);
    ~KeyString();
    int GetId();
    string GetValue();
    KeyString *GetLeft();
    KeyString *GetRight();
    KeyString *CreateLeft(int id, string value);
    KeyString *CreateRight(int id, string value);
};
KeyString::KeyString(int id, string value)
{
    this->id = id;
    this->value = value;
    this->left = nullptr;
    this->right = nullptr;
}
KeyString::~KeyString()
{
    if (this->left != nullptr)
    {
        delete this->left;
        this->left = nullptr;
    }
    if (this->right != nullptr)
    {
        delete this->right;
        this->right = nullptr;
    }
}
int KeyString::GetId()
{
    return this->id;
}
string KeyString::GetValue()
{
    return this->value;
}
KeyString *KeyString::GetLeft()
{
    return this->left;
}
KeyString *KeyString::GetRight()
{
    return this->right;
}
KeyString *KeyString::CreateLeft(int id, string value)
{
    this->left = new KeyString(id, value);
    return this->left;
}
KeyString *KeyString::CreateRight(int id, string value)
{
    this->right = new KeyString(id, value);
    return this->right;
}


int main(){

    KeyValue *kv1 = new KeyValue(1,1.5);
    KeyValue *temp = kv1->CreateNext(2,2.5);
    for (int i = 3; i < 1000; i++)
    {
        KeyValue *temp2 = temp->CreateNext(i,i+0.5);
        temp = temp2;
    }
    delete temp;
    temp = nullptr;

    cout << kv1->GetKey() << endl;
    KeyValue *kvtemp = kv1->GetNext();
    while (kvtemp->GetNext() != nullptr)
    {
        KeyValue *kvtemp2 = kvtemp->GetNext();
        cout << kvtemp2->GetKey() << endl;
        kvtemp = kvtemp2;
    }

    KeyString *ks1 = new KeyString(1, "Stromy");
    ks1->CreateLeft(2, "jehličnany");
    ks1->CreateRight(3,"Listnaté");
    KeyString *ks1l = ks1->GetLeft();
    KeyString *ks1r = ks1->GetRight();
    

    //KeyValue *kv1 = new KeyValue(1,1.5);
    //cout << kv1->CreateNext(2,2.5)->GetKey() << endl;
    //KeyValue *kv2 = kv1->GetNext();
    //cout << kv2->GetNext() << endl;
    //delete kv1;
    //delete kv2;
    //kv1 = nullptr;
    //kv2 = nullptr;
    //cout << kv1->GetKey() << endl;
    //cout << kv2->GetKey() << endl;

    getchar();
    return 0;   
}