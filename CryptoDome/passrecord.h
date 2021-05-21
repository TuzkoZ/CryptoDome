#ifndef PASSRECORD_H
#define PASSRECORD_H

#include <QString>

class PassRecord
{
public:
    PassRecord(QString name, QString URL, QString login, QString password, QString description);

    QString getName();
    QString getURL();
    QString getLogin();
    QString getPassword();
    QString getDescription();

    void setName(QString name);
    void setURL(QString URL);
    void setLogin(QString login);
    void setPassword(QString password);
    void setDescription(QString description);

private:
    QString name;
    QString URL;
    QString login;
    QString password;
    QString description;
};

#endif // PASSRECORD_H
