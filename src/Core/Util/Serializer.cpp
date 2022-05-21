#include "../Window.h"
#include "Serializer.h"
#include "ToYAML.h"
#include "FileIO.h"
#include <iostream>

bool lf::Util::Serializer(Registry* registry, const std::string& filename) {
	using namespace lf::Component;

	YAML::Emitter out;
	out << YAML::BeginSeq;
	for (auto entity: registry->view<Tag>()) {
		out << YAML::BeginMap;

		auto* tag = registry->try_get<Tag>(entity);
		if (tag != nullptr) {
			out << YAML::Key << "Tag";
			out << YAML::Value << tag;
		}
		auto* transform = registry->try_get<Transform>(entity);
		if (transform != nullptr) {
			out << YAML::Key << "Transform";
			out << YAML::Value << transform;
		}
		auto* camera = registry->try_get<Camera>(entity);
		if (camera != nullptr) {
			out << YAML::Key << "Camera";
			out << YAML::Value << camera;
		}
		auto* light = registry->try_get<Light>(entity);
		if (light != nullptr) {
			out << YAML::Key << "Light";
			out << YAML::Value << light;
		}
		auto* spriterenderer = registry->try_get<SpriteRenderer>(entity);
		if (spriterenderer != nullptr) {
			out << YAML::Key << "SpriteRenderer";
			out << YAML::Value << spriterenderer;
		}
		auto* meshrenderer = registry->try_get<MeshRenderer>(entity);
		if (meshrenderer != nullptr) {
			out << YAML::Key << "MeshRenderer";
			out << YAML::Value << meshrenderer;
		}
		out << YAML::EndMap;
	}
	out << YAML::EndSeq;

	return WriteFile(filename, out.c_str());
}

lf::Entity is_entity_present(const lf::Registry* registry, const std::string& id) {
	for (auto [entity, tag]: registry->view<lf::Component::Tag>().each()) {
		if (tag.id == id) return entity;
	}

	return (lf::Entity)0;
}


void lf::Util::Deserializer(Registry* registry, const std::string& filename) {
	using namespace lf::Component;

	std::string src = ReadFile(filename);

	if (src == "") return;

	YAML::Node scene = YAML::LoadFile(filename);

	for (std::size_t i = 0; i < scene.size(); i++) {
		Entity entity;

		if (scene[i]["Tag"]) {
			auto tag = scene[i]["Tag"].as<Tag>();

			entity = is_entity_present(registry, tag.id);
			
			if (entity == (Entity)0)
				entity = registry->create();

			registry->emplace<Tag>(entity, tag);
		} else continue;

		if (scene[i]["Transform"]) {
			registry->emplace<Transform>(entity, scene[i]["Transform"].as<Transform>());
		}
		if (scene[i]["Camera"]) {
			auto camera = scene[i]["Camera"].as<Camera>();
			registry->emplace<Camera>(entity, camera);
			if (camera.enable)
				registry->store<GameWindow>().camera = entity;
		}
		if (scene[i]["Light"]) {
			registry->emplace<Light>(entity, scene[i]["Light"].as<Light>());
		}
		if (scene[i]["SpriteRenderer"]) {
			registry->emplace<SpriteRenderer>(entity, scene[i]["SpriteRenderer"].as<SpriteRenderer>());
		}
		if (scene[i]["MeshRenderer"]) {
			registry->emplace<MeshRenderer>(entity, scene[i]["MeshRenderer"].as<MeshRenderer>());
		}
	}
}
