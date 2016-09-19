#ifndef CLOUD_DIALOG_H
#define CLOUD_DIALOG_H

#include <QDialog>

namespace Ui {
class CloudDialog;
}

struct CloudData{
    int verticesCount;
    float ringsDivider;
    float sectionsDivider;
    float distortion;
};

class CloudDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CloudDialog(QWidget *parent = 0);
    ~CloudDialog();
    CloudData getData() {return data;}
    bool getResult() {return result;}

public slots:

    void cancelButtonClicked();
    void okButtonClicked();

private:
    bool result;
    CloudData data;

    Ui::CloudDialog *ui;

    void initDialog();
};

#endif // CLOUD_DIALOG_H
