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
    atk = 10;
    def = 10;
    vulnerableExperience = 10;
    visible = true;
    target = NULL;
    atkTime = 30;
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
    atk = 10;
    def = 10;
    vulnerableExperience = 10;
    visible = true;
    target = NULL;
    atkTime = 30;
}
Character::Character( float r, float g, float b, Position p ){
    //Character constructor
    red = r;
    green = g;
    blue = b;
    position = p;
    level = 1;
    experience = 0;
    atk = 10;
    def = 10;
    vulnerableExperience = 10;
    visible = true;
    target = NULL;
    atkTime = 30;
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
    atk = 10;
    def = 10;
    vulnerableExperience = 10;
    visible = true;
    target = NULL;
    atkTime = 30;
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
void Character::setRangeAtk( float rAtk){
    rangeAtk = rAtk;
}
void Character::setTeam( int t ){
    team = t;
}
void Character::setRadiusCharacterAproximation( float r ){
    radiusCharacterAproximation = r;
}
/*====================Class methods====================*/
void Character::addLevel( int lvl ){
    lvl += lvl;
    atk += atk*(0.3)*lvl;
    def += def*(0.25)*lvl;
    int maxLife = characterLife.getMaxLife();
    setCharacterMaxLife( (int)(maxLife + maxLife*lvl*(0.183)));
}
void Character::addExperience( int exp ){
    int interval = 100;
    experience += 100;
    if(experience/interval > level) addLevel(1);
}
void Character::heal( float perCentHeal ){
    float aux;
    if( perCentHeal > 1.0 ) aux = 1.0;
    else if ( perCentHeal < 0.0 ) aux = 0;
    else aux = perCentHeal;
    int actualLife = characterLife.getLife();
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
void Character::atkTarget(){
    Character * aux;
    atkCicle--;
    if( atkCicle < 0 ) atkCicle = 0;
    if( atkCicle == 0){
        if( getTarget() != NULL ){
            aux = (Character*)getTarget();
            float enemyDist;
            float x = getPosition().getX();
            float z = getPosition().getZ();
            enemyDist = sqrt( pow(( x - (*aux).getPosition().getX()),2)  +  pow( (z - (*aux).getPosition().getZ()) ,2) );
            if( enemyDist < (getRangeAtk() + (*aux).getRadiusCharacterAproximation() )){
                toDamage(target);
                atkCicle = atkTime;
            }
        }
    }  
}