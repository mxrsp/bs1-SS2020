
finit.o: ../src/lib/finit.cc
CgaChar.o: ../src/device/CgaChar.cc ../include/device/CgaChar.h \
 ../include/device/CgaAttr.h
CgaChannel.o: ../src/device/CgaChannel.cc ../include/io/OutputChannel.h \
 ../include/device/CgaScreen.h ../include/device/CgaAttr.h \
 ../include/device/CgaChar.h ../include/io/IOPort.h \
 ../include/device/CgaChannel.h
CgaScreen.o: ../src/device/CgaScreen.cc ../include/device/CgaScreen.h \
 ../include/device/CgaAttr.h ../include/device/CgaChar.h \
 ../include/io/IOPort.h
PrintStream.o: ../src/io/PrintStream.cc ../include/io/PrintStream.h \
 ../include/io/OutputChannel.h
Queue.o: ../src/lib/Queue.cc ../include/lib/Queue.h \
 ../include/lib/Chain.h
Scheduler.o: ../src/thread/Scheduler.cc ../include/lib/Queue.h \
 ../include/lib/Chain.h ../include/thread/Schedulable.h \
 ../include/thread/Scheduler.h
ActivityScheduler.o: ../src/thread/ActivityScheduler.cc \
 ../include/lib/Queue.h ../include/lib/Chain.h \
 ../include/thread/Activity.h ../include/thread/Schedulable.h \
 ../include/thread/Coroutine.h ../include/thread/Dispatcher.h \
 ../include/thread/Scheduler.h ../include/thread/ActivityScheduler.h
Coroutine.o: ../src/thread/Coroutine.cc ../include/thread/Coroutine.h
Activity.o: ../src/thread/Activity.cc ../include/thread/Activity.h \
 ../include/thread/Schedulable.h ../include/lib/Chain.h \
 ../include/thread/Coroutine.h ../include/thread/ActivityScheduler.h \
 ../include/thread/Scheduler.h ../include/lib/Queue.h \
 ../include/thread/Dispatcher.h
mainCo.o: ../src/mainCo.cc ../include/device/CgaChannel.h \
 ../include/io/OutputChannel.h ../include/device/CgaScreen.h \
 ../include/device/CgaAttr.h ../include/device/CgaChar.h \
 ../include/io/IOPort.h ../include/io/PrintStream.h \
 ../include/thread/Coroutine.h
