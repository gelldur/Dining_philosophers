#include "MainWindow.h"

MainWindow::MainWindow(QWidget* parent)
		: QMainWindow(parent)
		, _ui(new Ui::MainWindow)
{
	_ui->setupUi(this);
}
