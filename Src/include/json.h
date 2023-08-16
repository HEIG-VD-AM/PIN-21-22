#ifndef JSON_H
#define JSON_H

#include <string>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <sstream>
#include <string>
#include <iostream>

#include "../thirdparty/nlohmann.h"
#include "QApplication"
#include "state.h"

template <typename T>
T import(QString &filename){
    QFile file(filename);
    if(!file.exists()){
        QApplication::beep();
        std::cerr << "File not found\n";
        T empty;
        empty.isEmpty = true;
        return empty;
    }
    if(!file.open(QIODevice::ReadOnly)){
        QApplication::beep();
        std::cerr << "Couldn't not open file\n";
        T empty;
        empty.isEmpty = true;
        return empty;
    }
    QFileInfo fileInfo(filename);
    filename = fileInfo.fileName();
    QTextStream stream(&file);
    QString data = stream.readAll();
    std::string str = data.toStdString();
    nlohmann::json json;
    std::stringstream(str) >> json;
    T result = json.get<T>();
    result.isEmpty = false;
    return result;
}

void exportState(State state, QString filename){
    nlohmann::json json = state;
    std::string str = json.dump();
    QFile f(filename);
    if(!f.open(QIODevice::WriteOnly)){
        QApplication::beep();
        std::cerr << "Cound not open file\n";
        return;
    }
    QTextStream out(&f); out << QtPrivate::convertToQString(str);
    f.close();
}
#endif // JSON_H
