#include "passrecord.h"

PassRecord::PassRecord(QString name, QString URL, QString login, QString password, QString description)
{
    this->name = name;
    this->URL = URL;
    this->login = login;
    this->password = password;
    this->description = description;
}

QString PassRecord::getName()
{
    return this->name;
}

QString PassRecord::getURL()
{
    return this->URL;
}

QString PassRecord::getLogin()
{
    return this->login;
}

QString PassRecord::getPassword()
{
    return this->password;
}

QString PassRecord::getDescription()
{
    return this->description;
}

void PassRecord::setName(QString name)
{
    this->name = name;
}

void PassRecord::setURL(QString URL)
{
    this->URL = URL;
}

void PassRecord::setLogin(QString login)
{
    this->login = login;
}

void PassRecord::setPassword(QString password)
{
    this->password = password;
}

void PassRecord::setDescription(QString description)
{
    this->description = description;
}
