
#include <QtWidgets/QApplication>
#include"myGUI.h"
#include "Abonament.h"
#include "Service.h"
#include"Repository.h"
#include "Teste.h"
int main(int argc, char* argv[])
{
    testare(); 
    {
        QApplication a(argc, argv);

        Repository r{ "abonamente.txt" };
        Service srv{ r };

        myGUI gui{ srv };
        gui.show();
        return a.exec();
    }

}
