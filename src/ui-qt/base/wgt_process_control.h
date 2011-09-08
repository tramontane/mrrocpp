/*!
 * @file
 * @brief File containing the declaration of the wgt_process_control class.
 *
 * @author mwroble1
 *
 */
#ifndef WGT_PROCESS_CONTROL_H
#define WGT_PROCESS_CONTROL_H

#include <QtGui/QWidget>
#include <QVBoxLayout>
#include <QDockWidget>
#include "ui_wgt_process_control.h"
#include "wgt_base.h"



namespace mrrocpp {
namespace ui {
namespace common {
class Interface;
class AllRobots;

}
}
}
/*!
 *
 * @brief Class for all robots process control window.
 *
 *
 * @ingroup ui
 */
class wgt_process_control : public wgt_base
{
Q_OBJECT

public:
	/**
	 * @brief Constructor.
	 * @param _interface reference for Interface class
	 * @param parent Pointer to widget`s parent (null by default).
	 */
	wgt_process_control(mrrocpp::ui::common::Interface& _interface, QWidget *parent = 0);
	//! Destructor.
	~wgt_process_control();
	//! Emits process_control_window_init_signal handled by process_control_window_init_slot().
	void process_control_window_init();
	/**
	 * @brief Opens window.
	 * @param set_on_top Indicates whether the window should be on top after opening (false by default).
	 */
	void my_open(bool set_on_top=false);
	/**
	 * @brief Returns pointer to window prepared in QtDesigner.
	 * @return Pointer to robot process control window prepared in QtDesigner.
	 */
	Ui::wgt_process_controlClass * get_ui();
//
//	virtual void add_button(QPushButton *button, int row, int space){};
//	virtual void setup_ui(){};

private:
	//! A pointer to window created in QtDesigner.
	Ui::wgt_process_controlClass* ui;
	/**
	 * @brief Updates all process control buttons.
	 * @return 1 if succeeded.
	 */
	int init();
	/**
	 * @brief Blocks trigger push button.
	 * @return 1 if succeeded.
	 */
	int block_all_ecp_trigger_widgets();
	/**
	 * @brief Unblocks trigger push button.
	 * @return 1 if succeeded.
	 */
	int unblock_all_ecp_trigger_widgets();
signals:
	//! Signal for initializing process control window.
	void process_control_window_init_signal();
public slots:
	//! Manages process_control_window_init_signal(). Calls init().
	void process_control_window_init_slot();
private slots:
	//! Manages pressing start button. Starts MP.
	void on_mp_start_pushButton_clicked();
	//! Manages pressing stop button. Stops MP.
	void on_mp_stop_pushButton_clicked();
	//! Manages pressing pause button. Pauses MP.
	void on_mp_pause_pushButton_clicked();
	//! Manages pressing resume button. Resumes MP.
	void on_mp_resume_pushButton_clicked();
	//! Manages pressing trigger button. Starts MP.
	void on_mp_trigger_pushButton_clicked();
	//! Manages pressing ECP trigger button. Triggers ECP pulse.
	void on_all_ecp_trigger_pushButton_clicked();
	//! Slot for managing clicking start button. Starts reader for all robots.
	void on_all_reader_start_pushButton_clicked();
	//! Slot for managing clicking stop button. Stops reader for all robots.
	void on_all_reader_stop_pushButton_clicked();
	//! Slot for managing clicking trigger button. Triggers pulse reader for all robots.
	void on_all_reader_trigger_pushButton_clicked();
};

#endif // WGT_PROCESS_CONTROL_H
