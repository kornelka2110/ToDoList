#include "todo.h"

Task::Task(string t, string o, int p, string s) {
    this->tytul = t;
    this->opis = o;
    this->priorytet = p;
    this->status = s;
}

string Task::getTytul() { return tytul; }
string Task::getOpis() { return opis; }
int Task::getPriorytet() { return priorytet; }
string Task::getStatus() { return status; }

void Task::ustawTytul(string t) { this->tytul = t; }
void Task::ustawOpis(string o) { this->opis = o; }
void Task::ustawPriorytet(int p) { this->priorytet = p; }
void Task::ustawStatus(string s) { this->status = s; }

string Task::doPliku() {
    return tytul + "|" + opis + "|" + to_string(priorytet) + "|" + status;
}

void Task::wyswietl(int numer) {
    cout << "Numer zadania: " << numer << endl;
    
    if(priorytet == 1) cout << "Priorytet: wysoki" << endl;
    else if(priorytet == 2) cout << "Priorytet: sredni" << endl;
    else cout << "Priorytet: niski" << endl;

    cout << "Tytul: " << tytul << endl;
    cout << "Opis: " << opis << endl;
    cout << "Status: " << status << endl;
    cout << endl; 
}

TaskList::~TaskList() {
    for (size_t i = 0; i < lista.size(); i++) {
        delete lista[i];
    }
    lista.clear();
}

void TaskList::dodajZadanie(string t, string o, int p, string s) {
    Task* nowe = new Task(t, o, p, s);
    lista.push_back(nowe);
    cout << "Zadanie dodane." << endl;
}

void TaskList::usunZadanie(int numer) {
    if (numer > 0 && numer <= lista.size()) {
        delete lista[numer - 1];
        lista.erase(lista.begin() + (numer - 1));
        cout << "Zadanie usuniete." << endl;
    } else {
        cout << "Nie ma takiego numeru zadania." << endl;
    }
}

void TaskList::usunWszystkieZadania() {
    if (lista.empty()) {
        cout << "Lista jest juz pusta." << endl;
        return;
    }
    for (size_t i = 0; i < lista.size(); i++) {
        delete lista[i];
    }
    lista.clear();
    cout << "Wszystkie zadania zostaly usuniete!" << endl;
}

void TaskList::oznaczJakoWykonane(int numer) {
    if (numer > 0 && numer <= lista.size()) {
        lista[numer - 1]->ustawStatus("Zakonczone");
        cout << "Sukces! Zadanie nr " << numer << " oznaczone jako zakonczone." << endl;
    } else {
        cout << "Nie ma takiego numeru zadania." << endl;
    }
}

void TaskList::edytujZadanie(int numer) {
    if (numer > 0 && numer <= lista.size()) {
        Task* t = lista[numer - 1];
        cout << "Edytujesz zadanie nr " << numer << ": " << t->getTytul() << endl;
        
        string nowyTytul, nowyOpis, nowyStatus;
        int nowyPrio;
        int wyborStatusu;

        cout << "Nowy tytul: "; cin.ignore(); getline(cin, nowyTytul);
        cout << "Nowy opis: "; getline(cin, nowyOpis);
        cout << "Nowy priorytet (1-Wysoki, 2-Sredni, 3-Niski): "; cin >> nowyPrio;
        
        if(nowyPrio < 1 || nowyPrio > 3) {
            nowyPrio = 3; 
        }

        cout << "Wybierz nowy status:" << endl;
        cout << "1. Nowe" << endl;
        cout << "2. W trakcie" << endl;
        cout << "3. Zakonczone" << endl;
        cout << "Wybor: ";
        cin >> wyborStatusu;

        if (wyborStatusu == 2) nowyStatus = "W trakcie";
        else if (wyborStatusu == 3) nowyStatus = "Zakonczone";
        else nowyStatus = "Nowe";

        t->ustawTytul(nowyTytul);
        t->ustawOpis(nowyOpis);
        t->ustawPriorytet(nowyPrio);
        t->ustawStatus(nowyStatus);
        
        cout << "Zadanie zaktualizowane." << endl;
    } else {
        cout << "Nie ma takiego numeru zadania." << endl;
    }
}

void TaskList::wyswietlWszystkie() {
    if (lista.empty()) {
        cout << "Lista jest pusta." << endl;
        return;
    }
    cout << "\nWSZYSTKIE ZADANIA" << endl;
    for (size_t i = 0; i < lista.size(); i++) {
        lista[i]->wyswietl(i + 1);
    }
}

void TaskList::wyswietlTylkoDoZrobienia() {
    cout << "\nTYLKO NIEUKONCZONE" << endl;
    bool znaleziono = false;
    for (size_t i = 0; i < lista.size(); i++) {
        if (lista[i]->getStatus() != "Koniec" && lista[i]->getStatus() != "Zakonczone") {
            lista[i]->wyswietl(i + 1);
            znaleziono = true;
        }
    }
    if (!znaleziono) cout << "Brak zadan do zrobienia!" << endl;
}

void TaskList::zapiszDoPliku() {
    ofstream plik("tasks.txt");
    if (plik.good()) {
        for (size_t i = 0; i < lista.size(); i++) {
            plik << lista[i]->getTytul() << endl;
            plik << lista[i]->getOpis() << endl;
            plik << lista[i]->getPriorytet() << endl;
            plik << lista[i]->getStatus() << endl;
        }
        plik.close();
        cout << "Zapisano do pliku." << endl;
    }
}

void TaskList::wczytajZPliku() {
    ifstream plik("tasks.txt");
    if (!plik.good()) return;

    string t, o, s, p_str;
    while (getline(plik, t)) {
        getline(plik, o);
        getline(plik, p_str);
        getline(plik, s);
        if(t != "") {
            dodajZadanie(t, o, stoi(p_str), s);
        }
    }
    plik.close();
}

Uzytkownik::Uzytkownik(string n) {
    this->nick = n;
}


Menu::Menu() {
    lista = new TaskList();
   
}

Menu::~Menu() {
    delete lista;
    
}

void Menu::uruchom() {
    lista->wczytajZPliku();
    
    
    int wybor;
    bool dziala = true;

    while (dziala) {
        cout << "\n1. Dodaj zadanie" << endl;
        cout << "2. Wyswietl wszystkie" << endl;
        cout << "3. Filtr: Do zrobienia" << endl;
        cout << "4. Oznacz jako wykonane" << endl;
        cout << "5. Edytuj zadanie" << endl;
        cout << "6. Usun zadanie" << endl;
        cout << "7. Usun WSZYSTKIE zadania" << endl;
        cout << "8. Zapisz i Wyjdz" << endl;
        cout << "Wybor: ";
        
        if (!(cin >> wybor)) {
            cout << "Podaj liczbe!" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (wybor) {
        case 1: {
            string t, o, s;
            int p;
            int wyborStatusu;

            cout << "Tytul: "; cin.ignore(); getline(cin, t);
            cout << "Opis: "; getline(cin, o);
            cout << "Priorytet (1-Wysoki, 2-Sredni, 3-Niski): "; cin >> p;
            
            if(p < 1 || p > 3) p = 3; 
            
            cout << "Wybierz status:" << endl;
            cout << "1. Nowe" << endl;
            cout << "2. W trakcie" << endl;
            cout << "3. Zakonczone" << endl;
            cout << "Wybor: ";
            cin >> wyborStatusu;

            if (wyborStatusu == 2) s = "W trakcie";
            else if (wyborStatusu == 3) s = "Zakonczone";
            else s = "Nowe";

            lista->dodajZadanie(t, o, p, s);
            break;
        }
        case 2:
            lista->wyswietlWszystkie();
            break;
        case 3:
            lista->wyswietlTylkoDoZrobienia();
            break;
        case 4: {
            int numer;
            cout << "Podaj numer zadania do zakonczenia: "; cin >> numer;
            lista->oznaczJakoWykonane(numer);
            break;
        }
        case 5: {
            int numer;
            cout << "Podaj numer zadania do edycji: "; cin >> numer;
            lista->edytujZadanie(numer);
            break;
        }
        case 6: {
            int numer;
            cout << "Podaj numer zadania do usuniecia: "; cin >> numer;
            lista->usunZadanie(numer);
            break;
        }
        case 7: {
            char decyzja;
            cout << "Czy na pewno chcesz usunac WSZYSTKO? (t/n): "; cin >> decyzja;
            if(decyzja == 't' || decyzja == 'T') {
                lista->usunWszystkieZadania();
            } else {
                cout << "Anulowano." << endl;
            }
            break;
        }
        case 8:
            lista->zapiszDoPliku();
            dziala = false;
            break;
        default:
            cout << "Nie ma takiej opcji." << endl;
        }
    }
}