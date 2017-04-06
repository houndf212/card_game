#include "comparehandinfowidget.h"

CompareHandInfoWidget::CompareHandInfoWidget(QWidget *parent)
    : QWidget(parent)
{
    m_chooser1 = new CardChooser;
    m_chooser2 = new CardChooser;

    connect(m_chooser1, &CardChooser::sig_slected,
            this, &CompareHandInfoWidget::onChanged);

    connect(m_chooser2, &CardChooser::sig_slected,
            this, &CompareHandInfoWidget::onChanged);

    m_info_widget1 = new HandInfoWidget;
    m_info_widget2 = new HandInfoWidget;

    m_small_big = new QLabel;
    QFont font;
    font.setBold(true);
    font.setPointSize(40);
    m_small_big->setFont(font);

    QTabWidget *tab = new QTabWidget;
    tab->addTab(m_chooser1, "info1");
    tab->addTab(m_chooser2, "info2");

    QBoxLayout* hlayout = new QHBoxLayout;
    hlayout->addWidget(m_info_widget1);
    hlayout->addWidget(m_small_big);
    hlayout->addWidget(m_info_widget2);
    hlayout->addStretch(1);

    QBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(tab);
    layout->addLayout(hlayout);

    resize(900, 1000);
}

void CompareHandInfoWidget::onChanged()
{
    Hand_Info info1, info2;

    info1.set_cards(m_chooser1->selected_cards());
    info2.set_cards(m_chooser2->selected_cards());

    m_info_widget1->display_info(info1);
    m_info_widget2->display_info(info2);

    if (info1.isValid() && info2.isValid())
    {
        if (hand_less(info1, info2))
            m_small_big->setText("<");
        else
            m_small_big->setText(">");
    }
    else
    {
        m_small_big->setText("?");
    }
}
