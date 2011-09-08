/*!
 * @file
 * @brief File containing the declaration of the mrrocpp::ui::shead1::UiRobot class.
 *
 *
 */

#ifndef __UI_R_SHEAD1_H
#define __UI_R_SHEAD1_H

#include <QObject>
#include <QMenu>
#include "ui_r_shead.h"
#include "robot/shead/const_shead1.h"

namespace mrrocpp {
namespace ui {
namespace common {
class Interface;
}
namespace shead1 {

//
//
// KLASA UiRobot
//
//


class UiRobot : public shead::UiRobot
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

