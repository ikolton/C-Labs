module VectorModuleInstantiate;

import VectorModule;

template class emcpp::Vector<int, 5, emcpp::SafePolicy>;
template class emcpp::Vector<double, 4, emcpp::SafePolicy>;
template class emcpp::Vector<std::string, 3, emcpp::SafePolicy>;
