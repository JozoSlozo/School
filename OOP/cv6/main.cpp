#include <iostream>
using namespace std;

#pragma region pacient
class pacient
{
private:
    string Jmeno;
    string Nemoc;
public:
    pacient(string j, string n);
    string GetJmeno();
    string GetNemoc();
};
pacient::pacient(string j, string n){
    this->Jmeno = j;
    this->Nemoc = n;
}
string pacient::GetJmeno(){
    return this->Jmeno;
}
string pacient::GetNemoc(){
    return this->Nemoc;
}
#pragma endregion

#pragma region zamestnanec
class zamestnanec
{
private:
    string Jmeno;
    string Pozice;
public:
    zamestnanec(string j, string p);
    string GetJmeno();
    string GetPozice();
};
zamestnanec::zamestnanec(string j, string p){
    this->Jmeno = j;
    this->Pozice = p;
}
string zamestnanec::GetJmeno(){
    return this->Jmeno;
}
string zamestnanec::GetPozice(){
    return this->Pozice;
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
    pacient* VytvoritPacienta(string j, string n);
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
pacient* pokoj::VytvoritPacienta(string j, string n){
    if (this->JeMisto())
    {
        this->Pacienti[this->PacientiCount] = new pacient(j, n);
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
    zamestnanec** Zamestnanci;
    int ZamestnanciCount;
    pokoj** Pokoje;
    int PokojeCount;
public:
    nemocnice(int z, int p);
    ~nemocnice();
    zamestnanec* VytvoritZamestnance(string j, string p);
    zamestnanec* GetZamestnance(string j);
    pokoj* VytvoritPokoj(int c, int l);
    pokoj* GetPokoj(int c);
    pokoj** GetVolnePokoje(int& len);
    bool PridelitPokoj(string j, string n);
};
nemocnice::nemocnice(int z, int p){
    this->Zamestnanci = new zamestnanec*[z];
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
zamestnanec* nemocnice::VytvoritZamestnance(string j, string p){
    this->Zamestnanci[this->ZamestnanciCount] = new zamestnanec(j, p);
    this->ZamestnanciCount++;
    return this->Zamestnanci[this->ZamestnanciCount-1];
}
pokoj* nemocnice::VytvoritPokoj(int c, int l){
    this->Pokoje[this->PokojeCount] = new pokoj(c, l);
    this->PokojeCount++;
    return this->Pokoje[this->PokojeCount-1];
}
zamestnanec* nemocnice::GetZamestnance(string j){
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
bool nemocnice::PridelitPokoj(string j, string n){
    for (int i = 0; i < this->PokojeCount; i++)
    {
        if (Pokoje[i]->JeMisto())
        {
            Pokoje[i]->VytvoritPacienta(j, n);
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
    nem->PridelitPokoj("pepa", "rak");
    nem->PridelitPokoj("joza", "horecka");
    int len = 0;
    pokoj** temp = nem->GetVolnePokoje(len);
    for (int i = 0; i < len; i++)
    {
        cout << "cislo pokoje: " << temp[i]->GetCislo() << " volne luzka: " << temp[i]->PocetvolnychMist() << endl;
    }
    return 0;
}