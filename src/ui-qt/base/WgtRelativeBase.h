/*!
 * @file
 * @brief File containing the declaration of the WgtRelativeBase class.
 *
 * @author mwroble1
 *
 */
#ifndef WGTRELATIVEBASE_H_
#define WGTRELATIVEBASE_H_

#include "wgt_base.h"
/*!
 *
 * @brief Base class for all windows which handle relative moves.
 *
 *
 */
class WgtRelativeBase: public wgt_base
{
Q_OBJECT

public:
	/**
	 * @brief Constructor.
	 * @param _widget_label Window title.
	 * @param _interface A reference to Interface object - main ui class.
	 * @param robo A pointer to robot.
	 * @param parent Pointer to object`s parent.
	 */
	WgtRelativeBase(QString _widget_label, mrrocpp::ui::common::Interface& _interface, mrrocpp::ui::common::UiRobot *robo, QWidget *parent = 0);
	//! Destructor (empty).
	virtual ~WgtRelativeBase();

protected:
	/**
	 * @brief Disables or enables widgets in window depending whether robot is synchronized or not.
	 * @param set_disabled A flag which indicates whether to enable or disable widgets.
	 * @return 1 if succeeded.
	 */
	int synchro_depended_widgets_disable(bool set_disabled);
	/**
	 * @brief Copies passed pointer on QGridLayout object by calling wgt_base::setup_ui and creates buttons and spinboxes.
	 * @param layout A layout needed to add dynamically created widgets to window.
	 */
	void setup_ui(QGridLayout *layout);
	//! Number of angle axis in relative moves.
	const static int angle_axis_number;

private:
	//! Creates l_button and r_button and connects their signals to appropriate slots.
	void create_buttons();
	//! Moves motors.
	virtual int move_it(){return 0;}
	//! Window`s widgets initialization.
	virtual int init(){return 0;}
	//! Default position of desired position spin boxes.
	const static int desired_pos_column=1;
	//! Default position of incremental move buttons.
	const static int inc_move_column=9;
	//! Left arrow push button.
	QPushButton *l_button;
	//! Right arrow push button.
	QPushButton *r_button;

public slots:
	/**
	 * @brief Slot for managing clicking left incremental move button.
	 * @param button Button index in buttons vector.
	 */
	virtual void inc_move_left_button_clicked(int button);
	/**
	 * @brief Slot for managing clicking right incremental move button.
	 * @param button Button index in buttons vector.
	 */
	virtual void inc_move_right_button_clicked(int button);
	/**
	 * @brief Slot for managing clicking right arrow move button. Increments desired position spin boxes.
	 */
	void r_button_clicked();
	/**
	 * @brief Slot for managing clicking left arrow move button. Decrements desired position spin boxes.
	 */
	void l_button_clicked();
	//! Slot for initializing and copying data to spin boxes (i.e. current position).
	void init_and_copy_slot();
};

#endif /* WGTRELATIVEBASE_H_ */
