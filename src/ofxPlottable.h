#pragma once

#include <string>
#include <vector>
#include <memory>
#include "ofGraphics.h"
#include "ofPath.h"

// NOTE: this is very similar to ofxIntrospector

// FIXME: Sets circle resolution but doesn't restore it (can't find a way to get the current value). Arc resolution is only local to the ofPath so that's OK. Could model circles as arcs to avoid this.
class Plottable {
  static const int ARC_RESOLUTION = 128;
  static const int CIRCLE_RESOLUTION = 128;

  struct Shape {
    Shape(ofColor color_, uint64_t lifetime_) : color(color_), lifetime(lifetime_) {};
    virtual ~Shape() = default;
    void update() { if (lifetime > 0) lifetime--; };
    bool isExpired() const { return (lifetime <= 0); };
    virtual void draw() = 0;
    ofColor color;
    uint64_t lifetime;
  };

  struct LineShape : public Shape {
    LineShape(float x1_, float y1_, float x2_, float y2_, ofColor color_, uint64_t lifetime_) :
      Shape(color_, lifetime_), x1(x1_), y1(y1_), x2(x2_), y2(y2_) {};
    void draw() override { ofSetColor(color); ofDrawLine(x1, y1, x2, y2); };
    float x1, y1, x2, y2;
  };

  struct CircleShape : public Shape {
    CircleShape(float x_, float y_, float r_, ofColor color_, uint64_t lifetime_) :
      Shape(color_, lifetime_), x(x_), y(y_), r(r_) {};
    void draw() override { ofSetCircleResolution(CIRCLE_RESOLUTION); ofSetColor(color); ofNoFill(); ofDrawCircle(x, y, r); };
    float x, y, r;
  };

  struct ArcShape : public Shape {
    ArcShape(float x_, float y_, float r_, float angleBegin_, float angleEnd_, ofColor color_, uint64_t lifetime_) :
      Shape(color_, lifetime_), x(x_), y(y_), r(r_), angleBegin(angleBegin_), angleEnd(angleEnd_) {};
    void draw() override { ofPolyline path; path.arc(x, y, r, r, angleBegin, angleEnd, Plottable::ARC_RESOLUTION); ofSetColor(color); path.draw(); };
    float x, y, r;
    float angleBegin, angleEnd;
  };

public:
  void addCircle(float x, float y, float r, ofColor color, uint64_t lifetimeFrames=40);
  void addLine(float x, float y, float x2, float y2, ofColor color, uint64_t lifetimeFrames=40);
  void addArc(float x, float y, float r, float angleBegin, float angleEnd, ofColor color, uint64_t lifetimeFrames=40);

  void update();
  void draw() const;
  bool keyPressed(int key); // return true if key press handled
  void save(const std::string& filepath) const;

private:
  std::vector<std::unique_ptr<Plottable::Shape>> shapes;
  bool visible { false };
};
