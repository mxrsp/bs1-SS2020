#ifndef Background_h
#define Background_h

#include "system/Thread.h"
#include "user/Environment.h"


// Ein Hintergrundprozess, der einfach mitlaeuft ...

class Background: public Thread {
public:
	Background(void* sp, int show): Thread(sp)
	{   
		this->show = show;
		start();
	}

	~Background()
	{
        console.attach();
		out.println("Background should be killed now!");
        console.detach();
	}

private:
	void run()
	{
        console.attach(); // löschen
		out.println("Background is running!");
        console.detach(); // löschen
        
		for(int i=0;;i++) {
			if (i % show == 0) {
                console.attach();
				out.print("*");
                console.detach();
            }
			yield();
		}

	}

	int show;
};

#endif
