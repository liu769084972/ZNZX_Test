#include "SortUI.h"
#include "CalculateSortDataUI.h"
#include "SortDataShowUI.h"
SortUI::SortUI( QWidget *parent)
{
    setFrameShape(QFrame::Box);
    calSortData = new CalculateSortDataUI;
    sortData = new SortDataShowUI;

    layoutMain = new QVBoxLayout;
    layoutMain->addWidget(calSortData);
    layoutMain->addWidget(sortData);

    setLayout(layoutMain);
}
