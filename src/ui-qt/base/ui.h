/*!
 * @file
 * @brief File containing the declaration of the mrrocpp::ui::common::function_execution_buffer,
 * mrrocpp::ui::common::feb_thread, mrrocpp::ui::common::busy_flagger, mrrocpp::ui::common::busy_flag classes and state enums.
 *
 *
 */

#ifndef __UI_H
#define __UI_H

#include <boost/function.hpp>
#include <boost/thread/condition_variable.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/thread.hpp>

#include <stdexcept>
#include <iostream>
#include <string>
#include <list>

#include "base/lib/com_buf.h"
#include "base/lib/sr/srlib.h"

#include "base/lib/messip/messip_dataport.h"
#include "base/lib/agent/RemoteAgent.h"

enum UI_NOTIFICATION_STATE_ENUM
{
	UI_N_STARTING, UI_N_READY, UI_N_BUSY, UI_N_EXITING, UI_N_COMMUNICATION, UI_N_PROCESS_CREATION, UI_N_SYNCHRONISATION
};

// FIXME: moved from proto.h for linux compatibility


namespace mrrocpp {
namespace ui {
namespace common {

class Interface;

enum TEACHING_STATE
{
	ECP_TEACHING, MP_RUNNING, MP_PAUSED, MP_PAUSED_H
};

enum TEACHING_STATE_ENUM
{
	FSTRAJECTORY, FSCONFIG
};

enum UI_ECP_COMMUNICATION_STATE
{
	UI_ECP_AFTER_RECEIVE, UI_ECP_REPLY_READY, UI_ECP_AFTER_REPLY
};

enum UI_MP_STATE
{
	UI_MP_NOT_PERMITED_TO_RUN,
	UI_MP_PERMITED_TO_RUN,
	UI_MP_WAITING_FOR_START_PULSE,
	UI_MP_TASK_RUNNING,
	UI_MP_TASK_PAUSED,
	UI_MP_STATE_NOT_KNOWN
};

enum UI_ALL_EDPS_STATE
{
	UI_ALL_EDPS_STATE_NOT_KNOWN,
	UI_ALL_EDPS_NONE_ACTIVATED,
	UI_ALL_EDPS_NONE_LOADED,
	UI_ALL_EDPS_SOME_LOADED,
	UI_ALL_EDPS_ALL_LOADED,
};

enum UI_ALL_EDPS_SYNCHRO_STATE
{
	UI_ALL_EDPS_SYNCHRO_STATE_NOT_KNOWN,
	UI_ALL_EDPS_SYNCHRO_NONE_EDP_LOADED,
	UI_ALL_EDPS_NONE_SYNCHRONISED,
	UI_ALL_EDPS_SOME_SYNCHRONISED,
	UI_ALL_EDPS_ALL_SYNCHRONISED
};

// -1 mp jest wylaczone i nie moze zostac wlaczone , 0 - mp wylaczone ale wszystkie edp gotowe,  1- wlaczone czeka na start
// 2 - wlaczone czeka na stop 3 -wlaczone czeka na resume

typedef enum _EDP_STATE
{
	INACTIVE = -1, OFF = 0, WAITING_TO_START_READER = 1, WAITING_TO_STOP_READER = 2
} EDP_STATE;

typedef struct _edp_state_def
{
	pid_t pid;
	int test_mode;
	std::string node_name;
	std::string section_name; // nazwa sekcji, w ktorej zapisana jest konfiguracja
	std::string network_resourceman_attach_point;
	std::string hardware_busy_attach_point; // do sprawdzenie czy edp juz nie istnieje o ile nie jest tryb testowy
	std::string network_reader_attach_point;
	int node_nr;
	lib::fd_client_t reader_fd;
	bool is_synchronised;
	//! TODO: change from int to EDP_STATE enum
	int state; // -1, edp nie aktywne, 0 - edp wylaczone 1- wlaczone czeka na reader start 2 - wlaczone czeka na reader stop
	int last_state;

	double preset_position[3][lib::MAX_SERVOS_NR]; // pozycje zapisane w konfiguracji
	double front_position[lib::MAX_SERVOS_NR];
} edp_state_def;

typedef struct
{
	pid_t pid;
	std::string node_name;
	std::string section_name; // nazwa sekcji, w ktorej zapisana jest konfiguracja
	std::string network_trigger_attach_point;
	int node_nr;
	lib::fd_client_t trigger_fd;
	int state;
	int last_state;
} ecp_state_def;

typedef struct
{
	bool is_active;
	edp_state_def edp;
	ecp_state_def ecp;
} ecp_edp_ui_robot_def;

typedef struct
{
	pid_t pid;
	std::string node_name;
	std::string network_pulse_attach_point;
	int node_nr;
	RemoteAgent * MP;
	OutputBuffer<char> * pulse;
	UI_MP_STATE state;
	UI_MP_STATE last_process_control_state;
	UI_MP_STATE last_manage_interface_state;
} mp_state_def;

typedef struct
{
	std::string program_name;
	std::string node_name;
	std::string user_name;
	bool is_qnx;
} program_node_user_def;

/*!
 *
 * @brief class creating function execution buffer.
 *
 *
 */
class function_execution_buffer
{
public:
	typedef boost::function <int()> command_function_t;
	Interface& interface;
	int wait_and_execute();
	void command(command_function_t _com_fun);
	function_execution_buffer(Interface& _interface);
private:
	boost::condition_variable cond; //! active command condition
	boost::mutex mtx; //! mutex related to condition variable

	bool has_command; //! flag indicating active command to execute

	command_function_t com_fun; //! command functor
};

/*!
 *
 * @brief class creating feb thread.
 *
 *
 */
class feb_thread : public boost::noncopyable
{
private:
	function_execution_buffer & feb;
	boost::thread thread_id;

public:
	void operator()();

	feb_thread(function_execution_buffer & _feb);
	~feb_thread();

};

// forward declaration
class busy_flag;
/*!
 *
 * @brief class creating busy flagger.
 *
 *
 */
class busy_flagger
{
private:
	//! flag object to decrement in destructor
	busy_flag & flag;

public:
	//! increment busy flag for in a  scoped manner
	busy_flagger(busy_flag & _flag);

	//! desctructor makes flag unbusy
	~busy_flagger();
};
/*!
 *
 * @brief class creating busy flag.
 *
 *
 */
class busy_flag
{
	friend class busy_flagger;

private:
	//! count busy flagging
	int counter;

	//! guard counter variable
	mutable boost::mutex m_mutex;

	//! increment counter
	void increment();

	//! decrement counter
	void decrement();

public:
	bool is_busy() const;

	//! constructor
	busy_flag();
};

}
}
}

#endif

