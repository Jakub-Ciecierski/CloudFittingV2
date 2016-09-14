#ifndef SPHERE_DIALOG_H
#define SPHERE_DIALOG_H

#include <QDialog>

namespace Ui {
class SphereDialog;
}

struct SphereData{
    float radius;
    int rings;
    int sections;
};

class SphereDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SphereDialog(QWidget *parent = 0);
    ~SphereDialog();

    SphereData getData() {return data;}
    bool getResult() {return result;}

public slots:

    void cancelButtonClicked();
    void okButtonClicked();

private:
    bool result;
    SphereData data;

    void initDialog();

    Ui::SphereDialog *ui;
};

#endif // SPHERE_DIALOG_H
