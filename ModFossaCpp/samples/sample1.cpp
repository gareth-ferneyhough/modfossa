#include "../src/Experiment.h"

int main()
{
  ModFossa::Experiment experiment;
  ModFossa::ModelDefinition* mm = experiment.GetMarkovModel();
  ModFossa::ModelDescription* modelDesc = mm.GetModelDescription();

  mm->AddState("s1", true);
  mm->AddState("s2", false);
  mm->AddState("s3", false, initial=true);

  mm->AddConstantRateConstant("rate1", 3.4);
  mm->AddLigandDependentRateConstant("rate2", 1.2, 1.0, "Ca");
  mm->AddConstantRateConstant("rate3", 1.2);

  modelDesc->AddConnection("s1", "s2", "rate1");
  modelDesc->AddConnection("s2", "s3", "rate2");
  modelDesc->AddConnection("s1", "s3", "rate3");


  experiment.AddVoltageProtocol("vp1");
  experiment.AddVoltageProtocolStage("vp1", "start", -50, 200);
  // etc...


  experiment.AddIonicConcentration("Ca");


  // experiment.Sweep() will first validate the ModelDefinition
  // by calling BuildConnections(), which creates the 3d 
  // transition matrix. If an error is discovered in the string 
  // logic from the user defining connections, ligands, etc, an
  // exception will be thrown. If no errors are detected, the 
  // simulation runner is initialized and run, and the method
  // returns when complete.  

  experiment.Sweep(); // need parameters...

  ModFossa::Results* results = experiment.GetResults();
  results->GetIv();
  results->GetTail();
  
  return 0;
}
