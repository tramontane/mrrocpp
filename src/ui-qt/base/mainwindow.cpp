/*!
 * @file
 * @brief File containing definitions of MainWindow class methods.
 *
 */


#include <QTextCharFormat>
#include <QBrush>
#include <QColor>
#include <QFileDialog>
#include <QThread>

#include <ctime>
#include <fstream>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "ui.h"
#include "interface.h"
#include "ui_sr.h"
#include "ui_ecp.h"

#include <boost/tokenizer.hpp>
#include <boost/foreach.hpp>



MainWindow::MainWindow(mrrocpp::ui::common::Interface& _interface, QWidget *parent) :
	QMainWindow(parent), ui(new Ui::MainWindow), interface(_interface)
{
	ui->setupUi(this);

	connect(this, SIGNAL(ui_notification_signal()), this, SLOT(ui_notification_slot()), Qt::QueuedConnection);
	connect(this, SIGNAL(enable_menu_item_signal(QMenu *, bool)), this, SLOT(enable_menu_item_slot(QMenu *, bool)), Qt::QueuedConnection);
	connect(this, SIGNAL(enable_menu_item_signal(QAction *, bool)), this, SLOT(enable_menu_item_slot(QAction *, bool)), Qt::QueuedConnection);
	connect(this, SIGNAL(open_new_window_signal(wgt_base *, bool)), this, SLOT(open_new_window_slot(wgt_base *, bool)), Qt::QueuedConnection);
	connect(this, SIGNAL(ui_robot_signal(mrrocpp::ui::common::UiRobot *)), this, SLOT(ui_robot_slot(mrrocpp::ui::common::UiRobot *)), Qt::QueuedConnection);
	connect(this, SIGNAL(ui_robot_signal_int(mrrocpp::ui::common::UiRobot *, int)), this, SLOT(ui_robot_slot_int(mrrocpp::ui::common::UiRobot *, int)), Qt::QueuedConnection);
	connect(this, SIGNAL(ui_robot_int_signal_int(mrrocpp::ui::common::UiRobot *, int)), this, SLOT(ui_robot_int_slot_int(mrrocpp::ui::common::UiRobot *, int)), Qt::QueuedConnection);
	connect(this, SIGNAL(ui_robot_int_signal(mrrocpp::ui::common::UiRobot *)), this, SLOT(ui_robot_int_slot(mrrocpp::ui::common::UiRobot *)), Qt::QueuedConnection);
	connect(this, SIGNAL(clear_console_signal()), this, SLOT(clear_console_slot()), Qt::QueuedConnection);

	menuBar = new Ui::MenuBar(&interface, this);
	menuBar->setupMenuBar(this);

	signalDispatcher = new Ui::SignalDispatcher(interface);

	main_thread_id = pthread_self();
}

void MainWindow::setMenu()
{
	menuBar->setupMenuBar(this);
}


Ui::SignalDispatcher* MainWindow::getSignalDispatcher()
{
	return signalDispatcher;
}

mrrocpp::ui::common::Interface* MainWindow::getInterface()
{
	return &interface;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
	interface.UI_close();

	if (interface.ui_state == 6) {
		event->accept();
	} else {
		event->ignore();
	}
}

MainWindow::~MainWindow()
{
	delete ui;
	delete signalDispatcher;
}

Ui::MenuBar* MainWindow::getMenuBar()
{
	return menuBar;
}

Ui::MainWindow * MainWindow::get_ui()
{
	return ui;
}

void MainWindow::clear_console()
{
	emit clear_console_signal();
}

void MainWindow::clear_console_slot()
{
	get_ui()->textEdit_sr->clear();
}


void MainWindow::enable_menu_item(bool _enable, int _num_of_menus, QMenu *_menu_item, ...)
{
	va_list menu_items;
	// usuniete bo metoda wolana z dobrego watku przez manage interface_slot

//	 emit
//	 enable_menu_item_signal(_menu_item, _enable);
	if(_menu_item)
	enable_menu_item_slot(_menu_item, _enable);
	va_start(menu_items, _menu_item);

	for (int i = 1; i < _num_of_menus; i++) {
		//interface.print_on_sr("signal");
		// usuniete bo metoda wolana z dobrego watku przez manage interface_slot

//		 emit enable_menu_item_signal(va_arg(menu_items, QMenu *), _enable);
		QMenu *action = va_arg(menu_items, QMenu *);
		if(action)
		enable_menu_item_slot(action, _enable);
	}

	va_end(menu_items);
}

void MainWindow::enable_menu_item(bool _enable, int _num_of_menus, QAction *_menu_item, ...)
{
	va_list menu_items;
	// usuniete bo metoda wolana z dobrego watku przez manage interface_slot

//	 emit
//	 enable_menu_item_signal(_menu_item, _enable);

	if(_menu_item)
	enable_menu_item_slot(_menu_item, _enable);

	va_start(menu_items, _menu_item);

	for (int i = 1; i < _num_of_menus; i++) {
		//interface.print_on_sr("signal");
		// usuniete bo metoda wolana z dobrego watku przez manage interface_slot

//		 emit enable_menu_item_signal(va_arg(menu_items, QAction *), _enable);
		QAction *action = va_arg(menu_items, QAction *);
		if(action)
		enable_menu_item_slot(action, _enable);
	}

	va_end(menu_items);
}

void MainWindow::open_new_window(wgt_base *window, bool set_on_top)
{
	emit open_new_window_signal(window, set_on_top);
}

void MainWindow::open_new_window_slot(wgt_base *window, bool set_on_top)
{
	window->my_open(set_on_top);
}

void MainWindow::ui_notification()
{

	if (main_thread_id == pthread_self()) {
		// jeśli wątek główny
		//	interface.ui_msg->message("same thread");
		ui_notification_slot();

	} else {
		//jeśli inny wątek niż główny
		//	interface.ui_msg->message("different thread");
		emit ui_notification_signal();
	}

}

void MainWindow::get_lineEdit_position(double* val, int number_of_servos)
{

	// TODO dodac obsluge wyjatku
	std::string text((ui->lineEdit_position->text()).toStdString());

	boost::char_separator <char> sep(" ");
	boost::tokenizer <boost::char_separator <char> > tokens(text, sep);

	int j = 0;
	BOOST_FOREACH(std::string t, tokens)
	{

		val[j] = boost::lexical_cast <double>(t);

		if (j == number_of_servos)
		{
			break;
		}
		j++;
	}

}

void MainWindow::enable_menu_item_slot(QMenu *_menu_item, bool _active)
{
	if(_menu_item!=NULL)
	_menu_item->menuAction()->setDisabled(!_active);
}

void MainWindow::enable_menu_item_slot(QAction *_menu_item, bool _active)
{
	if(_menu_item!=NULL)
	_menu_item->setDisabled(!_active);//
}

void MainWindow::ui_notification_slot()
{

	if (interface.next_notification != interface.notification_state) {

		QString _string;
		QColor _color;

		interface.notification_state = interface.next_notification;

		switch (interface.next_notification)
		{
			case UI_N_STARTING:
				_string = "STARTING";
				_color = Qt::magenta;

				break;
			case UI_N_READY:
				_string = "READY";
				_color = Qt::blue;

				break;
			case UI_N_BUSY:
				_string = "BUSY";
				_color = Qt::red;

				break;
			case UI_N_EXITING:
				_string = "EXITING";
				_color = Qt::magenta;

				break;
			case UI_N_COMMUNICATION:
				_string = "COMMUNICATION";
				_color = Qt::red;

				break;
			case UI_N_SYNCHRONISATION:
				_string = "SYNCHRONISATION";
				_color = Qt::red;

				break;
			case UI_N_PROCESS_CREATION:
				_string = "PROCESS CREATION";
				_color = Qt::red;

				break;
		}

		QPalette pal;
		pal.setColor(QPalette::Text, _color);
		pal.setColor(QPalette::Foreground, _color);

		ui->notification_label->setPalette(pal);

		ui->notification_label->setText(_string);
		ui->notification_label->repaint();
		ui->notification_label->update();
		qApp->processEvents();
	}
}




