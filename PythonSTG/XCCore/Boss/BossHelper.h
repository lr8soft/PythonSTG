#pragma once
#ifndef _BOSS_HELPER_H_
#define _BOSS_HELPER_H_
#include <string>
#include "Boss.h"
#include "SpellCard.h"
#include <Python.h>
class BossHelper {
public:
	static Boss* parseBossFromObject(PyObject* pBossPyObject);
	static SpellCard* parseSpellCardFromObject(std::string parentUuid, PyObject* spellCardPyObject);
};
#endif