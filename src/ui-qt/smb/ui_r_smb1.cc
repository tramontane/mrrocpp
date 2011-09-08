/*!
 * @file
 * @brief File containing the definitions of the mrrocpp::ui::smb1::UiRobot class.
 *
 *
 */


#include "ui_r_smb1.h"
#include "ui_ecp_r_smb1.h"

namespace mrrocpp {
namespace ui {
namespace smb1 {

UiRobot::UiRobot(common::Interface& _interface) :
	smb::UiRobot(_interface, lib::smb1::ROBOT_NAME)
{

}

void UiRobot::create_ui_ecp_robot()
{
	ui_ecp_robot = new EcpRobot(*this);
//	return 1;
}

void UiRobot::setup_menubar()
{
	smb::UiRobot::setup_menubar();
	robot_menu->setTitle(QApplication::translate("MainWindow", "S&mb1", 0, QApplication::UnicodeUTF8));
}


}
} //namespace ui
} //namespace mrrocpp

