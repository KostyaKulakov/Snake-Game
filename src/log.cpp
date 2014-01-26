#include "log.h"

Log::Log()
{
}

QString Log::getCurrentTime()
{
    time_t seconds = time(NULL);
    tm* timeinfo = localtime(&seconds);

    QString time(asctime(timeinfo));

    return time;
}

void Log::push_log(LogLevel level, QString sender, QString text)
{
    if(level == logError)
        QMessageBox::critical(0, sender, "ERROR: "+text);
    else if(level == logWarning)
        QMessageBox::warning(0, sender, "Warning: "+text);

    QFile file;
    file.setFileName("log.txt");
    file.open(QIODevice::WriteOnly);
    QTextStream stream;
    stream.setDevice(&file);

    stream << getCurrentTime() << ' '  << sender << ": " << text << "\n";

    file.close();
}
