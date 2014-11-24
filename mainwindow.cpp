
#include <QLineEdit>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "appiumengine.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    capMap()
{
    ui->setupUi(this);
    on_setup();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_setup()
{
    loadJson(QString("../../caps_meta.json"), capMap);

    for (std::map<const QString,QSharedPointer<Cap> >::iterator i = capMap.begin(); i != capMap.end(); ++i) {
        if(i->second->group() == "android" || i->second->group() == "common") {
            QLineEdit *lineEdit = new QLineEdit() ;
            lineEdit->setObjectName("android_" + i->first);
            QObject::connect(lineEdit, SIGNAL(textChanged(const QString)), i->second.data(), SLOT(setValue(const QString)));
            ui->androidForm->addRow(i->second->friendlyName(), lineEdit );
        }
    }
AppiumEngine a(NULL);
    //ui->androidScrollArea->setLayout(ui->androidForm);
}

