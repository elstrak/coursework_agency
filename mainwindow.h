#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <string>
#include "Database.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void debug_message(std::string message);
    void error_message(QString message);
    void success_message(QString message);

    void append_data_to_table(QTableWidget *table, vector<string> data);

    void add_realtor_to_table(Realtor realtor);
    void add_deal_to_table(Deal deal);

    void add_realtors_to_table(vector<Realtor> realtors);
    void add_deals_to_table(vector<Deal> deals);

    void show_realtors_on_table(vector<Realtor> realtors);
    void show_deals_on_table(vector<Deal> deals);

    void update_realtors_table();
    void update_deals_table();
    void update_tables();

public slots:

private slots:

    void on_pushButton_import_default_files_clicked();
    void on_pushButton_export_default_files_clicked();
    void on_pushButton_search_export_default_clicked();

    // Поиск в справочнике Риэлторы
    void on_pushButton_realtors_search_experience_clicked();
    void on_pushButton_realtors_search_realtor_phone_clicked();
    void on_pushButton_realtors_reset_search_clicked();

    // Добавление / удаление
    void on_pushButton_realtors_add_clicked();
    void on_pushButton_realtors_rem_clicked();

    // Поиск в справочнике Сделки
    void on_pushButton_deals_search_price_clicked();
    void on_pushButton_deals_search_realtor_phone_clicked();
    void on_pushButton_deals_reset_search_clicked();

    // Добавление / удаление
    void on_pushButton_deals_add_clicked();
    void on_pushButton_deals_rem_clicked();

    // Отчёт
    void on_pushButton_search_clicked();

    // Отладка
    void on_pushButton_debug_realtors_table_clicked();
    void on_pushButton_debug_realtors_experience_tree_clicked();
    void on_pushButton_debug_deals_price_tree_clicked();
    void on_pushButton_debug_deals_realtor_phone_tree_clicked();

    void on_pushButton_deals_search_key_clicked();

private:
    Ui::MainWindow *ui;
    Database database;

    // Пути по умолчанию
    std::string default_import_realtors_path = "./realtors.txt";
    std::string default_import_deals_path = "./deals.txt";
    std::string default_export_realtors_path = "./realtors.txt";
    std::string default_export_deals_path = "./deals.txt";
    std::string default_export_search_path = "./report.txt";

    // Названия файлов. Любые другие названия не будут приниматься
    std::string realtors_filename = "realtors.txt";
    std::string deals_filename = "deals.txt";
    std::string report_filename = "report.txt";

    bool check_realtors_path(std::string path);
    bool check_deals_path(std::string path);
    bool check_report_path(std::string path);

};
#endif // MAINWINDOW_H
