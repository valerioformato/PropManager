#include <DragonManager.h>


using namespace std;

MyDRAGON::MyDRAGON() : DRAGON(){};
MyDRAGON::MyDRAGON( Input* inp ) : DRAGON( inp ){};

vector<double> MyDRAGON::GetEnergyGrid(){
  return gal->GetCoordinates()->GetEk();
}


vector<TParticle*> MyDRAGON::GetParticles(){
  return particles;
}
