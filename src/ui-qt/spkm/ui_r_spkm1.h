/*!
 * @file
 * @brief File containing the declaration of the mrrocpp::ui::spkm1::UiRobot class.
 *
 *
 */

#ifndef __UI_R_SPKM1_H
#define __UI_R_SPKM1_H

#include <QObject>
#include <QMenu>
#include "ui_r_spkm.h"
#include "robot/spkm/const_spkm1.h"

namespace mrrocpp {
namespace ui {
namespace common {
class Interface;
}
namespace spkm1 {

//
//
// KLASA UiRobot
//
//


class UiRobot : public spkm::UiRobot
{
Q_OBJECT

public:

	UiRobot(common::Interface& _interface);

	void create_ui_ecp_robot();
	void setup_menubar();
};

}
} //namespace ui
} //namespace mrrocpp

#endif

