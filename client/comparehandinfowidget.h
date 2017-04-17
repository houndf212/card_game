#ifndef COMPAREHANDINFOWIDGET_H
#define COMPAREHANDINFOWIDGET_H

#include <QtWidgets>
#include "cardchooser.h"
#include "handinfowidget.h"

class CompareHandInfoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CompareHandInfoWidget(QWidget *parent = 0);
private:
    Q_SLOT void onChanged();
    void do_compare();
private:
    CardChooser* m_chooser1;
    CardChooser* m_chooser2;

    HandInfoWidget *m_info_widget1;
    HandInfoWidget *m_info_widget2;
    QLabel *m_small_big;

};

#endif // COMPAREHANDINFOWIDGET_H
