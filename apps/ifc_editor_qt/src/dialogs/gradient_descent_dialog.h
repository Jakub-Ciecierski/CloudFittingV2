#ifndef GRADIENT_DESCENT_DIALOG_H
#define GRADIENT_DESCENT_DIALOG_H

#include <QDialog>

namespace Ui {
class GradientDescentDialog;
}

struct GradientDescentData{
    int max_iter;
    float learning_rate;
    float translation_weight;
    float rotation_weight;
};

class GradientDescentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GradientDescentDialog(QWidget *parent = 0);
    ~GradientDescentDialog();

    GradientDescentData getData() {return data;}
    bool getResult() {return result;}

public slots:

    void cancelButtonClicked();
    void okButtonClicked();

private:
    void initDialog();

    Ui::GradientDescentDialog *ui;

    bool result;
    GradientDescentData data;
};

#endif // GRADIENT_DESCENT_DIALOG_H
