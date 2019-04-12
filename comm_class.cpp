#include "comm_class.h"


void CommObject::serialize(ByteConstructor &bc){
	bc.add(poly);
	bc.add(x);
	bc.add(y);
	bc.add(color);
}
void CommObject::deserialize(ByteReceiver &br){
	br.get(poly);
	br.get(x);
	br.get(y);
	br.get(color);
}
#ifndef ARDUINO
void CommObject::GetBytes(std::vector<CommObject*> &objects, ByteConstructor& bc){
	if (objects.size()==0)return;
	bc.add<uint8_t>(objects.size());
	for (auto o: objects)o->serialize(bc);
}
#endif
CommObject** CommObject::GetObjects(ByteReceiver &br, int& s){
	s = br.get<uint8_t>();
	CommObject **objects = new CommObject*[s];
	for(int i=0;i<s;i++){
		objects[i] = CommObject::Deserialize(br);
	}
	return objects;
}
void CommObject::DeleteObjects(CommObject** objects, int s){for(int i=0;i<s;i++)delete objects[i]; delete[] objects;}

CommObject* CommObject::Deserialize(ByteReceiver &br){
	CommObject o;
	o.deserialize(br);
	CommObject* p; if (o.poly) p = new CommPoly(o); else p = new CommCircle(o);
	p->deserialize(br);
	return p;
}

void CommPoly::serialize(ByteConstructor &bc){
	CommObject::serialize(bc);
	bc.add(sx);
	bc.add(sy);
}
void CommPoly::deserialize(ByteReceiver &br){
	br.get(sx);
	br.get(sy);
}

void CommCircle::serialize(ByteConstructor &bc){
	CommObject::serialize(bc);
	bc.add(r);
}
void CommCircle::deserialize(ByteReceiver &br){
	br.get(r);
}