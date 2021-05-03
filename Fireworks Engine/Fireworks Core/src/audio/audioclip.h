#pragma once
#include <al.h>
#include <alc.h>
#include <src/utils/wavloader.h>


namespace fireworks { namespace audio {

/// The max buffers for concurrent streaming of audio data.
#define STREAM_BUFFER_COUNT 4
/// The max size of each streaming buffer
#define STREAM_BUFFER_SIZE  65536

	/// Class responsible for managing audio clips.
	class AudioClip
	{
	public:
		/// Sets the gain of the audio source
		int					gain;	
		/// Sets the pitch of the audio source
		int					pitch;
	public:
		/// Creates a audio clip to play in your application.
		///
		/// @param filePath The file path of the audio clip
		/// @note currently only supports .WAV files
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
		/// Play the Source Once in any loop
		void PlayOnce();
		/// Play the Source only Once in any loop
		void PlayOnceOnly();
		/// Play the Source in Looping mode in any loop
		void Loop();

		/// Gets the audio format of the audio clip
		///
		/// @note formats include 8-bit mono/stereo or 16-bit mono/stereo
		inline std::uint32_t getAudioFormat() const { return m_AudioFormat; }
		/// Gets the sample rate of the audio clip
		inline std::uint32_t getSampleRate() const { return m_SampleRate; }
		/// Gets the bits per second of the audio clip
		inline std::uint32_t getBPS() const { return m_BitsPerSecond; }
		/// Gets the the clip size in Kb
		inline std::uint32_t getClipSizeinKB() const { return (m_Size / 1024); }

		/// Tells whether the audio clip is in looping state or not
		inline bool isLooping() { alGetSourcei(m_Source, AL_LOOPING, &m_SourceState); return m_SourceState == 1; }
		/// Tells whether the audio clip is paused or not
		inline bool isPaused() { getSourceState(); return m_SourceState == AL_PAUSED; }
		/// Tells whether the audio clip is playing or not
		inline bool isPlaying() { getSourceState(); return m_SourceState == AL_PLAYING; }
		/// Tells whether the audio clip is stopped or not
		inline bool isStopped() { getSourceState(); return m_SourceState == AL_STOPPED; }
		/// Tells whether if the audio clip did play at least once
		inline bool didPlayonce() const { return m_DidPlayOnce; }

		/// Gets the Buffer of the audio clip data
		inline ALuint getBuffer() const { return m_BufferID; }
		/// Gets the Source ID of the audio source that plays the clip
		inline ALuint getSource() const { return m_Source; }
	private:
		static ALboolean	s_g_bEAX;
		static ALCdevice*	s_Device;
		static ALCcontext*	s_Context;

		std::string			m_FilePath;
		const char* m_Data;
		utils::WavLoader	m_WavLoader;

		std::uint32_t		m_AudioFormat;
		std::uint32_t		m_SampleRate;
		std::uint32_t		m_BitsPerSecond;
		std::uint32_t		m_Size;

		ALuint				m_BufferID;
		ALuint				m_Source;
		ALint				m_SourceState;

		bool				m_EnableLooping;
		bool				m_DidPlayOnce;
	private:
		inline void getSourceState() { alGetSourcei(m_Source, AL_SOURCE_STATE, &m_SourceState); }
		void init();
		void load();
		void enableStreamingMode();
	};
} }
