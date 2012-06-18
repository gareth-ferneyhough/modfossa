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

#include "SundialsCpp.h"
#include "uncopyable.h"

namespace ModFossa {
typedef std::string state_name;

struct Transition {
	state_name source;
	double rate;
};

struct State {
	state_name name;
	std::vector<Transition> in_transitions;
	std::vector<Transition> out_transitions;
	bool is_initial;
	bool is_conducting;
	double current_probability;
};

class Model {
public:
	static Model* getInstance();
	void addState(state_name);
	void connect(state_name from, state_name to, double rate);
	void setInitialState(state_name);
	void setTspan(std::vector<double> times);
	boost::numeric::ublas::matrix<double> run();

	int numStates() const;
	void setState(const N_Vector& state);
	double inProb(int index);
	double outProb(int index);

	State* getStateByName(state_name name);

private:
	DISALLOW_COPY_AND_ASSIGN(Model);
	Model();
	~Model();

	std::vector<State> states;
	std::vector<double> times;
};

static int channelProb(realtype t, N_Vector y_vec, N_Vector ydot,
		void *f_data) {
	/* y(0) = PC1
	 * y(1) = PC2
	 * y(2) = PO
	 */

	//int kon1 = 1;
	//int koff1 = 100;
	//int kon2 = 1;
	//int koff2 = 100;

	//double pC1 = NV_Ith_S(y_vec, 0);
	//double pC2 = NV_Ith_S(y_vec, 1);
	//double pO  = NV_Ith_S(y_vec, 2);

	// p_dot[i] = model.inProb[i] - model.outProb[i];
	//double pC1_dot = -kon1 * pC1 + koff1 * pC2;
	//double pC2_dot = -koff1 * pC2 + kon1 * pC1 -kon2 * pC2 + koff2 * pO;
	//double pO_dot = -koff2 * pO + kon2 * pC2;

	Model* model = Model::getInstance();
	model->setState(y_vec);

	for(int i = 0; i < model->numStates(); ++i){
		double p_dot_i = model->inProb(i) - model->outProb(i);
		NV_Ith_S(ydot, i) = p_dot_i;
	}

	//NV_Ith_S(ydot, 0) = pC1_dot;
	//NV_Ith_S(ydot, 1) = pC2_dot;
	//NV_Ith_S(ydot, 2) = pO_dot;



	return 0;
}

} /* namespace ModFossa */
#endif /* MODEL_H_ */
