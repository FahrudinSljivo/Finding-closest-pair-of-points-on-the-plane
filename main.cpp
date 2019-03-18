#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

/* Kao priprema za izradu samog rada, tj. pronalaženja dvije najbliže taèke neke ravni, uvedene su neke pomoæne strukture podataka i funkcije. To su struktura/klasa tacka kao fokus posmatranja
tokom izrade, kolekcijaTacaka koja èuva zbir tih taèaka. Tokom rada je prvobitno trebala èuvati pokazivaè na niz pokazivaèa na taèke i broj elemenata, ali je kasnije tokom rada radi jednostavnosti
odluèeno da ipak bude samo vektor kao container. Takoðer, tu je i struktura parTacaka koja je napravljena samo u demonstrativne svrhe. */

class tacka {
    int x,y;
public:
    tacka(int _x, int _y);
    void ispisi() {cout << "(" << x << "," << y << ")";}
    friend double udaljenost(const tacka &t1,const tacka &t2);
    int dajX() const {return x;}
    int dajY() const {return y;}
};

tacka::tacka (int _x = 0, int _y = 0) {
    x = _x;
    y = _y;
}

double udaljenost(const tacka &t1,const tacka &t2) {  // Raèuna euklidsku udaljenost dvije taèke. Mnogo pojednostavljuje daljnji kod.
    return sqrt((t1.x - t2.x) * (t1.x - t2.x) + (t1.y - t2.y) * (t1.y - t2.y));
}

bool poredbaPoX(const tacka &t1, const tacka &t2) { //korišteno prilikom sortiranja vektora taèaka po x koordinati kao šablon koji govori kako se sortira
    return (t1.dajX() < t2.dajX());
}

bool poredbaPoY(const tacka &t1, const tacka &t2) { //korišteno prilikom sortiranja vektora taèaka po y koordinati kao šablon koji govori kako se sortira
    return (t1.dajY() < t2.dajY());
}

struct parTacaka {
    tacka t1,t2;
};

/* Osmišljeno je da unutar ove klase budu implementirane funkcije koje æe vraæati razne podatke o kolekciji taèaka u ravni. Implementirane su dvije funkcije za dodavanje (i za direktno unošenje
koordinata, a i kada unosimo taèku). Imena ostalih funkcija govore dovoljno o tome šta ta funkcija radi. Napomenimo da je implementirana funkcija koja odreðuje dvije najbliže taèke brute-force
metodom (ova funkcija nije tu bezveze, nego æe kasnije biti upotrebljena prilikom implementacije traženog algoritma.). Funkcija za odreðivanje najbližih taèaka vremenske kompleksnosti O(nlog^2n)
nije implementirana jer nema baš nekog ni smisla, a ni potrebe (ako baš moramo, dovoljno je sortirati svaki put u rekurzivnom pozivu vektore). Objašenjenje pojedinih funkcija, ako bude potrebno,
æe biti prilikom odbrane ovog rada. */

class kolekcijaTacaka {
    vector <tacka> V;
public:
    void dodajNovuTacku (int _x, int _y);
    void dodajNovuTacku (tacka t);
    void ispisiTacke ();
    vector<tacka> dajSortiranVektorPoXevima ();
    vector<tacka> dajSortiranVektorPoYima ();
    void ispisSortiranogVektoraPoXevima();
    void ispisSortiranogVektoraPoYima();
    double najmanjaUdaljenostBruteForce();
    void najblizeTackeBruteForce();
    double najmanjaUdaljenost();
    double najmanjaUdaljenost(vector<tacka> Vx, vector<tacka> Vy);
    void ispisiNajblizeTacke();
    parTacaka dajNajblizeTacke();
};

void kolekcijaTacaka::dodajNovuTacku(int _x, int _y) {
    V.push_back(tacka{_x, _y});
}

void kolekcijaTacaka::dodajNovuTacku(tacka t) {
    V.push_back(t);
}

void kolekcijaTacaka::ispisiTacke() {
    cout << "[";
    for (int i=0; i<V.size(); i++)
        if (i < V.size()-1) {V[i].ispisi(); cout << " ";}
        else V[i].ispisi();
    cout << "]";
}

vector<tacka> kolekcijaTacaka::dajSortiranVektorPoXevima() {
    vector <tacka> v;
    v = V;
    sort(v.begin(), v.end(), poredbaPoX);  //Prva dva parametra su raspon sortiranja, a treæi je naèin sortiranja.
    return v;
}

vector<tacka> kolekcijaTacaka::dajSortiranVektorPoYima() {
    vector <tacka> vv;
    vv = V;
    sort(vv.begin(), vv.end(), poredbaPoY);
    return vv;
}

void kolekcijaTacaka::ispisSortiranogVektoraPoXevima() {
    cout << "(";
    vector <tacka> v = dajSortiranVektorPoXevima();
    for (int i = 0; i < v.size(); i++) {
        if (i < v.size()-1) {v[i].ispisi(); cout << ", ";}
        else
            v[i].ispisi();
    }
    cout << ")";
}

void kolekcijaTacaka::ispisSortiranogVektoraPoYima() {
    cout << "(";
    vector <tacka> v = dajSortiranVektorPoYima();
    for (int i = 0; i < v.size(); i++) {
        if (i < v.size()-1) {v[i].ispisi(); cout << ", ";}
        else
            v[i].ispisi();
    }
    cout << ")";
}

double kolekcijaTacaka::najmanjaUdaljenostBruteForce() {
    if (V.size() < 2) throw "Ne može se racunati najmanja udaljenost.";
    double a = udaljenost(V[0],V[1]);
    for (int i = 0; i < V.size()-1; i++) {
        for (int j = i+1; j < V.size(); j++) {
            if (udaljenost(V[i], V[j]) < a) a = udaljenost(V[i], V[j]);
        }
    }
    return a;
}

void kolekcijaTacaka::najblizeTackeBruteForce() {
    if (V.size() < 2) throw "Ne može se racunati najmanja udaljenost.";
    double a = udaljenost(V[0],V[1]);
    int c = 0, b = 1;
    for (int i = 0; i < V.size()-1; i++) {
        for (int j = i+1; j < V.size(); j++) {
            if (udaljenost(V[i], V[j]) < a) {
                a = udaljenost(V[i], V[j]);
                c = i;
                b = j;
            }
        }
    }
    cout << "[";
    V[c].ispisi();
    cout << ", ";
    V[b].ispisi();
    cout << "]";
}

/* Kljuèni dio. Napravljene su dvije funkcije: jedna u kojoj je implementiran sam algoritam pronalaženja i druga koja poziva prethodnu, a služi kao preèica, tj. za olakšan rad sa ovom funkcijom.
Dalje æemo govoriti, naravno, samo o implementaciji. Funkcija radi na principu rekurzije te veæe probleme razbija na manje sve dok ne doðe do nekog èije se rješenje pronalazi veoma lahko
(brute-force) metodom. Ideja je da se sve unesene taèke u kolekciju taèaka kopiraju i smjeste u dva vektora. U jednom su sortirane po x, a u drugom po y osi. Funkciji smo kao parametre proslijedili
ove vektore i svaki rekurzivni poziv poèinje sa njima. Dijelimo sve taèke sortirane prema x-osi na dva jednaka dijela u odnosu na vertikalnu liniju povuèenu kroz središnju taèku. Pravimo
dva para vektora lvx,lvy i rvx,rvy koje æemo prosljeðivati kao parametre unutar funkcije. Time æemo dobiti najkraæe udaljenosti u lijevom, odnosno desnom dijelu ravni. Uzeæemo manju od te dvije
i oznaèiti je sa d. Gledaæemo traku oko središnje taèke vektora Vx taèaka sortiranih po x osi. Ako postoji sluèajno par taèaka da je njihova udaljenost manja od d, onda se taj par mora nalaziti
unutar trake 2d. Napravit æemo vektor Vs takav da u njega upadnu sve taèke iz Vy takve da su iz te trake. Provjeravamo u for petlji za svaku taèku iz ovog vektora svaku drugu taèku iz istog vektora
da li je na udaljenosti d. Ako nije, onda je ni nema smisla razmatrati. Ova druga petlja ima konstantan broj iteracija pa vrijeme nije O(n^2). Razlog za ovo je to što ako podijelimo posmatranu
traku na kvadrate dimenzija d/2 * d/2, dokaže se lahko da dvije taèke ne mogu pripadati istom kvadratu. Dakle, za dovoljno veliko n, ovo ipak nije O(n^2) vremenska kompleksnost. Kod ispod
je prilièno jasan. Ovo je funkcija koja vraæa najmanju udaljenost, a same taèke vraæa druga funkcija koja u vremenu O(n) pronalazi te taèke uz pomoæ ove funkcije. Linije gdje nema dodatnog komentara
su dovoljno jasne.  */

double kolekcijaTacaka::najmanjaUdaljenost() {
    return najmanjaUdaljenost(dajSortiranVektorPoXevima(),dajSortiranVektorPoYima());
}

double kolekcijaTacaka::najmanjaUdaljenost(vector<tacka> Vx, vector<tacka> Vy) { //vektori sa taèkama sortiranim po x i y osama redom
    if (Vx.size() < 4) {
        kolekcijaTacaka privremena;
        for (int i = 0;i < Vx.size(); i++) privremena.dodajNovuTacku(Vx[i]);
        return privremena.najmanjaUdaljenostBruteForce();
    }
    int sredina = Vx.size()/2;
    tacka sredisnja = Vx[sredina];
    vector<tacka> lvx;  //vektor taèaka koje su lijevo u odnosu na središnju
    vector<tacka> rvx;  //vektor taèaka koje su desno u odnosu na središnju
    for (int i = 0; i < sredina; i++) {  //O(n)
        lvx.push_back(Vx[i]);
    }
    for (int i = sredina; i < Vx.size(); i++){  //O(n)
        rvx.push_back(Vx[i]);
    }
    vector<tacka> lvy; //vektor taèaka iz vektora Vy takvih su lijevo od središnje
    vector<tacka> rvy; //vektor taèaka iz vektora Vy takvih su desno od središnje
    for (int i = 0; i < Vy.size(); i++) { // O(n)
        if (Vy[i].dajX() <= sredisnja.dajX()) lvy.push_back(Vy[i]);
        if (Vy[i].dajX() > sredisnja.dajX()) rvy.push_back(Vy[i]);
    }
    double dL = najmanjaUdaljenost(lvx,lvy);
    double dD = najmanjaUdaljenost(rvx,rvy);
    double dMin = min(dL,dD);
    vector<tacka> Vs; //u ovaj vektor kupimo sve taèke iz trake širine 2dMin oko vertikalne linije povuèene kroz središnju taèku
    for (int i = 0; i < Vy.size(); i++) {
        if (abs(sredisnja.dajX()-Vy[i].dajX()) < dMin) Vs.push_back(Vy[i]);
    }
    int brojTacakaOkoSredista = Vs.size();
    double najblizi = dMin;
    if (brojTacakaOkoSredista > 0) {
        for (int i = 0; i < brojTacakaOkoSredista; i++) {
            int j = i+1;
            while ((j <= brojTacakaOkoSredista) && ((Vs[j].dajY() - Vs[i].dajY()) < dMin)) {   //ovaj dio je objašnjen gore, a biæe objašnjen i prilikom samog branjenja rada
                if (udaljenost(Vs[j],Vs[i]) < najblizi)
                    najblizi = udaljenost(Vs[j],Vs[i]);
                j++;
            }
        }
    }
    return najblizi;
}

void kolekcijaTacaka::ispisiNajblizeTacke() {  //funkcija koja u vremenu O(nlogn) ispisuje dvije najbliže taèke.
    vector <tacka> v = dajSortiranVektorPoXevima();
    double a = najmanjaUdaljenost();
    for (int i = 1; i < v.size(); i++) // O(n)
        if (udaljenost(v[i],v[i-1]) == a) {
            cout << "(" << v[i].dajX() << "," << v[i].dajY() << ")" << " (" << v[i-1].dajX() << "," << v[i-1].dajY() << ")";
            break;
        }
}

parTacaka kolekcijaTacaka::dajNajblizeTacke() {  //funkcija koja u vremenu O(nlogn) vraæa dvije najbliže taèke.
    vector <tacka> v = dajSortiranVektorPoXevima();
    parTacaka TT;
    double a = najmanjaUdaljenost();
    for (int i = 1; i < v.size(); i++)  // O(n)
        if (udaljenost(v[i],v[i-1]) == a) {
            TT.t1 = v[i];
            TT.t2 = v[i-1];
            break;
        }
    return TT;
}

// Kratki testni program

int main()
{
    try {
    kolekcijaTacaka kt;
    tacka d(-5,-1);
    tacka dd(4,5);
    kt.dodajNovuTacku(d);
    kt.dodajNovuTacku(dd);
    kt.dodajNovuTacku(-1,1);
    kt.dodajNovuTacku(1,2);
    kt.dodajNovuTacku(3,4);
    kt.dodajNovuTacku(-2,-2);
    kt.dodajNovuTacku(0,0);
    kt.ispisiTacke();
    cout << endl;
    kt.ispisSortiranogVektoraPoXevima();
    cout << endl;
    kt.ispisSortiranogVektoraPoYima();
    cout << endl;
    cout << kt.najmanjaUdaljenostBruteForce();
    cout << endl;
    kt.najblizeTackeBruteForce();
    cout << endl;
    cout << kt.najmanjaUdaljenost();
    cout << endl;
    kolekcijaTacaka kt2;
    kt2.dodajNovuTacku(2,3);
    kt2.dodajNovuTacku(12,30);
    kt2.dodajNovuTacku(40,50);
    kt2.dodajNovuTacku(40,51);
    kt2.dodajNovuTacku(5,1);
    kt2.dodajNovuTacku(12,10);
    kt2.dodajNovuTacku(3,4);
    cout <<kt2.najmanjaUdaljenost() << endl;
    kt2.ispisiNajblizeTacke(); }
    catch (...) {
        cout << "Problem.";
    }
    return 0;
}
