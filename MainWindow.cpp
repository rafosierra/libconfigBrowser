/*
 * This file is part of the libconfig browser distribution (https://github.com/rafosierra/libconfigBrowser).
 * Copyright (c) 2021 Rafael Sierra.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QDebug>

#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupTreeWidget();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionExit_triggered()
{
    close();
}

void MainWindow::on_actionOpen_triggered()
{
    /* Open a config file */
    QString filterName1 = tr("Config files");
    QString filterName2 = tr("All files");
    QString filterStr = filterName1 + "(*.cfg *.conf);;" + filterName2 + "(*)";
    QString filename = QFileDialog::getOpenFileName(this, tr("Select a configuration file"), QString(), filterStr);
    if (filename.isNull()) {
        // null = user pressed cancel: do nothing.
        return;
    }
    ui->labelInputFilename->setText(filename);
    qDebug() << "inputFilename= " << filename;
    inputFilename = filename.toStdString();

    if (loadInputfile()) {
        qDebug() << "input loaded";
        ui->actionListSettings->setEnabled(true);
    } else {
        ui->actionListSettings->setEnabled(false);
    }
}

bool MainWindow::loadInputfile()
{
    // Read the file. If there is an error, report it and fail (return false).
    try
    {
      config.readFile(inputFilename.c_str());
    }
    catch(const libconfig::FileIOException &fioex)
    {
      qDebug() << "I/O error while reading file.";
      return(false);
    }
    catch(const libconfig::ParseException &pex)
    {
      qDebug() << "Parse error at " << pex.getFile() << ":" << pex.getLine()
                << " - " << pex.getError();
      return(false);
    }
    return true;
}

/**
 * @brief MainWindow::listSettings Recursively read settings while appending them to a QTreeWidget
 * @param setting
 * @param treeWidgetItem
 */
void MainWindow::listSettings(libconfig::Setting& setting, QTreeWidgetItem *treeWidgetItem)
{
    // skip new widget if it's the root setting:
    QTreeWidgetItem * item = setting.isRoot()? treeWidgetItem : new QTreeWidgetItem();

    if (setting.getLength() > 0) {
        qDebug() << "entering group/list/array. name=" << setting.getName();
        QString sName = QString::fromLatin1(setting.getName());
        item->setText(0, sName.isEmpty()?tr("(noname)"): sName);
        item->setText(1, QString::fromStdString(settingTypeToString(setting)));
        treeWidgetItem->addChild(item);
        for (auto & s: setting) {
            listSettings(s, item);
        }
    } else {
        qDebug() << "setting name=" << setting.getName()  << " path=" << setting.getPath().c_str() << " value = " << settingToString(setting).c_str();
        item->setText(0, QString::fromLatin1(setting.getName()));
        item->setText(1, QString::fromStdString(settingTypeToString(setting)));
        item->setText(2, QString::fromStdString(settingToString(setting)));
        item->setText(3, QString::fromStdString(setting.getPath()));
        treeWidgetItem->addChild(item);
    }
}

/**
 * @brief MainWindow::settingToString Get the string representation of a setting's value.
 * @param setting
 * @return
 */
std::string MainWindow::settingToString(libconfig::Setting &setting)
{
    using namespace libconfig;
    std::string result;
    switch (setting.getType()) {
    default:
        break;
    case Setting::TypeInt:
        result = std::to_string((int)setting);
        break;
    case Setting::TypeInt64:
        result = std::to_string((long long)setting);
        break;
    case Setting::TypeFloat:
        result = std::to_string((float)setting);
        break;
    case Setting::TypeString:
        result = (const char*)setting;
        break;
    case Setting::TypeBoolean:
        bool val = setting;
        result = val;
        break;
    }
    return result;
}

/**
 * @brief MainWindow::settingTypeToString: Get the type of a setting as a string
 * @param setting
 * @return
 */
std::string MainWindow::settingTypeToString(libconfig::Setting &setting)
{
    using namespace libconfig;
    std::string result;
    switch (setting.getType()) {
    default:
        result = "n/a";
        break;
    case Setting::TypeInt:
        result = "int";
        break;
    case Setting::TypeInt64:
        result = "int64";
        break;
    case Setting::TypeFloat:
        result = "float";
        break;
    case Setting::TypeString:
        result = "string";
        break;
    case Setting::TypeBoolean:
        result = "boolean";
        break;
    case Setting::TypeArray:
        result = "Array";
        break;
    case Setting::TypeGroup:
        result = "Group";
        break;
    case Setting::TypeList:
        result = "List";
        break;
    }
    return result;
}

void MainWindow::on_actionListSettings_triggered()
{
    listSettings(config.getRoot(), ui->treeWidget->invisibleRootItem());
    ui->treeWidget->expandAll();
}

void MainWindow::setupTreeWidget()
{
    QStringList headers;
    headers << tr("Setting") << tr("Type") << tr("Value") << tr("Path");
    ui->treeWidget->setColumnCount(4);
    ui->treeWidget->setHeaderLabels(headers);
}
