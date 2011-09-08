/*!
 * @file
 * @brief File containing the declaration of the mrrocpp::ui::bird_hand::EcpRobot class.
 *
 *
 */

#ifndef _UI_ECP_R_BIRD_HAND_H
#define _UI_ECP_R_BIRD_HAND_H

#include "../base/ui.h"
// Konfigurator.
#include "base/lib/configurator.h"
#include "base/lib/mrmath/mrmath.h"
#include "base/ecp/ecp_robot.h"
#include "robot/bird_hand/ecp_r_bird_hand.h"
#include "../base/ui_ecp_robot/ui_ecp_r_data_port.h"

namespace mrrocpp {
namespace ui {
namespace common {
class Interface;
}
namespace bird_hand {

// ---------------------------------------------------------------
class EcpRobot : public common::EcpRobotDataPort
{

public:

	//! Setting regulators.
	mrrocpp::lib::single_thread_port <mrrocpp::lib::bird_hand::command> *bird_hand_command_data_port;

	//! Setting configuration.
	lib::single_thread_port <lib::bird_hand::configuration> *bird_hand_configuration_command_data_port;

	//! Replying robot`s status.
	lib::single_thread_request_port <lib::bird_hand::status> *bird_hand_status_reply_data_request_port;

	//! Reading configuration parameters.
	lib::single_thread_request_port <lib::bird_hand::configuration> *bird_hand_configuration_reply_data_request_port;

	/**
	 * @brief Constructor.
	 * @param _ui_robot Reference to robot.
	 */
	EcpRobot(common::UiRobot& _ui_robot); // Konstruktor
};

}
} //namespace ui
} //namespace mrrocpp

#endif

