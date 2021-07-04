#ifndef ERRORCONTROLLER_H
#define ERRORCONTROLLER_H
#include <QObject>


// TODO: impliment this class
class ErrorDialogConfig {

};

class ErrorController : public QObject {

public slots:
    void slot_displayErrorDialog(ErrorDialogConfig config);
};

#endif // ERRORCONTROLLER_H
