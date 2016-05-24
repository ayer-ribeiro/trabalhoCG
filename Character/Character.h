#include "../Util/LifeBar.cpp"
#include "../gLib.h"


using namespace std;

class Character{
	//Atributos
private:
	void * target;
	float rangeAtk;
	Position position;
	float red;
	float green;
	float blue;
	int atk;
	int def;
	int level;
	int experience;
	int vulnerableExperience;
	LifeBar characterLife;
	bool visible;
	int team;
	float radiusCharacterAproximation;
	int atkCicle;
	int atkTime;
public:
	/*Constructors and destructors*/
	Character();
	Character( float, float, float );
	Character( Position );
	Character( float, float, float, Position );
	Character( float, float, float, Position , LifeBar );
	~Character();

	/*Getters*/
	float getColorR();
	float getColorG();
	float getColorB();
	int getAtk();
	int getDef();
	int getLevel();
	int getExperience();
	int getCharacterMaxLife();
	int getCharacterLife();
	Position getPosition();
	LifeBar getLifeBar();
	bool isVisible();
	void* getTarget();
	float getRangeAtk();
	int getTeam();
	float getRadiusCharacterAproximation();

	/*Setters*/
	void setColor3f( float, float, float );
	void setPosition( float, float, float );
	void setLifeBar( LifeBar );
	void setAtk( int );
	void setDef( int );
	void setCharacterMaxLife( int );
	void setLifeBarPosition( int, int, int );
	void setVulnerableExperience( int );
	void setVisibility( bool );
	void setBarLifeRotate( float, float, float );
	void setTarget( void* );
	void setRangeAtk( float );
	void setTeam( int );
	void setRadiusCharacterAproximation( float );

	/*Class methods*/
	void addLevel( int );
	void addExperience( int );
	void heal( float );
	int toDamage( void* );
	int takeDamage( int );
	void atkTarget();
};
