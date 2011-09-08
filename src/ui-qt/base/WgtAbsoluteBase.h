/*!
 * @file
 * @brief File containing the declaration of the WgtAbsoluteBase class.
 *
 * @author mwroble1
 *
 */
#ifndef WGTABSOLUTEBASE_H_
#define WGTABSOLUTEBASE_H_

#include "wgt_base.h"
#include <QGridLayout>
#include <QPushButton>
#include <iostream>

/*!
 *
 * @brief Base class for all windows which handle absolute moves.
 *
 *
 */
class WgtAbsoluteBase: public wgt_base
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
	WgtAbsoluteBase(QString _widget_label, mrrocpp::ui::common::Interface& _interface, mrrocpp::ui::common::UiRobot *robo, QWidget *parent = 0);
	//! Destructor (empty).
	virtual ~WgtAbsoluteBase();

protected:
	//! Vector holding current position spin boxes.
	QVector <QDoubleSpinBox*> current_pos_spin_boxes;
	//! Spin box for setting step for incremental moves.
	QDoubleSpinBox *step_spinbox;
	//! Read button.
    QPushButton *read_button;
    //! Execute button.
    QPushButton *execute_button;
    //! Import button.
    QPushButton *import_button;
    //! Export button.
    QPushButton *export_button;
    //! Copy button.
    QPushButton *copy_button;
	/**
	 * @brief Adds incremental move buttons and current position spin boxes to window.
	 */
	void create_buttons_and_spin_boxes();
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
	/**
	 * @brief Adds current position spin box to window.
	 * @param spin_box A pointer to spin box to be added.
	 * @param row A row in which the spin box will be added.
	 */
	virtual void add_current_position_spin_box(QDoubleSpinBox *spin_box, int row);

private:
	//! Creates read, execute, import, export and copy buttons and connects their signals to appropriate slots.
	void create_buttons();
	//! Creates step spin box used for incremental moves.
	void create_step_spinbox();
	//! Copies current position values to desired ones.
	int copy();
	//! Moves motors.
	virtual int move_it(){return 0;}
	//! Window`s widgets initialization.
	virtual int init(){return 0;}
	//! Default position of desired position spin boxes.
	const static int desired_pos_column=6;
	//! Default position of incremental move buttons.
	const static int inc_move_column=10;

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
	//! Slot for managing Read button click.
	void read_button_clicked();
	//! Slot for managing Export button click.
	void export_button_clicked();
	//! Slot for managing Import button click.
	void import_button_clicked();
	//! Slot for managing Copy button click.
	void copy_button_clicked();
	//! Slot for managing Execute button click.
	void execute_button_clicked();
	//! Slot for initializing and copying data to spin boxes (i.e. current position).
	void init_and_copy_slot();
};

#endif /* WGTABSOLUTEBASE_H_ */
