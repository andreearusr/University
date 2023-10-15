#include "myGUI.h"
#include <random>

void myGUI::initGUI()
{
	setLayout(lyMain);
	lyMain->addWidget(lst);

	QFormLayout* lyF = new QFormLayout;
	lyF->addRow("Tip", l);

	ly->addWidget(sp1);
	ly->addWidget(sp2);
	ly->addWidget(mod);
	ly->addWidget(viz);
	ly->addWidget(sort);
	ly->addWidget(nesort);

	ly->addLayout(lyF);
	lyMain->addLayout(ly);

}

void myGUI::reloadList(const vector<Abonament>& ab)
{
	lst->clear();
	for (const Abonament& a : ab)
	{
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(a.get_nume()) + "," + QString::number(a.get_pret()) +","+ QString::number(a.get_numar()));
		lst->addItem(item);
	}

}


void myGUI::connect() {

	QObject::connect(sort, &QPushButton::clicked, this, [=]()
		{
			reloadList(srv.sortare());
		});

	QObject::connect(nesort, &QPushButton::clicked, this, [=]()
		{
			reloadList(srv.get_all());
		});

	QObject::connect(viz, &QPushButton::clicked, this, [=]()
		{
			lst->clear();
			int S = 0;
			int nr = 0;
			int Medie;
			for (const Abonament& a : srv.get_all())
			{
				int pret = a.get_pret();
				int nr_intrari = a.get_numar();
				int pret_total = pret * nr_intrari;

				 S += pret_total;
				 nr++;
			}
			Medie = S / nr;

			for (const Abonament& a : srv.get_all())
			{
				int pret = a.get_pret();
				int nr_intrari = a.get_numar();
				int pret_total = pret * nr_intrari;

				if (pret_total < Medie)
				{
					QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(a.get_nume()) + "," + QString::number(a.get_pret()) + "," + QString::number(a.get_numar()));
					item->setData(Qt::BackgroundRole, QBrush(Qt::green));
					lst->addItem(item);
				}
				else
				{
					QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(a.get_nume()) + "," + QString::number(a.get_pret()) + "," + QString::number(a.get_numar()));
					lst->addItem(item);
				}
			}


		});

	QObject::connect(mod, &QPushButton::clicked, this, [=]()
		{
			lst->clear();
			string tip = l->text().toStdString();
			for (const Abonament& a : srv.get_all())
			{
				if (a.get_tip() == tip)
				{
					int minIntrari = sp1->value();
					int maxIntrari = sp2->value();
					int valoare = _RANDOM_(minIntrari, maxIntrari);
					QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(a.get_nume()) + "," + QString::number(a.get_pret()) + "," + QString::number(valoare));
					lst->addItem(item);
				}
				else {
					QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(a.get_nume()) + "," + QString::number(a.get_pret()) + "," + QString::number(a.get_numar()));
					lst->addItem(item);
				}
			}
		});

}
