/* 
 * File:   ThreeState.cpp
 * Author: gareth
 *
 * Created on March 13, 2013, 11:35 PM
 */

#include <ModFossa/ModelDefinition/MarkovModel.h>
#include <ModFossa/ModelDefinition/TransitionMatrix.h>
#include <ModFossa/ModelDefinition/ConstantRateConstant.h>
#include <cassert>

using namespace ModFossa;
using std::string;
using std::cout;
using std::endl;

/*
 * 
 */
int main(int argc, char** argv) {

    MarkovModel* markov_model = new MarkovModel();

    markov_model->addState(State::SharedPointer(new State("s1", false)));
    markov_model->addState(State::SharedPointer(new State("s2", false)));
    markov_model->addState(State::SharedPointer(new State("s3", true)));

    RateConstantBase::SharedPointer rate1(
            new ConstantRateConstant("rate1", 1.0));

    RateConstantBase::SharedPointer rate2(
            new ConstantRateConstant("rate2", 2.0));

    RateConstantBase::SharedPointer rate3(
            new ConstantRateConstant("rate3", 3.0));

    RateConstantBase::SharedPointer rate4(
            new ConstantRateConstant("rate4", 4.0));

    markov_model->addRateConstant(rate1);
    markov_model->addRateConstant(rate2);
    markov_model->addRateConstant(rate3);
    markov_model->addRateConstant(rate4);

    markov_model->addConnection(Connection::SharedPointer(
            new Connection("s1", "s2", "rate1")));

    markov_model->addConnection(Connection::SharedPointer(
            new Connection("s2", "s1", "rate2")));

    markov_model->addConnection(Connection::SharedPointer(
            new Connection("s2", "s3", "rate3")));

    markov_model->addConnection(Connection::SharedPointer(
            new Connection("s3", "s2", "rate4")));

    markov_model->setInitialState("s1");


    StateOfTheWorld::ConcentrationMap map;
    StateOfTheWorld::SharedPointer state_of_the_world(new StateOfTheWorld(map));

    Validation::ValidationResults results =
            markov_model->validate(state_of_the_world);

    assert(results.overall_result == Validation::NO_WARNINGS);

    TransitionMatrix* transition_matrix = new TransitionMatrix(*markov_model);
    transition_matrix->update(state_of_the_world);
    
    cout << transition_matrix->get() << endl;
    
    return 0;
}

