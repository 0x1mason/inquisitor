#include <QSpinBox>
#include <QLineEdit>
#include <QComboBox>
#include <assert.h>
#include <QObject>
#include <QTextBrowser>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "deviceform.h"
#include "serverform.h"
#include "appiumclient.h"
#include <map>
#include <string>
#include <memory>

#include "seleniumpp/webdriver.hpp"
#include "seleniumpp/capabilities.hpp"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    capMap(),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    on_setup();
   // c = new AppiumClient(QUrl(QStringLiteral("ws://localhost:4723")), this);
    WebDriver* s = new WebDriver("http://localhost:4723/wd/hub", false);

    //creates new selenium session.
    auto caps = getCapKvps();
   Session* sess = s->createSession(&caps);

    //goes to the google home page.
   // sess->url("http://www.google.com");
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
    ui->horizontalLayout_4->addWidget(new DeviceForm(ui->iosTab));
    ui->horizontalLayout_5->addWidget(new ServerForm(ui->tab_3));
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


map<string, string> MainWindow::getCapKvps() {
    map<string, string> kvps;

    for (std::unordered_map<const QString, const Cap* >::iterator i = capMap.begin(); i != capMap.end(); ++i) {
        stringstream ss;
        if (!i->second->value().isNull() && !i->second->value().isEmpty()) {
            if (i->second->type() == "string") {
                ss << "\"" << i->second->value().toStdString() << "\"";
            } else {
                ss << i->second->value().toStdString();
            }
            qDebug() << ss.str().c_str();
            kvps[i->first.toStdString()] = ss.str();
        }
    }
return kvps;
   // return unique_ptr<map<string, string>>(&kvps);
}

void MainWindow::populateCapForm(const QString &capGroup)
{
    for (std::unordered_map<const QString, const Cap* >::iterator i = capMap.begin(); i != capMap.end(); ++i) {
        if(i->second->group() == capGroup || i->second->group() == "common") {
            QWidget* widget = getWidgetForType(i->second);
            widget->setObjectName(capGroup + "_" + i->first);
            ui->androidForm->setSpacing(7);
            ui->androidForm->addRow(i->second->friendlyName(), widget );
            widget->installEventFilter(this);
            auto label = ui->androidForm->labelForField(widget);
            QFont f( "Roboto", 14, QFont::Light);
            label->setFont(f);
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
