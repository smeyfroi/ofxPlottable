#include "ofxPlottable.h"
#include "ofGraphicsCairo.h"
#include "ofFileUtils.h"
#include "ofUtils.h"
#include <memory>

void Plottable::addCircle(float x, float y, float r, ofColor color, uint64_t lifetimeFrames) {
  shapes.push_back(std::make_unique<Plottable::CircleShape>(x, y, r, color, lifetimeFrames));
}

void Plottable::addLine(float x, float y, float x2, float y2, ofColor color, uint64_t lifetimeFrames) {
  shapes.push_back(std::make_unique<Plottable::LineShape>(x, y, x2, y2, color, lifetimeFrames));
}

void Plottable::addArc(float x, float y, float r, float angleBegin, float angleEnd, ofColor color, uint64_t lifetimeFrames) {
  shapes.push_back(std::make_unique<Plottable::ArcShape>(x, y, r, angleBegin, angleEnd, color, lifetimeFrames));
}

void Plottable::update() {
  for (auto& shape : shapes) {
    shape->update();
  }
  shapes.erase(std::remove_if(shapes.begin(),
                              shapes.end(),
                              [](const std::unique_ptr<Plottable::Shape>& s) { return s->lifetime == 0; }),
               shapes.end());
}

void Plottable::draw() const {
  if (!visible) return;
  for (auto& shape : shapes) {
    ofSetColor(shape->color);
    shape->draw();
  }
}

void Plottable::save(const std::string& filepath) const {
  ofBeginSaveScreenAsSVG(filepath);
  draw();
  ofEndSaveScreenAsSVG();
}

bool Plottable::keyPressed(int key) {
  if (key == 'v') {
    visible = !visible;
    return true;
  }
  if (key == 'V') {
    const std::string plotsDir = ofFilePath::getUserHomeDir()+"/plots/";
    ofDirectory::createDirectory(plotsDir, false);
    save(plotsDir+"plot-"+ofGetTimestampString()+".svg");
    return true;
  }
  return false;
}
