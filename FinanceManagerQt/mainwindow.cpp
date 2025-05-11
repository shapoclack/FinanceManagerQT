#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QInputDialog>
#include <QDateEdit>
#include <QChart>
#include <QBarSeries>
#include <QBarSet>
#include <QBarCategoryAxis>
#include <QValueAxis>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->transactionsTable->setColumnCount(6);
    ui->transactionsTable->setHorizontalHeaderLabels({"ID", "Дата", "Описание", "Сумма", "Категория", "Тип"});
    ui->transactionsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    barChartView = new QChartView(this);
    barChartView->setRenderHint(QPainter::Antialiasing);

    barSeries = new QBarSeries();

    QChart *barChart = new QChart();
    barChart->addSeries(barSeries);
    barChart->setTitle("Динамика доходов и трат по категориям");
    barChart->legend()->setVisible(true);
    barChart->legend()->setAlignment(Qt::AlignBottom);
    barChartView->setChart(barChart);

    QVBoxLayout *chartLayout = new QVBoxLayout;
    chartLayout->addWidget(barChartView);
    ui->chartWidget->setLayout(chartLayout);

    loadTransactions();
    updateTransactionsTable();
    updateStatistics();
    updateCharts();

    connect(ui->addButton, &QPushButton::clicked, this, &MainWindow::addButtonClicked);
    connect(ui->editButton, &QPushButton::clicked, this, &MainWindow::editButtonClicked);
    connect(ui->deleteButton, &QPushButton::clicked, this, &MainWindow::deleteButtonClicked);
    connect(ui->transactionsTable, &QTableWidget::cellDoubleClicked, this, &MainWindow::transactionsTableCellDoubleClicked);
    connect(ui->filterButton, &QPushButton::clicked, this, &MainWindow::filterTransactions);
    connect(ui->saveReportButton, &QPushButton::clicked, this, &MainWindow::saveReportButtonClicked);
}

MainWindow::~MainWindow()
{
    saveTransactions();
    delete ui;
}

void MainWindow::addButtonClicked()
{
    bool ok;
    QString description = QInputDialog::getText(this, "Добавить транзакцию",
                                                "Описание:", QLineEdit::Normal, "", &ok);
    if (!ok || description.isEmpty()) {
        if (ok && description.isEmpty()) {
            QMessageBox::warning(this, "Ошибка", "Описание не может быть пустым");
        }
        return;
    }

    double amount = QInputDialog::getDouble(this, "Добавить транзакцию",
                                            "Сумма:", 0, -1000000, 1000000, 2, &ok);
    if (!ok) return;
    if (amount <= 0) {
        QMessageBox::warning(this, "Ошибка", "Сумма должна быть больше нуля");
        return;
    }

    QString category = QInputDialog::getText(this, "Добавить транзакцию",
                                             "Категория:", QLineEdit::Normal, "", &ok);
    if (!ok || category.isEmpty()) {
        if (ok && category.isEmpty()) {
            QMessageBox::warning(this, "Ошибка", "Категория не может быть пустой");
        }
        return;
    }

    QStringList types = {"Доход", "Расход"};
    QString type = QInputDialog::getItem(this, "Добавить транзакцию",
                                         "Тип:", types, 0, false, &ok);
    if (!ok) return;


    double totalIncome = 0;
    double totalExpense = 0;
    for (const Transaction &t : transactions) {
        if (t.isIncome) {
            totalIncome += t.amount;
        } else {
            totalExpense += t.amount;
        }
    }
    double currentBalance = totalIncome - totalExpense;


    if (type == "Расход" && currentBalance <= 0) {
        QMessageBox::warning(this, "Ошибка", "Нельзя добавить расход при нулевом балансе");
        return;
    }

    Transaction newTransaction;
    newTransaction.id = nextId++;
    newTransaction.date = QDate::currentDate();
    newTransaction.description = description;
    newTransaction.amount = amount;
    newTransaction.category = category;
    newTransaction.isIncome = (type == "Доход");

    transactions.append(newTransaction);
    updateTransactionsTable();
    updateStatistics();
    updateCharts();
}

void MainWindow::editButtonClicked()
{
    int row = ui->transactionsTable->currentRow();
    if (row == -1) {
        QMessageBox::warning(this, "Ошибка", "Выберите транзакцию для редактирования");
        return;
    }

    int id = ui->transactionsTable->item(row, 0)->text().toInt();
    auto it = std::find_if(transactions.begin(), transactions.end(),
                           [id](const Transaction &t) { return t.id == id; });
    if (it == transactions.end()) return;

    bool ok;
    QString description = QInputDialog::getText(this, "Редактировать транзакцию",
                                                "Описание:", QLineEdit::Normal, it->description, &ok);
    if (!ok || description.isEmpty()) {
        if (ok && description.isEmpty()) {
            QMessageBox::warning(this, "Ошибка", "Описание не может быть пустым");
        }
        return;
    }

    double amount = QInputDialog::getDouble(this, "Редактировать транзакцию",
                                            "Сумма:", it->amount, -1000000, 1000000, 2, &ok);
    if (!ok) return;
    if (amount <= 0) {
        QMessageBox::warning(this, "Ошибка", "Сумма должна быть больше нуля");
        return;
    }

    QString category = QInputDialog::getText(this, "Редактировать транзакцию",
                                             "Категория:", QLineEdit::Normal, it->category, &ok);
    if (!ok || category.isEmpty()) {
        if (ok && category.isEmpty()) {
            QMessageBox::warning(this, "Ошибка", "Категория не может быть пустой");
        }
        return;
    }

    QString dateStr = QInputDialog::getText(this, "Редактировать транзакцию",
                                            "Дата (dd.MM.yyyy):", QLineEdit::Normal, it->date.toString("dd.MM.yyyy"), &ok);
    if (!ok) return;
    QDate date = QDate::fromString(dateStr, "dd.MM.yyyy");
    if (!date.isValid()) {
        QMessageBox::warning(this, "Ошибка", "Неверный формат даты. Используйте dd.MM.yyyy");
        return;
    }

    QStringList types = {"Доход", "Расход"};
    QString type = QInputDialog::getItem(this, "Редактировать транзакцию",
                                         "Тип:", types, it->isIncome ? 0 : 1, false, &ok);
    if (!ok) return;

    it->description = description;
    it->amount = amount;
    it->category = category;
    it->date = date;
    it->isIncome = (type == "Доход");

    updateTransactionsTable();
    updateStatistics();
    updateCharts();
}

void MainWindow::deleteButtonClicked()
{
    int row = ui->transactionsTable->currentRow();
    if (row == -1) {
        QMessageBox::warning(this, "Ошибка", "Выберите транзакцию для удаления");
        return;
    }

    int id = ui->transactionsTable->item(row, 0)->text().toInt();
    auto it = std::find_if(transactions.begin(), transactions.end(),
                           [id](const Transaction &t) { return t.id == id; });
    if (it == transactions.end()) return;

    if (QMessageBox::question(this, "Удаление", "Вы уверены, что хотите удалить эту транзакцию?") == QMessageBox::Yes) {
        transactions.erase(it);
        updateTransactionsTable();
        updateStatistics();
        updateCharts();
    }
}

void MainWindow::transactionsTableCellDoubleClicked(int row, int column)
{
    Q_UNUSED(column);
    editButtonClicked();
}

void MainWindow::updateStatistics()
{
    double totalIncome = 0;
    double totalExpense = 0;
    QMap<QString, double> categories;

    for (const Transaction &t : transactions) {
        if (t.isIncome) {
            totalIncome += t.amount;
        } else {
            totalExpense += t.amount;
            categories[t.category] += t.amount;
        }
    }

    double balance = totalIncome - totalExpense;

    ui->totalIncomeLabel->setText(QString("Доходы: %1 руб.").arg(totalIncome, 0, 'f', 2));
    ui->totalExpenseLabel->setText(QString("Расходы: %1 руб.").arg(totalExpense, 0, 'f', 2));
    ui->balanceLabel->setText(QString("Баланс: %1 руб.").arg(balance, 0, 'f', 2));
}

void MainWindow::updateCharts()
{
    barSeries->clear();


    QMap<QString, double> totalByCategory;
    for (const Transaction &t : transactions) {
        totalByCategory[t.category] += t.amount * (t.isIncome ? 1 : -1);
    }


    QBarSet *incomeSet = new QBarSet("Доходы");
    QBarSet *expenseSet = new QBarSet("Расходы");
    QStringList categories;
    for (auto it = totalByCategory.constBegin(); it != totalByCategory.constEnd(); ++it) {
        double value = it.value();
        if (value > 0) {
            *incomeSet << value;
        } else {
            *expenseSet << -value;
        }
        categories << it.key();
    }

    barSeries->append(incomeSet);
    barSeries->append(expenseSet);

    QChart *barChart = barChartView->chart();
    barChart->removeSeries(barSeries);


    QList<QAbstractAxis*> axes = barChart->axes();
    for (QAbstractAxis *axis : axes) {
        barChart->removeAxis(axis);
        delete axis;
    }


    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    axisX->setTitleText("Категории");
    barChart->addAxis(axisX, Qt::AlignBottom);
    barSeries->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("Сумма (руб.)");
    barChart->addAxis(axisY, Qt::AlignLeft);
    barSeries->attachAxis(axisY);

    barChart->setTitle("Динамика доходов и трат по категориям");
    barChart->addSeries(barSeries);

    if (barSeries->barSets().isEmpty()) {
        barChart->setTitle("Нет данных для графика");
    }
}

void MainWindow::loadTransactions()
{
    QFile file("transactions.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    QSet<QString> categories;
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(";");
        if (parts.size() != 6) continue;

        Transaction t;
        t.id = parts[0].toInt();
        t.date = QDate::fromString(parts[1], "dd.MM.yyyy");
        t.description = parts[2];
        t.amount = parts[3].toDouble();
        t.category = parts[4];
        t.isIncome = parts[5] == "1";

        if (!t.isIncome) {
            t.amount = -t.amount;
        }

        transactions.append(t);
        categories.insert(t.category);
        if (t.id >= nextId) nextId = t.id + 1;
    }
    file.close();

    ui->categoryFilter->clear();
    QStringList items;
    items << "Все";
    items.append(QList<QString>(categories.constBegin(), categories.constEnd()));
    ui->categoryFilter->addItems(items);
}

void MainWindow::saveTransactions()
{
    QFile file("transactions.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    for (const Transaction &t : transactions) {
        out << t.id << ";"
            << t.date.toString("dd.MM.yyyy") << ";"
            << t.description << ";"
            << t.amount << ";"
            << t.category << ";"
            << (t.isIncome ? "1" : "0") << "\n";
    }

    file.close();
}

void MainWindow::saveReportButtonClicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Сохранить отчет", "", "Text Files (*.txt)");
    if (fileName.isEmpty())
        return;

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл для записи");
        return;
    }

    QTextStream out(&file);
    out << "Финансовый отчет\n";
    out << "Дата создания: " << QDate::currentDate().toString("dd.MM.yyyy") << "\n\n";

    double totalIncome = 0;
    double totalExpense = 0;
    QMap<QString, double> categories;

    for (const Transaction &t : transactions) {
        if (t.isIncome) {
            totalIncome += t.amount;
        } else {
            totalExpense += t.amount;
            categories[t.category] += t.amount;
        }
    }

    out << "Общая статистика:\n";
    out << "Доходы: " << QString::number(totalIncome, 'f', 2) << " руб.\n";
    out << "Расходы: " << QString::number(totalExpense, 'f', 2) << " руб.\n";
    out << "Баланс: " << QString::number(totalIncome - totalExpense, 'f', 2) << " руб.\n\n";

    out << "Расходы по категориям:\n";
    for (auto it = categories.constBegin(); it != categories.constEnd(); ++it) {
        out << it.key() << ": " << QString::number(it.value(), 'f', 2) << " руб.\n";
    }

    out << "\nДетализация транзакций:\n";
    for (const Transaction &t : transactions) {
        out << "ID: " << t.id << "\n";
        out << "Дата: " << t.date.toString("dd.MM.yyyy") << "\n";
        out << "Описание: " << t.description << "\n";
        out << "Сумма: " << QString::number(t.amount, 'f', 2) << " руб.\n";
        out << "Категория: " << t.category << "\n";
        out << "Тип: " << (t.isIncome ? "Доход" : "Расход") << "\n\n";
    }

    file.close();
    QMessageBox::information(this, "Успех", "Отчет успешно сохранен");
}

void MainWindow::updateTransactionsTable()
{
    ui->transactionsTable->setRowCount(0);

    for (const Transaction &t : transactions) {
        int row = ui->transactionsTable->rowCount();
        ui->transactionsTable->insertRow(row);

        ui->transactionsTable->setItem(row, 0, new QTableWidgetItem(QString::number(t.id)));
        ui->transactionsTable->setItem(row, 1, new QTableWidgetItem(t.date.toString("dd.MM.yyyy")));
        ui->transactionsTable->setItem(row, 2, new QTableWidgetItem(t.description));
        ui->transactionsTable->setItem(row, 3, new QTableWidgetItem(QString::number(t.amount, 'f', 2)));
        ui->transactionsTable->setItem(row, 4, new QTableWidgetItem(t.category));
        ui->transactionsTable->setItem(row, 5, new QTableWidgetItem(t.isIncome ? "Доход" : "Расход"));

        for (int col = 0; col < 6; ++col) {
            QTableWidgetItem *item = ui->transactionsTable->item(row, col);
            if (t.isIncome) {
                item->setBackground(QColor(200, 255, 200));
            } else {
                item->setBackground(QColor(255, 200, 200));
            }
        }
    }
}

void MainWindow::filterTransactions()
{
    QString categoryFilter = ui->categoryFilter->currentText();
    QString typeFilter = ui->typeFilter->currentText();
    QDate fromDate = ui->fromDate->date();
    QDate toDate = ui->toDate->date();

    for (int i = 0; i < ui->transactionsTable->rowCount(); ++i) {
        bool showRow = true;

        QDate date = QDate::fromString(ui->transactionsTable->item(i, 1)->text(), "dd.MM.yyyy");
        QString type = ui->transactionsTable->item(i, 5)->text();
        QString category = ui->transactionsTable->item(i, 4)->text();

        if (!categoryFilter.isEmpty() && categoryFilter != "Все" && category != categoryFilter) {
            showRow = false;
        }
        if (!typeFilter.isEmpty() && typeFilter != "Все" && type != typeFilter) {
            showRow = false;
        }
        if (date < fromDate || date > toDate) {
            showRow = false;
        }

        ui->transactionsTable->setRowHidden(i, !showRow);
    }

    updateCharts();
}
