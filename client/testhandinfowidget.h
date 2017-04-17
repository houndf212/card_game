#ifndef TESTHANDINFOWIDGET_H
#define TESTHANDINFOWIDGET_H

#include <QWidget>
#include "cardchooser.h"
#include "handinfowidget.h"

class TestHandInfoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TestHandInfoWidget(QWidget *parent = 0);
private:
    Q_SLOT void onSelected();
private:
    CardChooser *m_chooser;
    HandInfoWidget *m_handinfo;
};

#endif // TESTHANDINFOWIDGET_H
