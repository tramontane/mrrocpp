/// \file ecp_t_eih_acquisition.h
/// \brief definicja zadania akwizycji danych potrzebnych do kalibracji ukladu oko - reka
/// \author 2009 Jakub Kosiorek
///////////////////////////////////////////////////////////////////////////////

#if !defined(_ECP_T_EIH_ACQUISITION_H)
#define _ECP_T_EIH_ACQUISITION_H

#include "lib/typedefs.h"
#include "lib/impconst.h"
#include "lib/com_buf.h"
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <unistd.h>

#include "ecp/irp6_on_track/ecp_r_irp6ot.h"
#include "ecp/irp6_postument/ecp_r_irp6p.h"
#include "ecp/common/ecp_task.h"
#include "ecp/common/ecp_g_smooth2.h"
#include "ecp/common/ecp_generator_t.h"
#include "ecp_mp/ecp_mp_s_cvfradia.h"
#include "ecp/common/ecp_g_force.h"
#include "ecp/common/ecp_g_eihcalibration.h"

#define POSTUMENT 0
#define TRACK 1

namespace mrrocpp {
namespace ecp {
namespace common {
namespace task {

/*
class eihacquisition: public common::task::acquisition {
	std::string smooth_path;
	int delay_ms, robot, M;
	double A, C, D, E;

	protected:
		// generator do wodzenia za nos
		generator::eih_nose_run* nose;
		// generator smooth2
		generator::smooth2* smooth2gen;
		// generator do wysylania danych do fradii
		generator::eihgenerator* generator;

	public:
		eihacquisition(lib::configurator &_config);

		void main_task_algorithm(void);
};
*/
}
} // namespace common
} // namespace ecp
} // namespace mrrocpp

#endif