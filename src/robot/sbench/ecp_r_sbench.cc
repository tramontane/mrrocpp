/*!
 * @file
 * @brief File contains ecp robot class definition for SwarmItFix Head
 * @author twiniars <twiniars@ia.pw.edu.pl>, Warsaw University of Technology
 *
 * @ingroup sbench
 */

#include "base/lib/impconst.h"
#include "base/lib/sr/sr_ecp.h"

#include "robot/sbench/ecp_r_sbench.h"
#include "robot/sbench/kinematic_model_sbench.h"

namespace mrrocpp {
namespace ecp {
namespace sbench {

robot::robot(lib::configurator &_config, lib::sr_ecp &_sr_ecp) :
	ecp::common::robot::ecp_robot(lib::sbench::ROBOT_NAME, lib::sbench::NUM_OF_SERVOS, _config, _sr_ecp),
			sbench_head_soldification_data_port(lib::sbench::HEAD_SOLIDIFICATION_DATA_PORT, port_manager),
			sbench_vacuum_activation_data_port(lib::sbench::VACUUM_ACTIVATION_DATA_PORT, port_manager),
			sbench_reply_data_request_port(lib::sbench::REPLY_DATA_REQUEST_PORT, port_manager)
{
	//  Stworzenie listy dostepnych kinematyk.
	create_kinematic_models_for_given_robot();
}

robot::robot(common::task::task_base& _ecp_object) :
	ecp::common::robot::ecp_robot(lib::sbench::ROBOT_NAME, lib::sbench::NUM_OF_SERVOS, _ecp_object),
			sbench_head_soldification_data_port(lib::sbench::HEAD_SOLIDIFICATION_DATA_PORT, port_manager),
			sbench_vacuum_activation_data_port(lib::sbench::VACUUM_ACTIVATION_DATA_PORT, port_manager),
			sbench_reply_data_request_port(lib::sbench::REPLY_DATA_REQUEST_PORT, port_manager)
{
	//  Stworzenie listy dostepnych kinematyk.
	create_kinematic_models_for_given_robot();
}

// Stworzenie modeli kinematyki dla robota IRp-6 na postumencie.
void robot::create_kinematic_models_for_given_robot(void)
{
	// Stworzenie wszystkich modeli kinematyki.
	add_kinematic_model(new kinematics::sbench::model());
	// Ustawienie aktywnego modelu.
	set_kinematic_model(0);
}

void robot::create_command()
{
	//	int new_data_counter;
	bool is_new_data;
	bool is_new_request;

	sr_ecp_msg.message("create_command");

	is_new_data = false;

	if (sbench_head_soldification_data_port.get() == mrrocpp::lib::NewData) {
		ecp_command.set_type = ARM_DEFINITION;

		// generator command interpretation
		// narazie proste przepisanie

		ecp_edp_cbuffer.variant = lib::sbench::CBUFFER_HEAD_SOLIDIFICATION;

		ecp_edp_cbuffer.head_solidification = sbench_head_soldification_data_port.data;

		if (is_new_data) {
			throw common::robot::ECP_error(lib::NON_FATAL_ERROR, INVALID_COMMAND_TO_EDP);
		} else {
			is_new_data = true;
		}
	}

	if (sbench_vacuum_activation_data_port.get() == mrrocpp::lib::NewData) {
		ecp_command.set_type = ARM_DEFINITION;

		// generator command interpretation
		// narazie proste przepisanie

		ecp_edp_cbuffer.variant = lib::sbench::CBUFFER_VACUUM_ACTIVATION;

		ecp_edp_cbuffer.vacuum_activation = sbench_vacuum_activation_data_port.data;

		if (is_new_data) {
			throw common::robot::ECP_error(lib::NON_FATAL_ERROR, INVALID_COMMAND_TO_EDP);
		} else {
			is_new_data = true;
		}

	}

	is_new_request = sbench_reply_data_request_port.is_new_request();

	communicate_with_edp = true;

	if (is_new_data && is_new_request) {
		ecp_command.instruction_type = lib::SET_GET;
	} else if (is_new_data) {
		ecp_command.instruction_type = lib::SET;
	} else if (is_new_request) {
		ecp_command.instruction_type = lib::GET;
	} else {
		communicate_with_edp = false;
	}

	if (is_new_request) {
		ecp_command.get_type = ARM_DEFINITION;
	}

	// message serialization
	if (communicate_with_edp) {
		memcpy(ecp_command.arm.serialized_command, &ecp_edp_cbuffer, sizeof(ecp_edp_cbuffer));
		assert(sizeof(ecp_command.arm.serialized_command) >= sizeof(ecp_edp_cbuffer));
	}
}

void robot::get_reply()
{

	// message deserialization
	memcpy(&edp_ecp_rbuffer, reply_package.arm.serialized_reply, sizeof(edp_ecp_rbuffer));

	// generator reply generation

	if (sbench_reply_data_request_port.is_new_request()) {
		sbench_reply_data_request_port.data = edp_ecp_rbuffer.sbench_reply;

		sbench_reply_data_request_port.set();
	}

}

} // namespace smb
} // namespace ecp
} // namespace mrrocpp

