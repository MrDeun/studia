#include "mainwindow.h"
#include "calculator.h"
#include <QGridLayout>
#include <cassert>
#include <qgridlayout.h>
#include <qlayout.h>
#include <qnamespace.h>
#include <qobject.h>

#define NOT_IMPLEMENTED false

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

  Button *pointButton = createButton(tr("."), &MainWindow::pointClicked);
  Button *changeSignButton =
      createButton("\302\261", &MainWindow::changeSignClicked);

  Button *backspaceButton =
      createButton(tr("backspace"), &MainWindow::backspaceClicked);
  Button *clearButton = createButton(tr("Clear"), &MainWindow::clear);
  Button *clearAllButton = createButton(tr("Clear All"), &MainWindow::clearAll);

  Button *clearMemoryButton = createButton(tr("MC"), &MainWindow::clearMemory);
  Button *setMemoryButton = createButton(tr("MS"), &MainWindow::setMemory);
  Button *readMemoryButton = createButton(tr("MR"), &MainWindow::readMemory);
  Button *addToMemoryButton = createButton(tr(""), &MainWindow::addToMemory);

  Button *divisionButton =
      createButton(tr("\303\267"), &MainWindow::multiplyOperatorClicked);
  Button *multiplicationButton =
      createButton(tr("\303\277"), &MainWindow::multiplyOperatorClicked);
  Button *sumButton = createButton(tr("+"), &MainWindow::addOperatorClicked);
  Button *substractButton =
      createButton(tr("-"), &MainWindow::addOperatorClicked);

  Button *squareButton =
      createButton(tr("Sqrt"), &MainWindow::unaryOperationClicked);
  Button *powerButton =
      createButton(tr("x\302\262"), &MainWindow::unaryOperationClicked);
  Button *reciprocalButton =
      createButton(tr("1/x"), &MainWindow::unaryOperationClicked);
  Button *equalButton = createButton(tr("="), &MainWindow::equalClicked);

  QGridLayout *layout = new QGridLayout;

  layout->setSizeConstraint(QLayout::SetFixedSize);
  layout->addWidget(display, 0, 0, 1, 6);
  layout->addWidget(backspaceButton, 1, 0, 1, 2);
  layout->addWidget(clearButton, 1, 2, 1, 2);
  layout->addWidget(clearAllButton, 1, 4, 1, 2);

  layout->addWidget(clearMemoryButton, 2, 0);
  layout->addWidget(readMemoryButton, 3, 0);
  layout->addWidget(setMemoryButton, 4, 0);
  layout->addWidget(addToMemoryButton, 5, 0);

  for (int i = 1; i < NumDigitButtons; ++i) {
    int row = ((9 - i) / 3) + 2;
    int column = ((i - 1) % 3) + 1;
    layout->addWidget(digitButtons[i], row, column);
  }

  layout->addWidget(digitButtons[0], 5, 1);
  layout->addWidget(pointButton, 5, 2);
  layout->addWidget(changeSignButton, 5, 3);

  layout->addWidget(divisionButton, 2, 4);
  layout->addWidget(multiplicationButton, 3, 4);
  layout->addWidget(substractButton, 4, 4);
  layout->addWidget(sumButton, 5, 4);

  layout->addWidget(squareButton, 2, 5);
  layout->addWidget(powerButton, 3, 5);
  layout->addWidget(reciprocalButton, 4, 5);
  layout->addWidget(equalButton, 5, 5);

  QWidget *window = new QWidget();
  window->setLayout(layout);
  setCentralWidget(window);
  setWindowTitle(tr("Calculator"));
}

void MainWindow::pointClicked() { assert(NOT_IMPLEMENTED); }
void MainWindow::unaryOperationClicked() { assert(NOT_IMPLEMENTED); }
void MainWindow::addOperatorClicked() {
    if(!waitingForOperand)
        return;
    Button *clickedButton = qobject_cast<Button*>(sender());
    auto operation = clickedButton->text();
    auto operand = display->text().toDouble();
    if(!pendingMultiplicativeOperation.isEmpty()){
        if(!calculate(operand, operation))
    }


}
void MainWindow::multiplyOperatorClicked() { assert(NOT_IMPLEMENTED); }
void MainWindow::equalClicked() { assert(NOT_IMPLEMENTED); }
void MainWindow::changeSignClicked() { assert(NOT_IMPLEMENTED); }
void MainWindow::backspaceClicked() { assert(NOT_IMPLEMENTED); }
void MainWindow::clear() { assert(NOT_IMPLEMENTED); }
void MainWindow::clearAll() { assert(NOT_IMPLEMENTED); }
void MainWindow::clearMemory() { assert(NOT_IMPLEMENTED); }
void MainWindow::readMemory() { assert(NOT_IMPLEMENTED); }
void MainWindow::setMemory() { assert(NOT_IMPLEMENTED); }
void MainWindow::addToMemory() { assert(NOT_IMPLEMENTED); }

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

template <typename PointerToMemberFunction>
Button *MainWindow::createButton(const QString &text,
                                 const PointerToMemberFunction &member) {
  Button *button = new Button(text);
  connect(button, &Button::clicked, this, member);
  return button;
}
