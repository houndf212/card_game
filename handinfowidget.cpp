#include "handinfowidget.h"

HandInfoWidget::HandInfoWidget(QWidget *parent)
    : QWidget(parent)
    ,m_size(new QLabel)
    ,m_type(new QLabel)
    ,m_type_size(new QLabel)
    ,m_prime(new QLabel)
    ,m_prime_size(new QLabel)
{
    QFormLayout *layout = new QFormLayout(this);
    layout->addRow("size", m_size);
    layout->addRow("type", m_type);
    layout->addRow("type size", m_type_size);
    layout->addRow("prime", m_prime);
    layout->addRow("prime size", m_prime_size);
}

void HandInfoWidget::display_info(const Hand_Info &info)
{
    m_size->setText(QString::number(info.size()));

    QVariant type;
    type.setValue(info.type());
    m_type->setText(type.toString());

    m_type_size->setText(QString::number(info.type_size()));

    QVariant prime;
    prime.setValue(info.prime());
    m_prime->setText(prime.toString());

    m_prime_size->setText(QString::number(info.prime_size()));
}
