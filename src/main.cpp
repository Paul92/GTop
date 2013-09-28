#include <QApplication>
#include "dialog.h"

int main(int argc, char *argv[]){
    QApplication app(argc, argv);
    Dialog *dial = new Dialog;
    dial -> show();
    return app.exec();
}
