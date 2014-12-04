#include "serverform.h"
#include "ui_serverform.h"

ServerForm::ServerForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ServerForm)
{
    ui->setupUi(this);
}

ServerForm::~ServerForm()
{
    delete ui;
}
