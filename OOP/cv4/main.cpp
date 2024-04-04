#include <iostream>
using namespace std;

class KeyValue
{
    private:
        int key;
        double value;
    public:
        KeyValue(int k, double v);
        int GetKey();
        double GetValue();
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
}
class KeyValues
{
    private:
        KeyValue** keyValues;
        int count;
        int len;
    public:
        KeyValues(int n);
        ~KeyValues();
        KeyValue* CreateObject(int k, double v);
        KeyValue* SearchObject(int key);
        KeyValue* RemoveObject(int key);
        int Count();
        int GetLen();

};
int KeyValues::GetLen(){
    return this->len;
}
KeyValues::KeyValues(int n){
    this->keyValues = new KeyValue*[n];
    this->count = 0;
    this->len = n;
}
KeyValues::~KeyValues(){
    for (int i = 0; i < this->count; i++)
    {
        delete this->keyValues[i];
    }
    delete[] this->keyValues;
}
int KeyValues::Count(){
    return this->count;
}
KeyValue* KeyValues::CreateObject(int k, double v){
    KeyValue* newObject = new KeyValue(k, v);

    this->keyValues[this->count] = newObject;
    this->count += 1;

    return newObject;
}
KeyValue* KeyValues::SearchObject(int key){
    for (int i = 0; i < this->count; i++)
    {
        if (this->keyValues[i]->GetKey() == key)
        {
            return this->keyValues[i];
        }
        
    }
    return nullptr;
}
KeyValue* KeyValues::RemoveObject(int key){
    KeyValue** temp = new KeyValue*[this->len];
    KeyValue* temp2 = nullptr;
    int a = 0;
    for (int i = 0; i < this->count; i++)
    { 
        if (this->keyValues[i]->GetKey() == key)
        {
            temp2 = this->keyValues[i];
            continue;
        }
        temp[a] = this->keyValues[i];
        a++;
    }
    this->keyValues = temp;
    this->count -= 1;
    return temp2;
}

class Osoba
{
private:
    string jmeno;
    string adresa;
public:
    Osoba(string x, string y);
    string GetJmeno();
};
Osoba::Osoba(string x, string y)
{
    this->jmeno = x;
    this->adresa = y;
}
string Osoba::GetJmeno(){
    return this->jmeno;
}

class PolozkaFaktury
{
private:
    string nazev;
    int cena;
public:
    PolozkaFaktury(string x, int y);
    int GetCena();
};
PolozkaFaktury::PolozkaFaktury(string x, int y)
{
    this->nazev = x;
    this->cena = y;
}
int PolozkaFaktury::GetCena(){
    return this->cena;
}

class Faktura
{
private:
    int cislo;
    Osoba* ososba;
    PolozkaFaktury** faktury;
    int pocetFaktur;
public:
    Faktura(int x, Osoba* y, int len);
    ~Faktura();
    PolozkaFaktury* VytvoritFakturu(string x, int y);
    int GetCelkovaCena();
    string GetInformace();
    int VytvoritFaktury(string* x, int *y, int pocet);
};
PolozkaFaktury* Faktura::VytvoritFakturu(string x, int y){
    PolozkaFaktury* temp = new PolozkaFaktury(x, y);
    this->faktury[this->pocetFaktur] = temp;
    this->pocetFaktur += 1;
    return temp;
}
int Faktura::VytvoritFaktury(string* x, int* y, int pocet){
    for (int i = 0; i < pocet; i++)
    {
        this->VytvoritFakturu(x[i], y[i]);
    }
    return 0;
}
Faktura::Faktura(int x, Osoba* y, int len)
{
    this->cislo = x;
    this->ososba = y;
    this->faktury = new PolozkaFaktury*[len];
    this->pocetFaktur = 0;
}
Faktura::~Faktura()
{
    delete this->ososba;
    for (int i = 0; i < this->pocetFaktur; i++)
    {
        delete this->faktury[i];
    }
    delete[] this->faktury;
}
int Faktura::GetCelkovaCena(){
    int tempCena = 0;
    for (int i = 0; i < this->pocetFaktur; i++)
    {
        tempCena += this->faktury[i]->GetCena();
    }
    return tempCena;
}
string Faktura::GetInformace(){
    char temp[100];
    sprintf(temp, "jméno: %s, čislo: %d, počet položek: %d, celková cena: %d", this->ososba->GetJmeno().c_str(), this->cislo, this->pocetFaktur, this->GetCelkovaCena());
    return temp;
}
int main(){
    /*
    int N = 5;
    KeyValues* myKeyValues = new KeyValues (N);

    KeyValue* myKeyValue = myKeyValues->CreateObject(0, 0.5); 
    for (int i = 1; i < N; i++)
    {
        myKeyValues->CreateObject(i, i + 0.5);
    }

    for (int i = 0; i < myKeyValues->Count(); i++)
    {
        cout << myKeyValues->SearchObject(i)->GetValue() << endl;
    }
    cout << "removed Object: ";
    cout << myKeyValues->RemoveObject(2)->GetValue() << endl;
    cout << "after remove: \n";
    for (int i = 0; i < myKeyValues->GetLen(); i++)
    {
        if (myKeyValues->SearchObject(i) != nullptr)
        {
            cout << myKeyValues->SearchObject(i)->GetValue() << endl;
            continue;
        }
        cout << "key not found" << endl;
    }
    
    
    delete myKeyValues;
    */
    Faktura* faktura = new Faktura(4520, new Osoba("Jan Novák", "Praha 68"), 5);
    string nazvy[5] = {"jablka", "hrusky", "pes", "les", "kniha"};
    int ceny[5] = {50,120,5,4500,600};
    faktura->VytvoritFaktury(nazvy, ceny, 5);
    cout << faktura->GetCelkovaCena() << endl;
    cout << faktura->GetInformace() << endl;
    
    
    return 0;
}