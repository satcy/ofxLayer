#pragma once

#include "ofMain.h"

#include "ofxLayerConstants.h"

#include "ofxLayerManager.h"

#define OFX_LAYER_DEFINE_LAYER_CLASS(Klass) public: const char* getClassName() const { return #Klass; } \
	unsigned int getClassID() const { return ofx::Layer::Type2Int<Klass>::value(); }

OFX_LAYER_BEGIN_NAMESPACE

class Layer
{
	friend class Manager;
	
public:
	
	// use OFX_LAYER_DEFINE_LAYER_CLASS
	virtual const char* getClassName() const = 0;
	virtual unsigned int getClassID() const = 0;
	
public:
	
	virtual void setup() {}
    virtual void updateEvery() {}
	virtual void update() {}
	virtual void draw() {}
	
	void setVisible(bool v) { visible = v; }
	bool getVisible() { return visible; }
	bool isVisible() { return visible; }
	
	void setAlpha(float a)
	{
		visible = (a > 0);
		alpha = a;
	}
	float getAlpha() { return alpha; }
	
	int getLayerIndex();
	void setLayerIndex(int index);
	
	void moveFront();
	void moveBack();
	
	void moveUp();
	void moveDown();
	
	void mute();
	void solo();
    
    ofBlendMode getBlendMode(){
        return blendMode;
    }
    
    void setBlendMode(ofBlendMode mode){
        blendMode = mode;
    }

protected:
	
	void ofBackground(int r, int g, int b, int a = 255);
	void ofBackground(int b, int a = 255);
	
	inline ofRectangle ofGetCurrentViewport()
	{
		return ofRectangle(rect);
	}
	
	inline int ofGetWidth()
	{
		return rect.width;
	}
	
	inline int ofGetHeight()
	{
		return rect.height;
	}
	
protected:
	
	Layer();
	virtual ~Layer();
	
	void layerSetup(int width, int height);
	void layerUpdate();
	
private:
    
    ofBlendMode blendMode;
	
	Manager *manager;
	
	unsigned int class_id;
	int layer_index;
	
	bool visible;

	ofRectangle rect;
	ofColor background;
	float alpha;
	
	Layer(const Layer&);
	Layer& operator=(const Layer&);
};

OFX_LAYER_END_NAMESPACE