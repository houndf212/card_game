#ifndef HANDINFOWIDGET_H
#define HANDINFOWIDGET_H

#include <QtWidgets>
#include <set>
#include "card.h"
#include "hand_info.h"

class HandInfoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit HandInfoWidget(QWidget *parent = 0);
    void display_info(const Hand_Info& info);
private:
    QLabel *m_size;
    QLabel *m_type;
    QLabel *m_type_size;
    QLabel *m_prime;
    QLabel *m_prime_size;
};

#endif // HANDINFOWIDGET_H
