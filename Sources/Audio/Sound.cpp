﻿#include "Sound.hpp"

#if defined(ACID_BUILD_MACOS)
#include <OpenAL/al.h>
#else
#include <al.h>
#endif
#include "Scenes/Entity.hpp"

namespace acid
{
Sound::Sound(const std::string &filename, const Transform &localTransform, const Audio::Type &type, const bool &begin, const bool &loop, const float &gain, const float &pitch) :
	m_soundBuffer(SoundBuffer::Create(filename)),
	m_source(0),
	m_localTransform(localTransform),
	m_type(type),
	m_gain(gain),
	m_pitch(pitch)
{
	alGenSources(1, &m_source);
	alSourcei(m_source, AL_BUFFER, m_soundBuffer->GetBuffer());

	Audio::CheckAl(alGetError());

	SetGain(gain);
	SetPitch(pitch);

	if (begin)
	{
		Play(loop);
	}

	Audio::Get()->OnGain().Add([this](Audio::Type type, float volume)
	{
		if (type == m_type)
		{
			SetGain(m_gain);
		}
	}, this);
}

Sound::~Sound()
{
	alDeleteSources(1, &m_source);
	Audio::CheckAl(alGetError());
}

void Sound::Start()
{
}

void Sound::Update()
{
	SetPosition(GetWorldTransform().GetPosition());
}

void Sound::Play(const bool &loop)
{
	alSourcei(m_source, AL_LOOPING, loop);
	alSourcePlay(m_source);
	Audio::CheckAl(alGetError());

	SetGain(m_gain);
}

void Sound::Pause()
{
	if (!IsPlaying())
	{
		return;
	}

	alSourcePause(m_source);
	Audio::CheckAl(alGetError());
}

void Sound::Resume()
{
	if (IsPlaying())
	{
		return;
	}

	alSourcePlay(m_source);
	Audio::CheckAl(alGetError());

	SetGain(m_gain);
}

void Sound::Stop()
{
	if (!IsPlaying())
	{
		return;
	}

	alSourceStop(m_source);
	Audio::CheckAl(alGetError());
}

bool Sound::IsPlaying() const
{
	ALenum state;
	alGetSourcei(m_source, AL_SOURCE_STATE, &state);
	return state == AL_PLAYING;
}

Transform Sound::GetWorldTransform() const
{
	if (m_localTransform.IsDirty() || GetParent()->GetWorldTransform().IsDirty())
	{
		m_worldTransform = GetParent()->GetWorldTransform() * m_localTransform;
		m_localTransform.SetDirty(false);
	}

	return m_worldTransform;
}

void Sound::SetPosition(const Vector3f &position)
{
	m_position = position;
	alSource3f(m_source, AL_POSITION, m_position.m_x, m_position.m_y, m_position.m_z);
	Audio::CheckAl(alGetError());
}

void Sound::SetDirection(const Vector3f &direction)
{
	m_direction = direction;
	alSource3f(m_source, AL_DIRECTION, m_direction.m_x, m_direction.m_y, m_direction.m_z);
	Audio::CheckAl(alGetError());
}

void Sound::SetVelocity(const Vector3f &velocity)
{
	m_velocity = velocity;
	alSource3f(m_source, AL_VELOCITY, m_velocity.m_x, m_velocity.m_y, m_velocity.m_z);
	Audio::CheckAl(alGetError());
}

void Sound::SetGain(const float &gain)
{
	m_gain = gain;
	alSourcef(m_source, AL_GAIN, m_gain * Audio::Get()->GetGain(m_type));
	Audio::CheckAl(alGetError());
}

void Sound::SetPitch(const float &pitch)
{
	m_pitch = pitch;
	alSourcef(m_source, AL_PITCH, m_pitch);
	Audio::CheckAl(alGetError());
}

const Metadata &operator>>(const Metadata &metadata, Sound &sound)
{
	metadata.GetResource("Buffer", sound.m_soundBuffer);
	return metadata;
}

Metadata &operator<<(Metadata &metadata, const Sound &sound)
{
	metadata.SetResource("Buffer", sound.m_soundBuffer);
	return metadata;
}
}
