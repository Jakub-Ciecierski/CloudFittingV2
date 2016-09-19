#include "gradient_descent_dialog.h"
#include "ui_gradient_descent_dialog.h"

GradientDescentDialog::GradientDescentDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GradientDescentDialog)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);

    initDialog();
}

GradientDescentDialog::~GradientDescentDialog()
{
    delete ui;
}


void GradientDescentDialog::initDialog(){
    QLineEdit* maxIterLineEdit = ui->maxIterLineEdit;
    QLineEdit* learningRateLineEdit = ui->learningRateLineEdit;
    QLineEdit* translationWeightLineEdit = ui->translationWeightLineEdit;
    QLineEdit* rotationWeightLineEdit = ui->rotationWeightLineEdit;

    QPushButton* cancelButton = ui->cancelPushButton;
    QPushButton* okButton = ui->okPushButton;

    QDoubleValidator* floatValidator =
            new QDoubleValidator(0, 1000.0, 10, NULL);
    QIntValidator* intValidator = new QIntValidator(1, 100000, NULL);

    maxIterLineEdit->setValidator(intValidator);
    learningRateLineEdit->setValidator(floatValidator);
    translationWeightLineEdit->setValidator(floatValidator);
    rotationWeightLineEdit->setValidator(floatValidator);

    maxIterLineEdit->setText("1000");
    learningRateLineEdit->setText("0.0001");
    translationWeightLineEdit->setText("1.0");
    rotationWeightLineEdit->setText("1.0");

    okButton->setDefault(true);
    okButton->setAutoDefault(false);

    cancelButton->setDefault(false);
    cancelButton->setAutoDefault(false);
}


void GradientDescentDialog::cancelButtonClicked(){
    result = false;
    close();
}

void GradientDescentDialog::okButtonClicked(){
    result = true;

    QLineEdit* maxIterLineEdit = ui->maxIterLineEdit;
    QLineEdit* learningRateLineEdit = ui->learningRateLineEdit;
    QLineEdit* translationWeightLineEdit = ui->translationWeightLineEdit;
    QLineEdit* rotationWeightLineEdit = ui->rotationWeightLineEdit;

    data.max_iter = maxIterLineEdit->text().toInt();
    data.learning_rate = learningRateLineEdit->text().toFloat();
    data.translation_weight = translationWeightLineEdit->text().toFloat();
    data.rotation_weight = rotationWeightLineEdit->text().toFloat();

    close();
}
