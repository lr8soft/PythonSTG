#include "AudioHelper.h"
#include <iostream>
#include <string>
#include <thread>
bool AudioHelper::isEvonInit = false;
float AudioHelper::audioVolume = 0.4f;
ALCdevice*  AudioHelper::device = nullptr;
ALCcontext* AudioHelper::context = nullptr;

std::map<std::string, XCWavFile> AudioHelper::wavSourceGroup;
void AudioHelper::EvonInit()
{
	if (!isEvonInit) {
		device = alcOpenDevice(NULL);
		if (device==nullptr) {
			std::cout << "[ERROR]Failed to init openal device.\n";
		}
		else {
			ALCcontext* context = alcCreateContext(device, NULL);
			if (context == nullptr) {
				std::cout << "[ERROR]Failed to create openal context.\n";
			}
			else {
				alcMakeContextCurrent(context);
				isEvonInit = true;
				std::cout << "[INFO]Now OpenAL environment init.\n";
			}
		}
		alGetError(); //clear all error
	}
	
}

void AudioHelper::UnloadEvon()
{
	alcMakeContextCurrent(NULL);
	alcDestroyContext(context);
	alcCloseDevice(device);

	context = nullptr;
	device = nullptr;

	std::cout << "[INFO]Now OpenAL environment unloaded.\n";
	isEvonInit = false;
}

XCWavFile AudioHelper::loadWavFromFile(const std::string filename)
{
	XCWavFile wavFile;
	auto wavIter = wavSourceGroup.find(filename);
	if (wavIter !=wavSourceGroup.end()) {
		wavFile = wavIter->second;
	}
	else {
		bool success = loadWavFile(filename, &wavFile);
		if (success) {
			wavSourceGroup.insert(std::make_pair(filename, wavFile));
			std::cout << "[INFO] Load wav from file " << filename << std::endl;
		}
		else {
			std::cerr << "[ERROR] Failed to load wav from file " << filename << std::endl;
		}
	}
	return wavFile;
}

void AudioHelper::playerWavFile(XCWavFile file)
{
	auto playerFunc = [file](ALCcontext* context) {
		ALuint source;
		alGenSources(1, &source);
		alSourcei(source, AL_BUFFER, file.wavSource);
		alSourcef(source, AL_GAIN, audioVolume);
		alSourcePlay(source);
		
		ALint state;
		do {		
			alGetSourcei(source, AL_SOURCE_STATE, &state);		
		} while (state==AL_PLAYING);
	};
	std::thread playThread(playerFunc, context);
	playThread.detach();
}

void AudioHelper::setVolume(float volume)
{
	audioVolume = volume;
}

bool AudioHelper::loadWavFile(const std::string filename, XCWavFile *wavFile) {
	/*ALuint* buffer, ALsizei* size, ALsizei* frequency, ALenum* format*/
	//Local Declarations
	FILE* soundFile = NULL;
	WAVE_Format wave_format;
	RIFF_Header riff_header;
	WAVE_Data wave_data;
	unsigned char* data;

	try {
		soundFile = fopen(filename.c_str(), "rb");
		if (!soundFile)
			throw (filename);

		// Read in the first chunk into the struct
		fread(&riff_header, sizeof(RIFF_Header), 1, soundFile);

		//check for RIFF and WAVE tag in memeory
		if ((riff_header.chunkID[0] != 'R' ||
			riff_header.chunkID[1] != 'I' ||
			riff_header.chunkID[2] != 'F' ||
			riff_header.chunkID[3] != 'F') ||
			(riff_header.format[0] != 'W' ||
				riff_header.format[1] != 'A' ||
				riff_header.format[2] != 'V' ||
				riff_header.format[3] != 'E'))
			throw ("Invalid RIFF or WAVE Header");

		//Read in the 2nd chunk for the wave info
		fread(&wave_format, sizeof(WAVE_Format), 1, soundFile);
		//check for fmt tag in memory
		if (wave_format.subChunkID[0] != 'f' ||
			wave_format.subChunkID[1] != 'm' ||
			wave_format.subChunkID[2] != 't' ||
			wave_format.subChunkID[3] != ' ')
			throw ("Invalid Wave Format");

		//check for extra parameters;
		if (wave_format.subChunkSize > 16)
			fseek(soundFile, sizeof(short), SEEK_CUR);

		//Read in the the last byte of data before the sound file
		fread(&wave_data, sizeof(WAVE_Data), 1, soundFile);
		//check for data tag in memory
		if (wave_data.subChunkID[0] != 'd' ||
			wave_data.subChunkID[1] != 'a' ||
			wave_data.subChunkID[2] != 't' ||
			wave_data.subChunkID[3] != 'a')
			throw ("Invalid data header");

		//Allocate memory for data
		data = new unsigned char[wave_data.subChunk2Size];

		// Read in the sound data into the soundData variable
		if (!fread(data, wave_data.subChunk2Size, 1, soundFile))
			throw ("Error loading WAVE data into struct!");

		//Now we set the variables that we passed in with the
		//data from the structs
		wavFile->wavSize = wave_data.subChunk2Size;
		wavFile->wavFrequent = wave_format.sampleRate;
		//The format is worked out by looking at the number of
		//channels and the bits per sample.
		if (wave_format.numChannels == 1) {
			if (wave_format.bitsPerSample == 8)
				wavFile->wavFormat = AL_FORMAT_MONO8;
			else if (wave_format.bitsPerSample == 16)
				wavFile->wavFormat = AL_FORMAT_MONO16;
		}
		else if (wave_format.numChannels == 2) {
			if (wave_format.bitsPerSample == 8)
				wavFile->wavFormat = AL_FORMAT_STEREO8;
			else if (wave_format.bitsPerSample == 16)
				wavFile->wavFormat = AL_FORMAT_STEREO16;
		}
		//create our openAL buffer and check for success
		alGenBuffers(1, &(wavFile->wavSource));
		//errorCheck();
		//now we put our data into the openAL buffer and
		//check for success
		alBufferData(wavFile->wavSource, wavFile->wavFormat, (void*)data,
			wavFile->wavSize, wavFile->wavFrequent);
		//errorCheck();
		//clean up and return true if successful
		fclose(soundFile);
		return true;
	}
	catch (std::string error) {
		std::cerr << "[ERROR]" << error << " : trying to load " << filename << std::endl;
		if (soundFile != NULL)
			fclose(soundFile);
		return false;
	}

}
