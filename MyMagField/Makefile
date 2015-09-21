all:
	g++ -fPIC -shared -rdynamic -I`root-config --cflags` MyMagField.cxx -o libMyMagField.so
test:
	g++ -I`root-config --cflags` MyMagField2.cxx test_fieldmap.cxx `root-config --libs` -o test_fieldmap 

