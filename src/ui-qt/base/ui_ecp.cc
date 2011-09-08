/*!
 * @file
 * @brief File containing the definitions of the mrrocpp::ui::common::ecp_buffer class.
 *
 *
 */

/* Standard headers */
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <cstring>
#include <cerrno>// Y&7
#include <ctime>
#include <iostream>
#include <fstream>

#include "ui.h"

#include "base/lib/sr/srlib.h"
#include "base/ecp/ecp_task.h"
#include "base/lib/com_buf.h"
#include "base/lib/mis_fun.h"
#include "interface.h"
#include "ui_sr.h"
#include "ui_ecp.h"

#include "base/lib/messip/messip_dataport.h"
#include "mainwindow.h"

namespace mrrocpp {

namespace ecp {
namespace common {
namespace task {

//! Dummy task required for dynamic linking
mrrocpp::ecp::common::task::task_base * return_created_ecp_task(mrrocpp::lib::configurator&)
{
	return NULL;
}

} // namespace ecp
} // namespace common
} // namespace task

namespace ui {
namespace common {

ecp_buffer::ecp_buffer(Interface& _interface) :
	interface(_interface), communication_state(UI_ECP_AFTER_REPLY)
{
	thread_id = boost::thread(boost::bind(&ecp_buffer::operator(), this));
}

ecp_buffer::~ecp_buffer()
{
	// thread_id.interrupt();
	// thread_id.join(); // join it
}

void ecp_buffer::operator()()
{

	lib::set_thread_priority(pthread_self(), lib::PTHREAD_MAX_PRIORITY - 5);

	lib::set_thread_name("comm");

	lib::fd_server_t ch;

	ch = messip::port_create(interface.ui_attach_point);
	assert(ch);

	while (1) {
		// communication_state = ui::common::UI_ECP_REPLY_READY;
		communication_state = UI_ECP_AFTER_REPLY;

		int32_t type, subtype;
		int rcvid = messip::port_receive(ch, type, subtype, ecp_to_ui_msg);

		if ((rcvid != MESSIP_MSG_NOREPLY) && (rcvid != 0)) {
			continue;
		}

		synchroniser.null_command();

		// tu wyemitowac sygnal (wywqaolac odpowiednia metode mainwindow)

		//dalszy kod do obslugi slotu
		interface.raise_ui_ecp_window();

		synchroniser.wait();

		messip::port_reply(ch, rcvid, 0, ui_rep);

	}

}

}
} //namespace ui
} //namespace mrrocpp
