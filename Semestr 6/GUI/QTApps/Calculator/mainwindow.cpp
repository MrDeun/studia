#include "mainwindow.h"
#include "button.h"
#include <QGridLayout>
#include <cassert>
#include <cmath>
#include <iostream>
#include <qgridlayout.h>
#include <qlayout.h>
#include <qnamespace.h>
#include <qobject.h>

#define NOT_IMPLEMENTED false

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), sumSoFar(0.0), memory(0.0), factorSoFar(1.0),
      waitingForOperand(true) {
  display = new QLineEdit(this);
  display->setReadOnly(true);
  display->setAlignment(Qt::AlignCenter);
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
  Button *blankButton = createButton(tr(""), &MainWindow::clearAll);
  Button *clearMemoryButton = createButton(tr("MC"), &MainWindow::clearMemory);
  Button *setMemoryButton = createButton(tr("MS"), &MainWindow::setMemory);
  Button *readMemoryButton = createButton(tr("MR"), &MainWindow::readMemory);
  Button *addToMemoryButton = createButton(tr("M+"), &MainWindow::addToMemory);
  Button *substractFromMemoryButton =
      createButton(tr("M-"), &MainWindow::removeFromMemory);

  Button *divisionButton =
      createButton(tr("\303\267"), &MainWindow::multiplyOperatorClicked);
  Button *multiplicationButton =
      createButton(tr("\u00d7"), &MainWindow::multiplyOperatorClicked);
  Button *sumButton = createButton(tr("+"), &MainWindow::addOperatorClicked);
  Button *substractButton =
      createButton(tr("-"), &MainWindow::addOperatorClicked);

  Button *squareButton =
      createButton(tr("Sqrt"), &MainWindow::unaryOperationClicked);
  Button *powerButton =
      createButton(tr("x\302\262"), &MainWindow::unaryOperationClicked);
  Button *reciprocalButton =
      createButton(tr("1/x"), &MainWindow::unaryOperationClicked);
  Button *sinButton =
      createButton(tr("sin"), &MainWindow::unaryOperationClicked);
  Button *cosButton =
      createButton(tr("cos"), &MainWindow::unaryOperationClicked);
  Button *tanButton =
      createButton(tr("tan"), &MainWindow::unaryOperationClicked);
  Button *eulerPowerButton=createButton(tr("e\u02e3"),&MainWindow::unaryOperationClicked);
  Button *logButton=createButton(tr("log"),&MainWindow::unaryOperationClicked);
      Button *equalButton = createButton(tr("="), &MainWindow::equalClicked);

  QGridLayout *layout = new QGridLayout;

  layout->setSizeConstraint(QLayout::SetFixedSize);
  layout->addWidget(display, 0, 0, 1, 6);
  layout->addWidget(backspaceButton, 1, 0, 1, 2);
  layout->addWidget(clearButton, 1, 2, 1, 2);
  layout->addWidget(clearAllButton, 1, 4, 1, 2);

  layout->addWidget(substractFromMemoryButton, 6, 0);
  layout->addWidget(clearMemoryButton, 2, 0);
  layout->addWidget(readMemoryButton, 3, 0);
  layout->addWidget(setMemoryButton, 4, 0);
  layout->addWidget(addToMemoryButton, 5, 0);

  for (int i = 1; i < NumDigitButtons; ++i) {
    int row = ((9 - i) / 3) + 3;
    int column = ((i - 1) % 3) + 1;
    layout->addWidget(digitButtons[i], row, column);
  }
  layout->addWidget(sinButton, 2, 1);
  layout->addWidget(cosButton, 2, 2);
  layout->addWidget(tanButton, 2, 3);
  layout->addWidget(eulerPowerButton, 2, 4);
  layout->addWidget(logButton, 2, 5);
  layout->addWidget(digitButtons[0], 6, 1);
  layout->addWidget(pointButton, 6, 2);
  layout->addWidget(changeSignButton, 6, 3);

  layout->addWidget(divisionButton, 3, 4);
  layout->addWidget(multiplicationButton, 4, 4);
  layout->addWidget(substractButton, 5, 4);
  layout->addWidget(sumButton, 6, 4);

  layout->addWidget(squareButton, 3, 5);
  layout->addWidget(powerButton, 4, 5);
  layout->addWidget(reciprocalButton, 5, 5);
  layout->addWidget(equalButton, 6, 5);

  QWidget *window = new QWidget();
  window->setLayout(layout);
  setCentralWidget(window);
  setWindowTitle(tr("Calculator"));
}

void MainWindow::removeFromMemory() {
  equalClicked();
  memory -= display->text().toDouble();
}

void MainWindow::pointClicked() {
  if (waitingForOperand) {
    display->setText(tr("0"));
  }
  if (!display->text().contains('.'))
    display->setText(display->text() + tr("."));
  waitingForOperand = false;
}
void MainWindow::unaryOperationClicked() {
  Button *clickedButton = qobject_cast<Button *>(sender());
  QString clickedOperator = clickedButton->text();
  double operand = display->text().toDouble();
  double result = 0.0;
  if (clickedOperator == tr("Sqrt")) {
    if (operand < 0.0) {
      abortOperation();
      return;
    }
    result = std::sqrt(operand);
  } else if (clickedOperator == tr("x\302\262")) {
    result = std::pow(operand, 2.0);
  } else if (clickedOperator == tr("1/x")) {
    if (operand == 0.0) {
      abortOperation();
      return;
    }
    result = 1.0 / operand;
  } else if (clickedOperator == tr("sin")) {
    result = std::sin(operand);
  } else if (clickedOperator == tr("cos")) {
    result = std::cos(operand);
  } else if (clickedOperator == tr("tan")) {
    result = std::tan(operand);
  } else if (clickedOperator == tr("log")){
    result = std::log(operand);
  } else if (clickedOperator == tr("e\u02e3")){
    result = std::exp(operand);
  }
  display->setText(QString::number(result));
  waitingForOperand = true;
}
void MainWindow::addOperatorClicked() {
  Button *clickedButton = qobject_cast<Button *>(sender());
  if (!clickedButton)
    return;
  auto operation = clickedButton->text();
  auto operand = display->text().toDouble();
  if (!pendingMultiplicativeOperation.isEmpty()) {
    if (!calculate(operand, operation)) {
      abortOperation();
      return;
    }
    display->setText(QString::number(factorSoFar));
    operand = factorSoFar;
    pendingMultiplicativeOperation.clear();
  }
  if (!pendingAdditiveOperation.isEmpty()) {
    if (!calculate(operand, pendingAdditiveOperation)) {
      abortOperation();
      return;
    }
    display->setText(QString::number(sumSoFar));
  } else {
    sumSoFar = operand;
  }
  pendingAdditiveOperation = operation;
  waitingForOperand = true;
}
void MainWindow::multiplyOperatorClicked() {
  Button *clickedButton = qobject_cast<Button *>(sender());
  if (!clickedButton) {
    return;
  }
  QString clickedOperator = clickedButton->text();
  double operand = display->text().toDouble();

  if (!pendingMultiplicativeOperation.isEmpty()) {
    if (!calculate(operand, pendingMultiplicativeOperation)) {
      abortOperation();
      return;
    }
    display->setText(QString::number(operand));
  } else {
    factorSoFar = operand;
  }
  pendingMultiplicativeOperation = clickedOperator;
  waitingForOperand = true;
}
void MainWindow::equalClicked() {
  double operand = display->text().toDouble();
  if (!pendingMultiplicativeOperation.isEmpty()) {
    if (!calculate(operand, pendingMultiplicativeOperation)) {
      abortOperation();
      return;
    }
    operand = factorSoFar;
    factorSoFar = 0.0;
    pendingMultiplicativeOperation.clear();
  }
  if (!pendingAdditiveOperation.isEmpty()) {
    if (!calculate(operand, pendingAdditiveOperation)) {
      abortOperation();
      return;
    }
    pendingAdditiveOperation.clear();
  } else {
    sumSoFar = operand;
  }
  display->setText(QString::number(sumSoFar));
  sumSoFar = 0.0;
  waitingForOperand = true;
}
void MainWindow::changeSignClicked() {
  QString text = display->text();
  double value = text.toDouble();
  if (value > 0.0) {
    text.prepend(tr("-"));
  } else if (value < 0.0) {
    text.remove(0, 1);
  }
  display->setText(text);
}
void MainWindow::backspaceClicked() {
  if (waitingForOperand)
    return;
  QString text = display->text();
  text.chop(1);
  if (text.isEmpty()) {
    text = "0";
    waitingForOperand = true;
  }
  display->setText(text);
}
void MainWindow::clear() {
  if (waitingForOperand)
    return;
  display->setText("0");
  waitingForOperand = true;
}
void MainWindow::clearAll() {
  sumSoFar = 0.0;
  factorSoFar = 0.0;
  pendingAdditiveOperation.clear();
  pendingMultiplicativeOperation.clear();
  display->setText("0");
  waitingForOperand = true;
}
void MainWindow::clearMemory() { memory = 0.0; }
void MainWindow::readMemory() {
  display->setText(QString::number(memory));
  waitingForOperand = true;
}
void MainWindow::setMemory() {
  equalClicked();
  memory = display->text().toDouble();
}
void MainWindow::addToMemory() {
  equalClicked();
  memory += display->text().toDouble();
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

bool MainWindow::calculate(double rightOperand,
                           const QString &pendingOperator) {
  std::cout << "Current operation: " << pendingOperator.data();
  if (pendingOperator == tr("+")) {
    sumSoFar += rightOperand;
  } else if (pendingOperator == tr("-")) {
    sumSoFar -= rightOperand;
  } else if (pendingOperator == tr("\303\277")) {
    std::cout << factorSoFar << " * " << rightOperand;
    factorSoFar *= rightOperand;
  } else if (pendingOperator == tr("\303\267")) {
    if (rightOperand == 0.0)
      return false;
    factorSoFar /= rightOperand;
  }
  return true;
}

void MainWindow::abortOperation() {
  clearAll();
  display->setText(tr("Error"));
}

template <typename PointerToMemberFunction>
Button *MainWindow::createButton(const QString &text,
                                 const PointerToMemberFunction &member) {
  Button *button = new Button(text);
  connect(button, &Button::clicked, this, member);
  return button;
}
