/*!
 * @file
 * @brief File containing the declarations of the mrrocpp::ui::shead2::EcpRobot class.
 *
 *
 */

#ifndef _UI_ECP_R_SHEAD2_H
#define _UI_ECP_R_SHEAD2_H

#include "../base/ui.h"
// Konfigurator.
#include "base/lib/configurator.h"
#include "base/lib/mrmath/mrmath.h"
#include "base/ecp/ecp_robot.h"
#include "robot/shead/ecp_r_shead2.h"
#include "../base/ui_ecp_robot/ui_ecp_r_data_port.h"
#include "ui_ecp_r_shead.h"

namespace mrrocpp {
namespace ui {
namespace shead2 {

// ---------------------------------------------------------------
class EcpRobot : public shead::EcpRobot
{
public:
	// ecp_buffer ui_edp_package; // by Y
	EcpRobot(common::UiRobot& _ui_robot); // Konstruktor
};

}
} //namespace ui
} //namespace mrrocpp

#endif

