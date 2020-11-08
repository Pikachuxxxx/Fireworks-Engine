#pragma once

#include <iostream>
#include <fstream>
#include <cstring>
#include <al.h>
#include <bit>

namespace fireworks { namespace utils {

	/// A class to load WAVE (.wav) audio files
	class WavLoader
	{
	public:
		bool isBigEndian()
		{
			int a = 1;
			return !((char*)&a)[0];
		}

		int convertToInt(char* buffer, std::uint32_t len)
		{
			std::uint32_t a = 0;
			if (!isBigEndian())
				for (std::uint32_t i = 0; i < len; i++)
					((char*)&a)[i] = buffer[i];
			else
				for (std::uint32_t i = 0; i < len; i++)
					((char*)&a)[3 - i] = buffer[i];
			return a;
		}

		/// Loads the wav file 
		char* loadWAV(const char* fn, std::uint32_t& format, std::uint32_t& samplerate, std::uint32_t& bps, std::uint32_t& size)
		{
			std::uint32_t channels;
			char buffer[4];
			std::ifstream in(fn, std::ios::binary);
			in.read(buffer, 4);
			if (strncmp(buffer, "RIFF", 4) != 0)
			{
				std::cout << "this is not a valid WAVE file" << std::endl;
				return NULL;
			}
			in.read(buffer, 4);
			in.read(buffer, 4);      //WAVE
			in.read(buffer, 4);      //fmt
			in.read(buffer, 4);      //16
			in.read(buffer, 2);      //1
			in.read(buffer, 2);
			channels = convertToInt(buffer, 2);
			in.read(buffer, 4);
			samplerate = convertToInt(buffer, 4);
			in.read(buffer, 4);
			in.read(buffer, 2);
			in.read(buffer, 2);
			bps = convertToInt(buffer, 2);
			in.read(buffer, 4);      //data
			in.read(buffer, 4);
			size = convertToInt(buffer, 4);
			char* data = new char[size];
			in.read(data, size);

			if (channels == 1)
			{
				if (bps == 8)
				{
					format = AL_FORMAT_MONO8;
				}
				else {
					format = AL_FORMAT_MONO16;
				}
			}
			else {
				if (bps == 8)
				{
					format = AL_FORMAT_STEREO8;
				}
				else {
					format = AL_FORMAT_STEREO16;
				}
			}
			return data;
		}
	};

} }