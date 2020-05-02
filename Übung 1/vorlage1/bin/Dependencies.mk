
finit.o: ../src/lib/finit.cc
CgaChar.o: ../src/device/CgaChar.cc ../include/device/CgaChar.h \
 ../include/device/CgaAttr.h
CgaScreen.o: ../src/device/CgaScreen.cc ../include/device/CgaScreen.h \
 ../include/device/CgaAttr.h ../include/device/CgaChar.h \
 ../include/io/IOPort.h
PrintStream.o: ../src/io/PrintStream.cc ../include/io/PrintStream.h \
 ../include/io/OutputChannel.h
CgaChannel.o: ../src/device/CgaChannel.cc ../include/io/OutputChannel.h \
 ../include/device/CgaScreen.h ../include/device/CgaAttr.h \
 ../include/device/CgaChar.h ../include/io/IOPort.h \
 ../include/device/CgaChannel.h
main.o: ../src/main.cc ../include/io/PrintStream.h \
 ../include/io/OutputChannel.h ../include/device/CgaChannel.h \
 ../include/device/CgaScreen.h ../include/device/CgaAttr.h \
 ../include/device/CgaChar.h ../include/io/IOPort.h
