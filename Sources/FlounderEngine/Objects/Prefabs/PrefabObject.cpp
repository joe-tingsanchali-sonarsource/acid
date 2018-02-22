#include "PrefabObject.hpp"

#include "../GameObject.hpp"
#include "../../Helpers/FileSystem.hpp"

namespace Flounder
{
	PrefabObject::PrefabObject(const std::string &filename) :
		IResource(),
		m_filename(filename),
		m_fileCsv(new FileCsv(filename)),
		m_components(new std::unordered_map<std::string, PrefabComponent *>())
	{
		if (!FileSystem::FileExists(filename))
		{
			FileSystem::CreateFile(filename);
		}

		m_fileCsv->Load();

		for (unsigned int i = 0; i < m_fileCsv->GetRowCount(); i++)
		{
			RowCsv row = m_fileCsv->GetRow(i);

			if (!row.m_elements.empty())
			{
				std::string name = row.m_elements.at(0);
				std::vector<std::string> data = std::vector<std::string>(row.m_elements);
				data.erase(data.begin());
				m_components->insert(std::make_pair(name, new PrefabComponent(data)));
			}
		}
	}

	PrefabObject::~PrefabObject()
	{
		for (auto component : *m_components)
		{
			delete component.second;
		}

		delete m_fileCsv;
		delete m_components;
	}

	void PrefabObject::Write(GameObject *gameObject)
	{
		for (auto component : *m_components)
		{
			delete component.second;
		}

		m_components->clear();

		for (auto component : *gameObject->GetComponents())
		{
			PrefabComponent *componentPrefab = new PrefabComponent(std::vector<std::string>());
			component->Write(componentPrefab);
			m_components->insert(std::make_pair(component->GetName(), componentPrefab));
		}
	}

	void PrefabObject::Save()
	{
		m_fileCsv->Clear();

		for (auto component : *m_components)
		{
			std::vector<std::string> data = std::vector<std::string>();
			data.push_back(component.first);

			for (const auto &i : component.second->GetData())
			{
				data.push_back(i);
			}

			RowCsv row = RowCsv(data);
			m_fileCsv->PushRow(row);
		}

		m_fileCsv->Save();
	}

	PrefabComponent *PrefabObject::GetComponentData(const std::string &component)
	{
		auto it = m_components->find(component);

		if (it != m_components->end())
		{
			return (*it).second;
		}

		return nullptr;
	}

	std::vector<std::string> PrefabObject::GetComponents()
	{
		std::vector<std::string> keys = std::vector<std::string>();

		for (auto it : *m_components)
		{
			keys.push_back(it.first);
		}

		return keys;
	}
}
