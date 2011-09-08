/*!
 * @file
 * @brief File containing the declaration of the MenuBarAction class.
 *
 * @author mwroble1
 *
 * @ingroup Ui
 */

#ifndef MENUBARACTION_H_
#define MENUBARACTION_H_

#include <QAction>
#include "ui_robot.h"
#include "wgt_base.h"


namespace Ui
{
class SignalDispatcher;
/*!
 *
 * @brief Class which defines actions in menu.
 *
 * The reason of subclassing the QAction class is that there`s need for reemiting triggered() signal
 * so that it can pass information on which robot the action was called.
 *
 * @ingroup Ui
 */
class MenuBarAction : public QAction
{
Q_OBJECT

public:
/**
 * @brief Constructor.
 * @param text It will be displayed in menu bar.
 * @param robo A pointer holding the robot object on which the command was called.
 * @param parent Pointer to object`s parent.
 */
	MenuBarAction(QString text, mrrocpp::ui::common::UiRobot* robo, QWidget *parent);
/**
 * @brief Constructor.
 * @param text It will be displayed in menu bar.
 * @param _wgt A pointer holding information telling which window will be opened after triggering the action.
 * @param signalDispatcher A pointer to SignalDispatcher class - for connecting appropriate signals.
 * @param parent Pointer to object`s parent.
 */
	MenuBarAction(QString text, wgt_base* _wgt, SignalDispatcher *signalDispatcher, QWidget *parent);

signals:
/**
 * @brief Signal which will be emitted if action was pressed.
 * @param robot A pointer to robot on which the action was called.
 */
	void triggered(mrrocpp::ui::common::UiRobot* robot);
/**
 * @brief Signal which will be emitted if action was pressed.
 * @param wgt A pointer to window opening command on which the action was called.
 */
	void triggered(wgt_base* wgt);

private slots:
//! Emits signal with pointer on robot or window.
	void reemitTriggered();

private:
	/**
	 * @brief Anonymous union for storing either robot pointer or window pointer.
	 */
	union
	{
		mrrocpp::ui::common::UiRobot* robot;
		wgt_base* wgt;
	};
	//! A flag for indicating which pointer is kept.
	bool robot_action;

};
}
#endif
