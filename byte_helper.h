#ifndef BYTE_HELPER
#define BYTE_HELPER

#ifdef ARDUINO
#include <Arduino.h>
#include <string.h>
#else
#include <cstring>
#include <iostream>
#endif

class ByteConstructor{
private:
    int m=0;
    int c=0;
    unsigned char *bytes=nullptr;
    void update(int new_size);
public:
    unsigned char *getBytes(){return bytes;}
    int getSize(){return c;}
    int getMaxSize(){return m;}
    
    ~ByteConstructor(){delete[] bytes;}
    ByteConstructor(){update(4);}
    ByteConstructor(int _m){update(_m);}
    
//    template<typename T>
//    void add( T &v);
	template<typename T>
    void add(const T &v);
    void add(const void *v, int size);
};

class ByteReceiver{
    int m=0;
    int c=0;
    unsigned char *bytes=nullptr;
public:
    ByteReceiver(unsigned char *_b, int size):bytes(_b),m(size){}
    
    bool done(){return c >= m;}
    
    template<typename T>
    T get();
    template<typename T>
    T get(T& v);
};


//template<typename T>
//void ByteConstructor::add(T &v){add(&v, sizeof(T));}
template<typename T>
void ByteConstructor::add(const T &v){add(&v, sizeof(T));}

// ByteReceiver ************
template<typename T>
T ByteReceiver::get(){
	if(sizeof (T) > m-c){ // Checks if we have enough space in buffer
    #ifdef ARDUINO
        Serial.println(F("Byte reciver cannot output"));
    #else
		std::cout << "Byte reciver cannot output"<< std::endl;
    #endif
//		Serial.println("Byte reciver cannot output " + String(sizeof(T)) + " " + String(m) + " " + String(c));
		return 0;
	}
	
    T v = *((T*)(bytes+c));
    c+=sizeof(T);
	return v;
}

template<typename T>
T ByteReceiver::get(T& v){
    v = get<T>();
	return v;
}

#endif