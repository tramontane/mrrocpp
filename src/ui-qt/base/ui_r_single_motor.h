/*!
 * @file
 * @brief File containing the declaration of the single_motor class.
 *
 *
 * @ingroup ui
 */

#ifndef __UI_R_SINGLE_MOTOR_H
#define __UI_R_SINGLE_MOTOR_H

#include "../base/ui.h"
#include "../base/ui_robot.h"
#include "robot/conveyor/const_conveyor.h"

class wgt_single_motor_move;

namespace Ui{
class MenuBar;
class MenuBarAction;
}

namespace mrrocpp {
namespace ui {
namespace common {
class Interface;
class EcpRobot;
}
namespace single_motor {
/*!
 *
 * @brief Base class for single motors.
 *
 *
 * @ingroup Ui
 */
class UiRobot : public common::UiRobot
{
private:

public:

//	double current_pos[1];// pozycja biezaca
//	double desired_pos[1]; // pozycja zadana

	//! Pointer to ECP driver.
	common::EcpRobot *ui_ecp_robot;
	/**
	 * @brief Constructor.
	 * @param _interface reference for Interface class
	 * @param _robot_name The name of the robot.
	 * @param _number_of_servos Number of servomechanisms.
	 */
	UiRobot(common::Interface& _interface, lib::robot_name_t _robot_name, int _number_of_servos);
	//! Deletes ui_ecp_robot.
	void delete_ui_ecp_robot();
	//! Sets ui_ecp_robot to null.
	void null_ui_ecp_robot();
	//! Sets actions in menu bar and makes connections of their signals to appropriate slots.
	void setup_menubar();
	//! Manages interface state.
	int manage_interface();

protected:
	//! Action in menu bar.
	QAction *action_Synchronisation;

private:
	//! Action in menu bar.
    QAction *action_Synchro_Position;
    //! Action in menu bar.
    QAction *action_Front_Position;
    //! Action in menu bar.
    QAction *action_Position_0;
    //! Action in menu bar.
    QAction *action_Position_1;
    //! Action in menu bar.
    QAction *action_Position_2;
    //! Submenu in menu bar.
    QMenu *menu_Preset_Positions;
};

}
} //namespace ui
} //namespace mrrocpp

#endif

