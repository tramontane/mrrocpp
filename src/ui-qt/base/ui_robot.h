/*!
 * @file
 * @brief File containing the declaration of the common::UiRobot class.
 *
 *
 * @ingroup ui
 */

#ifndef __UI_ROBOT_H
#define __UI_ROBOT_H

#include <QObject>
#include <QMenu>
#include "ui.h"
#include "base/lib/sr/sr_ecp.h"
#include "base/ecp/ecp_robot.h"
#include "wgt_base.h"

class QDockWidget;
class wgt_robot_process_control;

namespace Ui {
class MenuBar;
class SignalDispatcher;
}

namespace mrrocpp {
namespace ui {
namespace common {

const std::string WGT_ROBOT_PC = "WGT_ROBOT_PC";

#define CATCH_SECTION_IN_ROBOT catch (ecp::common::robot::ECP_main_error & e) { \
	/* Obsluga bledow ECP */ \
		catch_ecp_main_error(e); \
  } /*end: catch */ \
\
catch (ecp::common::robot::ECP_error & er) { \
	/* Wylapywanie bledow generowanych przez modul transmisji danych do EDP */ \
		catch_ecp_error(er); \
} /* end: catch */ \
\
catch(const std::exception & e){\
	catch_std_exception(e); \
}\
\
catch (...) {  /* Dla zewnetrznej petli try*/ \
	/* Wylapywanie niezdefiniowanych bledow*/ \
		catch_tridot(); \
} /*end: catch */\


#define CATCH_SECTION_UI catch (ecp::common::robot::ECP_main_error & e) { \
	/* Obsluga bledow ECP */ \
		robot.catch_ecp_main_error(e); \
  } /*end: catch */ \
\
catch (ecp::common::robot::ECP_error & er) { \
	/* Wylapywanie bledow generowanych przez modul transmisji danych do EDP */ \
		robot.catch_ecp_error(er); \
} /* end: catch */ \
\
catch(const std::exception & e){\
	robot.catch_std_exception(e); \
}\
\
catch (...) {  /* Dla zewnetrznej petli try*/ \
	/* Wylapywanie niezdefiniowanych bledow*/ \
		robot.catch_tridot(); \
} /*end: catch */\


#define CATCH_SECTION_UI_PTR catch (ecp::common::robot::ECP_main_error & e) { \
	/* Obsluga bledow ECP */ \
		robot->catch_ecp_main_error(e); \
  } /*end: catch */ \
\
catch (ecp::common::robot::ECP_error & er) { \
	/* Wylapywanie bledow generowanych przez modul transmisji danych do EDP */ \
		robot->catch_ecp_error(er); \
} /* end: catch */ \
\
catch(const std::exception & e){\
	robot->catch_std_exception(e); \
}\
\
catch (...) {  /* Dla zewnetrznej petli try*/ \
	/* Wylapywanie niezdefiniowanych bledow*/ \
		robot->catch_tridot(); \
} /*end: catch */\


class Interface;

/*!
 *
 * @brief Base class for all robots which will be managed by the UI.
 *
 *
 * @ingroup ui
 */
class UiRobot : public QObject
{
Q_OBJECT

public:
	//! Reference to Interface.
	Interface& interface;
	//! Returns robot`s name.
	const lib::robot_name_t getName();
	//! Pointer to thread.
	feb_thread* tid;
	//! Execution buffer thread.
	function_execution_buffer eb;
	//! State of EDP and ECP of the robot.
	ecp_edp_ui_robot_def state;
	//! Pointer to object needed for communication with SR and ECP for all robots.
	boost::shared_ptr <lib::sr_ecp> msg;
	/**
	 * @brief Unique robot name
	 */
	const lib::robot_name_t robot_name;
	//! Number of servomechanisms.
	int number_of_servos;
	/**
	 * @brief Constructor.
	 * @param _interface Reference for Interface class.
	 * @param _robot_name The name of the robot.
	 * @param _number_of_servos The count of servomechanisms.
	 */
	UiRobot(Interface& _interface, lib::robot_name_t _robot_name, int _number_of_servos);
	//! Destructor.
	~UiRobot();
	//! Creates tid thread.
	void create_thread();
	//! Aborts tid thread.
	void abort_thread();
	/**
	 * @brief Sends pulse to reader.
	 * @param code Code of the pulsr.
	 * @param value Value for port_send_pulse.
	 */
	void pulse_reader_execute(int code, int value);
	/**
	 * @brief Start pulse for reader.
	 * @return True if succeeded.
	 */
	bool pulse_reader_start_exec_pulse(void);
	/**
	 * @brief Stop pulse for reader.
	 * @return True if succeeded.
	 */
	bool pulse_reader_stop_exec_pulse(void);
	/**
	 * @brief Trigger pulse for reader.
	 * @return True if succeeded.
	 */
	bool pulse_reader_trigger_exec_pulse(void);
	//! Sends ECP pulse if ECP is running.
	void pulse_ecp(void);
	//! Closes all opened windows.
	void close_all_windows();
	//! Slays EDP.
	void EDP_slay_int();
	//! Closes all EDP connections.
	void close_edp_connections();
	//! Connects to reader. The attempt is made lib::CONNECT_RETRY times.
	void connect_to_reader(void);
	//! Connects to ECP pulse channel.
	void connect_to_ecp_pulse_chanell(void); //TODO: channel, nie chanell
	/**
	 * @brief Pulse for ECP.
	 * @param code Code of the pulse to be sent.
	 * @param value Value to be sent to port_send_pulse.
	 */
	void pulse_ecp_execute(int code, int value);
	//! Delete ECP robot driver.
	virtual void delete_ui_ecp_robot() = 0;
	//! Set ECP driver to null.
	virtual void null_ui_ecp_robot() = 0;
	//! Get process id of EDP.
	virtual int ui_get_edp_pid() = 0;
	/**
	 * @brief Pulse for ECP.
	 * @param[out] robot_controller_initial_state_l Sets robot initial controller state.
	 */
	virtual void ui_get_controler_state(lib::controller_state_t & robot_controller_initial_state_l) = 0;
	//! Manages interface state.
	virtual int manage_interface();
	//! Sets menu items to menu bar and makes their connections.
	virtual void setup_menubar();
	//! Cleares fault.
	virtual int execute_clear_fault()
	{
		return 0;
	}
	//! Gets pointer to current position array.
	virtual double* getCurrentPos()
	{
		return NULL;
	}
	//! Gets pointer to desired position array.
	virtual double* getDesiredPos()
	{
		return NULL;
	}
	//! Synchronizes robot.
	virtual int synchronise() = 0;
	//! Creates EDP for robot.
	virtual void edp_create();
	//! Creates EDP for robot.
	virtual int edp_create_int();
	//! Creates ECP for robot.
	virtual void create_ui_ecp_robot() = 0;
	/**
	 * @brief Gets pointer to robot process control window.
	 * @return Pointer to robot process control window.
	 */
	wgt_robot_process_control * get_wgt_robot_pc();
	//! Performs my_close on robot process control window.
	void delete_robot_process_control_window();
	//! Performs my_open on robot process control window.
	void open_robot_process_control_window();
	//! Blocks all ECP trigger widgets in process control window.
	void block_ecp_trigger();
	//! Unblocks all ECP trigger widgets in process control window.
	void unblock_ecp_trigger();
	//! Creates EDP and extra operations depending on specyfic robot.
	virtual int edp_create_int_extra_operations();
	/**
	 * @brief Checks if robot has EDP loaded and if it`s synchronized.
	 * @return True if EDP loaded and robot synchronized, false otherwise.
	 */
	bool check_synchronised_and_loaded();
	/**
	 * @brief Deactivates ECP trigger.
	 * @return True if succeeded, false otherwise.
	 */
	bool deactivate_ecp_trigger();
	/**
	 * @brief Reloads configuration from configuration file.
	 * @return 1 if succeeded.
	 */
	int reload_configuration();
	/**
	 * @brief Moves robot to synchro position,
	 * @return 1 if succeeded.
	 */
	virtual int move_to_synchro_position();
	/**
	 * @brief Moves robot to front position,
	 * @return 1 if succeeded.
	 */
	virtual int move_to_front_position();
	/**
	 * @brief Moves robot to preset position.
	 * @param variant 0, 1, 2 variants possible.
	 * @return 1 if succeeded.
	 */
	virtual int move_to_preset_position(int variant);
	/**
	 * @brief Default try catch handler for ECP.
	 * @param e ECP main error.
	 */
	void catch_ecp_main_error(ecp::common::robot::ECP_main_error & e);
	/**
	 * @brief Default try catch handler for ECP.
	 * @param er ECP error.
	 */
	void catch_ecp_error(ecp::common::robot::ECP_error & er);
	/**
	 * @brief Default try catch handler for standard exceptions.
	 * @param e std exception.
	 */
	void catch_std_exception(const std::exception & e);
	//! Default try catch handler for managing undefined errors.
	void catch_tridot();
	//! Typedef for map holding all windows.
	typedef std::map <std::string, wgt_base*> wgt_t;
	//! Typedef for value type of wgt_t.
	typedef wgt_t::value_type wgt_pair_t;
	//! Pointer to robot process control window.
	wgt_robot_process_control *wgt_robot_pc;
	//! A map holding all windows.
	wgt_t wgts;
	//! Sets desired positions to zero.
	void zero_desired_position();
	/**
	 * @brief Template for creating and adding new window to wgts map.
	 * @param name Window name in map.
	 * @param label Window title
	 * @tparam T Specyfic window to be created.
	 */
	template <typename T> void add_wgt(std::string name, QString label)
	{
		wgt_base *created_wgt = new T(label, interface, this);
		wgts[name] = created_wgt;
	}
	//! Current position array.
	double *current_pos;
	//! Desired position array.
	double *desired_pos;

protected:
	//! Action added to menu bar.
	QAction *EDP_Load;
	//! Action added to menu bar.
	QAction *EDP_Unload;
	//! Action added to menu bar.
	QAction *wgt_robot_process_control_action;
	//! Submenu added to menu bar.
	QMenu *robot_menu;
};

}
}
}
#endif

