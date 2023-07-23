#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QFileDialog"
#include "QMessageBox"
#include <fstream>
#include "ToString.cpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label_default_import_realtors->setText(ui->label_default_import_realtors->text() + QString::fromStdString(" " + this->default_import_realtors_path));
    ui->label_default_import_deals->setText(ui->label_default_import_deals->text() + QString::fromStdString(" " + this->default_import_deals_path));
    ui->label_default_export_realtors->setText(ui->label_default_export_realtors->text() + QString::fromStdString(" " + this->default_export_realtors_path));
    ui->label_default_export_deals->setText(ui->label_default_export_deals->text() + QString::fromStdString(" " + this->default_export_deals_path));
    ui->label_default_search_export->setText(ui->label_default_search_export->text() + QString::fromStdString(" " + this->default_export_search_path));

    ui->label_default_search_export->setVisible(false);
    ui->pushButton_search_export_default->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief MainWindow::debug_message
 * Записывает сообщение message в окно отладки
 *
 * @param message Сообщение, которое хотим записать в отладку
 */
void MainWindow::debug_message(std::string message) {
    std::string text = ui->textEdit_debug->toPlainText().toStdString() + message + "\n";
    ui->textEdit_debug->setText(QString::fromStdString(text));
}

void MainWindow::success_message(QString message) {
    QMessageBox::information(this, "Успех", message);
}

void MainWindow::error_message(QString message) {
    QMessageBox::critical(this, "Ошибка", message);
}


void MainWindow::on_pushButton_debug_realtors_table_clicked() {
    this->debug_message(this->database.to_string_realtors_realtor_phone_table() + "\n\n");
}
void MainWindow::on_pushButton_debug_realtors_experience_tree_clicked() {
    this->debug_message(this->database.to_string_realtors_experience_tree() + "\n\n");
}
void MainWindow::on_pushButton_debug_deals_price_tree_clicked() {
    this->debug_message(this->database.to_string_deals_table() + "\n\n");
}
void MainWindow::on_pushButton_debug_deals_realtor_phone_tree_clicked() {
    this->debug_message(this->database.to_string_deals_realtor_phone_tree() + "\n\n");
}


void MainWindow::append_data_to_table(QTableWidget *table, vector<string> data) {
    int row = table->rowCount();
    table->insertRow(row);
    for (int col = 0; col < data.size(); col++) {
        table->setItem(row, col, new QTableWidgetItem(QString::fromStdString(data[col])));
    }
}


void MainWindow::add_realtor_to_table(Realtor realtor) {
    vector<string> data = {
        string_to_str(realtor.fio),
        longlong_to_str(realtor.realtor_phone),
        int_to_str(realtor.commission),
        int_to_str(realtor.experience)
    };
    this->append_data_to_table(ui->tableWidget_realtors, data);
}

void MainWindow::add_deal_to_table(Deal deal) {
    vector<string> data = {
        date_to_str(deal.date),
        int_to_str(deal.price),
        longlong_to_str(deal.realtor_phone),
        string_to_str(deal.address)
    };
    this->append_data_to_table(ui->tableWidget_deals, data);
}

void MainWindow::add_realtors_to_table(vector<Realtor> realtors) {
    for (Realtor &realtor: realtors) {
        this->add_realtor_to_table(realtor);
    }
}

void MainWindow::add_deals_to_table(vector<Deal> deals) {
    for (Deal &deal: deals) {
        this->add_deal_to_table(deal);
    }
}

void MainWindow::show_realtors_on_table(vector<Realtor> realtors) {
    ui->tableWidget_realtors->setRowCount(0);
    this->add_realtors_to_table(realtors);
}

void MainWindow::show_deals_on_table(vector<Deal> deals) {
    ui->tableWidget_deals->setRowCount(0);
    this->add_deals_to_table(deals);
}

void MainWindow::update_realtors_table() {
    ui->tableWidget_realtors->setRowCount(0);
    vector<Realtor> realtors = this->database.get_all_realtors();
    this->add_realtors_to_table(realtors);
}

void MainWindow::update_deals_table() {
    ui->tableWidget_deals->setRowCount(0);
    vector<Deal> deals = this->database.get_all_deals();
    this->add_deals_to_table(deals);
}

void MainWindow::update_tables() {
    this->update_realtors_table();
    this->update_deals_table();
}


void MainWindow::on_pushButton_import_default_files_clicked()
{
    if (this->check_realtors_path(this->default_import_realtors_path) && this->check_deals_path(this->default_import_deals_path)) {  // Проверяем соответствие названия файлов заданным названиям
        this->database.load_realtors_file(this->default_import_realtors_path);
        this->database.load_deals_file(this->default_import_deals_path);
        this->update_tables();
        this->success_message("Загрузка прошла успешно");
    } else {
        this->error_message("Неверный файл(ы)");
    }
}

void MainWindow::on_pushButton_export_default_files_clicked()
{
    this->database.save_realtors_to_file(this->default_export_realtors_path);
    this->database.save_deals_to_file(this->default_export_deals_path);
    this->success_message("Справочники сохранены");
}

void MainWindow::on_pushButton_search_export_default_clicked()
{
    // std::ofstream out(this->default_export_search_path);
    // out << ui->textEdit_search->toPlainText().toStdString();
    // out.close();
    // this->success_message("Отчёт сохранен");
    this->success_message("Не реализовано");
}


void MainWindow::on_pushButton_realtors_search_experience_clicked() {
    int experience = ui->spinBox_realtors_search_experience->value();
    vector<Realtor> realtors = this->database.find_realtors_higher_experience(experience);
    this->show_realtors_on_table(realtors);
}
void MainWindow::on_pushButton_realtors_search_realtor_phone_clicked() {
    unsigned long long realtor_phone = ui->lineEdit_realtors_search_realtor_phone->text().toULongLong();
    vector<Realtor> realtors = this->database.find_realtors_by_realtor_phone(realtor_phone);
    this->show_realtors_on_table(realtors);
}
void MainWindow::on_pushButton_realtors_reset_search_clicked() {
    this->update_realtors_table();
}


void MainWindow::on_pushButton_deals_search_price_clicked() {
    int price = ui->spinBox_deals_search_price->value();
    vector<Deal> deals = this->database.find_deals_lower_price(price);
    this->show_deals_on_table(deals);
}
void MainWindow::on_pushButton_deals_search_realtor_phone_clicked() {
    unsigned long long realtor_phone = ui->lineEdit_deals_search_realtor_phone->text().toULongLong();
    vector<Deal> deals = this->database.find_deals_by_realtor_phone(realtor_phone);
    this->show_deals_on_table(deals);
}
void MainWindow::on_pushButton_deals_reset_search_clicked() {
    this->update_deals_table();
}


void MainWindow::on_pushButton_search_clicked()
{
    int experience = ui->spinBox_search_experience->value();
    int price = ui->spinBox_search_price->value();

    vector<ReportData> search_result = this->database.search(experience, price);
    ui->tableWidget_search->setRowCount(0);
    for (ReportData &info: search_result) {
        vector<string> data = {
            string_to_str(info.fio),
            longlong_to_str(info.realtor_phone),
            int_to_str(info.experience),
            date_to_str(info.date),
            int_to_str(info.price),
            string_to_str(info.address)
        };
        this->append_data_to_table(ui->tableWidget_search, data);
    }
}

bool MainWindow::check_realtors_path(std::string path) {
    std::string pattern = this->realtors_filename;
    int patt_len = pattern.size();
    if (patt_len <= path.size()) {
        return path.substr(path.size() - patt_len, patt_len) == pattern;
    } else {
        return false;
    }
}

bool MainWindow::check_deals_path(std::string path) {
    std::string pattern = this->deals_filename;
    int patt_len = pattern.size();
    if (patt_len <= path.size()) {
        return path.substr(path.size() - patt_len, patt_len) == pattern;
    } else {
        return false;
    }
}

bool MainWindow::check_report_path(std::string path) {
    std::string pattern = this->report_filename;
    int patt_len = pattern.size();
    if (patt_len <= path.size()) {
        return path.substr(path.size() - patt_len, patt_len) == pattern;
    } else {
        return false;
    }
}

void MainWindow::on_pushButton_realtors_add_clicked()
{
    string fio = ui->lineEdit_realtors_add_fio->text().toStdString();
    string realtor_phone_str = ui->lineEdit_realtors_add_realtor_phone->text().toStdString();
    unsigned long long realtor_phone = ui->lineEdit_realtors_add_realtor_phone->text().toULongLong();
    int commission = ui->spinBox_realtors_add_commission->value();
    int experience = ui->spinBox_realtors_add_experience->value();

    if (fio.empty() || realtor_phone_str.empty()) {
        this->error_message("Незаполненное поле");
        return;
    }



    AddResult result = this->database.add_realtor(fio, realtor_phone, commission, experience);
    switch (result)
    {
    case AddResult::SUCCESS:
        this->update_realtors_table();
        this->success_message("Запись добавлена");
        break;
    case AddResult::DUPLICATE:
        this->error_message("Нельзя добавить.");
        break;
    }
}


void MainWindow::on_pushButton_realtors_rem_clicked()
{
    unsigned long long realtor_phone = ui->lineEdit_realtors_rem_realtor_phone->text().toULongLong();

    RemoveResult result = this->database.remove_realtor(realtor_phone, true);
    switch (result)
    {
    case RemoveResult::SUCCESS:
        this->update_tables();
        this->success_message("Запись удалена");
        break;
    case RemoveResult::NOT_FOUND:
        this->error_message("Запись не найдена");
        break;
    case RemoveResult::LINKED_DEALS:
        this->error_message("Нельзя удалить. Есть связанные сделки.");
        break;
    }
}


void MainWindow::on_pushButton_deals_add_clicked()
{
    auto qd = ui->dateEdit_deals_add_date->date();
    Date date = {qd.day(), qd.month(), qd.year()};
    int price = ui->spinBox_deals_add_price->value();
    string realtor_phone_str = ui->lineEdit_deals_add_realtor_phone->text().toStdString();
    unsigned long long realtor_phone = ui->lineEdit_deals_add_realtor_phone->text().toULongLong();
    string address = ui->lineEdit_deals_add_address->text().toStdString();

    if (realtor_phone_str.empty() || address.empty()) {
        this->error_message("Незаполненное поле");
        return;
    }



    AddResult result = this->database.add_deal(date, price, realtor_phone, address);
    switch (result)
    {
    case AddResult::SUCCESS:
        this->update_deals_table();
        this->success_message("Запись добавлена");
        break;
    case AddResult::DUPLICATE:
        this->error_message("Такая запись уже существует");
        break;
    case AddResult::NO_LINKED_REALTOR:
        this->error_message("Нельзя добавить. Не существует связанного риэлтора");
        break;
    case AddResult::PHONE_EXIST:
        this->error_message("Такой номер телефона занят другим человеком");
        break;
    }
}


void MainWindow::on_pushButton_deals_rem_clicked()
{
    auto qd = ui->dateEdit_deals_rem_date->date();
    Date date = {qd.day(), qd.month(), qd.year()};
    string address = ui->lineEdit_deals_rem_address->text().toStdString();

    RemoveResult result = this->database.remove_deal(date, address);
    switch (result)
    {
    case RemoveResult::SUCCESS:
        this->update_deals_table();
        this->success_message("Запись удалена");
        break;
    case RemoveResult::NOT_FOUND:
        this->error_message("Запись не найдена");
        break;
    }
}

void MainWindow::on_pushButton_deals_search_key_clicked()
{
    auto qd = ui->dateEdit_deals_search_date->date();
    Date date = {qd.day(), qd.month(), qd.year()};
    string address = ui->lineEdit_deals_search_address->text().toStdString();

    vector<Deal> deals = this->database.find_deals_by_key(date, address);
    this->show_deals_on_table(deals);
}

