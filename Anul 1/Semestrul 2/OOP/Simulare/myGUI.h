#pragma once

#include <QtWidgets/QApplication>
#include<qlistwidget.h>

#include "qboxlayout.h"
#include "Service.h"
#include"Abonament.h"
#include<vector>
using std::vector;
#include<string>
using std::string;

#include"qlineedit.h"
#include"qspinbox.h"
#include "qpushbutton.h"
#include "qformlayout.h"

class myGUI:public QWidget
{

private:
	Service& srv;

	QHBoxLayout* lyMain = new QHBoxLayout;
	QVBoxLayout* ly = new QVBoxLayout;

	QListWidget* lst = new QListWidget;

	QLineEdit* l = new QLineEdit;

	QSpinBox* sp1 = new QSpinBox;
	QSpinBox* sp2 = new QSpinBox;
	QPushButton* mod = new QPushButton("Modifica intrari");
	QPushButton* viz = new QPushButton("Vizualizare dupa pret");
	QPushButton* sort = new QPushButton("Sortare");
	QPushButton* nesort = new QPushButton("Afiseaza nesortat");

	//functie pentru initializare GUI
	void initGUI();

	//functie pentru incarcarea abonamentelor in lista din GUI
	// ab- vectorul de abonamente
	void reloadList(const vector<Abonament>& ab);

	//functie pentru conectarea semnalelor
	void connect();

	
public:

	myGUI(Service& srv) :srv{ srv }
	{
		initGUI();
		reloadList(srv.get_all());
		connect();
	}
};

