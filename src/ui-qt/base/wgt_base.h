/*!
 * @file
 * @brief File containing the declaration of the wgt_base class.
 *
 * @author mwroble1
 *
 */

#ifndef WGT_BASE_H
#define WGT_BASE_H

#include <QtGui/QWidget>
//#include <QVBoxLayout>
#include <QDockWidget>
#include <QPushButton>
#include <QDoubleSpinBox>
#include <QGridLayout>
#include <QSignalMapper>
#include <iostream>

namespace mrrocpp {
namespace ui {
namespace common {
class Interface;
class UiRobot;
}
}
}
/*!
 *
 * @brief Base class for all windows opened in ui.
 *
 * Some windows use templates created in QtDesigner and dynamically add widgets to them at specified position.
 * wgt_base provides functions which support such mechanism.
 *
 */
class wgt_base : public QWidget
{
Q_OBJECT

public:
	/**
	 * @brief Constructor.
	 * @param _widget_label Window title.
	 * @param _interface A reference to Interface object - main ui class.
	 * @param parent Pointer to object`s parent.
	 */
	wgt_base(QString _widget_label, mrrocpp::ui::common::Interface& _interface, QWidget *parent = 0);
	/**
	 * @brief Constructor.
	 * @param _widget_label Window title.
	 * @param _interface A reference to Interface object - main ui class.
	 * @param robo A pointer to robot.
	 * @param parent Pointer to object`s parent.
	 */
	wgt_base(QString _widget_label, mrrocpp::ui::common::Interface& _interface, mrrocpp::ui::common::UiRobot *robo, QWidget *parent);
	//! Destructor (empty).
	~wgt_base();
	/**
	 * @brief A function which shows window.
	 * @param set_on_top A flag which indicates whether the window should pop on top after opening.
	 */
	virtual void my_open(bool set_on_top=false);
	//! Hides window.
	void my_close();
	//! Window title.
	QString widget_label;
	//! Pointer to docked widget (a window itself).
	QDockWidget* dwgt;
	//! Shows or hides window widgets depending if a robot is synchronized.
	virtual void synchro_depended_init();
	//! Emits init_and_copy_signal which is connected to init_and_copy_slot().
	virtual void init_and_copy();
	/**
	 * @brief Disables or enables widgets in window depending whether robot is synchronized or not.
	 * @param set_disabled A flag which indicates whether to enable or disable widgets.
	 * @return 1 if succeeded.
	 */
	virtual int synchro_depended_widgets_disable(bool set_disabled){return 0;}

protected:
	//! Reference to Interface object.
	mrrocpp::ui::common::Interface& interface;
	//! Pointer to robot for which the window is opened.
	mrrocpp::ui::common::UiRobot *robot;
	//! Vector holding left incremental move buttons.
	QVector<QPushButton *> inc_move_left_buttons;
	//! Vector holding right incremental move buttons.
	QVector<QPushButton *> inc_move_right_buttons;
	//! Vector holding desired position spin boxes.
	QVector<QDoubleSpinBox*> desired_pos_spin_boxes;
	//! A pointer to gridLayout which is taken from moc`ed *.ui file needed to place elements in window dynamically.
	QGridLayout *gridLayout;
	/**
	 * @brief Adds incremental move button to window.
	 * @param button A pointer to button to be placed in the window.
	 * @param row Row in which the button will be placed on grid layout.
	 * @param column Column in which the button will be placed on grid layout.
	 */
	void add_incremental_move_button(QPushButton *button, int row, int column);
	/**
	 * @brief Adds desired position spin box to window.
	 * @param spin_box A pointer to spin_box to be placed in the window.
	 * @param row Row in which the button will be placed on grid layout.
	 * @param column Column in which the button will be placed on grid layout.
	 */
	void add_desired_position_spin_box(QDoubleSpinBox *spin_box, int row, int column);
	/**
	 * @brief Adds incremental move buttons to window.
	 * @param desiredPosColumn Column in which the desired position spin box will be placed in window.
	 * @param incMoveColumn Column in which the left incremental button will be placed in window (right button is automatically placed in next column).
	 * @param spinBoxesCount Count of how many spin boxes and incremental buttons are to be created.
	 */
	virtual void create_buttons_and_spin_boxes(int desiredPosColumn, int incMoveColumn, int spinBoxesCount);
	/**
	 * @brief Adds incremental move buttons to window.
	 * @param desiredPosColumn Column in which the desired position spin box will be placed in window.
	 * @param incMoveColumn Column in which the left incremental button will be placed in window (right button is automatically placed in next column).
	 */
	virtual void create_buttons_and_spin_boxes(int desiredPosColumn, int incMoveColumn);
	/**
	 * @brief Creates desired position spin boxes and adds them to vector.
	 * @param desiredPosColumn Column in which the desired position spin box will be placed in window.
	 * @param spinBoxesCount Count of how many spin boxes and incremental buttons are to be created.
	 */
	void create_spin_boxes(int desiredPosColumn, int spinBoxesCount);
	/**
	 * @brief Copies passed pointer on QGridLayout object.
	 * @param layout A layout needed to add dynamically created widgets to window.
	 */
	virtual void setup_ui(QGridLayout *layout);
	//! Rewrites desired position from spin boxes to robot provided the robot is synchronized; otherwise fills with zeros.
	virtual int get_desired_position();
	/**
	 * @brief Creates spin box and adds it to passed QVector.
	 * @param spin_boxes A reference to QVector object to which spin box will be added.
	 * @return Pointer to created spin box.
	 */
	QDoubleSpinBox* create_spin_box_to_vector(QVector <QDoubleSpinBox*> &spin_boxes);
	/**
	 * @brief Creates button and adds it to passed QVector.
	 * @param buttons A reference to QVector object to which button will be added.
	 * @param label Text which will be placed on the button.
	 * @return Pointer to created button.
	 */
	QPushButton* create_button_to_vector(QVector<QPushButton *> &buttons, QString label);
	/**
	 * @brief Creates button and adds it to grid layout.
	 * @param label Text which will be placed on the button.
	 * @param x A row in which the button will be placed.
	 * @param y A column in which the button will be placed.
	 * @param rowSpan Height of the button.
	 * @param columnSpan Width of the button.
	 * @return Pointer to created button.
	 */
	QPushButton* add_button(QString label, int x, int y, int rowSpan, int columnSpan);

signals:
	//! Signal emitted for initialization caught by init_and_copy_slot().
	void synchro_depended_init_signal();
	//! Signal emitted for initializing and copying data to spin boxes (i.e. current position).
	void init_and_copy_signal();

public slots:
	/**
	 * @brief Slot for managing clicking left incremental move button.
	 * @param button Button index in buttons vector.
	 */
	virtual void inc_move_left_button_clicked(int button){}
	/**
	 * @brief Slot for managing clicking right incremental move button.
	 * @param button Button index in buttons vector.
	 */
	virtual void inc_move_right_button_clicked(int button){}
	//! Slot for initializing and copying data to spin boxes (i.e. current position).
	virtual void init_and_copy_slot(){};

private slots:
	//! Shows or hides window widgets depending if a robot is synchronized.
	void synchro_depended_init_slot();

private:
	/**
	 * @brief Connects button to signal mapper. Needed for learning from which button the signal was emitted.
	 * @param button A pointer to button which will be mapped.
	 * @param i An index mapped to button.
	 * @param signalMapper A pointer to signal mapper which will handle button and index mapping.
	 */
	void connect_to_signal_mapper(QPushButton *button, int i, QSignalMapper *signalMapper);
};

#endif // WGT_PROCESS_CONTROL_H
