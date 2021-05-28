#include "config.h"
#include "../../dependencies/json/json.hpp"

namespace config 
{
	bool setup() 
	{
		ADD_ITEM(bool, "example.test_checkbox", false);
		ADD_ITEM(int, "example.test_slider_int", 0);
		ADD_ITEM(float, "example.test_slider_float", 0.f);
		ADD_ITEM(int, "example.test_combo", 0);

		ADD_ITEM(bool, "visuals.esp.name", true);
		ADD_ITEM(bool, "visuals.esp.health", true);

		return true;
	}

	void save() 
	{
		const auto path = std::filesystem::path(m_folder) /= m_name;

		std::filesystem::create_directory(path.parent_path());

		nlohmann::json out;

		for (auto& item : m_items) {
			nlohmann::json cur;

			cur["identifier"] = item.first;
			cur["type"] = item.second.m_type;

			switch (item.second.m_type) {
			case fnv1a::hash_ct("bool"): cur["inner"] = item.second.get<bool>(); break;
			case fnv1a::hash_ct("float"): cur["inner"] = item.second.get<float>(); break;
			case fnv1a::hash_ct("int"): cur["inner"] = item.second.get<int>(); break;
			case fnv1a::hash_ct("std::vector<int>"): {
				const auto vec = item.second.get<std::vector<int>>();

				nlohmann::json sub;

				for (auto& value : vec) {
					sub.push_back(value);
				}

				cur["inner"] = sub.dump();
			} break;
			case fnv1a::hash_ct("std::vector<float>"): {
				const auto vec = item.second.get<std::vector<float>>();

				nlohmann::json sub;

				for (auto& value : vec) {
					sub.push_back(value);
				}

				cur["inner"] = sub.dump();
			} break;
			case fnv1a::hash_ct("std::vector<bool>"): {
				const auto vec = item.second.get<std::vector<bool>>();

				nlohmann::json sub;

				for (const auto& value : vec) {
					sub.push_back(static_cast<int>(value));
				}

				cur["inner"] = sub.dump();
			} break;
			}

			out.push_back(cur);
		}

		std::ofstream file(path, std::ios::out | std::ios::trunc);

		file << out.dump(4);

		file.close();
	}

	void load() 
	{
		const auto path = std::filesystem::path(m_folder) /= m_name;

		std::filesystem::create_directory(path.parent_path());

		nlohmann::json in;

		std::ifstream file(path, std::ios::in);;

		in = nlohmann::json::parse(file, nullptr, false);

		if (in.is_discarded()) // check is json parse failed
			return;

		file.close();

		for (auto& item : in) {
			const auto hash = item["identifier"].get<uint32_t>();
			if (m_items.find(hash) == m_items.end())
				continue;

			auto& cur_item = m_items.at(hash);

			switch (item["type"].get<uint32_t>()) {
			case fnv1a::hash_ct("bool"): cur_item.set<bool>(item["inner"].get<bool>()); break;
			case fnv1a::hash_ct("float"): cur_item.set<float>(item["inner"].get<float>()); break;
			case fnv1a::hash_ct("int"): cur_item.set<int>(item["inner"].get<int>()); break;
			case fnv1a::hash_ct("std::vector<int>"): {
				const auto vec = nlohmann::json::parse(item["inner"].get<std::string>());

				auto& item_vec = cur_item.get<std::vector<int>>();

				for (auto i = 0u; i < vec.size(); i++) {
					if (i >= item_vec.size())
						continue;

					item_vec.at(i) = vec.at(i).get<int>();
				}
			} break;
			case fnv1a::hash_ct("std::vector<float>"): {
				const auto vec = nlohmann::json::parse(item["inner"].get<std::string>());

				auto& item_vec = cur_item.get<std::vector<float>>();

				for (auto i = 0u; i < vec.size(); i++) {
					if (i >= item_vec.size())
						continue;

					item_vec.at(i) = vec.at(i).get<float>();
				}
			} break;
			case fnv1a::hash_ct("std::vector<bool>"): {
				const auto vec = nlohmann::json::parse(item["inner"].get<std::string>());

				auto& item_vec = cur_item.get<std::vector<bool>>();

				for (auto i = 0u; i < vec.size(); i++) {
					if (i >= item_vec.size())
						continue;

					item_vec.at(i) = vec.at(i).get<int>();
				}
			} break;
			}
		}
	}

	std::string m_name = "default.cfg";
	std::string m_folder = "rain-csgo-base";

	std::unordered_map<uint32_t, item> m_items;
}
