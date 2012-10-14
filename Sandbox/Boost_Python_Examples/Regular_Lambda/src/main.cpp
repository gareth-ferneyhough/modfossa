#include <iostream>
#include <boost/python.hpp>
#include <boost/shared_ptr.hpp>
#include <vector>
using namespace std;

// Define the simulator, no hooks

class Simulator {
public:
    void runSimIteration(int iter_num, float value){
        cout << "--------------------------------------------------" << endl;
        cout << "Running iteration number: " << iter_num << endl;
        cout << "Using interesting value : " << value << endl;
        // ... do some kind of sim here...
    }
};

// Wrap things

using namespace boost::python;

BOOST_PYTHON_MODULE (libpyembex) {
    class_<Simulator>("Simulator")
              .def("runSimIteration", &Simulator::runSimIteration);
}


