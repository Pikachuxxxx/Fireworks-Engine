#pragma once
#include <al.h>
#include <alc.h>
#include "../utils/wavloader.h"


namespace fireworks { namespace audio {

#define STREAM_BUFFER_COUNT 4
#define STREAM_BUFFER_SIZE  65536

	class AudioClip
	{
	public:
		bool				enableLooping;
		int					gain;
		int					pitch;
	private:
		std::string			m_FilePath;
		const char*			m_Data;
		utils::WavLoader	m_WavLoader;

		std::uint32_t		m_AudioFormat;
		std::uint32_t		m_SampleRate;
		std::uint32_t		m_BitsPerSecond;
		std::uint32_t		m_Size;

		static ALboolean	m_g_bEAX;
		static ALCdevice*	m_Device;
		static ALCcontext*	m_Context;
		ALuint				m_BufferID;
		ALuint				m_Source;
		ALint				m_SourceState;
		
		bool				m_DidPlayOnce;
	public:
		AudioClip(const std::string& filePath);
		~AudioClip();

		/// Play, Replay, or Resume a Source
		void Play();
		/// Pause a Source
		void Pause();
		/// Stop a Source
		void Stop();
		/// Rewind a Source (set playback position to beginning) 
		void Replay();
		/// Play the Source only Once in any loop
		void PlayOnce();
		/// Play the Source in Looping mode in any loop
		void Loop();

		inline std::uint32_t getAudioFormat() const { return m_AudioFormat; }
		inline std::uint32_t getSampleRate() const { return m_SampleRate; }
		inline std::uint32_t getBPS() const { return m_BitsPerSecond; }
		inline std::uint32_t getClipSizeinKB() const { return (m_Size / 1024); }

		inline bool isLooping() { alGetSourcei(m_Source, AL_LOOPING, &m_SourceState); return m_SourceState == 1; }
		inline bool isPaused() { getSourceState(); return m_SourceState == AL_PAUSED; }
		inline bool isPlaying() { getSourceState(); return m_SourceState == AL_PLAYING; }
		inline bool isStopped() { getSourceState(); return m_SourceState == AL_STOPPED; }
		inline bool didPlayonce() const { return m_DidPlayOnce; }

		inline ALuint getBuffer() const { return m_BufferID; }
		inline ALuint getSource() const { return m_Source; }
	private:
		inline void getSourceState() { alGetSourcei(m_Source, AL_SOURCE_STATE, &m_SourceState); }
		void init();
		void load();
		void enableStreamingMode();
	};

} }