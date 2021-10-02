#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include <fstream>
#include <sstream>

using namespace std;

struct Adresat
{
    int idAdresata = 0;
    int idUzytkownika  = 0;
    string imie = "", nazwisko = "", nrTel = "", email = "", adres = "";
};

struct Uzytkownik
{
    int idUzytkownika = 0;
    string login, haslo;
};

vector <Adresat> adresaci;
vector <Uzytkownik> uzytkownicy;

int zarejestrujUzytkownika (vector <Uzytkownik> &uzytkownicy, int iloscUzytkownikow)
{
    string login, haslo;
    int idUzytkownika = 0;
    Uzytkownik pomoc;

    if(uzytkownicy.size() == 0)
    {
        idUzytkownika = 1;    //jezeli ksiazka jest pusta pierwszy  osoba ma ID 1
    }
    else
    {
        idUzytkownika = uzytkownicy[uzytkownicy.size() - 1].idUzytkownika + 1;
    }

    cout << "Podaj login: ";
    cin >> login;
    cin.sync();
    cout << "Podaj haslo: ";
    cin >> haslo;
    cout << "Rejsetracja przebiegla pomyslnie. Twoje ID to: " << idUzytkownika << endl;
    Sleep(1000);

    pomoc.idUzytkownika = idUzytkownika;
    pomoc.login = login;
    pomoc.haslo = haslo;

    uzytkownicy.push_back(pomoc);

    //zapisz do pliku
    fstream plikDoZapisu;
    plikDoZapisu.open("Uzytkownicy.txt", ios::out | ios::app);

    if (plikDoZapisu.good() == true)
    {
        plikDoZapisu << pomoc.idUzytkownika << "|" << pomoc.login << "|" << pomoc.haslo << "|" << endl;
        plikDoZapisu.close();
    }
    else
    {
        cout << "Nie udalo sie otworzyc pliku";
        system("pause");
    }
}

void przejdzDoMenuLogowania()
{
    system("cls");
    cout << "Witaj w Ksiazce Adresowej!" << endl;
    cout << "Wybierz jedna z ponizszych opcji: " << endl;
    cout << "1. Logowanie" << endl;
    cout << "2. Rejestracja" << endl;
    cout << "3. Zakoncz program" << endl;
}

void wyswietlMenuPoZalogowaniu()
{
    system("cls");
    cout << "Wybierz opcje: " << endl;
    cout << "1. Dodaj adresata" << endl;
    cout << "2. Wyszukaj po imieniu" << endl;
    cout << "3  Wyszukaj po nazwisku" << endl;
    cout << "4. Wyswietl wszystkich adresatow" << endl;
    cout << "5. Usun adresata" << endl;
    cout << "6. Edytuj adresata" << endl;
    cout << "7. Zmien haslo" << endl;
    cout << "8. Wyloguj sie" << endl;

}

int zalogujUzytkownika(vector <Uzytkownik> &uzytkownicy, int iloscUzytkownikow)
{
    string login = "", haslo = "";
    cout << "Podaj login: ";
    cin.sync();
    cin >> login;
    cin.sync();
    vector <Uzytkownik>::iterator itr = uzytkownicy.begin();
    for (itr; itr != uzytkownicy.end(); itr++)
    {
        if (itr->login == login)
        {
            cout << "Podaj haslo: ";
            cin >> haslo;
            if (itr->haslo == haslo)
            {
                cout << "Zostales zalogowany." << endl;
                Sleep(1000);
                return itr->idUzytkownika;
            }
            else
            {
                cout << "Podales bledne haslo!! Sprobuj ponownie: ";
                cin >> haslo;
                if (itr->haslo == haslo)
                {
                    cout << "Zostales zalogowany." << endl;
                    Sleep(1000);
                    return itr->idUzytkownika;
                }
            }
            cout << "Znowu podales zle haslo!! Koniec programu!";
            exit(0);
        }

    }
    cout << "Podales zly login. Nie ma takiego uzytkownika!!" << endl;
    Sleep(1000);
    exit(0);


    return 0;
}

vector <Uzytkownik> rozdzielDaneUzytkonikaNaPojedynczeLinie(vector <Uzytkownik> &uzytkownicy, string liniaDoOdczytania, char znakPionowejKreski)
{
    Uzytkownik pomoc;
    int nrLinii = 1;
    stringstream ss(liniaDoOdczytania);
    string pojedynczaDana = " ";

    while (getline(ss, pojedynczaDana, znakPionowejKreski))
    {
        switch(nrLinii)
        {
        case 1:
            pomoc.idUzytkownika = atoi(pojedynczaDana.c_str());
            break;
        case 2:
            pomoc.login = pojedynczaDana;
            break;
        case 3:
            pomoc.haslo = pojedynczaDana;
            break;

        }
        nrLinii++;
    }
    uzytkownicy.push_back(pomoc);

    return uzytkownicy;
}

int wczytajPlikUzytkownicy(vector <Uzytkownik> &uzytkownicy)
{
    string liniaTesktu;
    int nrLinii = 1;
    fstream plikDoOdczytu;

    plikDoOdczytu.open("Uzytkownicy.txt", ios::in);
    if(plikDoOdczytu.good() == true)
    {
        while (getline(plikDoOdczytu, liniaTesktu))
        {
            uzytkownicy = rozdzielDaneUzytkonikaNaPojedynczeLinie(uzytkownicy, liniaTesktu, '|');
        }
    }
    plikDoOdczytu.close();
}

vector <Adresat> rozdzielDaneAdresatowNaPojedynczeDane (vector <Adresat> &adresaci, string liniaDoOdczytania, char znakPionowejKreski)
{
    Adresat adresat;
    int nrLinii = 1;
    stringstream ss(liniaDoOdczytania);
    string pojedynczaDana = " ";

    while (getline(ss, pojedynczaDana, znakPionowejKreski))
    {
        switch (nrLinii)
        {
        case 1:
            adresat.idAdresata = (atoi(pojedynczaDana.c_str()));
            break;
        case 2:
            adresat.idUzytkownika = (atoi(pojedynczaDana.c_str()));
            break;
        case 3:
            adresat.imie = pojedynczaDana;
            break;
        case 4:
            adresat.nazwisko = pojedynczaDana;
            break;
        case 5:
            adresat.nrTel = pojedynczaDana;
            break;
        case 6:
            adresat.email = pojedynczaDana;
            break;
        case 7:
            adresat.adres = pojedynczaDana;
            break;

        }
        nrLinii++;
    }
    adresaci.push_back(adresat);

    return adresaci;
}

int wczytajPlikZDanymiAdresatow (vector <Adresat> &adresaci, int idZalogowanegoUzytkownika)
{
    string liniaTekstu;
    int nrLinii = 1;
    fstream plikDoOdczytu;
    string ostatniaOsobaWPliku = " ";

    plikDoOdczytu.open("Adresaci.txt", ios::in);

    if (plikDoOdczytu.good() == true)
    {
        while (getline(plikDoOdczytu, liniaTekstu))
        {
            adresaci = rozdzielDaneAdresatowNaPojedynczeDane(adresaci, liniaTekstu, '|');
        }

    }
    plikDoOdczytu.close();

}

int pobierzIDOstatniegoAdresata ()
{
    fstream plik;
    int ostatnieID = 0;
    string liniaTekstu;
    int pozycjaWLinii = 1;
    char znakPionowejKreski = '|';

    plik.open("Adresaci.txt", ios::in);
    if (plik.good() == true)
    {
        while(getline(plik, liniaTekstu, znakPionowejKreski))
        {
            switch(pozycjaWLinii)
            {
            case 1:
                if (atoi(liniaTekstu.c_str()) == 0)
                    return ostatnieID;
                else
                    ostatnieID = atoi(liniaTekstu.c_str());

                break;
            }

            if(pozycjaWLinii == 7)
            {
                pozycjaWLinii = 0;
            }
            pozycjaWLinii++;

        }
    }
    plik.close();

    return ostatnieID;
}

void zapiszAdresataDoPlikuTymczasowegoGdyIDSieNieZgadza(Adresat pomoc)
{
    fstream plikTymczasowy;

    plikTymczasowy.open("Adresaci_tymczasowy.txt", ios::out | ios::app);

    plikTymczasowy << pomoc.idAdresata << "|" << pomoc.idUzytkownika << "|" << pomoc.imie << "|" << pomoc.nazwisko << "|" << pomoc.nrTel << "|" << pomoc.email << "|" << pomoc.adres << "|" << endl;
    plikTymczasowy.close();
}

void zapiszAdresataDoPlikuTymczasowegoGdyIDSieZgadza(vector <Adresat> &adresaci,int idEdytowanegoAdresata)
{
    fstream plikTymczasowy;
    vector <Adresat> :: iterator itr = adresaci.begin();
    plikTymczasowy.open("Adresaci_tymczasowy.txt", ios::out | ios::app);
    if(plikTymczasowy.good() == true)
    {
        for (itr; itr != adresaci.end(); ++itr)
        {
            if(itr->idAdresata == idEdytowanegoAdresata)
            {
                plikTymczasowy << itr->idAdresata << "|" << itr->idUzytkownika << "|" << itr->imie << "|" << itr->nazwisko << "|" << itr->nrTel << "|" << itr->email << "|" << itr->adres << "|" << endl;
            }
        }
        plikTymczasowy.close();
    }

}

int dodajAdresataDoKsiazki (vector <Adresat> &adresaci, int idZalogowanegoUzytkownika, int iloscOsob)
{
    string imie, nazwisko, nrTel, email, adres;
    int idAdresata = 0;
    Adresat pomoc2;

    if(iloscOsob == 0)
    {
        idAdresata = 1;    //jezeli ksiazka jest pusta pierwszy  osoba ma ID 1
    }
    else
    {
        idAdresata = pobierzIDOstatniegoAdresata() + 1;
    }

    cout << "Podaj imie: ";
    cin >> imie;
    cin.sync();
    cout << "Podaj nazwisko: ";
    cin >> nazwisko;
    cin.sync();
    cout << "Podaj nr telefonu: ";
    cin >> nrTel;
    cin.sync();
    cout << "Podaj email: ";
    cin >> email;
    cin.sync();
    cout << "Podaj swoj adres: ";
    getline(cin, adres);

    pomoc2.idAdresata = idAdresata;
    pomoc2.idUzytkownika = idZalogowanegoUzytkownika;
    pomoc2.imie = imie;
    pomoc2.nazwisko = nazwisko;
    pomoc2.nrTel = nrTel;
    pomoc2.email = email;
    pomoc2.adres = adres;

    //dodaj osobe do wektora
    adresaci.push_back(pomoc2);

    //zapisz do pliku
    fstream plikDoZapisuZAdresatami;
    plikDoZapisuZAdresatami.open("Adresaci.txt", ios::out | ios::app);

    if (plikDoZapisuZAdresatami.good() == true)
    {
        plikDoZapisuZAdresatami << pomoc2.idAdresata << "|" << pomoc2.idUzytkownika << "|" << pomoc2.imie << "|" << pomoc2.nazwisko << "|" << pomoc2.nrTel << "|" << pomoc2.email << "|" << pomoc2.adres << "|" << endl;
        plikDoZapisuZAdresatami.close();
        iloscOsob++;
        cout << "Adresat zostal dodany do ksiazki." << endl;
        Sleep(1000);
    }
    else
    {
        cout << "Nie udalo sie otworzyc pliku";
        system("pause");
    }
    return iloscOsob;

}

void wyszukajAdresataPoImieniu (int idZalogowanegoUzytkownika)
{
    string imie;
    cout << "Podaj imie, ktore chcesz wyszukac: ";
    cin.sync();
    cin >> imie;
    cin.sync();
    int iloscAdresatow = 0;
    vector <Adresat>::iterator itr = adresaci.begin();
    for (itr; itr != adresaci.end(); itr++)
    {
        if ((itr->idUzytkownika == idZalogowanegoUzytkownika) && (itr->imie == imie))
        {
            cout << "Znalazlem osobe o takim imieniu" << endl;
            cout << itr->imie << "|" << itr->nazwisko << "|" << itr->nrTel << "|" << itr->email << "|" << itr->adres;
            iloscAdresatow++;
            Sleep(1500);
        }
    }
    if (iloscAdresatow == 0)
    {
        cout << "Nie ma takiej osoby!" << endl;
        Sleep(1500);
        iloscAdresatow++;
    }
}

void wyszukajAdresataPoNazwisku (int idZalogowanegoUzytkownika)
{
    string nazwisko;
    cout << "Podaj nazwisko, ktore chcesz wyszukac: ";
    cin.sync();
    cin >> nazwisko;
    cin.sync();
    int iloscAdresatow = 0;
    vector <Adresat>::iterator itr = adresaci.begin();
    for (itr; itr != adresaci.end(); itr++)
    {
        if ((itr->idUzytkownika == idZalogowanegoUzytkownika) && (itr->nazwisko == nazwisko))
        {
            cout << "Znalazlem osobe o takim nazwisku" << endl;
            cout << itr->imie << "|" << itr->nazwisko << "|" << itr->nrTel << "|" << itr->email << "|" << itr->adres;
            iloscAdresatow++;
            Sleep(1500);
        }
    }
    if (iloscAdresatow == 0)
    {
        cout << "Nie ma takiej osoby!" << endl;
        Sleep(1500);
        iloscAdresatow++;
    }
}

void wyswietlWszystkichAdresatow (int idZalogowanegoUzytkownika)
{
    vector <Adresat>::iterator itr = adresaci.begin();

    for (itr; itr != adresaci.end(); itr++)
    {
        if (itr->idUzytkownika == idZalogowanegoUzytkownika)
        {
            cout << "ID Adresata: " << itr->idAdresata << endl;
            cout << "ID Uzytkownika: " << itr->idUzytkownika << endl;
            cout << endl;
            cout << "Imie: " << itr->imie << endl;
            cout << "Nazwisko: " << itr->nazwisko << endl;
            cout << "Nr tel: " << itr->nrTel << endl;
            cout << "Adres email: " << itr->email << endl;
            cout << "Adres zamieszkania: " << itr->adres << endl;
            cout << endl;
            Sleep(1500);
        }

    }
}

void zapiszUsunietegoAdresataDoPliku (int idUsuwanegoAdresata)
{
    fstream plikOryginalny;
    int nrLiniiPlikuOryginalnego = 1;
    string liniaTekstu;
    Adresat pomoc;
    char znakPionowejKreski = '|';
    bool czyNrIDRowny = false;

    plikOryginalny.open("Adresaci.txt", ios::in);
    if(plikOryginalny.good())
    {
        while(getline(plikOryginalny, liniaTekstu, znakPionowejKreski))
        {
            switch(nrLiniiPlikuOryginalnego)
            {
            case 1:
                if (atoi(liniaTekstu.c_str()) == idUsuwanegoAdresata)
                {
                    czyNrIDRowny = true;
                }
                else
                {
                    pomoc.idAdresata = atoi(liniaTekstu.c_str());
                }
                break;

            case 2:
                if (czyNrIDRowny == false)
                {
                    pomoc.idUzytkownika = atoi(liniaTekstu.c_str());
                }
                break;

            case 3:
                if (czyNrIDRowny == false)
                {
                    pomoc.imie = liniaTekstu;
                }
                break;

            case 4:
                if (czyNrIDRowny == false)
                {
                    pomoc.nazwisko = liniaTekstu;
                }
                break;

            case 5:
                if (czyNrIDRowny == false)
                {
                    pomoc.nrTel = liniaTekstu;
                }
                break;

            case 6:
                if (czyNrIDRowny == false)
                {
                    pomoc.email = liniaTekstu;
                }
                break;

            case 7:
                if (czyNrIDRowny == false)
                {
                    pomoc.adres = liniaTekstu;
                }
                break;

            }
            if(nrLiniiPlikuOryginalnego == 7)
            {
                if(czyNrIDRowny == false)
                {
                    zapiszAdresataDoPlikuTymczasowegoGdyIDSieNieZgadza(pomoc);
                }
                czyNrIDRowny = false;
                nrLiniiPlikuOryginalnego = 0;

            }
            nrLiniiPlikuOryginalnego++;
        }
        plikOryginalny.close();
    }
    remove("Adresaci.txt");
    rename("Adresaci_tymczasowy.txt", "Adresaci.txt");

}

void usunAdresata (vector <Adresat> &adresaci, int idZalogowanegoUzytkonika)
{
    fstream plikOryginalny;
    int idUsuwanegoAdresata;
    char potwierdzenieWyboru;
    vector <Adresat> ::iterator itr = adresaci.begin();
    vector <Adresat> ::iterator itr2 = adresaci.begin();

    cout << "Do Twojego ID sa przypisani tacy uzytkownicy: " << endl;
    for (itr; itr!= adresaci.end(); itr++)
    {
        if(itr->idUzytkownika == idZalogowanegoUzytkonika)
            cout << itr->idAdresata << "|" << itr->idUzytkownika <<  "|" << itr->imie << "|" << itr->nazwisko << "|" << itr->nrTel << "|" << itr->email << "|" << itr->adres << endl;
    }

    cout << "Podaj ID adresata, ktorego chcesz usunac: " << endl;
    cin.sync();
    cin >> idUsuwanegoAdresata;
    cin.sync();
    for (itr2; itr2 != adresaci.end(); itr2++)
    {
        if(itr2->idAdresata == idUsuwanegoAdresata)
        {
            cout << "Czy na pewno chcesz usunac tego adresata? Kliknij t: " << endl;
            cin >> potwierdzenieWyboru;
            if (potwierdzenieWyboru == 't')
            {
                adresaci.erase(itr2);
                cout << "Kontakt zostal usuniety";
                Sleep(1000);
                zapiszUsunietegoAdresataDoPliku (idUsuwanegoAdresata);
            }
            else if (potwierdzenieWyboru != 't')
            {
                cout << "Blad! Wcisnales zly klawisz!!";
            }
            break;

        }

    }

}


void zapiszEdytowaneZmianyDoPliku (vector <Adresat> &adresaci, int idEdytowanegoAdresata)
{
    fstream plikOryginalny;
    int nrLiniiPlikuOryginalnego = 1;
    string liniaTekstu;
    Adresat pomoc;
    char znakPionowejKreski = '|';
    bool czyNrIDRowny = false;

    plikOryginalny.open("Adresaci.txt", ios::in);
    if(plikOryginalny.good())
    {
        while(getline(plikOryginalny, liniaTekstu, znakPionowejKreski))
        {
            switch(nrLiniiPlikuOryginalnego)
            {
            case 1:
                if (atoi(liniaTekstu.c_str()) == idEdytowanegoAdresata)
                {
                    czyNrIDRowny = true;
                }
                else
                {
                    pomoc.idAdresata = atoi(liniaTekstu.c_str());
                }
                break;

            case 2:
                if (czyNrIDRowny == false)
                {
                    pomoc.idUzytkownika = atoi(liniaTekstu.c_str());
                }
                break;

            case 3:
                if (czyNrIDRowny == false)
                {
                    pomoc.imie = liniaTekstu;
                }
                break;

            case 4:
                if (czyNrIDRowny == false)
                {
                    pomoc.nazwisko = liniaTekstu;
                }
                break;

            case 5:
                if (czyNrIDRowny == false)
                {
                    pomoc.nrTel = liniaTekstu;
                }
                break;

            case 6:
                if (czyNrIDRowny == false)
                {
                    pomoc.email = liniaTekstu;
                }
                break;

            case 7:
                if (czyNrIDRowny == false)
                {
                    pomoc.adres = liniaTekstu;
                }
                break;

            }
            if(nrLiniiPlikuOryginalnego == 7)
            {
                if(czyNrIDRowny == true)
                {
                    zapiszAdresataDoPlikuTymczasowegoGdyIDSieZgadza(adresaci, idEdytowanegoAdresata);
                }
                else
                {
                    zapiszAdresataDoPlikuTymczasowegoGdyIDSieNieZgadza(pomoc);
                }

                nrLiniiPlikuOryginalnego = 0;
                czyNrIDRowny = false;

            }
            nrLiniiPlikuOryginalnego++;
        }
        plikOryginalny.close();
    }
    remove("Adresaci.txt");
    rename("Adresaci_tymczasowy.txt", "Adresaci.txt");

}

void edytujImieAdresata (vector <Adresat> &adresaci, int idEdytowanegoAdresata)
{
    string noweImie = "";
    cout << "Podaj nowe imie: ";
    cin >> noweImie;

    vector <Adresat> ::iterator itr = adresaci.begin();

    for (itr; itr != adresaci.end(); ++itr)
    {
        if (itr->idAdresata == idEdytowanegoAdresata)
        {
            itr->imie = noweImie;
        }
    }
    zapiszEdytowaneZmianyDoPliku(adresaci, idEdytowanegoAdresata);
    cout << "Imie zostalo zmienione" << endl;
    Sleep(1000);
}

void edytujNazwiskoAdresata (vector <Adresat> &adresaci, int idEdytowanegoAdresata)
{
    string noweNazwisko = "";
    cout << "Podaj nowe nazwisko: ";
    cin >> noweNazwisko;

    vector <Adresat> ::iterator itr = adresaci.begin();

    for (itr; itr != adresaci.end(); ++itr)
    {
        if (itr->idAdresata == idEdytowanegoAdresata)
        {
            itr->nazwisko = noweNazwisko;
        }
    }
    zapiszEdytowaneZmianyDoPliku(adresaci, idEdytowanegoAdresata);
    cout << "Nazwisko zostalo zmienione" << endl;
    Sleep(1000);
}

void edytujNrTelAdresata (vector <Adresat> &adresaci, int idEdytowanegoAdresata)
{
    string nowyNrTel = "";
    cout << "Podaj nowy numer telefonu: ";
    cin >> nowyNrTel;

    vector <Adresat> ::iterator itr = adresaci.begin();

    for (itr; itr != adresaci.end(); ++itr)
    {
        if (itr->idAdresata == idEdytowanegoAdresata)
        {
            itr->nrTel = nowyNrTel;
        }
    }
    zapiszEdytowaneZmianyDoPliku(adresaci, idEdytowanegoAdresata);
    cout << "Numer telefonu zostal zmieniony" << endl;
    Sleep(1000);
}

void edytujEmailAdresata (vector <Adresat> &adresaci, int idEdytowanegoAdresata)
{
    string nowyEmail = "";
    cout << "Podaj nowy email: ";
    cin >> nowyEmail;

    vector <Adresat> ::iterator itr = adresaci.begin();

    for (itr; itr != adresaci.end(); ++itr)
    {
        if (itr->idAdresata == idEdytowanegoAdresata)
        {
            itr->email = nowyEmail;
        }
    }
    zapiszEdytowaneZmianyDoPliku(adresaci, idEdytowanegoAdresata);
    cout << "Email zostaly zmieniony" << endl;
    Sleep(1000);
}

void edytujAdresAdresata (vector <Adresat> &adresaci, int idEdytowanegoAdresata)
{
    string nowyAdres = "";
    cout << "Podaj nowy email: ";
    cin >> nowyAdres;

    vector <Adresat> ::iterator itr = adresaci.begin();

    for (itr; itr != adresaci.end(); ++itr)
    {
        if (itr->idAdresata == idEdytowanegoAdresata)
        {
            itr->adres = nowyAdres;
        }
    }
    zapiszEdytowaneZmianyDoPliku(adresaci, idEdytowanegoAdresata);
    cout << "Adres zostaly zmieniony" << endl;
    Sleep(1000);
}

void edytujAdresata (vector <Adresat> &adresaci, int idZalogowanegoUzytkownika)
{
    int idAdresata;
    char wyborDanejDoEdycji;
    vector <Adresat> ::iterator itr = adresaci.begin();

    cout << "Do Twojego ID sa przypisani tacy uzytkownicy: " << endl;
    for (itr; itr!= adresaci.end(); itr++)
    {
        if(itr->idUzytkownika == idZalogowanegoUzytkownika)
            cout << itr->idAdresata << "|" << itr->idUzytkownika <<  "|" << itr->imie << "|" << itr->nazwisko << "|" << itr->nrTel << "|" << itr->email << "|" << itr->adres << endl;
    }
    cout << "Podaj ID adresata, ktorego dane maja byc edytowane: " << endl;
    cin >> idAdresata;

    cout << "Wybierz, ktora dane chcesz edytowac: " << endl;
    cout << "1. Edycja imienia" << endl;
    cout << "2. Edycja nazwiska" << endl;
    cout << "3. Edycja numeru telefonu" << endl;
    cout << "4. Edycja email" << endl;
    cout << "5. Edycja adresata" << endl;

    cin >> wyborDanejDoEdycji;
    switch(wyborDanejDoEdycji)
    {
    case '1':
        edytujImieAdresata(adresaci, idAdresata);
        cout << "Edycja przebiegla pomyslnie";
        Sleep(1000);
        break;

    case '2':
        edytujNazwiskoAdresata(adresaci, idAdresata);
        cout << "Edycja przebiegla pomyslnie";
        Sleep(1000);
        break;

    case '3':
        edytujNrTelAdresata(adresaci, idAdresata);
        cout << "Edycja przebiegla pomyslnie";
        Sleep(1000);
        break;

    case '4':
        edytujEmailAdresata(adresaci, idAdresata);
        cout << "Edycja przebiegla pomyslnie";
        Sleep(1000);
        break;

    case '5':
        edytujAdresAdresata(adresaci, idAdresata);
        cout << "Edycja przebiegla pomyslnie";
        Sleep(1000);
        break;
    }
}


void aktualizujPlikPoZmianieHasla (vector <Uzytkownik> &uzytkownicy)
{
    vector <Uzytkownik> ::iterator itr = uzytkownicy.begin();
    fstream plikPoZmianieHasla;

    plikPoZmianieHasla.open("Uzytkownicy.txt", ios::out | ios::trunc);
    if (plikPoZmianieHasla.good())
    {
        for (itr; itr != uzytkownicy.end(); ++itr)
        {
            plikPoZmianieHasla << itr->idUzytkownika << "|" << itr->login << "|" << itr->haslo << "|" << endl;
        }
        plikPoZmianieHasla.close();
    }
    uzytkownicy.clear();
}

void zmienHaslo(vector <Uzytkownik> &uzytkownicy, int idZalogowanegoUzytkownika, int iloscOsob)
{
    string noweHaslo = " ";
    vector <Uzytkownik> ::iterator itr = uzytkownicy.begin();

    cout << "Podaj nowe haslo: ";
    cin >> noweHaslo;

    for (itr; itr != uzytkownicy.end(); ++itr)
    {
        if (itr->idUzytkownika == idZalogowanegoUzytkownika)
        {
            itr->haslo = noweHaslo;
            aktualizujPlikPoZmianieHasla(uzytkownicy);
            iloscOsob++;
            cout << "Haslo zostalo zmienione.";
            Sleep(1000);
            exit(0);
        }
    }
}

int wylogujUzytkownika(vector <Adresat> &adresaci, int idZalogowanegoUzytkownika)
{
    cout << "Czy na pewno chcesz sie wylogowac? Jesli tak - kliknij t, jezeli nie - kliknij n " << endl;
    char wybor;

    while(1)
    {
        cin >> wybor;
        if (wybor == 't')
        {
            idZalogowanegoUzytkownika = 0;
            cout << "Nastapilo wylogowanie" << endl;
            Sleep(1500);
            adresaci.clear();
            return idZalogowanegoUzytkownika;
            exit(0);
        }
        else if (wybor == 'n')
        {
            return idZalogowanegoUzytkownika;
        }
        else
        {
            cout << "Podales bledna litere!!";
            Sleep(1000);
        }
    }
}

void zamknijProgram()
{
    exit(0);
}

int main()
{
    int iloscUzytkownikow = 0;
    int iloscOsob = 0;
    int idZalogowanegoUzytkownika = 0;
    char wybor;

    iloscUzytkownikow = wczytajPlikUzytkownicy(uzytkownicy);

    while(1)
    {
        if(idZalogowanegoUzytkownika == 0)
        {
            przejdzDoMenuLogowania();
            cin >> wybor;
            cin.sync();

            switch(wybor)
            {
            case '1':
                idZalogowanegoUzytkownika = zalogujUzytkownika(uzytkownicy, iloscUzytkownikow);
                if(idZalogowanegoUzytkownika != 0)
                {
                    iloscOsob = wczytajPlikZDanymiAdresatow(adresaci, idZalogowanegoUzytkownika);
                }
                break;

            case '2':
                iloscUzytkownikow = zarejestrujUzytkownika(uzytkownicy, iloscUzytkownikow);
                break;

            case '3':
                zamknijProgram();
                break;
            }
        }
        else
        {
            wyswietlMenuPoZalogowaniu();
            char wyborOpcji;
            cin >> wyborOpcji;
            cin.sync();
            switch (wyborOpcji)
            {
            case '1':
                iloscOsob = dodajAdresataDoKsiazki(adresaci, idZalogowanegoUzytkownika, iloscOsob);
                break;

            case '2':
                wyszukajAdresataPoImieniu(idZalogowanegoUzytkownika);
                break;

            case '3':
                wyszukajAdresataPoNazwisku(idZalogowanegoUzytkownika);
                break;

            case '4':
                wyswietlWszystkichAdresatow(idZalogowanegoUzytkownika);
                break;

            case '5':
                usunAdresata(adresaci, idZalogowanegoUzytkownika);
                break;

            case '6':
                edytujAdresata(adresaci, idZalogowanegoUzytkownika);
                break;

            case '7':
                zmienHaslo(uzytkownicy, idZalogowanegoUzytkownika, iloscOsob);
                break;

            case '8':
                idZalogowanegoUzytkownika = wylogujUzytkownika(adresaci, idZalogowanegoUzytkownika);
                break;
            }

        }
    }

    return 0;

}
