
#include <boost/python.hpp>
#include <boost/make_shared.hpp>

#include <stdexcept>
#include <iostream>
#include <vector>

#include <ModFossa/Experiment/SimulationRunner.h>

using namespace boost::python;
//using namespace ModFossa;
using boost::shared_ptr;
using boost::make_shared;

using ModFossa::SimulationRunner;
using ModFossa::Experiment;
using ModFossa::MarkovModel;
using ModFossa::State;

class Factory {
public:
    Factory() {}
    
//    State::SharedPointer createState(std::string name, bool conducting) {
//        return State::SharedPointer(new State("test1", false));
//    }
    
    void money() {
        throw std::runtime_error("wtf");
    }
    
    State::SharedPointer createState(const State& state) {
        return make_shared<State>(state);
    }
};

BOOST_PYTHON_MODULE(ModFossa) {
    
    class_<Factory>("factory")
            .def("createState", &Factory::createState)
            .def("money", &Factory::money)
            ;

    class_<State, shared_ptr<State> >("state", init < std::string, bool>())
            .def("name", &State::getName)
            .def("conducting", &State::getIsConducting)
            ;

    class_<MarkovModel, shared_ptr<MarkovModel> >("markovModel")
            .def("addState", &MarkovModel::addState)
            ;

    class_<Experiment, shared_ptr<Experiment> >("experiment")
            .def("markovModel", &Experiment::getMarkovModel)
            ;

    class_<SimulationRunner>("simulationRunner")
            .def("version", &SimulationRunner::getVersion)
            .def("experiment", &SimulationRunner::getExperiment)
            ;
    //
    //    class_<World, shared_ptr<World> >("World", init<std::string>())
    //            .def("greet", &World::greet)
    //            .def("set", &World::set)
    //            ;
}
