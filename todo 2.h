#ifndef TODO_H
#define TODO_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <limits> 

using namespace std;

class Task {
private:
    string tytul;
    string opis;
    int priorytet; 
    string status; 

public:
    Task(string t, string o, int p, string s);

    string getTytul();
    string getOpis();
    int getPriorytet();
    string getStatus();

    void ustawTytul(string t);
    void ustawOpis(string o);
    void ustawPriorytet(int p);
    void ustawStatus(string s);

    string doPliku();
    void wyswietl(int numer);
};

class TaskList {
private:
    vector<Task*> lista;

public:
    ~TaskList();

    void dodajZadanie(string t, string o, int p, string s);
    void usunZadanie(int numer);
    void usunWszystkieZadania();
    void oznaczJakoWykonane(int numer);
    void edytujZadanie(int numer);
    void wyswietlWszystkie();
    void wyswietlTylkoDoZrobienia();
    void zapiszDoPliku();
    void wczytajZPliku();
};

class Uzytkownik {
private:
    string nick;

public:
    Uzytkownik(string n);
    void powitanie();
};

class Menu {
private:
    TaskList* lista;
    Uzytkownik* user;

public:
    Menu();
    ~Menu();
    void uruchom();
};

#endif