#include "sphere_dialog.h"
#include "ui_sphere_dialog.h"

SphereDialog::SphereDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SphereDialog)
{   
    ui->setupUi(this);

    this->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);

    initDialog();
}

SphereDialog::~SphereDialog()
{
    delete ui;
}

void SphereDialog::initDialog(){
    QLineEdit* radiusEdit = ui->radiusLineEdit;
    QLineEdit* ringsEdit = ui->ringsLineEdit;
    QLineEdit* sectionsEdit = ui->sectionsLineEdit;

    QPushButton* cancelButton = ui->cancelButton;
    QPushButton* okButton = ui->okButton;

    QDoubleValidator* floatValidator =
            new QDoubleValidator(0, 1000.0, 2, NULL);
    QIntValidator* intValidator = new QIntValidator(1, 1000, NULL);

    radiusEdit->setValidator(floatValidator);
    ringsEdit->setValidator(intValidator);
    sectionsEdit->setValidator(intValidator);

    radiusEdit->setText("1.0");
    ringsEdit->setText("50");
    sectionsEdit->setText("50");

    okButton->setDefault(true);
    okButton->setAutoDefault(false);

    cancelButton->setDefault(false);
    cancelButton->setAutoDefault(false);
}


void SphereDialog::cancelButtonClicked(){
    result = false;
    close();
}

void SphereDialog::okButtonClicked(){
    result = true;

    QLineEdit* radiusEdit = ui->radiusLineEdit;
    QLineEdit* ringsEdit = ui->ringsLineEdit;
    QLineEdit* sectionsEdit = ui->sectionsLineEdit;

    float radius = radiusEdit->text().toFloat();
    int rings = ringsEdit->text().toInt();
    int sections = sectionsEdit->text().toInt();

    data.radius = radius;
    data.rings = rings;
    data.sections = sections;

    close();
}
