#ifndef LOGGER_H
#define LOGGER_H
#include "QFile"
#include "QTextStream"
#include "QTime"
#include "QDate"
using namespace std;

class logger {
    public : logger();
    void WriteMessage(QString message, QString time);
    private : QFile file;
};

static logger logger;

#endif // LOGGER_H
