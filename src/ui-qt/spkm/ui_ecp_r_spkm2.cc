/*!
 * @file
 * @brief File containing the definitions of the mrrocpp::ui::spkm2::EcpRobot class.
 *
 *
 */

/* Standard headers */
#include <iostream>

#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <cstring>
#include <fcntl.h>
#include <cerrno>
#include <cmath>

#include "base/lib/typedefs.h"
#include "base/lib/impconst.h"
#include "base/lib/com_buf.h"
#include "../base/interface.h"

#include "base/lib/sr/srlib.h"

#include "ui_ecp_r_spkm2.h"

namespace mrrocpp {
namespace ui {
namespace spkm2 {

// ---------------------------------------------------------------
EcpRobot::EcpRobot(common::UiRobot& _ui_robot) :
	spkm::EcpRobot(_ui_robot)
{
	the_robot = (boost::shared_ptr <robot_t>) new ecp::spkm2::robot(*(ui_robot.interface.config), *(ui_robot.msg));
}

}
} //namespace ui
} //namespace mrrocpp
