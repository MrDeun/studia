#include "mainwindow.h"
#include "calculator.h"
#include <QGridLayout>
#include <qgridlayout.h>
#include <qlayout.h>
#include <qnamespace.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), sumSoFar(0.0), memory(0.0), factorSoFar(0.0),
      waitingForOperand(true) {
  display = new QLineEdit(this);
  display->setReadOnly(true);
  display->setAlignment(Qt::AlignRight);
  display->setMaxLength(15);

  QFont font = display->font();
  font.setPointSize(font.pointSize() + 8);
  display->setFont(font);

  for (int i = 0; i < NumDigitButtons; i++) {
    digitButtons[i] =
        createButton(QString::number(i), &MainWindow::digitClicked);
  }

  // Button *pointButton = createButton(tr("."), &MainWindow::pointClicked);
  // Button *changeSignButton = createButton("\302\261",
  // &MainWindow::changeSignClicked);

  // Button *backspaceButton =
  // createButton(tr("backspace"),&MainWindow::backspaceClicked); Button
  // *clearButton = createButton(tr("Clear"), &MainWindow::clear); Button
  // *clearAllButton = createButton(tr("Clear All"),&MainWindow::clearAll);

  // Button *clearMemoryButton = createButton(tr("MC"),
  // &MainWindow::clearMemory); Button *setMemoryButton =
  // createButton(tr("MS"),&MainWindow::setMemory); Button *readMemoryButton =
  // createButton(tr("MR"),&MainWindow::readMemory); Button *addToMemoryButton =
  // createButton(tr(""),&MainWindow::addToMemory);

  // Button *divisionButton = createButton(tr("\303\267"),
  // &MainWindow::multiplyOperatorClicked); Button *multiplicationButton =
  // createButton(tr("\303\277"), &MainWindow::multiplyOperatorClicked); Button
  // *sumButton = createButton(tr("+"), &MainWindow::addOperatorClicked); Button
  // *substractButton = createButton(tr("-"), &MainWindow::addOperatorClicked);

  // Button *squareButton = createButton(tr("Sqrt"),
  // &MainWindow::unaryOperationClicked); Button *powerButton =
  // createButton(tr("x\302\262"), &MainWindow::unaryOperationClicked); Button
  // *reciprocalButton = createButton(tr("1/x"),
  // &MainWindow::unaryOperationClicked); Button *equalButton =
  // createButton(tr("="), &MainWindow::equalClicked);

  QGridLayout *layout = new QGridLayout;

  layout->setSizeConstraint(QLayout::SetFixedSize);
  layout->addWidget(display, 0, 0, 1, 6);
  // layout->addWidget(clearButton,1,0,1,1);

  for (int i = 1; i < NumDigitButtons; ++i) {
    int row = ((9 - i) / 3);
    int column = ((i - 1) % 3);
    layout->addWidget(digitButtons[i], row, column);
  }

  setWindowTitle(tr("Calculator"));
}

void MainWindow::digitClicked() {
  Button *clickedButton = qobject_cast<Button *>(sender());
  int digitValue = clickedButton->text().toInt();
  if (display->text() == "0" && digitValue == 0.0)
    return;
  if (waitingForOperand) {
    display->clear();
    waitingForOperand = false;
  }
  display->setText(display->text() + QString::number(digitValue));
}

template<typename PointerToMemberFunction>
Button *MainWindow::createButton(const QString &text, const PointerToMemberFunction &member)
{
    Button *button = new Button(text);
    connect(button, &Button::clicked, this, member);
    return button;
}