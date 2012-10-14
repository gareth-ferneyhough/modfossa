#include <iostream>
#include <boost/python.hpp>
#include <boost/shared_ptr.hpp>
#include <vector>
using namespace std;

// Define Hook objects

class ActionHook{
public:
    virtual void runHook()
    {
    }
};

// Definte python wrapper

typedef boost::shared_ptr<ActionHook> ActionHookPtr;

class ActionHookWrapper : public ActionHook, public boost::python::wrapper<ActionHook>
{
    virtual void runHook()
    {
        cout << "Debug: Starting an action hook via wrapper" << endl;
        this->boost::python::wrapper<ActionHook>::get_override("runHook")();
        cout << "Debug: Done with wrapped action hook" << endl;
    }

};

// Create an example Hook class in C++

class HelloHook : public ActionHook {
    virtual void runHook(){
        cout << "I am a C++ hook" << endl;
    }

};

// Define the simulator, which may call hooks

class Simulator {
public:
    Simulator()
    {
        number_of_iterations = 100;
    }

    void addHook(ActionHookPtr newHook){
        hook_list.push_back(newHook);
    }

    void setNumberOfIterations(int num){
        number_of_iterations = num;
    }

    void runSim(){
        for(int iter_num = 0; iter_num < number_of_iterations; ++iter_num) {
            cout << "Running iteration number: " << iter_num << endl;
            // ... do some kind of sim here...
            
            runHooks();
        }
    }

    void runHooks() {
        for(int hookIdx = 0; hookIdx < hook_list.size(); hookIdx++)
        {
            hook_list[hookIdx]->runHook();
        }
    }
private:
    vector<ActionHookPtr> hook_list;
    int number_of_iterations;
};

// Wrap things

using namespace boost::python;

int main(int argc, char **argv)
{
    Py_Initialize();
    object main_module((
                handle<>(borrowed(PyImport_AddModule("__main__")))));
    object main_namespace = main_module.attr("__dict__");
    main_namespace["Simulator"] = class_<Simulator>("Simulator")
              .def("setNumberOfIterations",&Simulator::setNumberOfIterations)
              .def("addHook",&Simulator::addHook, return_value_policy<manage_new_object>());

    main_namespace["ActionHook"] = class_<ActionHookWrapper, boost::noncopyable>("ActionHook").def("runHook", pure_virtual(&ActionHook::runHook));

    Simulator main_sim;
    main_sim.addHook(boost::shared_ptr<ActionHook>(new HelloHook));
    main_namespace["simulator"] = ptr(&main_sim);

    FILE *script_file = NULL;

    if(argc >= 2){
        script_file = fopen(argv[1],"r");
    }else{
        printf("No file given\n");
        return 1;
    }
    if(!script_file){
        printf("Could not open this file\n");
        return 2;
    }

    // Load config
    PyRun_File(
            script_file
            ,argv[1]
            ,Py_file_input
            ,main_namespace.ptr()
            ,main_namespace.ptr()
            );

    main_sim.runSim();
    
    // Attempt to pull a top level variable called x from the
    // python scope, and use it's value in C++
    try {
        int x = extract<int>(main_namespace["x"]);
        cout << "x is " << x << endl;
        cout << "twice x is " << x * 2 << endl;
    } catch (boost::python::error_already_set) {
        cout << "x is not set" << endl;
    }

    cout << "Finalizing" << endl;

    Py_Finalize();

    cout << "Done" << endl;
}

