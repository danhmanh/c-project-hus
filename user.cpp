#include <user.h>
using namespace std;

user::user() {

}

void user::WriteOwner(QString name, QString port) {
    QString file_name = "owner.txt";
    QFile file(file_name);
    QTextStream out(&file);

    if (file.open(QIODevice::Append)) {
        out << "Owner of port: " +port+" "+ name << endl;
      }
    else {

        qWarning("Could not open file");
      }

      file.close();
}

void user::WriteUser(QString name) {
    QString file_name = "user.txt";
    QFile file(file_name);
    QTextStream out(&file);

    if (file.open(QIODevice::Append)) {
        out << name << endl;
      }
    else {

        qWarning("Could not open file");
      }

      file.close();
}
