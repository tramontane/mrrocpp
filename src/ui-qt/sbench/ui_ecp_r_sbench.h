/*!
 * @file
 * @brief File containing the declaration of the mrrocpp::ui::sbench::EcpRobot class.
 *
 *
 */

#ifndef _UI_ECP_R_SBENCH_H
#define _UI_ECP_R_SBENCH_H

#include "../base/ui.h"
// Konfigurator.
#include "base/lib/configurator.h"
#include "base/lib/mrmath/mrmath.h"
#include "base/ecp/ecp_robot.h"
#include "robot/sbench/ecp_r_sbench.h"
#include "../base/ui_ecp_robot/ui_ecp_r_data_port.h"

namespace mrrocpp {
namespace ui {
namespace common {
class Interface;
}
namespace sbench {

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

