#ifdef UG_USE_PYBIND11

#include "json_plugin.h"

PYBIND11_MODULE(pylimex, m)
{
	m.doc() = "JSON toolkit module";
	m.attr("__name__") = "ug4py.json";

	ug::pybind::Registry registry(m);
	std::string name("JSON");

	ug::JSONToolkit::InitUGPlugin(&registry, name);
}
#endif
