#include "device/CgaChannel.h"
#include "io/PrintStream.h"

CgaChannel cga;		// unser CGA-Ausgabekanal
PrintStream out(cga);	// unseren PrintStream mit Ausgabekanal verknuepfen

int main()

{
	out.println("Hello World");
        
    for(int i = 0; i < 7; i++) {
		out.print(" Dezimal ");
		out.print(i);
        out.println();
		out.print(" Binaer ");
        out.print(i, 2);
        out.println();
		out.print(" Hexadezimal ");
		out.print(i, 16);
		out.println();
    }
    
	out.println("done");
    out.println("done2");
	while(1){}
	
	return 0;
}
