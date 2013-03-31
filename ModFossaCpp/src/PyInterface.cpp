
#include <boost/python.hpp>
#include <boost/make_shared.hpp>
#include <boost/python/suite/indexing/indexing_suite.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include <boost/python/suite/indexing/map_indexing_suite.hpp>

#include <stdexcept>
#include <iostream>
#include <vector>
#include <map>

#include <ModFossa/Experiment/SimulationRunner.h>
//#include "std_pair_conversion.h"

using namespace boost::python;

using boost::shared_ptr;
using boost::make_shared;

using ModFossa::Validation::ErrorType;
using ModFossa::Validation::ErrorLevel;
using ModFossa::Validation::ValidationResults;

using ModFossa::SimulationRunner;
using ModFossa::Experiment;
using ModFossa::MarkovModel;
using ModFossa::State;
using ModFossa::Connection;
using ModFossa::LigandGatedRateConstant;
using ModFossa::ConstantRateConstant;
using ModFossa::RateConstantBase;
using ModFossa::ExponentialRateConstant;
using ModFossa::SigmoidalRateConstant;
using ModFossa::VoltageProtocol;
using ModFossa::ExperimentSweep;
using ModFossa::Concentration;
using ModFossa::Results;
using ModFossa::Vector;
using ModFossa::Vector2d;
using ModFossa::Vector3d;
using ModFossa::VectorSharedPtr;
using ModFossa::Vector2dSharedPtr;
using ModFossa::Vector3dSharedPtr;

template<class T1, class T2>
struct PairToTupleConverter {

    static PyObject * convert(const std::pair<T1, T2>& pair) {
        return incref(make_tuple(pair.first, pair.second).ptr());
    }
};

template<class T>
struct VecToList {

    static PyObject * convert(const std::vector<T>& vec) {
        boost::python::list* l = new boost::python::list();
        for (size_t i = 0; i < vec.size(); i++)
            (*l).append(vec[i]);

        return l->ptr();
    }
};

class Test {
public:
    std::map<std::string, double> map;

    Test() {
    }

    void setMap(std::map<std::string, double> map) {
        this->map = map;
    }

    std::map<std::string, double> getMap() {
        return map;
    }

};

BOOST_PYTHON_MODULE(ModFossa) {

    typedef std::pair<int, int> IntPair;
    to_python_converter<IntPair, PairToTupleConverter<int, int> >();
    //to_python_converter<std::vector< IntPair, class std::allocator<IntPair > >, VecToList<IntPair > >();
    //def("getListValue", getListValue);

    //    class_ <IntPair> ("intpair")
    //          ;

    class_<Test>("Test")
            .def("setMap", &Test::setMap)
            .def("getMap", &Test::getMap)
            ;


    class_<std::map<std::string, double> >("MyMap")
            .def(map_indexing_suite<std::map<std::wstring, double> >());

    class_< std::vector< IntPair >, shared_ptr<std::vector< IntPair > > > ("vectorOfPairs")
            .def(vector_indexing_suite< std::vector< IntPair > >())
            ;

    class_<VoltageProtocol,
            shared_ptr<VoltageProtocol> >("voltageProtocol",
            init < std::string>())
            .def("addConstantStage", &VoltageProtocol::addConstantStage)
            .def("addSteppedStage", &VoltageProtocol::addSteppedStage)
            ;

    class_<ExperimentSweep,
            shared_ptr<ExperimentSweep> >("experimentSweep",
            init < std::string, std::string>())
            .def("addConcentration", &ExperimentSweep::addConcentration)
            ;


    class_<RateConstantBase, boost::noncopyable,
            shared_ptr<RateConstantBase> >("rateConstantBase", no_init)
            ;

    class_<ConstantRateConstant, bases<RateConstantBase>,
            shared_ptr<ConstantRateConstant> >("constantRateConstant",
            init < std::string, double>())
            ;

    class_<ExponentialRateConstant, bases<RateConstantBase>,
            shared_ptr<ExponentialRateConstant> >("exponentialRateConstant",
            init < std::string, double, double>())
            ;

    class_<LigandGatedRateConstant, bases<RateConstantBase>,
            shared_ptr<LigandGatedRateConstant> >("ligandGatedRateConstant",
            init < std::string, double, std::string, double>())
            ;

    class_<SigmoidalRateConstant, bases<RateConstantBase>,
            shared_ptr<SigmoidalRateConstant> >("sigmoidalRateConstant",
            init < std::string, double, double, double>())
            ;

    class_<Connection, shared_ptr<Connection> >("connection",
            init < std::string, std::string, std::string>())
            ;

    class_<Concentration, shared_ptr<Concentration> >("concentration",
            init < std::string, double>())
            ;

    class_<State, shared_ptr<State> >(
        "state", init <std::string, bool, double>())
            .def("name", &State::getName)
            .def("conducting", &State::getIsConducting)
            ;

    class_<MarkovModel, shared_ptr<MarkovModel> >("markovModel")
            .def("addState", &MarkovModel::addState)
            .def("addConnection", &MarkovModel::addConnection)
            .def("addRateConstant", &MarkovModel::addRateConstant)
            .def("setInitialState", &MarkovModel::setInitialState)
            .def("setMaxChannelConductance", 
                &MarkovModel::setMaxChannelConductance)
            .def("setReversalPotential", 
                &MarkovModel::setReversalPotential)
            .def("setMembraneCapacitance", &MarkovModel::setMembraneCapacitance)
            .def("setInitialState", &MarkovModel::setInitialState)    
            .def("isValid", &MarkovModel::isValid)
            .def("validate", &MarkovModel::validate)
            ;

    class_<Experiment, shared_ptr<Experiment> >("experiment")
            .def("markovModel", &Experiment::getMarkovModel)
            .def("validate", &Experiment::validate3) // fix this
            .def("addVoltageProtocol", &Experiment::addVoltageProtocol)
            .def("getVoltageProtocol", &Experiment::getVoltageProtocol)
            .def("addExperimentSweep", &Experiment::addExperimentSweep)
            .def("getExperimentSweep", &Experiment::getExperimentSweep)
            ;
    
    class_<Results, shared_ptr<Results> >("results")
            .def("getStateNames", &Results::getStateNames)
            .def("getCurrents", &Results::getCurrents)
            .def("getIV", &Results::getIV)
            .def("getStateProbabilities", &Results::getStateProbabilities)
            .def("getVoltageProtocol", &Results::getVoltageProtocol)
            ;

    enum_<ErrorLevel>("errorLevel")
            .value("no_warnings", ErrorLevel::NO_WARNINGS)
            .value("warnings", ErrorLevel::WARNINGS)
            .value("errors", ErrorLevel::ERRORS)
            ;

    enum_<ErrorType>("errorType")
            .value("no connections defined",
            ErrorType::NO_CONNECTIONS)
            .value("maximum channel conductance not defined",
            ErrorType::MAX_CONDUCTANCE_NOT_DEFINED)    
            .value("rate constant not defined",
            ErrorType::MEMBRANE_CAPACITANCE_NOT_DEFINED)    
            .value("membrane capacitance not defined",
            ErrorType::RATE_CONSTANT_NOT_DEFINED)
            .value("state not defined",
            ErrorType::STATE_NOT_DEFINED)
            .value("ligand not defined",
            ErrorType::LIGAND_NOT_DEFINED)
            .value("initial state not defined",
            ErrorType::INITIAL_STATE_NOT_DEFINED)
            .value("state of the world is null",
            ErrorType::STATE_OF_THE_WORLD_IS_NULL)
            .value("no voltage protocols defined",
            ErrorType::NO_VOLTAGE_PROTOCOLS)
            .value("no experiment sweeps defined",
            ErrorType::NO_EXPERIMENT_SWEEPS)
            .value("voltage protocol not defined",
            ErrorType::VOLTAGE_PROTOCOL_NOT_DEFINED)
            ;

    class_<ValidationResults, shared_ptr<ValidationResults> >(
            "validationResults",
            init < ErrorLevel, ValidationResults::ErrorVector>())
            .def_readonly("errorLevel", &ValidationResults::overall_result)
            .def_readonly("errors", &ValidationResults::errors)
            ;

    class_<SimulationRunner>("simulationRunner")
            .def("experiment", &SimulationRunner::getExperiment)
            .def("results", &SimulationRunner::getResultsClass)
            .def("runAllExperimentSweeps",
                &SimulationRunner::runAllExperimentSweeps)
            ;

    class_<Vector3d>("Vector3d")
            .def(vector_indexing_suite<Vector3d>())
            ;

    class_<Vector2d>("Vector2d")
            .def(vector_indexing_suite<Vector2d>())
            ;

    class_<Vector>("Vector")
            .def(vector_indexing_suite<Vector>())
            ;
        
    class_<std::vector<std::string> >("stringVector")
            .def(vector_indexing_suite<std::vector<std::string> >())
            ;
}
