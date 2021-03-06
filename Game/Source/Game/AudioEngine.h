#pragma once
#include "AudioDataStructures.h"

struct IXAudio2;
struct IXAudio2MasteringVoice;
class AudioVoice;

class AudioEngine
{
	public:
		AudioEngine();
		~AudioEngine();

		//create a source and add it to the list
		void CreateAudioVoice(AudioVoice* m_Voice);

		//delete a source and remove it from the list
		void DestroyAudioVoice(AudioVoice* m_Voice);

		//Set the volume for all the audio files being played, range 0.0f to 1.0f
		void SetVolume(float volume);

		//Returns the volume for all the audio files being played
		float GetVolume();

		//Returns a random public channel.
		AudioVoice* GetAvailablePublicChannel();

		//Sets the default wave format for the public channels
		void SetDefaultWaveFormat(WAVEFORMATEX format);

		//Creates the public channels
		void CreatePublicAudioChannels();

		//stops all channels that are playing of a type
		//pass VoiceType_Default to turn off all audio
		void StopChannelsOfType(enum VoiceType type);

		//ImGui call to display debug info for all channels this engine is managing
		void ImGuiDisplayChannels();


	private:

		//helper function to auto generate all channel treenodes to fill a collapsing header
		void GenerateImGuiChannelTreeNodes(enum VoiceType type);

		//main engine, voice and callback
		IXAudio2* m_Engine;
		IXAudio2MasteringVoice* m_MasteringVoice;
		AudioEventCallback m_Callback;

		//all channels
		std::vector<AudioVoice*> m_Channels;

		static const unsigned int MAX_PUBLIC_AUDIO_CHANNELS;//maximum public channels allowed
		static WAVEFORMATEX DEFAULT_WAVE_FORMAT;//default wave format for public channels
};
