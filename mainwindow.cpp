#include <QSpinBox>
#include <QLineEdit>
#include <QComboBox>
#include <assert.h>
#include <QObject>
#include <QTextBrowser>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "appiumengine.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    capMap(),
    ui(new Ui::MainWindow)
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
    //this->installEventFilter(new EventListener(&MainWindow::eFilter, this));
    loadJson(QString(":/tools/caps_meta.json"), capMap);
    populateCapForm("android");
    ui->androidScrollArea->setWidgetResizable(true);
    //ui->androidScrollAreaContents->res
    new AppiumEngine(this);
}



bool MainWindow::eventFilter(QObject *sender, QEvent *ev)
{

    // http://qt-project.org/doc/qt-5/qevent.html for constants
    if (ev->type() == QEvent::Enter)
    {
         int i = sender->objectName().indexOf("_");
         assert(i != -1);

         auto capName = sender->objectName().mid(i + 1);
         ui->descriptionBrowser->setText(capMap[capName]->description());
         ui->helpBrowser->setText(capMap[capName]->help());
         return true;
    }
    else if (ev->type() == QEvent::Leave)
    {
         ui->descriptionBrowser->setText("");
         ui->helpBrowser->setText("");
         return true;
    }
    else if (sender->parent())
    {
            return sender->parent()->eventFilter( sender, ev );
    }
    else
    {
        return false;
    }
}

void MainWindow::populateCapForm(const QString &capGroup)
{
    for (std::unordered_map<const QString, const Cap* >::iterator i = capMap.begin(); i != capMap.end(); ++i) {
        if(i->second->group() == capGroup || i->second->group() == "common") {
            QWidget* widget = getWidgetForType(i->second);
            widget->setObjectName(capGroup + "_" + i->first);
            ui->androidForm->addRow(i->second->friendlyName(), widget );
            widget->installEventFilter(this);
        }
    }
}

QWidget* MainWindow::getWidgetForType(const Cap* cap)
{
    QWidget *widget = NULL;

    if (cap->type() == "string")
    {
            QLineEdit *lineEdit = new QLineEdit() ;
            lineEdit->setText(cap->value());
            QObject::connect(lineEdit, SIGNAL(textChanged(const QString)), cap, SLOT(setValue(const QString)));
            widget = lineEdit;
    }
    else if (cap->type() == "bool")
    {
        QComboBox *cb = new QComboBox();
        cb->addItem("false");
        cb->addItem("true");
        QObject::connect(cb, SIGNAL(currentIndexChanged(int)), cap, SLOT(setValue(int)));
        cb->setCurrentIndex(cap->value() == "false" ? 0 : 1);
        widget = cb;
    }
    else if (cap->type() == "int")
    {
        QSpinBox *sb = new QSpinBox();
        sb->setMaximum(1000000);
        sb->setMinimum(0);
        sb->setValue(cap->value().toInt());
        QObject::connect(sb, SIGNAL(valueChanged(const QString)), cap, SLOT(setValue(const QString)));
        widget = sb;
    }
    else
    {
        assert(false);
    }

    return widget;
}
