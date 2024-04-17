#include <iostream>
using namespace std;

#pragma region clovek
class clovek
{
private:
    string jmeno;
    string email;
    string telefoniCislo;
    int rokNarozeni;
public:
    clovek(string j, string e, string t, int r);
    int GetVek();
    string GetJmeno();
};

clovek::clovek(string j, string e, string t, int r)
{
    this->jmeno = j;
    this->email = e;
    this->telefoniCislo = t;
    this->rokNarozeni = r;
}
int clovek::GetVek(){
    return 2024 - this->rokNarozeni;
}
string clovek::GetJmeno(){
    return this->jmeno;
}
#pragma endregion
#pragma region pacient
class pacient : public clovek
{
private:
    int cislo;
    string Nemoc;
public:
    pacient(string j, string e, string t, string n, int r, int c);
    string GetNemoc();
};
pacient::pacient(string j, string e, string t, string n, int r, int c) : clovek(j, e, t, r){
    this->Nemoc = n;
    this->cislo = c;
}

string pacient::GetNemoc(){
    return this->Nemoc;
}
#pragma endregion
#pragma region zamestnanec
class doktor : public clovek
{
private:
    string Pozice;
    int smena;
    pacient** osetruje;
    int osetrujecount;
public:
    doktor(string j, string e, string t, int r, string p);
    string GetPozice();
    pacient* NastavitOSetruje(pacient* p);
};
doktor::doktor(string j, string e, string t, int r, string p) : clovek(j, e, t, r){
    this->Pozice = p;
    this->smena = 0;
    this->osetruje = new pacient*[10];
    this->osetrujecount = 0;
}
string doktor::GetPozice(){
    return this->Pozice;
}
pacient* doktor::NastavitOSetruje(pacient* p){
    this->osetruje[this->osetrujecount] = p;
    this->osetrujecount += 1;
    return this->osetruje[this->osetrujecount-1];
}
#pragma endregion
#pragma region pokoj
class pokoj
{
private:
    int CisloPokoje;
    int Luzka;
    pacient** Pacienti;
    int PacientiCount;
public:
    pokoj(int c, int l);
    ~pokoj();
    pacient* VytvoritPacienta(string j, string e, string t, string n, int r, int c);
    pacient* GetPacienta(string j);
    pacient* OdebratPacienta(string j);
    int GetCislo();
    bool JeMisto();
    int PocetvolnychMist();
};
pokoj::pokoj(int c, int l){
    this->CisloPokoje = c;
    this->Luzka = l;
    this->Pacienti = new pacient*[l];
    this->PacientiCount = 0;
}
pokoj::~pokoj(){
    for (int i = 0; i < this->PacientiCount; i++)
    {
        delete this->Pacienti[i];
    }
    delete[] this->Pacienti;
}
pacient* pokoj::VytvoritPacienta(string j, string e, string t, string n, int r, int c){
    if (this->JeMisto())
    {
        this->Pacienti[this->PacientiCount] = new pacient(j, e, t, n, r, c);
        this->PacientiCount++;
        return this->Pacienti[this->PacientiCount-1];
    }
    return nullptr;
}
pacient* pokoj::GetPacienta(string j){
    for (int i = 0; i < this->PacientiCount; i++)
    {
        if(this->Pacienti[i]->GetJmeno() == j){
            return this->Pacienti[i];
        }
    }
    return nullptr;
}
pacient* pokoj::OdebratPacienta(string j){
    pacient** temp = new pacient*[this->Luzka];
    pacient* temp2 = nullptr;
    int a = 0;
    for (int i = 0; i < this->PacientiCount; i++)
    { 
        if (this->Pacienti[i]->GetJmeno() == j)
        {
            temp2 = this->Pacienti[i];
            continue;
        }
        temp[a] = this->Pacienti[i];
        a++;
    }
    this->Pacienti = temp;
    this->PacientiCount -= 1;
    return temp2;
}
int pokoj::GetCislo(){
    return this->CisloPokoje;
}
bool pokoj::JeMisto(){
    if (this->PacientiCount >= this->Luzka)
    {
        return 0;
    }
    return 1;
}
int pokoj::PocetvolnychMist(){
    if (this->JeMisto())
    {
        return this->Luzka - this->PacientiCount;
    }
    return 0;
}
#pragma endregion
#pragma region nemocnice
class nemocnice
{
private:
    doktor** Zamestnanci;
    int ZamestnanciCount;
    pokoj** Pokoje;
    int PokojeCount;
public:
    nemocnice(int z, int p);
    ~nemocnice();
    doktor* VytvoritZamestnance(string j, string e, string t, int r, string p);
    doktor* GetZamestnance(string j);
    pokoj* VytvoritPokoj(int c, int l);
    pokoj* GetPokoj(int c);
    pokoj** GetVolnePokoje(int& len);
    bool PridelitPokoj(string j, string e, string t, string n, int r, int c);
};
nemocnice::nemocnice(int z, int p){
    this->Zamestnanci = new doktor*[z];
    this->ZamestnanciCount = 0;
    this->Pokoje = new pokoj*[p];
    this->PokojeCount = 0;
}
nemocnice::~nemocnice(){
    for (int i = 0; i < this->ZamestnanciCount; i++)
    {
        delete this->Zamestnanci[i];
    }
    delete[] Zamestnanci;
    for (int i = 0; i < this->PokojeCount; i++)
    {
        delete this->Pokoje[i];
    }
    delete[] Pokoje;
}
doktor* nemocnice::VytvoritZamestnance(string j, string e, string t, int r, string p){
    this->Zamestnanci[this->ZamestnanciCount] = new doktor(j, e, t, r, p);
    this->ZamestnanciCount++;
    return this->Zamestnanci[this->ZamestnanciCount-1];
}
pokoj* nemocnice::VytvoritPokoj(int c, int l){
    this->Pokoje[this->PokojeCount] = new pokoj(c, l);
    this->PokojeCount++;
    return this->Pokoje[this->PokojeCount-1];
}
doktor* nemocnice::GetZamestnance(string j){
    for (int i = 0; i < this->ZamestnanciCount; i++)
    {
        if(this->Zamestnanci[i]->GetJmeno() == j){
            return this->Zamestnanci[i];
        }
    }
    return nullptr;
}
pokoj* nemocnice::GetPokoj(int c){
    for (int i = 0; i < this->PokojeCount; i++)
    {
        if(this->Pokoje[i]->GetCislo() == c){
            return this->Pokoje[i];
        }
    }
    return nullptr;
}
pokoj** nemocnice::GetVolnePokoje(int& len){
    pokoj** temp = new pokoj*[this->PokojeCount];
    int temp2 = 0;
    for (int i = 0; i < this->PokojeCount; i++)
    {
        if(this->Pokoje[i]->JeMisto()){
            temp[temp2] = this->Pokoje[i];
            temp2++;
        }
    }
    len = temp2;
    return temp;
}
bool nemocnice::PridelitPokoj(string j, string e, string t, string n, int r, int c){
    for (int i = 0; i < this->PokojeCount; i++)
    {
        if (Pokoje[i]->JeMisto())
        {
            Pokoje[i]->VytvoritPacienta(j, e, t, n, r, c);
            return 1;
        }
    }
    return 0;
}
#pragma endregion

int main(){
    nemocnice* nem = new nemocnice(5, 5);
    nem->VytvoritPokoj(1,3);
    nem->VytvoritPokoj(2,4);
    nem->PridelitPokoj("joza", "joza@seznam.cz", "60354785", "horecka", 1965, 1);
    nem->PridelitPokoj("pepa", "pepa@seznam.cz", "65247856", "noha", 1970, 2);
    int len = 0;
    pokoj** temp = nem->GetVolnePokoje(len);
    for (int i = 0; i < len; i++)
    {
        cout << "cislo pokoje: " << temp[i]->GetCislo() << " volne luzka: " << temp[i]->PocetvolnychMist() << endl;
    }
    return 0;
}