/*!
 * @file
 * @brief File containing the definitions of the mrrocpp::ui::shead2::UiRobot class.
 *
 *
 */

#include "ui_r_shead2.h"
#include "ui_ecp_r_shead2.h"

namespace mrrocpp {
namespace ui {
namespace shead2 {

UiRobot::UiRobot(common::Interface& _interface) :
	shead::UiRobot(_interface, lib::shead2::ROBOT_NAME)
{

}

void UiRobot::create_ui_ecp_robot()
{
	ui_ecp_robot = new EcpRobot(*this);
//	return 1;
}

void UiRobot::setup_menubar()
{
	shead::UiRobot::setup_menubar();
	robot_menu->setTitle(QApplication::translate("MainWindow", "S&head2", 0, QApplication::UnicodeUTF8));
}


}
} //namespace ui
} //namespace mrrocpp

