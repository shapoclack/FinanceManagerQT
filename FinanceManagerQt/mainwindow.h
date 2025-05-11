#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QDate>
#include <QChartView>
#include <QBarSeries>
#include <QBarSet>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct Transaction {
    int id;
    QDate date;
    QString description;
    double amount;
    QString category;
    bool isIncome;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void addButtonClicked();
    void editButtonClicked();
    void deleteButtonClicked();
    void transactionsTableCellDoubleClicked(int row, int column);
    void saveReportButtonClicked();
    void updateStatistics();
    void loadTransactions();
    void saveTransactions();
    void updateTransactionsTable();
    void filterTransactions();

private:
    Ui::MainWindow *ui;
    QVector<Transaction> transactions;
    int nextId = 1;
    QChartView *barChartView;
    QBarSeries *barSeries;
    void updateCharts();
};

#endif
