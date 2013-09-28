#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

class QPushButton;
class QLabel;
class QLineEdit;
class QRadioButton;

class Dialog:public QDialog{
    Q_OBJECT

    public:
        Dialog(QWidget *parent=0);

    signals:

    private slots:
        void okPressed();
        void changed();

    private:
        QPushButton *cancel, *ok;
        QLabel *inputLabel, *outputLabel, *radiereRadioLabel, *drumuireRadioLabel;
        QLineEdit *inputLine, *outputLine;
        QRadioButton *radiereRadio, *drumuireRadio;

};
#endif
