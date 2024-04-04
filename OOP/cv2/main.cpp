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

KeyValue::KeyValue(int k, double v){
    this->key = k;
    this->value = v;
}

int KeyValue::GetKey(){
    return this->key;
}
double KeyValue::GetValue(){
    return this->value;
}

class mail{
    private:
        string prijemce;
        string odesilatel;
        string obsah;
    public:
        string GetPrijemce();
        string GetOdesilatel();
        string GetObsah();
        mail(string p, string o, string b);
        mail* Odpoved(string obsah);
        string Odeslat();
};
string mail::GetPrijemce(){
    return this->prijemce;
}
string mail::GetOdesilatel(){
    return this->odesilatel;
}
string mail::GetObsah(){
    return this->obsah;
}
mail::mail(string p, string o, string b){
    this->prijemce = p;
    this->odesilatel = o;
    this->obsah = b;
}
mail* mail::Odpoved(string obsah){
    return new mail(this->odesilatel, this->prijemce, obsah);
}
string mail::Odeslat(){
    return "odesilatel: "+this->odesilatel + "\nprijemce: " + this->prijemce +"\nobsah: "+this->obsah;
}


class osoba{
    private:
        string rodnecislo;
        string jmeno;
        string prijmeni;
    public:
        osoba(string r, string j, string p);
        string GetDatumNarozeni();
        string GetPohlavi();
        string GetCeleJmeno();
};
osoba::osoba(string r, string j, string p){
    this->rodnecislo = r;
    this->jmeno = j;
    this->prijmeni = p;
}
string osoba::GetCeleJmeno(){
    return this->jmeno + " " + this->prijmeni;
}
string osoba::GetPohlavi(){
    string temp;
    temp += this->rodnecislo[2];
    temp += this->rodnecislo[3];
    if (stoi(temp) > 49)
    {
        return "žena";
    }
    return "muž";
}


int main(){
    mail *m1 = new mail("Pepa", "Joza", "ahoj");
    mail *odpoved = m1->Odpoved("nazdar");
    cout << m1->Odeslat() << endl;
    cout << "\n";
    cout << odpoved->Odeslat() << endl;
    cout << "\n";
    delete m1;
    delete odpoved;

    osoba *o1 = new osoba("0405068555", "Joza", "Dujka");
    cout << o1->GetCeleJmeno() << endl;
    cout << o1->GetPohlavi() << endl;


    getchar();
    return 0;
}