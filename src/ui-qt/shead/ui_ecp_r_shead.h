/*!
 * @file
 * @brief File containing the declaration of the mrrocpp::ui::shead::EcpRobot class.
 *
 *
 */

#ifndef _UI_ECP_R_SMB_H
#define _UI_ECP_R_SMB_H

#include "../base/ui.h"
// Konfigurator.
#include "base/lib/configurator.h"
#include "base/lib/mrmath/mrmath.h"
#include "base/ecp/ecp_robot.h"
#include "robot/shead/ecp_r_shead.h"
#include "../base/ui_ecp_robot/ui_ecp_r_data_port.h"

namespace mrrocpp {
namespace ui {
namespace common {
class Interface;
}
namespace shead {

// ---------------------------------------------------------------
class EcpRobot : public common::EcpRobotDataPort
{

public:

	// ecp_buffer ui_edp_package; // by Y
	EcpRobot(common::UiRobot& _ui_robot); // Konstruktor

};

}
} //namespace ui
} //namespace mrrocpp

#endif

