#include "debugdock.h"

DebugDock::DebugDock(QWidget *parent) :
    QDockWidget(parent)
{
}

void DebugDock::closeEvent(QCloseEvent *event)
{
    if (this->isFloating())
    {
        event->ignore();
        this->setFloating(false);
    }
}
