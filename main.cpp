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

#include <QApplication>
#include <QTranslator>
#include <QLibraryInfo>
#include <QDebug>

void loadTranslations(QApplication &a);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    loadTranslations(a);

    MainWindow w;
    w.show();
    return a.exec();
}

static QTranslator qtTranslator;
static QTranslator translator;
void loadTranslations(QApplication &a)
{
    QLocale locale = QLocale::system();

    // load system translations:
    QString translationsPath(QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    if (qtTranslator.load(locale, "qt", "_", translationsPath)) {
        qDebug() << "System Translator ok";
        a.installTranslator(&qtTranslator);
    } else {
        qDebug() << "System Translator failed";
    }
    qDebug() << "locale name=" << locale.name();
    //load this program's translations
    if (translator.load("libconfigBrowser_" +  locale.name())) {
        qDebug() << "Program Translator ok";
        a.installTranslator(&translator);
    } else {
        qDebug() << "Program Translator failed";
    }
}
