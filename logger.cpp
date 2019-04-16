#include "logger.h"
using namespace std;
logger::logger() {

}

void logger::WriteMessage(QString message, QString time) {
    QString name = "chat.log";
    QFile file(name);
    QTextStream out(&file);

    if (file.open(QIODevice::Append)) {
        out << time + " " + message << endl;
      }
    else {

        qWarning("Could not open file");
      }

      file.close();
}
