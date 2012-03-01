#ifndef IDRAWABLE
#define IDRAWABLE

#include <list>

class IDrawable 
{
public:
	virtual ~ IDrawable(){}
	virtual void Draw()=0;
};

class Graphics : public IDrawable
{
public:
	Graphics(){}
	virtual ~ Graphics(){}
	typedef std::list<IDrawable*>::iterator Iterator;
	virtual void Draw();
	
	void AddEelemts(IDrawable* element){ elements.push_back(element); }
	Iterator Begin(){ return elements.begin(); }
	Iterator End(){ return elements.end(); }
	void Clear(){ elements.clear(); }
private:
	std::list<IDrawable*> elements;
};



#endif

