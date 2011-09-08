/*!
 * @file
 * @brief File containing the declaration of the AllRobots class.
 *
 * @author mwroble1
 *
 * @ingroup ui
 */

#ifndef ALLROBOTS_H_
#define ALLROBOTS_H_

#include <boost/shared_ptr.hpp>
#include "ui.h"

class MainWindow;

namespace mrrocpp {
namespace ui {
namespace common {
class UiRobot;
class Interface;
class Mp;
/*!
 *
 * @brief Class separated from Interface class. Supports commands given to all robots at the same time.
 *
 *
 * @ingroup Ui
 */
class AllRobots
{
public:
	/**
	 * @brief Constructor.
	 * @param iface A pointer to Interface object - main ui class.
	 */
	AllRobots(Interface *iface);
	/**
	 * @brief Creates EDPs for all robots.
	 * @return 1 if succeeded.
	 */
	int EDP_all_robots_create();
	/**
	 * @brief Slays all robots processes.
	 * @return 1 if succeeded.
	 */
	int EDP_all_robots_slay();
	/**
	 * @brief Synchronizes all robots.
	 * @return 1 if succeeded.
	 */
	int EDP_all_robots_synchronise();
	/**
	 * @brief Start reader pulse for all robots.
	 * @return 1 if succeeded.
	 */
	int pulse_start_all_reader();
	/**
	 * @brief Stop reader pulse for all robots.
	 * @return 1 if succeeded.
	 */
	int pulse_stop_all_reader();
	/**
	 * @brief Trigger pulse for all robots.
	 * @return 1 if succeeded.
	 */
	int pulse_trigger_all_reader();


//	int pulse_start_reader(UiRobot *robot);

//	int pulse_stop_reader(UiRobot *robot);

//	int pulse_trigger_reader(UiRobot *robot);
//	//ECP pulse
//	int pulse_trigger_ecp(UiRobot *robot);


	//! Sets all EDPs state apart from MP.
	void set_edp_state();
	//! Manages all EDPs label on UI and menu actions for all robots.
	void manage_interface();
	//! ECP pulse
	int pulse_trigger_ecp();


	/**
	 * @brief Moves all robots to synchronized position.
	 * @return 1 if succeeded.
	 */
	int all_robots_move_to_synchro_position();
	/**
	 * @brief Moves all robots to front position.
	 * @return 1 if succeeded.
	 */
	int all_robots_move_to_front_position();
	/**
	 * @brief Moves all robots to preset position 0.
	 * @return 1 if succeeded.
	 */
	int all_robots_move_to_preset_position_0();
	/**
	 * @brief Moves all robots to preset position 1.
	 * @return 1 if succeeded.
	 */
	int all_robots_move_to_preset_position_1();
	/**
	 * @brief Moves all robots to preset position 2.
	 * @return 1 if succeeded.
	 */
	int all_robots_move_to_preset_position_2();
	/**
	 * @brief Checks if any robot is active.
	 * @return True if any robot active, false otherwise.
	 */
	bool is_any_robot_active();
	/**
	 * @brief Checks if all active robots have EDP loaded.
	 * @return True if all robots loaded, false otherwise.
	 */
	bool are_all_active_robots_loaded();
	/**
	 * @brief Checks if any active robot has EDP loaded.
	 * @return True if any robot loaded, false otherwise.
	 */
	bool is_any_active_robot_loaded();
	/**
	 * @brief Checks if all loaded robots are synchronized.
	 * @return True if all robots synchronized, false otherwise.
	 */
	bool are_all_loaded_robots_synchronised();
	/**
	 * @brief Checks if any loaded robot is synchronized.
	 * @return True if  any loaded robot is synchronized, false otherwise.
	 */
	bool is_any_loaded_robot_synchronised();

	//! State of all EDPs.
	UI_ALL_EDPS_STATE all_edps;
	//! Previous state of all EDPs.
	UI_ALL_EDPS_STATE all_edps_last_manage_interface_state;
	//! State of all EDPs synchronization.
	UI_ALL_EDPS_SYNCHRO_STATE all_edps_synchro;
	//! Previous state of all EDPs synchronization.
	UI_ALL_EDPS_SYNCHRO_STATE all_edps_synchro_last_manage_interface_state;

private:
	//! Pointer to MainWindow class needed for modifying menu bar state.
	boost::shared_ptr<MainWindow> mw;
	//! Pointer to Interface object.
	Interface *interface;
};

}
}
}

#endif /* ALLROBOTS_H_ */
