#include "system/Console.h"
#include "device/Keyboard.h"

void Console :: attach(){
	//semaphore sperren
	sem.wait();
}
void Console :: detach(){
	//semaphore freigeben
	sem.signal();
}
int Console :: read(char *data, int size){
	char readed = 0;
	int pos = 0;
	while((size > pos)){
		   if ((readed == '\n')) {
		            break;
		    }
		readed = this->read();
		output.write(readed);
		data[pos] = readed;
		pos++;
	}
	return pos;
}
char Console ::read(){
	char readed;
	char* saveplace = &readed;
	input.read(saveplace, 1);
	return readed;

}
int Console ::write(const char *data, int size){
	return output.write(data, size);
}
