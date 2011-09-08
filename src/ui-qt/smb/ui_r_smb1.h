/*!
 * @file
 * @brief File containing the declaration of the mrrocpp::ui::smb1::UiRobot class.
 *
 *
 */

#ifndef __UI_R_SMB1_H
#define __UI_R_SMB1_H

#include <QObject>
#include <QMenu>
#include "ui_r_smb.h"
#include "robot/smb/const_smb1.h"

namespace mrrocpp {
namespace ui {
namespace common {
class Interface;
}
namespace smb1 {

//
//
// KLASA UiRobot
//
//


class UiRobot : public smb::UiRobot
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

