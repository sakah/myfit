load.so:
	g++ -dynamiclib -fPIC `root-config --cflags --libs` Util.cc WireConfig.cc XTCurve.cc CounterHit.cc CdcHit.cc Hough.cc -o load.so

util.so:
	g++ -dynamiclib -fPIC `root-config --cflags` `root-config --libs` util.cc -o util.so

util.o:
	g++ -c `root-config --cflags` `root-config --libs` util.cc -o util.o

config.o:
	g++ -c `root-config --cflags` `root-config --libs` config.cc -o config.o


all:
	g++ `root-config --cflags` `root-config --libs` config.cc Event.cc -o Event.o
