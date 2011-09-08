/*!
 * @file
 * @brief File containing the declarations of the mrrocpp::ui::spkm1::EcpRobot class.
 *
 *
 */

#ifndef _UI_ECP_R_SPKM1_H
#define _UI_ECP_R_SPKM1_H

#include "../base/ui.h"
// Konfigurator.
#include "base/lib/configurator.h"
#include "base/lib/mrmath/mrmath.h"
#include "base/ecp/ecp_robot.h"
#include "robot/spkm/ecp_r_spkm1.h"
#include "../base/ui_ecp_robot/ui_ecp_r_data_port.h"
#include "ui_ecp_r_spkm.h"

namespace mrrocpp {
namespace ui {
namespace spkm1 {

// ---------------------------------------------------------------
class EcpRobot : public spkm::EcpRobot
{
public:
	// ecp_buffer ui_edp_package; // by Y
	EcpRobot(common::UiRobot& _ui_robot); // Konstruktor
};

}
} //namespace ui
} //namespace mrrocpp

#endif

