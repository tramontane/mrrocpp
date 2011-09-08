/*!
 * @file
 * @brief File containing the definitions of the WgtAbsoluteBase class.
 *
 * @author mwroble1
 *
 * @ingroup Ui
 */
#include "WgtAbsoluteBase.h"
#include "ui_robot.h"
#include "interface.h"
#include "mainwindow.h"

WgtAbsoluteBase::WgtAbsoluteBase(QString _widget_label, mrrocpp::ui::common::Interface& _interface, mrrocpp::ui::common::UiRobot *robo, QWidget *parent):
	wgt_base(_widget_label, _interface, robo, parent)
{

}

WgtAbsoluteBase::~WgtAbsoluteBase()
{
	// TODO Auto-generated destructor stub
}

void WgtAbsoluteBase::setup_ui(QGridLayout *layout)
{
	wgt_base::setup_ui(layout);
	wgt_base::create_buttons_and_spin_boxes(desired_pos_column, inc_move_column);

	create_buttons_and_spin_boxes();
	create_buttons();
	create_step_spinbox();
}

void WgtAbsoluteBase::create_step_spinbox()
{
    step_spinbox = new QDoubleSpinBox(this);
    step_spinbox->setDecimals(3);
    step_spinbox->setMaximum(10);
    step_spinbox->setSingleStep(0.01);

    gridLayout->addWidget(step_spinbox, 8, 10, 1, 2);
}

void WgtAbsoluteBase::create_buttons_and_spin_boxes()
{
	for(int i=0; i < robot->number_of_servos; i++)
		add_current_position_spin_box(create_spin_box_to_vector(current_pos_spin_boxes), i);
}

void WgtAbsoluteBase::add_current_position_spin_box(QDoubleSpinBox *spin_box, int row)
{
	gridLayout->addWidget(spin_box, row+1, 1, 1, 1);
}

void WgtAbsoluteBase::create_buttons()
{
    read_button =  add_button("Read", 8, 1, 1, 1);
    execute_button = add_button("Move", 8, 6, 1, 3);
    import_button = add_button("Import",  9, 6, 1, 1);
    export_button = add_button("Export", 9, 7, 1, 1);
    copy_button = add_button(">", 1, 3, robot->number_of_servos, 1);

	connect(read_button, 	SIGNAL(clicked()), this, SLOT(read_button_clicked()), 	Qt::QueuedConnection);
	connect(execute_button, SIGNAL(clicked()), this, SLOT(execute_button_clicked()),Qt::QueuedConnection);
	connect(import_button, 	SIGNAL(clicked()), this, SLOT(import_button_clicked()), Qt::QueuedConnection);
	connect(export_button, 	SIGNAL(clicked()), this, SLOT(export_button_clicked()), Qt::QueuedConnection);
	connect(copy_button, 	SIGNAL(clicked()), this, SLOT(copy_button_clicked()), 	Qt::QueuedConnection);
}

int WgtAbsoluteBase::synchro_depended_widgets_disable(bool set_disabled)
{
	execute_button->setDisabled(set_disabled);
	copy_button->setDisabled(set_disabled);
	export_button->setDisabled(set_disabled);
	import_button->setDisabled(set_disabled);
	read_button->setDisabled(set_disabled);

	for (int i = 0; i < robot->number_of_servos; i++)
	{
		current_pos_spin_boxes[i]->setDisabled(set_disabled);
		desired_pos_spin_boxes[i]->setDisabled(set_disabled);
	}

	return 1;
}

void WgtAbsoluteBase::inc_move_left_button_clicked(int button)
{
	get_desired_position();
	robot->desired_pos[button] -= step_spinbox->value();
	move_it();
}

void WgtAbsoluteBase::inc_move_right_button_clicked(int button)
{
	get_desired_position();
	robot->desired_pos[button] += step_spinbox->value();
	move_it();
}

void WgtAbsoluteBase::read_button_clicked()
{
	printf("read\n");
	init();
}

void WgtAbsoluteBase::import_button_clicked()
{
	double val[robot->number_of_servos];

	for (int i = 0; i < robot->number_of_servos; i++)
		val[i] = 0.0;

	interface.get_main_window()->get_lineEdit_position(val, robot->number_of_servos);

	for (int i = 0; i < robot->number_of_servos; i++)
		desired_pos_spin_boxes[i]->setValue(val[i]);
}

void WgtAbsoluteBase::export_button_clicked()
{
	std::stringstream buffer(std::stringstream::in | std::stringstream::out);

	buffer << widget_label.toStdString() << " INCREMENTAL POSITION\n ";
	for (int i = 0; i < robot->number_of_servos; i++)
		buffer << " " << desired_pos_spin_boxes[i]->value();

	interface.ui_msg->message(buffer.str());
}

void WgtAbsoluteBase::init_and_copy_slot()
{
	init();
	copy();
}

void WgtAbsoluteBase::copy_button_clicked()
{
	copy();
}

int WgtAbsoluteBase::copy()
{

	if (robot->state.edp.pid != -1)
	{
		if (robot->state.edp.is_synchronised) // Czy robot jest zsynchronizowany?
		{
			execute_button->setDisabled(false);
			for (int i = 0; i < robot->number_of_servos; i++)
			{
				desired_pos_spin_boxes[i]->setValue(current_pos_spin_boxes[i]->value());
			}
		}
		else
			execute_button->setDisabled(true);			// Wygaszanie elementow przy niezsynchronizowanym robocie
	}

	return 1;
}


void WgtAbsoluteBase::execute_button_clicked()
{
	get_desired_position();
	move_it();
}


