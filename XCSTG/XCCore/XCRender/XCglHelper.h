#pragma once
#ifndef _XCGLHELPER_H_
#define _XCGLHELPER_H_
#include <GL/glcorearb.h>
#include <vector>
class XCGlHelper {
private:
	std::vector<GLenum> EnableFeatures;
	std::vector<GLenum> blendParameter;
	std::vector<GLenum> blendValue;
public:
	void addFeatureToList(GLenum glFeature);
	void addBlendInfo(GLenum target, GLenum value);
	void UseFeature();
	void UnuseFeature();
};
#endif