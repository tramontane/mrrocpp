/*!
 * @file
 * @brief File contains MainWindow class declaration
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QCloseEvent>
#include <QSignalMapper>
#include <pthread.h>
#include "wgt_base.h"
#include "ui_robot.h"
#include "signal_dispatcher.h"
#include "menu_bar.h"




namespace Ui {
class MainWindow;
class SignalDispatcher;
}

namespace mrrocpp {
namespace ui {
namespace common {
class Interface;
//class UiRobot;
}
}
}

namespace mrrocpp {
namespace ui {
namespace irp6ot_m {
class UiRobot;
}
}
}

/*!
 * @brief Class which mostly manages main application window
 */

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
/**
 * @brief Constructor.
 * @param _interface reference for Interface class
 * @param parent pointer for parent of the widget (can be omitted).
 */
	explicit MainWindow(mrrocpp::ui::common::Interface& _interface, QWidget *parent = 0);
	/**
	 * @brief Destructor.
	 */
	~MainWindow();

	//! Checks which thread called this function and either emits notification signal or calls ui_notification_slot() which updates state label.
	void ui_notification();

	/**
	 * @brief Enables or disables items in menu bar by emitting appropriate signals.
	 * @param _enable flag indicating whether to enable or disable an item
	 * @param _num_of_menus menu count which will be passed for enabling/disabling
	 * @param *_menu_item first pointer of the menu item (the function can take many menu items to process at time)
	 */
	void enable_menu_item(bool _enable, int _num_of_menus, QMenu *_menu_item, ...);

	/**
	 * @brief Enables or disables items in menu bar by emitting appropriate signals.
	 * @param _enable flag indicating whether to enable or disable an item
	 * @param _num_of_menus menu count which will be passed for enabling/disabling
	 * @param *_menu_item first pointer to the menu action (the function can take many menu actions to process at time)
	 */
	void enable_menu_item(bool _enable, int _num_of_menus, QAction *_menu_item, ...);

	/**
	 * @brief Emits signal for opening new window.
	 * @param window pointer to window to be opened
	 * @param set_on_top flag to indicate if a window is shown at the top after opening, false by default
	 */
	void open_new_window(wgt_base *window, bool set_on_top=false);

	//! ?????
	void get_lineEdit_position(double* val, int number_of_servos);
	/**
	 * @brief Returns pointer to Ui::MainWindow - an object which holds all main window objects placed via QtDesigner.
	 * @return Pointer to window designed in QtDesigner
	 */
	Ui::MainWindow * get_ui();
	/**
	 * @brief Closes application.
	 * @param event contains parameters that describe close event.
	 */
	void closeEvent(QCloseEvent * event);
	/**
	 * @brief Returns SignalDispatcher object - it connects widgets` signals to appropriate functions.
	 * @return Pointer to SignalDispatcher object.
	 */
	Ui::SignalDispatcher* getSignalDispatcher();
	/**
	 * @brief Returns pointer to menu bar.
	 * @return Pointer to menu bar.
	 */
	Ui::MenuBar* getMenuBar();

	/**
	 * @brief Returns pointer to interface - main ui application class.
	 * @return Pointer to interface.
	 */
	mrrocpp::ui::common::Interface* getInterface();

	//! Sets menu bar to window.
	void setMenu();
	//! Clears application console.
	void clear_console();

private:
	//! Pointer to window designed in QtDesigner, which holds every widget placed there.
	Ui::MainWindow *ui;
	//! Pointer to menu bar.
	Ui::MenuBar *menuBar;
	//! Reference to interface - main application class.
	mrrocpp::ui::common::Interface& interface;
	//! Pointer to SignalDispatcher object - it connects widgets` signals to appropriate functions.
	Ui::SignalDispatcher *signalDispatcher;
	//! Id of main thread.
	pthread_t main_thread_id;

signals:
	//! Signal for notifying about state change.
	void ui_notification_signal();
	//! Signal for clearing console.
	void clear_console_signal();
	//! Signal for enabling menu_item.
	void enable_menu_item_signal(QMenu *_menu_item, bool _active);
	//! Signal for enabling menu_item.
	void enable_menu_item_signal(QAction *_menu_item, bool _active);
	//! Signal for opening new window.
	void open_new_window_signal(wgt_base *window, bool set_on_top);
	//! Signal for raising process control window.
	void raise_process_control_window_signal();
	//! Signal for raising ecp window.
	void raise_ui_ecp_window_signal();

private slots:
	//! Updates state label.
	void ui_notification_slot();
	//! Clears console.
	void clear_console_slot();
	/**
	 * @brief Enables or disables item in menu bar.
	 * @param *_menu_item pointer to the menu item
	 * @param _active flag indicating whether to enable or disable an item
	 */
	void enable_menu_item_slot(QMenu *_menu_item, bool _active);
	/**
	 * @brief Enables or disables item in menu bar.
	 * @param *_menu_item pointer to the menu action
	 * @param _active flag indicating whether to enable or disable an item
	 */
	void enable_menu_item_slot(QAction *_menu_item, bool _active);
	/**
	 * @brief Opens new window.
	 * @param window pointer to window to be opened
	 * @param set_on_top flag to indicate if a window is shown at the top after opening, false by default
	 */
	void open_new_window_slot(wgt_base *window, bool set_on_top);
};


#endif // MAINWINDOW_H
