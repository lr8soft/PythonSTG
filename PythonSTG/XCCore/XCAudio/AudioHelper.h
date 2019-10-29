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

struct XCWavFile {
	ALuint wavBuffer;
	ALsizei wavSize;
	ALsizei wavFrequent;
	ALenum wavFormat;
};

class AudioHelper {
private:
	static bool isEvonInit;
	//static ALCdevice* device;
	//static ALCcontext* context;
	static float audioVolume;

	static std::map<std::string, XCWavFile> wavSourceGroup;
	static std::map<ALuint, ALuint> effectPlayingList;/*buffer, source*/

	static bool loadWavFile(const std::string filename, XCWavFile *wavFile);

public:
	static void EvonInit();
	static void UnloadEvon();

	static XCWavFile loadWavFromFile(const std::string& filename);
	static ALuint loadWavByAlut(const std::string& filename);
	static void setVolume(float volume);

	static void playFromBuffer(ALuint buffer);
	static void stopByBuffer(ALuint buffer);
	static void releaseByBuffer(ALuint buffer);
};
#endif