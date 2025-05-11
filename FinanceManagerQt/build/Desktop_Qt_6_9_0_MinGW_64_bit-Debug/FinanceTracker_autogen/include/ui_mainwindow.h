/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QDate>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *topLayout;
    QLabel *totalIncomeLabel;
    QLabel *totalExpenseLabel;
    QLabel *balanceLabel;
    QHBoxLayout *filterLayout;
    QComboBox *categoryFilter;
    QComboBox *typeFilter;
    QDateEdit *fromDate;
    QDateEdit *toDate;
    QPushButton *filterButton;
    QTableWidget *transactionsTable;
    QHBoxLayout *buttonLayout;
    QPushButton *addButton;
    QPushButton *editButton;
    QPushButton *deleteButton;
    QPushButton *saveReportButton;
    QWidget *chartWidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1000, 700);
        MainWindow->setStyleSheet(QString::fromUtf8("/* Main window styling with purple theme */\n"
"QMainWindow {\n"
"    background-color: #2a1a3d; /* Dark purple background */\n"
"}\n"
"QLabel {\n"
"    color: #e0d4ff; /* Light purple text */\n"
"    font-size: 14px;\n"
"}\n"
"QPushButton {\n"
"    background-color: #6b4e9e; /* Medium purple */\n"
"    color: white;\n"
"    border: 1px solid #8a70c1;\n"
"    border-radius: 5px;\n"
"    padding: 8px;\n"
"    font-size: 14px;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #8a70c1; /* Lighter purple on hover */\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #4b367c; /* Darker purple when-pressed */\n"
"}\n"
"QTableWidget {\n"
"    background-color: #3c2957; /* Slightly lighter purple for table */\n"
"    color: #e0d4ff;\n"
"    gridline-color: #6b4e9e;\n"
"    selection-background-color: #8a70c1;\n"
"}\n"
"QTableWidget::item {\n"
"    padding: 5px;\n"
"    color: #000000; /* Black text color for table items */\n"
"}\n"
"QHeaderView::section {\n"
"    background-color: #6b4e9e;\n"
"    color: "
                        "white;\n"
"    padding: 5px;\n"
"    border: 1px solid #8a70c1;\n"
"}\n"
"QComboBox {\n"
"    background-color: #3c2957;\n"
"    color: #e0d4ff;\n"
"    border: 1px solid #6b4e9e;\n"
"    border-radius: 3px;\n"
"    padding: 5px;\n"
"}\n"
"QComboBox::drop-down {\n"
"    border: none;\n"
"}\n"
"QComboBox:hover {\n"
"    background-color: #4b367c;\n"
"}\n"
"QDateEdit {\n"
"    background-color: #3c2957;\n"
"    color: #e0d4ff;\n"
"    border: 1px solid #6b4e9e;\n"
"    border-radius: 3px;\n"
"    padding: 5px;\n"
"}\n"
"QWidget#chartWidget {\n"
"    background-color: #3c2957;\n"
"    border: 1px solid #6b4e9e;\n"
"    border-radius: 5px;\n"
"}"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        topLayout = new QHBoxLayout();
        topLayout->setObjectName("topLayout");
        totalIncomeLabel = new QLabel(centralwidget);
        totalIncomeLabel->setObjectName("totalIncomeLabel");

        topLayout->addWidget(totalIncomeLabel);

        totalExpenseLabel = new QLabel(centralwidget);
        totalExpenseLabel->setObjectName("totalExpenseLabel");

        topLayout->addWidget(totalExpenseLabel);

        balanceLabel = new QLabel(centralwidget);
        balanceLabel->setObjectName("balanceLabel");

        topLayout->addWidget(balanceLabel);


        verticalLayout->addLayout(topLayout);

        filterLayout = new QHBoxLayout();
        filterLayout->setObjectName("filterLayout");
        categoryFilter = new QComboBox(centralwidget);
        categoryFilter->addItem(QString());
        categoryFilter->setObjectName("categoryFilter");

        filterLayout->addWidget(categoryFilter);

        typeFilter = new QComboBox(centralwidget);
        typeFilter->addItem(QString());
        typeFilter->addItem(QString());
        typeFilter->addItem(QString());
        typeFilter->setObjectName("typeFilter");

        filterLayout->addWidget(typeFilter);

        fromDate = new QDateEdit(centralwidget);
        fromDate->setObjectName("fromDate");
        fromDate->setCalendarPopup(true);
        fromDate->setDate(QDate(2025, 1, 1));

        filterLayout->addWidget(fromDate);

        toDate = new QDateEdit(centralwidget);
        toDate->setObjectName("toDate");
        toDate->setCalendarPopup(true);
        toDate->setDate(QDate(2025, 12, 31));

        filterLayout->addWidget(toDate);

        filterButton = new QPushButton(centralwidget);
        filterButton->setObjectName("filterButton");

        filterLayout->addWidget(filterButton);


        verticalLayout->addLayout(filterLayout);

        transactionsTable = new QTableWidget(centralwidget);
        transactionsTable->setObjectName("transactionsTable");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(2);
        sizePolicy.setHeightForWidth(transactionsTable->sizePolicy().hasHeightForWidth());
        transactionsTable->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(transactionsTable);

        buttonLayout = new QHBoxLayout();
        buttonLayout->setObjectName("buttonLayout");
        addButton = new QPushButton(centralwidget);
        addButton->setObjectName("addButton");

        buttonLayout->addWidget(addButton);

        editButton = new QPushButton(centralwidget);
        editButton->setObjectName("editButton");

        buttonLayout->addWidget(editButton);

        deleteButton = new QPushButton(centralwidget);
        deleteButton->setObjectName("deleteButton");

        buttonLayout->addWidget(deleteButton);

        saveReportButton = new QPushButton(centralwidget);
        saveReportButton->setObjectName("saveReportButton");

        buttonLayout->addWidget(saveReportButton);


        verticalLayout->addLayout(buttonLayout);

        chartWidget = new QWidget(centralwidget);
        chartWidget->setObjectName("chartWidget");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(1);
        sizePolicy1.setHeightForWidth(chartWidget->sizePolicy().hasHeightForWidth());
        chartWidget->setSizePolicy(sizePolicy1);
        chartWidget->setMinimumSize(QSize(0, 200));

        verticalLayout->addWidget(chartWidget);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1000, 17));
        menubar->setStyleSheet(QString::fromUtf8("QMenuBar {\n"
"    background-color: #6b4e9e;\n"
"    color: white;\n"
"}\n"
"QMenuBar::item:selected {\n"
"    background-color: #8a70c1;\n"
"}"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        statusbar->setStyleSheet(QString::fromUtf8("QStatusBar {\n"
"    background-color: #6b4e9e;\n"
"    color: white;\n"
"}"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Financial Manager", nullptr));
        totalIncomeLabel->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\321\205\320\276\320\264\321\213: 0.00 \321\200\321\203\320\261.", nullptr));
        totalExpenseLabel->setText(QCoreApplication::translate("MainWindow", "\320\240\320\260\321\201\321\205\320\276\320\264\321\213: 0.00 \321\200\321\203\320\261.", nullptr));
        balanceLabel->setText(QCoreApplication::translate("MainWindow", "\320\221\320\260\320\273\320\260\320\275\321\201: 0.00 \321\200\321\203\320\261.", nullptr));
        categoryFilter->setItemText(0, QCoreApplication::translate("MainWindow", "\320\222\321\201\320\265", nullptr));

        typeFilter->setItemText(0, QCoreApplication::translate("MainWindow", "\320\222\321\201\320\265", nullptr));
        typeFilter->setItemText(1, QCoreApplication::translate("MainWindow", "\320\224\320\276\321\205\320\276\320\264", nullptr));
        typeFilter->setItemText(2, QCoreApplication::translate("MainWindow", "\320\240\320\260\321\201\321\205\320\276\320\264", nullptr));

        filterButton->setText(QCoreApplication::translate("MainWindow", "\320\244\320\270\320\273\321\214\321\202\321\200", nullptr));
        addButton->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", nullptr));
        editButton->setText(QCoreApplication::translate("MainWindow", "\320\240\320\265\320\264\320\260\320\272\321\202\320\270\321\200\320\276\320\262\320\260\321\202\321\214", nullptr));
        deleteButton->setText(QCoreApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));
        saveReportButton->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \320\276\321\202\321\207\320\265\321\202", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
