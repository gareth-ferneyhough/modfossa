/*
 * Model.h
 *
 *  Created on: Jun 13, 2012
 *      Author: gareth
 */

#ifndef MODEL_H_
#define MODEL_H_

#include <vector>
#include <iostream>

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/noncopyable.hpp>

#include "SundialsCpp.h"

namespace ModFossa {
typedef std::string StateName;

struct Transition {
	StateName source;
	double rate;
};

struct State {
	StateName name;
	std::vector<Transition> in_transitions;
	std::vector<Transition> out_transitions;
	bool is_initial;
	bool is_conducting;
	double current_probability;
};

class Model : private boost::noncopyable{
public:
	static Model* getInstance();
	void addState(StateName);
	void connect(StateName from, StateName to, double rate);
	void setInitialState(StateName);
	void setIntegrationWindow(std::vector<double> times);
	boost::numeric::ublas::matrix<double> run();

	int numStates() const;
	void setState(const N_Vector& state);
	double inProb(int index);
	double outProb(int index);

	State* getStateByName(StateName name);

private:
	Model();
	~Model();

	std::vector<State> states;
	std::vector<double> times;
};

// Static function used by Sundials
static int channelProb(realtype t, N_Vector y_vec, N_Vector ydot,
		void *f_data) {

	Model* model = Model::getInstance();
	model->setState(y_vec);

	for(int i = 0; i < model->numStates(); ++i){
		double p_dot_i = model->inProb(i) - model->outProb(i);
		NV_Ith_S(ydot, i) = p_dot_i;
	}

	return 0;
}

} /* namespace ModFossa */
#endif /* MODEL_H_ */
