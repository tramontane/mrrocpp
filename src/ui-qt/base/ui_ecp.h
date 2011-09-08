/*!
 * @file
 * @brief File containing the declaration of the mrrocpp::ui::common::ecp_buffer class.
 *
 *
 */
#ifndef __UI_ECP_H
#define __UI_ECP_H

#include <boost/thread/thread.hpp>
#include <stdexcept>
#include <iostream>
#include <string>
#include <list>

#include "base/lib/com_buf.h"
#include "base/lib/sr/srlib.h"
#include "base/lib/condition_synchroniser.h"

#include "ui.h"

namespace mrrocpp {
namespace ui {
namespace common {

/*!
 *
 * @brief Class creating ECP buffer for communication.
 *
 *
 */
class ecp_buffer : public boost::noncopyable
{
private:
	Interface& interface;
	boost::thread thread_id;

public:
	//! Communication state.
	UI_ECP_COMMUNICATION_STATE communication_state;
	//! A message sent from ECP to UI.
	lib::ECP_message ecp_to_ui_msg;
	//! A reply from UI to ECP.
	lib::UI_reply ui_rep;
	//! main thread loop
	void operator()();
	//! For synchronization.
	lib::condition_synchroniser synchroniser;
	/**
	 * @brief Constructor.
	 * @param _interface A reference to Interface object - main ui class.
	 */
	ecp_buffer(Interface& _interface);
	//! Destructor.
	~ecp_buffer();
};

}
} //namespace ui
} //namespace mrrocpp

#endif

