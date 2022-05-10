#ifndef SCRIPT_H
#define SCRIPT_H


struct Script {
protected:


public:
	virtual ~Script() {}

	virtual const std::string getName() = 0;

	virtual void Update() = 0;

};


#endif // !SCRIPT_H

