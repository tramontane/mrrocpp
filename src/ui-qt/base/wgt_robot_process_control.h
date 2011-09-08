/*!
 * @file
 * @brief File containing the declaration of the wgt_robot_process_control class.
 *
 * @author mwroble1
 *
 */

#ifndef WGT_ROBOT_PROCESS_CONTROL_H
#define WGT_ROBOT_PROCESS_CONTROL_H

#include <QtGui/QWidget>
#include <QVBoxLayout>
#include <QDockWidget>
#include "ui_wgt_robot_process_control.h"
#include "wgt_base.h"

namespace mrrocpp {
namespace ui {
namespace common {
class Interface;
class UiRobot;
class AllRobots;

}
}
}
/*!
 *
 * @brief Class for single robot process control window.
 *
 *
 */
class wgt_robot_process_control : public wgt_base
{
Q_OBJECT

public:
	/**
	 * @brief Constructor.
	 * @param _widget_label Window title.
	 * @param _interface reference for Interface class
	 * @param robo Pointer on robot for which the window is open.
	 * @param parent Pointer to widget`s parent (null by default).
	 */
	wgt_robot_process_control(QString _widget_label, mrrocpp::ui::common::Interface& _interface, mrrocpp::ui::common::UiRobot *robo,  QWidget *parent = 0);
	//! Destructor.
	~wgt_robot_process_control();
	//! Emits process_control_window_init_signal handled by process_control_window_init_slot().
	void process_control_window_init();
	/**
	 * @brief Opens window.
	 * @param set_on_top Indicates whether the window should be on top after opening (false by default).
	 */
	void my_open(bool set_on_top=false);
	/**
	 * @brief Returns pointer to window prepared in QtDesigner.
	 * @return Pointer to robot process control window prepared in QtDesigner.
	 */
	Ui::wgt_robot_process_controlClass * get_ui();
	/**
	 * @brief Blocks trigger push button.
	 * @return 1 if succeeded.
	 */
	int block_all_ecp_trigger_widgets();
	/**
	 * @brief Unblocks trigger push button.
	 * @return 1 if succeeded.
	 */
	int unblock_all_ecp_trigger_widgets();
private:
	//! A pointer to window created in QtDesigner.
	Ui::wgt_robot_process_controlClass* ui;
	//! Pointer to robot for which the window is opened.
	mrrocpp::ui::common::UiRobot *robot;
	/**
	 * @brief Updates all process control buttons.
	 * @return 1 if succeeded.
	 */
	int init();
signals:
	//! Signal for initializing process control window.
	void process_control_window_init_signal();
public slots:
	//! Manages process_control_window_init_signal(). Calls init().
	void process_control_window_init_slot();
private slots:
	//! Slot for managing triggering ECP. Sends pulse ecp from robot.
	void on_ecp_trigger_pushButton_clicked();
	//! Slot for managing clicking start button. Starts reader.
	void on_reader_start_pushButton_clicked();
	//! Slot for managing clicking stop button. Stops reader.
	void on_reader_stop_pushButton_clicked();
	//! Slot for managing clicking trigger button. Sends trigger pulse.
	void on_reader_trigger_pushButton_clicked();
};

#endif // WGT_PROCESS_CONTROL_H
