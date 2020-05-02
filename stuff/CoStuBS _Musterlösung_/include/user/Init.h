#ifndef Init_h
#define Init_h

/** Die erste richtige Anwendung
 */
#include "system/Console.h"
#include "system/Environment.h"
#include "system/Thread.h"


class Init: public Thread {
 public:
 Init(int slice=1) :
	Thread(slice), console(keyboard, screen)
	{
	}
	
	~Init()
		{
		this->join();

		}
	
	virtual void run();
 private:
	Console console;
};

#endif
