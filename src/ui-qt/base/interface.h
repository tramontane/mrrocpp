/*!
 * @file
 * @brief File contains Interface class declaration
 */

#ifndef __INTERFACE_H
#define __INTERFACE_H

#include <iostream>
#include <vector>

#include <boost/shared_ptr.hpp>

#include <QMainWindow>
#include <QTimer>
#include <QVBoxLayout>
#include <QDockWidget>

//#include "mainwindow.h"
#include "wgt_process_control.h"
#include "wgt_robot_process_control.h"
#include "ui_ecp_dialogs/wgt_yes_no.h"
#include "ui_ecp_dialogs/wgt_message.h"
#include "ui_ecp_dialogs/wgt_input_integer.h"
#include "ui_ecp_dialogs/wgt_input_double.h"
#include "ui_ecp_dialogs/wgt_choose_option.h"
#include "ui_ecp_dialogs/wgt_teaching.h"

#include "base/lib/sr/sr_ecp.h"
#include "base/lib/sr/sr_ui.h"
#include "base/lib/configurator.h"
#include "base/ecp/ecp_robot.h"

//#include "string"

#include "ui.h"

#include "base/lib/messip/messip_dataport.h"



//namespace Ui{
class MainWindow;
//}


namespace mrrocpp {
namespace ui {
namespace common {

class AllRobots;
class Mp;



#define ADD_UI_ROBOT(__robot_name) \
		{\
			common::UiRobot *created_robot = new __robot_name::UiRobot(*this);\
			robot_m[created_robot->robot_name] = created_robot;\
		}

class UiRobot;

typedef std::map <lib::robot_name_t, UiRobot*> robots_t;
typedef robots_t::value_type robot_pair_t;

class sr_buffer;
class ecp_buffer;

/*!
 *
 * @brief Superclass aggregating most of the UI logic.
 *
 *
 * @ingroup ui
 */
class Interface : public QObject
{
Q_OBJECT
private:
	//! Creates all robots in the system using macro ADD_UI_ROBOT and sets their menu by calling setRobotsMenu().
	void create_robots();
	//! ???
	boost::shared_ptr<QTimer> timer;
	//! ???
	bool html_it(std::string &_input, std::string &_output);
	//! Calls setup_menubar() method on every robot.
	void setRobotsMenu();

signals:
	//! Signal for managing interface state.
	void manage_interface_signal();
	//! Signal for raising process control window.
	void raise_process_control_window_signal();
	//! Signal for raising ECP window.
	void raise_ui_ecp_window_signal();

private slots:
	//! Manages state for all robots, process control windows and menus.
	void manage_interface_slot();
	//! Raises process control window.
	void raise_process_control_window_slot();
	//! Raises ECP window.
	void raise_ui_ecp_window_slot();
	//! Slot managing timer when closing application.
	void timer_slot();

public:
	//! Constructor. Creates MainWindow.
	Interface();
	//! Destructor. Deletes all robots.
	~Interface();
	//! Emits signal to raise process control window handled by raise_process_control_window_slot().
	void raise_process_control_window();
	//! Emits signal to raise ECP window handled by raise_ui_ecp_window_slot().
	void raise_ui_ecp_window();
	//! ?????
	void start_on_timer();
	//! A pointer to MainWindow object.
	boost::shared_ptr<MainWindow> mw;
	/**
	 * @brief Returns pointer to MainWindow object.
	 * @return Pointer to MainWindow object.
	 */
	MainWindow* get_main_window() const;
	/**
	 * @brief Returns pointer to process control window.
	 * @return Pointer to process control window.
	 */
	wgt_process_control* get_process_control_window();
	/**
	 * @brief Prints message on the console.
	 * @param buff A message to be printed (in printf-like format).
	 */
	void print_on_sr(const char *buff, ...);
	//! Flag notifying about ui being busy with communication.
	busy_flag communication_flag;

	//! Pointer to SR thread.
	boost::shared_ptr <sr_buffer> ui_sr_obj;
	//! Pointer to ECP thread.
	boost::shared_ptr <ecp_buffer> ui_ecp_obj;
	//! Pointer to MEB thread.
	boost::shared_ptr <feb_thread> meb_tid;
	//! ?????
	function_execution_buffer *main_eb;

	typedef std::string list_t;

	//! Lists of sections and net nodes of configuration files.
	std::list <list_t> section_list, config_node_list, all_node_list;
	//! List of programs` names and nodes on which they will be running.
	std::list <program_node_user_def> program_node_user_list;

	// TODO: change to ENUM
	//! State of the user interface - 1 working, 2 exiting started, 3-5 exiting in progress - mrrocpp processes closing, 6 - exit immediately.
	short ui_state;
	//! Old systemState for teaching.
	TEACHING_STATE teachingstate;
	//! ?????
	TEACHING_STATE_ENUM file_window_mode;
	//! Holds current and next notification of state.
	UI_NOTIFICATION_STATE_ENUM notification_state, next_notification;
	//! File for logging.
	std::ofstream *log_file_outfile;
	//! Mutex for process creation.
	boost::mutex process_creation_mtx;
	//! Mutex for notification about ui state.
	boost::mutex ui_notification_state_mutex;
	//! ?????
	boost::shared_ptr<lib::configurator> config;
	//! A pointer to object for communication with SR thread.
	boost::shared_ptr <lib::sr_ui> ui_msg;
	//! Flag for indicating if master process and ECPs are active.
	bool is_mp_and_ecps_active;
	//! ?????
	const int position_refresh_interval;
	/**
	 * @brief Sets current state notification.
	 * @param new_notifacion New notification to be set.
	 */
	int set_ui_state_notification(UI_NOTIFICATION_STATE_ENUM new_notifacion);
	//! Manages application closing.
	void UI_close(void);
	//! Initializes application - creates windows, sets paths for ui, creates robots.
	void init();
	//! ?????
	int wait_for_child_termiantion(pid_t pid);
	//! Emits signal for managing interface state. The signal is connected to manage_interface_slot().
	int manage_interface(void);
	//! Manages process control window.
	void manage_pc(void);

	//! Reloads configuration after choosing configuration file.
	void reload_whole_configuration();

	//! @bug: this call is not used. It should be deleted, since
	//! thread objects are managed with boost::shared_ptr and deleted
	//! automatically when a container object is deleted.

	//! Resets sr, ecp and meb threads.
	void abort_threads();
	//! Fills all network nodes list.
	void fill_node_list(void);
	/**
	 * @brief Fills section list from configuration file
	 * @param file_name_and_path File name and path to configuration file.
	 * @return 1 if succeeded.
	 */
	int fill_section_list(const char *file_name_and_path);
	/**
	 * @brief Initializes configuration.
	 * @return 1 if succeeded.
	 */
	int initiate_configuration(void);
	/**
	 * @brief Clears all configuration lists.
	 * @return 1 if succeeded.
	 */
	int clear_all_configuration_lists(void);
	/**
	 * @brief Fills program node list.
	 * @return 1 if succeeded.
	 */
	int fill_program_node_list(void);
	/**
	 * @brief Gets default configuration filename from configs/default_file.cfg if exists. Otherwise creates such file and writes common.ini file to it.
	 * @return 1 if file existed, 2 otherwise.
	 */
	int get_default_configuration_file_name(void);
	/**
	 * @brief Writes default configuration name.
	 * @return 1 if succeeded.
	 */
	int set_default_configuration_file_name(void);

	/**
	 * @brief Modifies MP state considering states of all EDPs.
	 * @return 1 if succeeded.
	 */
	int check_edps_state_and_modify_mp_state(void);
	/**
	 * @brief Depracated method.
	 * @return Always returns 1.
	 */
	int check_gns(void);
	/**
	 * @brief Checks if node exists by pinging it.
	 * @param _node Reference to node being checked.
	 * @param beginnig_of_message Beginning of a message which is displayed if node does not exist.
	 * @return Returns true if node exists, false otherwise.
	 */
	bool check_node_existence(const std::string & _node, const std::string & beginnig_of_message);

	//! TODO: throw an exception (assumed inheritance from std::exception)

	//! Local path with config file for configuration.
	std::string config_file_relativepath;
	//! Network path with mrrocpp binaries.
	std::string binaries_network_path;
	//! Local path with mrrocpp binaries.
	std::string binaries_local_path;
	//! Local path of mrrocpp, i.e. "/home/yoyek/mrrocpp/build", where catalogs like bin, configs etc. should be.
	std::string mrrocpp_local_path;
	//! Local path of mrrocpp (without build), i.e."/home/yoyek/mrrocpp", where catalogs like bin, configs etc. should be.
	std::string mrrocpp_root_local_path;

	//! Default path for fileselect for teaching generator.
	std::string teach_filesel_fullpath;
	//! Config file name for UI.
	std::string config_file;
	//! Session name.
	std::string session_name;
	//! Global configuration path.
	std::string config_file_fullpath;


	//! ?????
	std::string ui_attach_point;
	//! ?????
	std::string network_sr_attach_point;
	//! ?????
	std::string sr_attach_point;
	//! Node name on which UI runs.
	std::string ui_node_name;
	//! ?????
	const std::string mrrocpp_bin_to_root_path;



	/**
	 * @brief Gets robots map.
	 * @return Robots map.
	 */
	common::robots_t getRobots() const;
	/**
	 * @brief map of all robots used in the task
	 */
	common::robots_t robot_m;
	//! Creates ui_sr_obj, meb_tid, ui_ecp_obj threads.
	void create_threads();
	//! Unloads all robots and MP.
	int unload_all();
	//! First calls unload_all() and then does brutal kill on processes.
	int slay_all();

	//! A pointer to Master Process object.
	Mp *mp;
	//! A pointer to AllRobots object.
	AllRobots *all_robots;
	//! Opens process windows for single robots.
	void open_process_control_windows();
	/**
	 * @brief Gets process control window.
	 * @return Pointer to process control window.
	 */
	wgt_process_control* get_wgt_pc()
	{
		return wgt_pc;
	}


	//! Process control window pointer.
	wgt_process_control* wgt_pc;
	//! Yes-No dialog window pointer.
	wgt_yes_no* wgt_yes_no_obj;
	//! Message dialog window pointer.
	wgt_message* wgt_message_obj;
	//! Input integer window pointer.
	wgt_input_integer* wgt_input_integer_obj;
	//! Input double window pointer.
	wgt_input_double* wgt_input_double_obj;
	//! Choose option window pointer.
	wgt_choose_option* wgt_choose_option_obj;
	//! Teaching dialog window pointer.
	wgt_teaching* wgt_teaching_obj;

};

}
}
}

#endif

