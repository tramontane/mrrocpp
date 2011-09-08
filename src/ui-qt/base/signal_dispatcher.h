/*!
 * @file
 * @brief File containing the declaration of the Ui::SignalDispatcher class.
 *
 * @author mwroble1
 *
 * @ingroup Ui
 */


#ifndef SIGNALDISPATCHER_H
#define SIGNALDISPATCHER_H
#include <QObject>


class wgt_base;
class wgt_robot_process_control;

namespace mrrocpp {
namespace ui {
namespace common {
class Interface;
class UiRobot;
}
}
}
namespace mrrocpp{
namespace ui{
namespace irp6ot_m{
class UiRobot;
}
}
}



namespace Ui
{
/*!
 *
 * @brief Class for connecting signals with appropriate functions.
 *
 * The reason of not placing some slots in UiRobot class and putting them in this class is because of Qt`s connect() requirements.
 *
 * @ingroup Ui
 */
class SignalDispatcher : public QObject
{
Q_OBJECT

public:
/**
 * @brief Constructor.
 * @param iface reference for Interface class
 */
	SignalDispatcher(mrrocpp::ui::common::Interface& iface);
	//! Destructor (empty).
	~SignalDispatcher();

public slots:
	/**
	 * @brief Calls EDP loading function for robot passed by argument.
	 * @param robot a pointer to robot object.
	 */
	void on_EDP_Load_triggered(mrrocpp::ui::common::UiRobot *robot);
	/**
	 * @brief Calls EDP unloading function for robot passed by argument.
	 * @param robot a pointer to robot object.
	 */
	void on_EDP_Unload_triggered(mrrocpp::ui::common::UiRobot *robot);
	/**
	 * @brief Calls robot synchronization function.
	 * @param robot a pointer to robot object.
	 */
	void on_Synchronisation_triggered(mrrocpp::ui::common::UiRobot *robot);
	/**
	 * @brief Calls robot fault clearing function.
	 * @param robot a pointer to robot object.
	 */
	void on_Clear_Fault_triggered(mrrocpp::ui::common::UiRobot *robot);
	/**
	 * @brief Calls moving to synchro position function for robot.
	 * @param robot a pointer to robot object.
	 */
	void on_Synchro_Position_triggered(mrrocpp::ui::common::UiRobot *robot);
	/**
	 * @brief Calls moving to front position for robot.
	 * @param robot a pointer to robot object.
	 */
	void on_Front_Position_triggered(mrrocpp::ui::common::UiRobot *robot);
	/**
	 * @brief Calls moving to predefined position 0 for robot.
	 * @param robot a pointer to robot object.
	 */
	void on_Position_0_triggered(mrrocpp::ui::common::UiRobot *robot);
	/**
	 * @brief Calls moving to predefined position 1 for robot.
	 * @param robot a pointer to robot object.
	 */
	void on_Position_1_triggered(mrrocpp::ui::common::UiRobot *robot);
	/**
	 * @brief Calls moving to predefined position 2 for robot.
	 * @param robot a pointer to robot object.
	 */
	void on_Position_2_triggered(mrrocpp::ui::common::UiRobot *robot);
	/**
	 * @brief  Calls to MainWindow class to open window passed by pointer.
	 * @param window a pointer to window to be opened.
	 * @param set_on_top Indicates whether opened window should pop on top.
	 */
	void open_new_window(wgt_base *window, bool set_on_top=true);

private:
	//! Reference to Interface object.
	mrrocpp::ui::common::Interface &interface;
};

}

#endif
