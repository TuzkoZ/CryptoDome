#include "graphicgenerator.h"

GraphicGenerator::GraphicGenerator(QProgressBar *progressBar, QWidget *parent)
{
    this->progressBar = progressBar;
    setPixmap(QPixmap(":/new/prefix1/Resources/check.png"));
}


void GraphicGenerator::mouseMoveEvent( QMouseEvent *event)
{
    value = (table[ event->x() ][ event->y() ] + value) % 256;
    count++;
    progressBar->setValue( progressBar->value()+1);
    if(count == 20)
    {
        result.append( characterMap[ value % characterMapCount ] );
        if(result.count() == size)
        {
            setMouseTracking(false);
            qDebug() << "OJK";
            emit generatingEnd();
        }
        count = 0;
    }
}

QString GraphicGenerator::getResult()
{
    return result;
}

void GraphicGenerator::initGenerator(int size, int characterSet)
{
    this->size = size;
    srand( time(0) );
    for(int i = 0; i < IMAGE_WIDTH; i++)
        for(int j = 0; j < IMAGE_HEIGHT; j++)
            table[i][j] = rand()%256;
    count = 0;
    result.clear();
    characterMapCount = 0;
    if(characterSet & digits)
    {
        for(int i = 0; i < 10; i++)
            characterMap[characterMapCount++] = i + 48;
    }
    if(characterSet & smallCharacters)
        for(int i = 0; i < 26; i++)
            characterMap[characterMapCount++] = i + 97;
    if(characterSet & bigCharacters)
        for(int i = 0; i < 26; i++)
            characterMap[characterMapCount++] = i + 65;
    if(characterSet & specialCharacters)
    {
        for(int i = 0; i < 15; i++)
            characterMap[characterMapCount++] = i + 33;
        for(int i = 0; i < 7; i++)
            characterMap[characterMapCount++] = i + 58;
        for(int i = 0; i < 6; i++)
            characterMap[characterMapCount++] = i + 91;
        for(int i = 0; i < 3; i++)
            characterMap[characterMapCount++] = i + 123;
    }
    setMouseTracking(true);
    progressBar->setValue(0);
    progressBar->setMaximum(size*20);
}


