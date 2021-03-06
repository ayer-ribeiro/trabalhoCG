#include "Character.h"

/*====================Constructors and destructors====================*/
Character::Character( void ){
	//Character constructor
    red = 0;
    green = 0;
    blue = 0;
    position.setX( 0.0 );
    position.setY( 0.0 );
    level = 1;
    experience = 0;
    interval = 30;
    atk = 10;
    def = 10;
    vulnerableExperience = 10;
    visible = true;
    target = NULL;
    rangeAtk = 5;
    sightRadius = 40;
    AI = false;
}
Character::Character( float r, float g, float b ){
	//Character constructor
    red = r;
    green = g;
    blue = b;
    position.setX( 0.0 );
    position.setY( 0.0 );
    level = 1;
    experience = 0;
    interval = 30;
    atk = 10;
    def = 10;
    vulnerableExperience = 10;
    visible = true;
    target = NULL;
    rangeAtk = 5;
    sightRadius = 40;
    AI = false;
}
Character::Character( float r, float g, float b, Position p ){
    //Character constructor
    red = r;
    green = g;
    blue = b;
    position = p;
    level = 1;
    experience = 0;
    interval = 30;
    atk = 10;
    def = 10;
    vulnerableExperience = 10;
    visible = true;
    target = NULL;
    rangeAtk = 5;
    sightRadius = 40;
    AI = false;
}

Character::Character( float r, float g, float b, Position p, LifeBar lifeBar){
    //Character constructor
    red = r;
    green = g;
    blue = b;
    position = p;
    characterLife = lifeBar;
    level = 1;
    experience = 0;
    interval = 30;
    atk = 10;
    def = 10;
    vulnerableExperience = 10;
    visible = true;
    target = NULL;
    rangeAtk = 5;
    sightRadius = 40;
    AI = false;
    
}
Character::~Character( void ){
    //Character destructor
}

/*====================Getters====================*/
float Character::getColorR(){
    return red;
}
float Character::getColorG(){
    return green;
}
float Character::getColorB(){
    return blue;
}
int Character::getAtk(){
    return atk;
}
int Character::getDef(){
    return def;
}
int Character::getLevel(){
    return level;
}
Position Character::getPosition(){
    return position;
}
LifeBar Character::getLifeBar(){
    return characterLife;
}
int Character::getExperience(){
    return experience;
}
int Character::getInterval(){
    return interval;
}
int Character::getCharacterMaxLife(){
    return characterLife.getMaxLife();
}
int Character::getCharacterLife(){
    return characterLife.getLife();
}
bool Character::isVisible(){
    return visible;
}
void* Character::getTarget(){
    return target;
}
float Character::getRangeAtk(){
    return rangeAtk;
}
int Character::getTeam(){
    return team;
}
float Character::getRadiusCharacterAproximation(){
    return radiusCharacterAproximation;
}
float Character::getSightRadius(){
    return sightRadius;
}
bool Character::isAI(){
    return AI;
}
float Character::getHeight(){
    return height;
}
string Character::getName(){
    return name;
}

/*====================Setters====================*/
void Character::setColor3f( float r, float g, float b){
    red = r;
    green = g;
    blue = b;
}
void Character::setPosition( float x, float y, float z ){
    position.setX(x);
    position.setY(y);
    position.setZ(z);
}
void Character::setLifeBar( LifeBar l ){
    characterLife = l;
}
void Character::setAtk( int a ){
    atk = a;
}
void Character::setDef( int d ){
    def = d;
}
void Character::setCharacterMaxLife( int ml ){
    characterLife.setMaxLife( ml );
}
void Character::setLifeBarPosition( int x, int y, int z ){
    characterLife.setPosition( x, y, z );
}
void Character::setVulnerableExperience( int vExp ){
    vulnerableExperience = vExp;
}
void Character::setVisibility( bool v ){
    visible = v;
}
void Character::setBarLifeRotate( float rx, float ry, float rz ){
    characterLife.setRotate( rx, ry, rz );
}
void Character::setTarget( void* t){
    target = t;
}
void Character::setRangeAtk( float rAtk ){
    rangeAtk = rAtk;
}
void Character::setTeam( int t ){
    team = t;
    if(team == 1){
    	characterLife.setColor3f( 0.0f, 1.0f, 0.0f );
    }else{
    	characterLife.setColor3f( 1.0f, 0.0f, 0.0f );
    }
}
void Character::setRadiusCharacterAproximation( float r ){
    radiusCharacterAproximation = r;
}
void Character::setSightRadius( float sightR ){
    sightRadius = sightR;
}
void Character::setAI( bool ai ){
    AI = ai;
}
void Character::setHeight( float h ){
    height = h;
}
void Character::setName( string n ){
    name = n;
}

/*====================Class methods====================*/
void Character::addLevel( int lvl ){
    level += lvl;
    atk += atk*(0.3)*lvl;
    def += def*(0.25)*lvl;
    int maxLife = characterLife.getMaxLife();
    setCharacterMaxLife( (int)(maxLife + maxLife*lvl*(0.183)));
    interval += interval*0.4;
    experience = 0;
}
void Character::addExperience( int exp ){
    experience += exp;
    if(experience/interval == 1) addLevel(1);
}
void Character::heal( float perCentHeal ){
    float aux;
    if( perCentHeal > 1.0 ) aux = 1.0;
    else if ( perCentHeal < 0.0 ) aux = 0;
    else aux = perCentHeal;
    int actualLife = characterLife.getMaxLife();
    characterLife.setLife( ( int )( actualLife + actualLife * ( perCentHeal ) ) );
}
int Character::takeDamage ( int opponentAtk ) {
    int damage, actualLife;
    damage = (100*opponentAtk) / (100+def);
    //damage = (opponentAtk - def*( 0.3 ));
    if( damage <= 0 ) damage = 1;
    actualLife = characterLife.getLife();
    characterLife.setLife( actualLife - damage );

    if( characterLife.getLife() == 0 ) return vulnerableExperience;
    else return 0;
}
int Character::toDamage( void* target ) {
    Character * aux;
    aux = (Character*)target;
    int ret;
    ret = aux->takeDamage(atk);
    return ret;
}
void Character::setTargetFromSightRadius( ){
    Character * aux;
    Character * enemyCloser;
    float closerEnemyDist = 99999999;
    float x = getPosition().getX();
    float z = getPosition().getZ();
    enemyCloser = NULL;

	for(int i = 0; i<figurantTeam1.size(); i++){
		float enemyDist;
		aux = (Character*)figurantTeam1[i];
		if((*aux).getCharacterLife() > 0){
			if((*aux).getTeam() != getTeam()){
				enemyDist = sqrt( pow(( x - (*aux).getPosition().getX()),2)  +  pow( (z - (*aux).getPosition().getZ()) ,2) );
				if( enemyDist < closerEnemyDist){
					enemyCloser = aux;
					closerEnemyDist = sqrt( pow(( x - (*enemyCloser).getPosition().getX()),2)  +  pow( (z - (*enemyCloser).getPosition().getZ()) ,2) );
				}
			}
		}
	}
	for(int i = 0; i<figurantTeam2.size(); i++){
		float enemyDist;
		aux = (Character*)figurantTeam2[i];
		if((*aux).getCharacterLife() > 0){
			if((*aux).getTeam() != getTeam()){
				enemyDist = sqrt( pow(( x - (*aux).getPosition().getX()),2)  +  pow( (z - (*aux).getPosition().getZ()) ,2) );
				if( enemyDist < closerEnemyDist){
					enemyCloser = aux;
					closerEnemyDist = sqrt( pow(( x - (*enemyCloser).getPosition().getX()),2)  +  pow( (z - (*enemyCloser).getPosition().getZ()) ,2) );
				}
			}
		}
	}
	for(int i = 0; i<charactersGame.size(); i++){
		float enemyDist;
		aux = (Character*)charactersGame[i];
		if((*aux).getCharacterLife() > 0){
			if((*aux).getTeam() != getTeam()){
				enemyDist = sqrt( pow(( x - (*aux).getPosition().getX()),2)  +  pow( (z - (*aux).getPosition().getZ()) ,2) );
				if( enemyDist < closerEnemyDist){
					enemyCloser = aux;
					closerEnemyDist = sqrt( pow(( x - (*enemyCloser).getPosition().getX()),2)  +  pow( (z - (*enemyCloser).getPosition().getZ()) ,2) );
				}
			}
		}
	}
	for(int i = 0; i<towers.size(); i++){
		float enemyDist;
		aux = (Character*)towers[i];
		if((*aux).getCharacterLife() > 0){
			if((*aux).getTeam() != getTeam()){
				enemyDist = sqrt( pow(( x - (*aux).getPosition().getX()),2)  +  pow( (z - (*aux).getPosition().getZ()) ,2) );
				if( enemyDist < closerEnemyDist){
					enemyCloser = aux;
					closerEnemyDist = sqrt( pow(( x - (*enemyCloser).getPosition().getX()),2)  +  pow( (z - (*enemyCloser).getPosition().getZ()) ,2) );
				}
			}
		}
	}

    /*

    Character baseC1;
    Character baseC2;
    baseC1.setPosition(-1000,0,-110);
    baseC1.setTeam(1);
    baseC1.setName("b1");
    baseC2.setPosition(1000,0,-110);
    baseC2.setTeam(2);
    baseC2.setName("b2");
    vector<void*> CBases;
    CBases.push_back(&baseC1);
    CBases.push_back(&baseC2);

    
    for(int i = 0; i<CBases.size(); i++){
    	float xEnemyBase,zEnemyBase;
        float enemyDist;
        aux = (Character*)CBases[i];

        if((*aux).getCharacterLife() > 0){
            if((*aux).getTeam() != getTeam()){
            	if(getTeam() == 1){
            		xEnemyBase = 1000;
            		zEnemyBase = -110;
            	}else if(getTeam() == 2){
            		xEnemyBase = -1000;
            		zEnemyBase = -110;
            	}

            	enemyDist = sqrt( pow(x-xEnemyBase,2.0)  +  pow( z - zEnemyBase ,2.0) );
                if( enemyDist < closerEnemyDist){
                    if(i == 0){
                        enemyCloser = (Character*)bases[0]; 
                    }
                    else{
                        enemyCloser = (Character*)bases[1];
                    }
                    closerEnemyDist = sqrt( pow(x - xEnemyBase,2)  +  pow( (z - zEnemyBase) ,2) );
                }
            }
        }
    }

    if(getName() == "Hero team 1"){
    	if(getTarget() != NULL){
    		//cout << "e aqui \n";
        	//cout << "enemyName: " << enemyCloser->getName() << endl;
    	}
    }
    */

    if(closerEnemyDist < sightRadius){
        setTarget(enemyCloser);

    }else{
        setTarget(NULL);
    }
}