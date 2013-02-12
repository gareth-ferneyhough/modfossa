#ifndef _STATE_H
#define _STATE_H

#include <string>

class State
{
public:
	State();
	~State();

	std::string GetName() const;
	void SetName(std::string name);
	
	int GetIndex() const;
	void SetIndex(int index);
	
	bool GetIsInitialState() const;
	void SetIsInitialState(bool isInitialState);
	
	bool GetIsConducting() const;
	void SetIsConducting(bool isConducting);

private:
	std::string name;
	int index;
	bool isInitialState;
	bool isConducting;
};

#endif