#ifndef TFEXCEPTION_H
#define TFEXCEPTION_H

#include <exception>
#include <QString>
#include <QByteArray>
#include <TGlobal>


class T_CORE_EXPORT TfException : public std::exception
{
public:
    TfException(const QString &message, const char *fileName = "", int lineNumber = 0) noexcept
        : msg(message), file(fileName), line(lineNumber)
    {
        whatmsg  = className().toLocal8Bit() + ": ";
        whatmsg += message.toLocal8Bit();
        if (lineNumber > 0) {
            whatmsg += " [";
            whatmsg += fileName;
            whatmsg += ":" + QByteArray::number(lineNumber) + "]";
        }
    }
    TfException(const TfException &e) noexcept
        : std::exception(e), msg(e.msg), file(e.file), line(e.line), whatmsg(e.whatmsg) { }
    virtual ~TfException() throw() { }

    QString message() const { return msg; }
    QString fileName() const { return file; }
    int lineNumber() const { return line; }

    virtual void raise() const { throw *this; }
    virtual std::exception *clone() const { return new TfException(*this); }
    virtual QString className() const { return QLatin1String("TfException"); }
    virtual const char *what() const noexcept override { return whatmsg.constData(); }

protected:
    QString msg;
    QString file;
    int line {0};
    QByteArray whatmsg;
};


class T_CORE_EXPORT RuntimeException : public TfException
{
public:
    RuntimeException(const QString &message, const char *fileName = "", int lineNumber = 0)
        : TfException(message, fileName, lineNumber) { }

    void raise() const override { throw *this; }
    std::exception *clone() const override { return new RuntimeException(*this); }
    QString className() const override { return QLatin1String("RuntimeException"); }
};


class T_CORE_EXPORT SecurityException : public TfException
{
public:
    SecurityException(const QString &message, const char *fileName = "", int lineNumber = 0)
        : TfException(message, fileName, lineNumber) { }

    void raise() const override { throw *this; }
    std::exception *clone() const override { return new SecurityException(*this); }
    QString className() const override { return QLatin1String("SecurityException"); }
};


class T_CORE_EXPORT SqlException : public TfException
{
public:
    SqlException(const QString &message, const char *fileName = "", int lineNumber = 0)
        : TfException(message, fileName, lineNumber) { }

    void raise() const override { throw *this; }
    std::exception *clone() const override { return new SqlException(*this); }
    QString className() const override { return QLatin1String("SqlException"); }
};


class T_CORE_EXPORT KvsException : public TfException
{
public:
    KvsException(const QString &message, const char *fileName = "", int lineNumber = 0)
        : TfException(message, fileName, lineNumber) { }

    void raise() const override { throw *this; }
    std::exception *clone() const override { return new KvsException(*this); }
    QString className() const override { return QLatin1String("KvsException"); }
};


class T_CORE_EXPORT ClientErrorException : public TfException
{
public:
    ClientErrorException(int statusCode, const char *fileName = "", int lineNumber = 0)
        : TfException(QString("HTTP status code: %1").arg(statusCode), fileName, lineNumber),
          code(statusCode) { }

    int statusCode() const { return code; }
    void raise() const override { throw *this; }
    std::exception *clone() const override { return new ClientErrorException(*this); }
    QString className() const override { return QLatin1String("ClientErrorException"); }

private:
    int code;
};


class T_CORE_EXPORT StandardException : public TfException
{
public:
    StandardException(const QString &message, const char *fileName = "", int lineNumber = 0)
        : TfException(message, fileName, lineNumber) { }

    void raise() const override { throw *this; }
    std::exception *clone() const override { return new StandardException(*this); }
    QString className() const override { return QLatin1String("StandardException"); }
};

#endif // TFEXCEPTION_H
