/*!
 * @file
 * @brief File containing the declaration of the mrrocpp::ui::shead1::EcpRobot class.
 *
 *
 */

#ifndef _UI_ECP_R_SHEAD1_H
#define _UI_ECP_R_SHEAD1_H

#include "../base/ui.h"
// Konfigurator.
#include "base/lib/configurator.h"
#include "base/lib/mrmath/mrmath.h"
#include "base/ecp/ecp_robot.h"
#include "robot/shead/ecp_r_shead1.h"
#include "../base/ui_ecp_robot/ui_ecp_r_data_port.h"
#include "ui_ecp_r_shead.h"

namespace mrrocpp {
namespace ui {
namespace shead1 {

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

