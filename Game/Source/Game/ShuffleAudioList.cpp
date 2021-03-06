#include "GamePCH.h"
#include "ShuffleAudioList.h"
#include "AudioDataStructures.h"
#include "AudioVoice.h"

void ShuffleAudioList::AddAudio(Audio* audio)
{
	AudioList::AddAudio(audio);
	m_LastPlayed = nullptr;
	Shuffle();
}

void ShuffleAudioList::PlayAudio()
{
	AudioList::PlayAudio();

	if (m_AudioPlaybackCount == m_Audios.size())
	{
		Shuffle();
	}
}

void ShuffleAudioList::Shuffle()
{
	std::random_shuffle(m_Audios.begin(), m_Audios.end());
	m_AudioPlaybackCount = 0;
}

void ShuffleAudioList::DisplayImGuiPanel()
{

	ImGui::Checkbox("Enabled", &isEnabled);

	if (isEnabled == true)
	{
		if (ImGui::Button("Shuffle"))
			Shuffle();
		if (ImGui::Button("Play Next"))
			PlayAudio();

		std::string last_display;
		if (m_LastPlayed != nullptr)
			last_display = "Last Audio Played: " + std::string(m_LastPlayed->GetName());
		else
			last_display = "Last Audio Played: NONE";

		if (IsUsingPublicChannels() == false)
		{
			if (ImGui::Button("Stop"))
				StopAudio();

			ImGui::SliderFloat("Volume", m_Voice->GetVolumePointer(), 0.0f, 1.0f);
			m_Voice->SetVolume(*m_Voice->GetVolumePointer());
		}

		ImGui::Text(last_display.c_str());

		for (unsigned int i = 0; i < m_Audios.size(); i++)
		{
			if (ImGui::TreeNode(m_Audios[i]->GetName()))
			{
				if (ImGui::Button("Play"))
					AudioList::PlayAudio(i);
				if (ImGui::Button("Stop"))
					StopAudio();

				ImGui::TreePop();
			}

		}
	}
}
