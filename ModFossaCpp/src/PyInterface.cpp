
#include <boost/python.hpp>
#include <boost/make_shared.hpp>

#include <stdexcept>
#include <iostream>
#include <vector>

#include <ModFossa/Experiment/SimulationRunner.h>

using namespace boost::python;

using boost::shared_ptr;
using boost::make_shared;

using ModFossa::SimulationRunner;
using ModFossa::Experiment;
using ModFossa::MarkovModel;
using ModFossa::State;
using ModFossa::Connection;
using ModFossa::LigandGatedRateConstant;
using ModFossa::ConstantRateConstant;
using ModFossa::RateConstantBase;
using ModFossa::SigmoidalRateConstant;

BOOST_PYTHON_MODULE(ModFossa) {
    
    class_<RateConstantBase, boost::noncopyable,  
            shared_ptr<RateConstantBase> >("rateConstantBase", no_init)
       ;
    
    class_<ConstantRateConstant, bases<RateConstantBase>,
            shared_ptr<ConstantRateConstant> >("constantRateConstant", 
                init < std::string, double>())    
            ;
        
    class_<LigandGatedRateConstant, bases<RateConstantBase>, 
            shared_ptr<LigandGatedRateConstant> >("ligandGatedRateConstant", 
                init < std::string, double, std::string, double>())    
            ;
    
    class_<SigmoidalRateConstant, 
            shared_ptr<SigmoidalRateConstant> >("sigmoidalRateConstant", 
                init < std::string, double, double, double>())    
            ;
    
    class_<Connection, shared_ptr<Connection> >("connection", 
                init < std::string, std::string, std::string>())    
            ;

    class_<State, shared_ptr<State> >("state", init < std::string, bool>())
            .def("name", &State::getName)
            .def("conducting", &State::getIsConducting)
            ;

    class_<MarkovModel, shared_ptr<MarkovModel> >("markovModel")
            .def("addState", &MarkovModel::addState)
            .def("addConnection", &MarkovModel::addConnection)
            .def("addRateConstant", &MarkovModel::addRateConstant)
            ;

    class_<Experiment, shared_ptr<Experiment> >("experiment")
            .def("markovModel", &Experiment::getMarkovModel)
            ;

    class_<SimulationRunner>("simulationRunner")
            .def("version", &SimulationRunner::getVersion)
            .def("experiment", &SimulationRunner::getExperiment)
            ;
    
}
