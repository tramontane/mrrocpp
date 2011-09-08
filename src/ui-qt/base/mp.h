/*!
 * @file
 * @brief File containing the declaration of the Mp class.
 *
 * @author mwroble1
 *
 * @ingroup Ui
 */
#ifndef MP_H_
#define MP_H_

#include "ui.h"

namespace mrrocpp {
namespace ui {
namespace common {
class UiRobot;
class Interface;
/*!
 *
 * @brief Class separated from Interface. Handles commands to MP.
 *
 *
 * @ingroup Ui
 */
class Mp
{
public:
	/**
	 * @brief Constructor.
	 * @param iface Pointer to Interface class.
	 */
	Mp(Interface *iface);
	/**
	 * @brief MP up.
	 * @return 1 if succeeded.
	 */
	int MPup();
	/**
	 * @brief MP up.
	 * @return 1 if succeeded.
	 */
	int MPup_int();
	/**
	 * @brief Slays MP.
	 * @return 1 if succeeded.
	 */
	int MPslay();
	/**
	 * @brief MP pulse start.
	 * @return 1 if succeeded.
	 */
	int pulse_start_mp();
	/**
	 * @brief MP pulse stop.
	 * @return 1 if succeeded.
	 */
	int pulse_stop_mp();
	/**
	 * @brief MP pulse pause.
	 * @return 1 if succeeded.
	 */
	int pulse_pause_mp();
	/**
	 * @brief MP pulse resume.
	 * @return 1 if succeeded.
	 */
	int pulse_resume_mp();
	/**
	 * @brief MP pulse trigger.
	 * @return 1 if succeeded.
	 */
	int pulse_trigger_mp();
	/**
	 * @brief Executes MP pulse depending on the passed code.
	 * @param pulse_code Code to be sent.
	 * @return 1 if succeeded.
	 */
	int execute_mp_pulse(char pulse_code);
	//! Allows to run MP depending whether all robots have EDPs loaded and are synchronized and if MP is not already running.
	void set_mp_state();
	//! Manages interface state - sets MP label notification and menu items for MP.
	void manage_interface();
	//! State of MP.
	mp_state_def mp_state;
private:
	//! Pointer to Interface object.
	Interface *interface;
};

}
}
}

#endif /* MP_H_ */
