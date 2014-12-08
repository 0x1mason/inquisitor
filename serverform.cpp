#include "serverform.h"
#include "ui_serverform.h"

ServerForm::ServerForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ServerForm)
{
    ui->setupUi(this);
  //  QObject::connect(lineEdit, SIGNAL(textChanged(const QString)), cap, SLOT(setValue(const QString)));
}

ServerForm::~ServerForm()
{
    delete ui;
}
