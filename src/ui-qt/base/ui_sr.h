/*!
 * @file
 * @brief File containing the declaration of the mrrocpp::ui::common::sr_buffer class.
 *
 *
 */
#ifndef __UI_SR_H
#define __UI_SR_H

#include <QMainWindow>

#include <boost/function.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/circular_buffer.hpp>
#include <stdexcept>
#include <iostream>
#include <string>
#include <list>

#include "base/lib/com_buf.h"
#include "base/lib/sr/srlib.h"
#include "base/lib/condition_synchroniser.h"

namespace mrrocpp {
namespace ui {
namespace common {
/*!
 *
 * @brief Class for creating sr_buffer thread.
 *
 *
 */
class sr_buffer : public boost::noncopyable
{
private:
	Interface& interface;
	boost::thread thread_id;
	boost::circular_buffer <lib::sr_package_t> cb;
	boost::circular_buffer <lib::sr_package_t> cb_inter;
	boost::mutex mtx;

public:
	//! Length of the sr buffer.
	static const int UI_SR_BUFFER_LENGHT = 200;

	lib::condition_synchroniser thread_started;
	/**
	 * @brief Constructor.
	 * @param _interface A reference to Interface object - main ui class.
	 */
	sr_buffer(Interface& _interface);
	//! Destructor.
	~sr_buffer();

	//! main thread loop
	void operator()();
	/**
	 * @brief Puts one message. Raises semaphore.
	 * @param new_msg A message to be put.
	 */
	void put_one_msg(const lib::sr_package_t& new_msg);
	/**
	 * @brief Gets one message. Raises semaphore.
	 * @param[out] new_msg A reference to message to get.
	 */
	void get_one_msg(lib::sr_package_t& new_msg);
	/**
	 * @brief Gets one message. Raises semaphore.
	 * @param[out] new_msg A reference to message to get.
	 */
	void inter_get_one_msg(lib::sr_package_t& new_msg);
	/**
	 * @brief Checks whether circular buffer is empty.
	 * @return True if empty.
	 */
	bool buffer_empty();
	/**
	 * @brief Checks whether circular buffer is empty.
	 * @return True if empty.
	 */
	bool inter_buffer_empty();
	//! Copies cb to cb_inter.
	void copy_buffers();
	//! Clears cb.
	void clear_buffer();
};

}
} //namespace ui
} //namespace mrrocpp
#endif

