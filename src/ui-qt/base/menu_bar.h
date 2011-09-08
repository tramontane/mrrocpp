/*!
 * @file
 * @brief File containing the declaration of the MenuBar class.
 *
 * @author mwroble1
 *
 * @ingroup Ui
 */

#ifndef MENUBAR_H_
#define MENUBAR_H_

#include <QObject>
#include <QMenu>
#include <QAction>
#include <QMenuBar>
#include <QMainWindow>
#include <QSignalMapper>
#include "mainwindow.h"


namespace mrrocpp {
namespace ui {

namespace common {
class Interface;
class AllRobots;
class Mp;
}
}
}

namespace Ui {
class MainWindow;
class MenuBarAction;
}

namespace Ui
{
/*!
 *
 * @brief Class representing menu bar at the top of the window.
 *
 * The menu bar is created dynamically. Previously it was created in QtDesigner and moc`ed.
 *
 * @ingroup Ui
 */
class MenuBar : public QMenuBar
{
Q_OBJECT

public:
	/**
	 * @brief Constructor.
	 * @param iface A pointer to Interface object - main ui class.
	 * @param parent Pointer to object`s parent.
	 */
	MenuBar(mrrocpp::ui::common::Interface* iface, QWidget *parent);
	/**
	 * @brief Sets all the commands and menus which aren`t specific to particular robot in menu bar.
	 * @param mainWindow A pointer to MainWindow object.
	 */
	void setupMenuBar(QMainWindow *mainWindow);
	//! Connects commands` signals with appropriate functions.
	void makeConnections();
	//! Quit command placed in menu bar.
    QAction *actionQuit;
	//! Clear console command placed in menu bar.
    QAction *actionClear_Console;
	//! Unloading all robots command placed in menu bar.
    QAction *actionUnload_All;
	//! Slaying all robots` processes command placed in menu bar.
    QAction *actionSlay_All;
    //! Command 'About' placed in Help in menu bar.
    QAction *actionAbout;
    //! Loading all robots` EDPs command placed in menu bar.
    QAction *actionall_EDP_Load;
    //! Unloading all robots` EDPs command placed in menu bar.
    QAction *actionall_EDP_Unload;
    //! Synchronizing all robots command placed in menu bar.
    QAction *actionall_Synchronisation;
    //! Moving all robots to synchro position command placed in menu bar.
    QAction *actionall_Synchro_Position;
    //! Moving all robots to front position command placed in menu bar.
    QAction *actionall_Front_Position;
    //! Moving all robots to predefined position 0 command placed in menu bar.
    QAction *actionall_Position_0;
    //! Moving all robots to predefined position 1 command placed in menu bar.
    QAction *actionall_Position_1;
    //! Moving all robots to predefined position 2 command placed in menu bar.
    QAction *actionall_Position_2;
    //! Loading MP command placed in menu bar.
    QAction *actionMP_Load;
    //! Unloading command placed in menu bar.
    QAction *actionMP_Unload;
    //! Opening process control window command placed in menu bar.
    QAction *actionProcess_Control;
    //! Choosing configuration file command placed in menu bar.
    QAction *actionConfiguration;
    //! Robot menu placed in menu bar.
    QMenu *menuRobot;
    //! File menu placed in menu bar.
    QMenu *menuFile;
    //! Special menu placed in menu bar.
    QMenu *menuSpecial;
    //! All robots menu placed in menu bar.
    QMenu *menuAll_Robots;
    //! All robots menu placed in menu bar.
    QMenu *menuall_Preset_Positions;
    //! Task menu placed in menu bar.
    QMenu *menuTask;
    //! Help menu placed in menu bar.
    QMenu *menuHelp;

public slots:
	// all robots menu
	//! Calls loading EDPs for all active robots.
	void on_actionall_EDP_Load_triggered();
	//! Calls unloading EDPs for all robots.
	void on_actionall_EDP_Unload_triggered();
	//! Calls synchronization for all robots which have EDP loaded.
	void on_actionall_Synchronisation_triggered();
	//! Calls moving all robots to synchro position.
	void on_actionall_Synchro_Position_triggered();
	//! Calls moving all robots to front position.
	void on_actionall_Front_Position_triggered();
	//! Calls moving all robots to preset position 0.
	void on_actionall_Position_0_triggered();
	//! Calls moving all robots to preset position 1.
	void on_actionall_Position_1_triggered();
	//! Calls moving all robots to preset position 2.
	void on_actionall_Position_2_triggered();

	// task menu
	//! Calls MP loading.
	void on_actionMP_Load_triggered();
	//! Calls MP unloading.
	void on_actionMP_Unload_triggered();
	//! Calls raising process control window.
	void on_actionProcess_Control_triggered();
	//! Changes configuration file.
	void on_actionConfiguration_triggered();

	// special menu
	//! Calls clearing console function.
	void on_actionClear_Console_triggered();
	//! Calls unloading all robots function.
	void on_actionUnload_All_triggered();
	//! Calls slaying all robots function.
	void on_actionSlay_All_triggered();

	//! Calls exiting function.
	void on_actionQuit_triggered();

private:
	//! Changes menu items` names.
	void retranslateMenuBar();
	//! A pointer to Interface object.
	mrrocpp::ui::common::Interface *interface;

};

}

#endif
