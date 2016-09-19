#include "cloud_dialog.h"
#include "ui_cloud_dialog.h"

CloudDialog::CloudDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CloudDialog)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);

    initDialog();
}

CloudDialog::~CloudDialog()
{
    delete ui;
}

void CloudDialog::initDialog(){
    QLineEdit* verticesCountEdit = ui->verticesCountLineEdit;
    QLineEdit* ringsDividerEdit = ui->ringsDividerLineEdit;
    QLineEdit* sectionsDividerEdit = ui->sectionsDividerLineEdit;
    QLineEdit* noiseLineEdit = ui->noiseLineEdit;

    QPushButton* cancelButton = ui->cancelButton;
    QPushButton* okButton = ui->okButton;

    QDoubleValidator* floatValidator =
            new QDoubleValidator(0, 1000.0, 2, NULL);
    QIntValidator* intValidator = new QIntValidator(1, 1000, NULL);

    verticesCountEdit->setValidator(intValidator);
    ringsDividerEdit->setValidator(floatValidator);
    sectionsDividerEdit->setValidator(floatValidator);
    noiseLineEdit->setValidator(floatValidator);

    verticesCountEdit->setText("100");
    ringsDividerEdit->setText("1");
    sectionsDividerEdit->setText("2");
    noiseLineEdit->setText("0.1");

    okButton->setDefault(true);
    okButton->setAutoDefault(false);

    cancelButton->setDefault(false);
    cancelButton->setAutoDefault(false);
}

void CloudDialog::cancelButtonClicked(){
    result = false;
    close();
}

void CloudDialog::okButtonClicked(){
    result = true;

    QLineEdit* verticesCountEdit = ui->verticesCountLineEdit;
    QLineEdit* ringsDividerEdit = ui->ringsDividerLineEdit;
    QLineEdit* sectionsDividerEdit = ui->sectionsDividerLineEdit;
    QLineEdit* noiseLineEdit = ui->noiseLineEdit;

    int verticesCount = verticesCountEdit->text().toInt();
    float ringsDivider = ringsDividerEdit->text().toFloat();
    float sectionsDivider = sectionsDividerEdit->text().toFloat();
    float noise = noiseLineEdit->text().toFloat();

    data.verticesCount = verticesCount;
    data.ringsDivider = ringsDivider;
    data.sectionsDivider = sectionsDivider;
    data.distortion = noise;

    close();
}
