/*
This file was automatically generated by configure script.
All the changes you made will be lost after the next run
of configure script.
*/

#ifndef _APP_INFO_APPLE_H_
#define _APP_INFO_APPLE_H_

#include <QtCore/QCoreApplication>
#include <QtCore/QDir>
#include <QtCore/QLocale>
#include <QtCore/QString>

/*! This class has to be used in the APPLEBUNDLE build types only!
 */
class AppInfo {
public:
    static QString name()            { return "JuffEd"; }
    static QString organization()    { return "Juff"; }
    static QString version()         { return "@JUFFED_VERSION@"; }

    static QString dataDirPath()     { return QCoreApplication::applicationDirPath() + "/../Resources/"; }
    static QString pluginsPath()     { return QCoreApplication::applicationDirPath() + "/../plugins"; }
    static QString translationPath() { return QCoreApplication::applicationDirPath() + "/../Resources/l10n"; }

    static QString configDirPath()   { return QDir::homePath() + "/.config/" + organization().toLower(); }
    static QString configFile()      { return configDirPath() + "/" + name().toLower() + ".conf"; }
    static QString logFile()         { return configDirPath() + "/juffed.log"; }
    static QString defaultPrjPath()  { return configDirPath() + "/empty_project.xml"; }
};

#endif
