#include "XCglHelper.h"
#include <GL3/gl3w.h>
void XCGlHelper::addFeatureToList(GLenum glFeature)
{
	EnableFeatures.push_back(glFeature);
}

void XCGlHelper::addBlendInfo(GLenum target, GLenum value)
{
	blendParameter.push_back(target);
	blendValue.push_back(value);
}

void XCGlHelper::UseFeature()
{
	auto featureEnd = EnableFeatures.end();
	for (auto iter = EnableFeatures.begin(); iter != featureEnd; iter++) {
		glEnable(*iter);
	}
	auto blendpEnd = blendParameter.end();
	auto blendvEnd = blendValue.end();
	auto iterator = blendParameter.begin();
	if (iterator != blendpEnd) {
		for (auto iterv = blendValue.begin(); iterator != blendpEnd && iterv != blendvEnd; iterator++, iterv++) {
			glBlendFunc(*iterator, *iterv);
		}
	}
}

void XCGlHelper::UnuseFeature()
{
	auto featureEnd = EnableFeatures.end();
	for (auto iter = EnableFeatures.begin(); iter != featureEnd; iter++) {
		glDisable(*iter);
	}
}
