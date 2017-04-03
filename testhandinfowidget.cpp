#include "testhandinfowidget.h"

TestHandInfoWidget::TestHandInfoWidget(QWidget *parent)
    : QWidget(parent)
{
    m_chooser = new CardChooser;
    m_handinfo = new HandInfoWidget;
    QBoxLayout* layout = new QVBoxLayout(this);

    layout->addWidget(m_chooser);
    layout->addWidget(m_handinfo);

    connect(m_chooser, &CardChooser::sig_slected,
            this, &TestHandInfoWidget::onSelected);
    resize(900, 950);
}

void TestHandInfoWidget::onSelected()
{
    std::set<Card> s = m_chooser->selected_cards();
    Hand_Info info;
    info.set_cards(s);
    m_handinfo->display_info(info);
}
