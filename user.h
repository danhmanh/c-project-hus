#ifndef USER_H
#define USER_H
#include "QFile"
#include "QTextStream"
using namespace std;

class user {
    public : user();
    void WriteOwner(QString name, QString port);
    void WriteUser(QString name);
    private : QFile file;
};

static user user;


#endif // USER_H

