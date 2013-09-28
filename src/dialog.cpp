#include <QtGui>
#include <iostream>
#include <string>
#include "include/dialog.h"

extern "C"{
#include "include/radiere.h"
#include "include/drumuire.h"
}

Dialog::Dialog(QWidget *parent): QDialog(parent){

    cancel = new QPushButton(tr("&Cancel"));
    ok     = new QPushButton(tr("&Ok"));

    ok -> setEnabled(false);

    inputLabel  = new QLabel(tr("Input File"));
    outputLabel = new QLabel(tr("Output File"));
    radiereRadioLabel  = new QLabel(tr("&Radiere"));
    drumuireRadioLabel = new QLabel(tr("&Drumuire"));

    QRegExp regExp("[A-Za-z0-9._]{0,255}");
    QRegExpValidator *valid = new QRegExpValidator(regExp);

    inputLine  = new QLineEdit;
    outputLine = new QLineEdit;

    inputLine  -> setFixedWidth(150);
    outputLine -> setFixedWidth(150);

    inputLine  -> setValidator(valid);
    outputLine -> setValidator(valid);

    radiereRadio  = new QRadioButton;
    drumuireRadio = new QRadioButton;

    radiereRadio -> setChecked(true);

    radiereRadioLabel  -> setBuddy(radiereRadio);
    drumuireRadioLabel -> setBuddy(drumuireRadio);

    inputLabel  -> setBuddy(inputLine);
    outputLabel -> setBuddy(outputLine);

    connect(ok, SIGNAL(clicked()), this, SLOT(okPressed()));
    connect(cancel, SIGNAL(clicked()), this, SLOT(close()));
    connect(inputLine, SIGNAL(textChanged(const QString&)), this, SLOT(changed()));
    connect(outputLine, SIGNAL(textChanged(const QString&)), this, SLOT(changed()));

    QHBoxLayout *topLeftLayout = new QHBoxLayout;
    topLeftLayout -> addWidget(inputLabel);
    topLeftLayout -> addStretch();
    topLeftLayout -> addWidget(inputLine);
    
    QHBoxLayout *bottomLeftLayout = new QHBoxLayout;
    bottomLeftLayout -> addWidget(outputLabel);
    bottomLeftLayout -> addWidget(outputLine);

    QVBoxLayout *buttons = new QVBoxLayout;
    buttons -> addWidget(ok);
    buttons -> addWidget(cancel);

    QHBoxLayout *radio = new QHBoxLayout;
    radio -> addStretch();
    radio -> addWidget(radiereRadioLabel);
    radio -> addWidget(radiereRadio);
    radio -> addWidget(drumuireRadioLabel);
    radio -> addWidget(drumuireRadio);

    QVBoxLayout *leftLayout = new QVBoxLayout;
    leftLayout -> addLayout(topLeftLayout);
    leftLayout -> addLayout(bottomLeftLayout);
    leftLayout -> addLayout(radio);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout -> addLayout(leftLayout);
    mainLayout -> addLayout(buttons);

    setLayout(mainLayout);

    setWindowTitle(tr("GNUTop"));
    setFixedSize(sizeHint());
}

void Dialog::okPressed(){
    QString input = inputLine -> text();
    std::string inputStr = input.toUtf8().constData();
    
    QString output = outputLine -> text();
    std::string outputStr = output.toUtf8().constData();

    char *inputPtr = const_cast<char *>(inputStr.c_str());
    char *outputPtr = const_cast<char *>(outputStr.c_str());

    if(radiereRadio -> isChecked()){
        radiere(inputPtr, outputPtr);
    }else if(drumuireRadio -> isChecked()){
        drumuire(inputPtr, outputPtr);
    }
}

void Dialog::changed(){
    if(inputLine  -> text().isEmpty() ||
       outputLine -> text().isEmpty() ){
        ok -> setEnabled(false);
    }else{
        ok -> setEnabled(true);
    }
}
