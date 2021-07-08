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

#pragma once

#include <QMainWindow>
#include <string>
#include <libconfig.h++>
#include <QTreeWidget>
#include <QTreeWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionExit_triggered();

    void on_actionOpen_triggered();

    void on_actionListSettings_triggered();

private:
    Ui::MainWindow *ui;
    libconfig::Config config;

    std::string inputFilename;

    bool loadInputfile();
    void listSettings(libconfig::Setting& setting, QTreeWidgetItem *treeWidgetItem);
    std::string settingToString(libconfig::Setting& setting);
    std::string settingTypeToString(libconfig::Setting& setting);
    void setupTreeWidget();
};
