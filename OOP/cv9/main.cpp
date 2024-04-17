using namespace std;
#include <iostream>

#pragma region Client
class Client
{
    private:
        static int clientCount;
        int code;
        string name;
    public:
        static int GetObjectsCount();
        ~Client();
        Client(int c, string n);
        int GetCode();
        string GetName();
};

int Client::clientCount = 0;

Client::Client(int c, string n){
    Client::clientCount += 1;
    this->code = c;
    this->name = n;
}
Client::~Client(){
    Client::clientCount -= 1;
}
int Client::GetObjectsCount(){
    return Client::clientCount;
}
int Client::GetCode(){
    return this->code;
}
string Client::GetName(){
    return this->name;
}
#pragma endregion

#pragma region Account
class Account
{
    private:
        int number;
        double interestRate;
        Client *owner;
        static int accountCount;
    protected:
        double balance;
    public:
        static int GetObjectsCount();
        ~Account();
        Account (int n, Client *c);
        Account (int n, Client *c, double ir);

        int GetNumber();
        double GetBalance();
        double GetInterestRate();
        Client *GetOwner();
        bool CanWithdraw (double a);

        void Deposit (double a);
        bool Withdraw (double a); 
        void AddInterest();
};

int Account::accountCount = 0;

int Account::GetObjectsCount(){
    return Account::accountCount;
}

#pragma region constructo and basic
Account::~Account(){
    Account::accountCount--;
}

Account::Account(int n, Client *c){
    this->number = n;
    this->balance = 0;
    this->interestRate = 0;
    this->owner = c;
    Account::accountCount++;
}
Account::Account(int n, Client *c, double ir){
    this->number = n;
    this->balance = 0;
    this->interestRate = 0;
    this->owner = c;
    this->interestRate = ir;
    Account::accountCount++;
}

int Account::GetNumber(){
    return this->number;
}
double Account::GetBalance(){
    return this->balance;
}
double Account::GetInterestRate(){
    return this->interestRate;
}
Client* Account::GetOwner(){
    return this->owner;
}
#pragma endregion

bool Account::CanWithdraw(double a){
    return (this->balance >= a);
}
bool Account::Withdraw(double a){
    if (this->CanWithdraw(a))
    {
        this->balance -= a;
        return 1;
    }
    return 0;
}
void Account::AddInterest(){
    this->balance += this->balance * this->interestRate;
}
#pragma endregion

#pragma region creditaccount
class CreditAccount : public Account
{
private:
    double credit;
public:
    CreditAccount(int n, Client* o, double c);
    CreditAccount(int n, Client* o, double ir, double c);

    bool CanWithdraw(double a);
    bool Withdraw(double a);
};

CreditAccount::CreditAccount(int n, Client* o, double c) : Account(n, o)
{
    this->credit = c;
}
CreditAccount::CreditAccount(int n, Client* o, double ir, double c) : Account(n, o, ir)
{
    this->credit = c;
}
bool CreditAccount::CanWithdraw(double a){
    return (this->GetBalance() + this->credit >= a);
}
bool CreditAccount::Withdraw(double a){
    if (this->CanWithdraw(a))
    {
        this->balance -= a;
        return 1;
    }
    return 0;
}
#pragma endregion


int main()
{
    Client *o = new Client(0, "Smith");

    CreditAccount *ca = new CreditAccount(1, o, 1000);
    cout << ca->CanWithdraw(1000) << endl;

    Account *a = ca;
    cout << a->CanWithdraw(1000) << endl;

    cout << ca->Withdraw(1000) << endl;

    a = nullptr; 
    delete ca;

    return 0;
}