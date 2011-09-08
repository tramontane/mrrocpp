/*!
 * @file
 * @brief File containing the declaration of the WgtToolBase class.
 *
 * @author mwroble1
 *
 */
#ifndef WGTTOOLBASE_H_
#define WGTTOOLBASE_H_

#include "wgt_base.h"
#include "ui_wgt_tool_template.h"
/*!
 *
 * @brief Base class for all windows which handle tools moves.
 *
 *
 */
class WgtToolBase : public wgt_base
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
	WgtToolBase(QString _widget_label, mrrocpp::ui::common::Interface& _interface, mrrocpp::ui::common::UiRobot *robo, QWidget *parent = 0);
	//! Destructor (empty).
	virtual ~WgtToolBase();

protected:
	//! Vector holding current position spin boxes.
	QVector <QDoubleSpinBox*> current_pos_spin_boxes;
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
	//! Number of angle axis.
	const static int angle_axis_number;
	/**
	 * @brief Adds current position spin boxes to window.
	 */
	void create_buttons_and_spin_boxes();

private:
	//! Creates Read, Set and Copy buttons and connects their signals to appropriate slots.
	void create_buttons();
	//! Moves motors.
	virtual int move_it(){return 0;}
	//! Window`s widgets initialization.
	virtual int init(){return 0;}
	/**
	 * @brief Adds current position spin box to window.
	 * @param spin_box A pointer to spin box to be added.
	 * @param row A row in which the spin box will be added.
	 */
	virtual void add_current_position_spin_box(QDoubleSpinBox *spin_box, int row);
	//! Copies current position values to desired ones.
	int copy();
	//! Default position of desired position spin boxes.
	const static int desired_pos_column=5;
	//! Default position of incremental move buttons.
	const static int inc_move_column=9;
	//! Read button.
	QPushButton *read_button;
    //! Set button.
	QPushButton *set_button;
    //! Copy button.
	QPushButton *copy_button;

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
	//! Slot for initializing and copying data to spin boxes (i.e. current position).
	void init_and_copy_slot();
	//! Slot for managing Read button click.
	void read_button_clicked();
	//! Slot for managing Copy button click.
	void copy_button_clicked();
	//! Slot for managing Set button click.
	void execute_button_clicked();
};

#endif /* WGTTOOLBASE_H_ */
