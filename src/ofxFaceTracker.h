/*
 ofxFaceTracker provides an interface to Jason Saragih's FaceTracker library.
 
 getImagePoint()/getImageMesh() are in image space. This means that all the
 points will line up with the pixel coordinates of the image you fed into
 ofxFaceTracker.
 
 getObjectPoint()/getObjectMesh() are in 3d object space. This is a product of
 the mean mesh with only the expression applied. There is no rotation or
 translation applied to the object space.
 
 getMeanObjectPoint()/getMeanObjectMesh() are also in 3d object space. However,
 there is no expression applied to the mesh.
 */

#pragma once

#include "ofxCv.h"
#include "Tracker.h"
#include "ExpressionClassifier.h"

class ofxFaceTracker {
public:
	ofxFaceTracker();
	void setup();
	bool update(cv::Mat image);
	void draw() const;
	void reset();
	
	int size() const;
	bool getFound() const;
	bool getVisibility(int i) const;
	ofVec2f getImagePoint(int i) const; // on the 2d screen
	ofVec3f getObjectPoint(int i) const; // in a normalized 3d space
	ofVec3f getMeanObjectPoint(int i) const; // in a normalized 3d space
	ofMesh getImageMesh() const; // on the 2d screen
	ofMesh getObjectMesh() const; // in a normalized 3d space
	ofMesh getMeanObjectMesh() const; // ideal, in a normalized 3d space
	const cv::Mat& getObjectPoints() const; // object points as a Mat, for classifier
	
	ofMesh getMeshFromVertices(vector<Point3d>& vertices);
	
	ofVec2f getPosition() const;
	float getScale() const; // multiply by ~20-23 to get pixel units (+/-20 units in the x axis, +23/-18 on the y axis)
	ofVec3f getOrientation() const;
	ofMatrix4x4 getRotationMatrix() const;
	
	enum Feature {
		LEFT_EYEBROW,
		RIGHT_EYEBROW,
		LEFT_EYE,
		RIGHT_EYE,
		LEFT_JAW,
		RIGHT_JAW,
		JAW,
		OUTER_MOUTH
		// INNER_MOUTH // needs a little more love
	};
	ofPolyline getFeature(Feature feature) const;
	
	enum Gesture {
		MOUTH_WIDTH, MOUTH_HEIGHT,
		LEFT_EYEBROW_HEIGHT, RIGHT_EYEBROW_HEIGHT,
		LEFT_EYE_OPENNESS, RIGHT_EYE_OPENNESS,
		JAW_OPENNESS,
		NOSTRIL_FLARE
		// MOUTH_WIGGLE // left/right
		// NOSE_WIGGLE // left/right
	};
	float getGesture(Gesture gesture) const;
	
	void setScale(float scale); // need to rename this due to getScale
	void setIterations(int iterations);
	void setClamp(float clamp);
	void setTolerance(float tolerance);
	void setAttempts(int attempts);
	
protected:
	void updateObjectPoints();
	
	bool failed;
	int idx;
	
	bool fcheck;
	double scale;
	int frameSkip;
	
	vector<int> wSize1, wSize2;
	int iterations;
	int attempts;
	double clamp, tolerance;
	
	FACETRACKER::Tracker tracker;
	cv::Mat tri, con;
	
	cv::Mat im, gray;
	cv::Mat objectPoints;
};
