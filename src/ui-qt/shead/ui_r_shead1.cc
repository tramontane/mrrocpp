/*!
 * @file
 * @brief File containing the definitions of the mrrocpp::ui::shead1::UiRobot class.
 *
 *
 */


#include "ui_r_shead1.h"
#include "ui_ecp_r_shead1.h"

namespace mrrocpp {
namespace ui {
namespace shead1 {

UiRobot::UiRobot(common::Interface& _interface) :
	shead::UiRobot(_interface, lib::shead1::ROBOT_NAME)
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
	robot_menu->setTitle(QApplication::translate("MainWindow", "S&head1", 0, QApplication::UnicodeUTF8));
}

}
} //namespace ui
} //namespace mrrocpp

