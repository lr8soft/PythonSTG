#pragma once
#ifndef _AUDIO_HELPER_H_
#define _AUDIO_HELPER_H_
#define _CRT_SECURE_NO_WARNINGS
#include <AL/al.h>
#include <AL/alc.h>
#include <map>
#include <iostream>
struct WAVE_Data {
	char subChunkID[4]; //should contain the word data
	long subChunk2Size; //Stores the size of the data block
};

struct WAVE_Format {
	char subChunkID[4];
	long subChunkSize;
	short audioFormat;
	short numChannels;
	long sampleRate;
	long byteRate;
	short blockAlign;
	short bitsPerSample;
};

struct RIFF_Header {
	char chunkID[4];
	long chunkSize;//size not including chunkSize or chunkID
	char format[4];

};

class AudioHelper {
private:
	static bool isEvonInit;
	static ALCdevice* device;
	static ALCcontext* context;

	//std::map<std::string, >
public:
	static void EvonInit();
	static void UnloadEvon();

	static bool loadWavFile(const std::string filename, ALuint* buffer, ALsizei* size, ALsizei* frequency, ALenum* format);
};
#endif