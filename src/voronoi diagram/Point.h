/* Created by Simone Tinella, University of Catania*/

class Punto{
	private:
		double x,y;
	public:
		Punto(double x,double y);
		double getX();
		double getY();
		void setX(double x);
		void setY(double y);
};

Punto::Punto(double x,double y){
	this->x=x;
	this->y=y;
}

double Punto::getX(){
	return x;
}

double Punto::getY(){
	return y;
}

void Punto::setX(double x){
	this->x+=x;
}

void Punto::setY(double y){
	this->y+=y;
}

