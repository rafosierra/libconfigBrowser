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
