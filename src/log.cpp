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

void Log::push_log(QString sender, QString text, LogLevel level)
{
    if(level == logError)
        QMessageBox::critical(0, sender, "ERROR: "+text);
    else if(level == logWarning)
        QMessageBox::warning(0, sender, "Warning: "+text);

    QFile file;
    file.setFileName("C:\\log.txt");
    file.open(/*QIODevice::Append | */QIODevice::WriteOnly);
    QTextStream stream;
    stream.setDevice(&file);

    stream << "=========================================" << "\n";
    stream << "time: "  << getCurrentTime()               << "\n";
    stream << "From: "  << sender                         << "\n";
    stream << "Level: " << level                          << "\n";
    stream << "Msg: "   << text                           << "\n";
    stream << "=========================================" << "\n";

    file.close();
}
