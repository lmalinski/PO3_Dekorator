
#include <iostream>
#include <cassert>


class Skladnik
{
protected:
    std::string m_nazwa;
public:
    Skladnik(std::string nazwa)
        : m_nazwa(nazwa)
    {}
    virtual void wypiszNazwe() = 0;
    virtual ~Skladnik() {};
    friend class SkladnikDecor;
};

class Ciasto : public Skladnik
{
public:
    Ciasto(std::string nazwa)
        : Skladnik(nazwa)
    {}
    void wypiszNazwe() override
    {
        std::cout << "Pizza: " << m_nazwa;
    }
};

class SkladnikDecor : public Skladnik
{
protected:
    Skladnik* m_baza = nullptr;
public:
    SkladnikDecor(std::string nazwa, Skladnik* baza)
        : Skladnik(nazwa)
    {
        assert(baza != nullptr);
        m_baza = baza;
    }
    void wypiszNazwe() override
    {
        assert(m_baza != nullptr);
        m_baza->wypiszNazwe();
        std::cout << ", " << m_nazwa;
    }
    ~SkladnikDecor()
    {
        assert(m_baza != nullptr);
        std::cerr << "Zwalniam " << m_baza->m_nazwa << std::endl;
        delete m_baza;
        m_baza = nullptr;
    }
};

class Dodatek : public SkladnikDecor
{
public:
    Dodatek(std::string nazwa, Skladnik* baza)
        : SkladnikDecor(nazwa, baza)
    {}

};

int main()
{
    using namespace std;

    const char* const NAZWY_CIASTA[] = { "cienkie", "normalne", "grube", "calzzone"};
    int liczbaOpcji = std::size(NAZWY_CIASTA);
    cout << "Wybierz rodzaj ciasta:\n";
    for (int opcja = 0; opcja < liczbaOpcji; opcja++)
        cout << "  " << opcja + 1 << " - " << NAZWY_CIASTA[opcja] << endl;
    int wybor = 0;
    do
    {
        cout << ": "; cin >> wybor;
    } while (wybor < 1 || liczbaOpcji < wybor);
    Skladnik* pizza = new Ciasto(NAZWY_CIASTA[wybor - 1]);
    
    const char* const NAZWY_DODATKOW[] = { "ser", "pieczarki", "oliwki", "papryka", "szynka", "cebula"};
    liczbaOpcji = std::size(NAZWY_DODATKOW);
    while (true)
    {
        system("cls");
        cout << "Twoj obecny wybor to: ";
        pizza->wypiszNazwe();
        cout << "\nWybierz dodatek:\n";
        for (int opcja = 0; opcja < liczbaOpcji; opcja++)
            cout << "  " << opcja + 1 << " - " << NAZWY_DODATKOW[opcja] << endl;
        cout << "  0 - koniec\n";
        do
        {
            cout << ": "; cin >> wybor;
        } while (wybor < 0 || liczbaOpcji < wybor);
        if (wybor == 0) 
            break;
        pizza = new Dodatek(NAZWY_DODATKOW[wybor - 1], pizza);

    } 
    cout << "Zamowiana pizza: ";
    pizza->wypiszNazwe(); cout << endl;
    delete pizza;   
}

