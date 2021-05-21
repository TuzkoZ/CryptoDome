#ifndef GRAPHICGENERATOR_H
#define GRAPHICGENERATOR_H

#include <QLabel>
#include <QObject>
#include <QDebug>
#include <QProgressBar>
#include <QMouseEvent>

#define IMAGE_WIDTH 255
#define IMAGE_HEIGHT 192

enum characterSetValues_
{
    smallCharacters = 1,
    bigCharacters = 2,
    digits = 4,
    specialCharacters = 8
};

class GraphicGenerator : public QLabel
{
    Q_OBJECT
    public:
        /*! Constructor of GraphicGenerator
        *
        * As one of argument it takes progessBar to show progress of
        * generation to user.
        *
        * @param progressBar progress bar to present progress of generation
        * @param parent parent of generator
        */
        GraphicGenerator(QProgressBar *progressBar, QWidget *parent);
        /*! This function initializes generator.
        *
        * This function calculates character set map,
        * calculates pseudo random table and initializes variables.
        *
        * @param size Size of string to generate.
        * @param characterSet Combination of characterSetValues.
        */
        void initGenerator(int size, int characterSet);
        /*!
        * Function returns generated value.
        */
        QString getResult();
    protected:
        void mouseMoveEvent( QMouseEvent *event);
    private:
        QProgressBar *progressBar;
        int count;
        int size;
        int value;
        int table[IMAGE_WIDTH][IMAGE_HEIGHT];
        char characterMap[128];
        int characterMapCount;
        QString result;

    signals:
        /*!
        * Signal emitted when generation is complete
        */
        void generatingEnd();
};

#endif // GRAPHICGENERATOR_H
