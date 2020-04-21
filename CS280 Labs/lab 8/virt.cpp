#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Instrument {
    string name;
public:
    Instrument(string name) : name(name) {}
    virtual bool isString() const {return false;}
    virtual bool isPercussion() const{return false;}
    virtual bool isBrass() const{return false;}
    virtual bool isWoodwind() const{return false;}
};

class Brass : public Instrument {
public:
    Brass(string name) : Instrument(name) {}
    Brass() : Instrument("Unnamed Brass") {}
    bool isBrass() const{return true;}
};

class Woodwind : public Instrument {
    public:
    Woodwind(string name) : Instrument(name) {}
    Woodwind() : Instrument("Unnamed Woodwind") {}
    bool isWoodwind() const{return true;}
};

class Percussion : public Instrument {
    public:
    Percussion(string name) : Instrument(name) {}
    Percussion() : Instrument("Unnamed Percussion") {}
    bool isPercussion() const{return true;}
};

class String : public Instrument {
    public:
    String(string name) : Instrument(name) {}
    String() : Instrument("Unnamed String") {}
    bool isString() const{return true;}
};
class Violin: public String{
    public: 
    Violin(string name): String(name){}
    Violin(): String("Unamed Violin"){}
};
class Piano: public Percussion{
    public: 
    Piano(string name): Percussion(name){}
    Piano(): Percussion("Unamed Piano"){}
};
class Trumpet: public Brass{
    public: 
    Trumpet(string name): Brass(name){}
    Trumpet(): Brass("Unamed Trumpet"){}
};
class Trombone: public Brass{
    public: 
    Trombone(string name): Brass(name){}
    Trombone(): Brass("Unamed Trombone"){}
};
class TenorSax: public Woodwind{
    public: 
    TenorSax(string name): Woodwind(name){}
    TenorSax(): Woodwind("Unamed TenorSax"){}
};

int
main(int argc, char *argv[])
{
    vector<Instrument *> allInstruments;
    
    
    allInstruments.push_back( new Violin() );
	allInstruments.push_back( new Piano() );
	allInstruments.push_back( new Trumpet() );
	allInstruments.push_back( new Trombone() );
	allInstruments.push_back( new TenorSax() );
   
     int brassCount =0;
    int woodwindCount =0;
    int percussionCount =0;
    int stringCount =0;
    for (Instrument *inst: allInstruments){
        brassCount+=inst->isBrass();
        woodwindCount+=inst->isWoodwind();
        percussionCount+=inst->isPercussion();
        stringCount+=inst->isString();
    }
    cout<<percussionCount<<endl;
    cout<<stringCount<<endl;
    cout<<brassCount<<endl;
    cout<<woodwindCount<<endl;
    return 0;
}
