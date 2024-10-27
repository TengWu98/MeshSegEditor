﻿#pragma once

#include "pch.h"
#include "Renderer/Camera/Camera.h"
#include "Renderer/Renderer.h"
#include "Renderer/Mesh/MeshElement.h"

#include "entt.hpp"
// #include "ImGuizmo.h"

// struct Gizmo;
class Mesh;

struct Model {
    Model(glm::mat4 &&InTransform)
        : Transform{std::move(InTransform)}, InvTransform{glm::transpose(glm::inverse(Transform))} {}

    glm::mat4 Transform{1};
    // `InvTransform` is the _transpose_ of the inverse of `Transform`.
    // Since this rarely changes, we precompute it and send it to the shader.
    glm::mat4 InvTransform{1};
};

struct SceneNode {
    entt::entity Parent = entt::null;
    std::vector<entt::entity> Children;
    // Maps entities to their index in the models buffer. Includes parent. Only present in parent nodes.
    // This allows for contiguous storage of models in the buffer, with erases but no inserts (only appends, which avoids shuffling memory regions).
    std::unordered_map<entt::entity, unsigned int> ModelIndices;
};

struct MeshCreateInfo
{
    std::string Name;
    glm::mat4 Transform {1};
    bool bIsSelect = true;
    bool bIsVisible = true;
    bool bIsSubmit = true;
};

class Scene
{
public:
    Scene();
    ~Scene();

    entt::entity AddMesh(Mesh&& InMesh, MeshCreateInfo InMeshCreateInfo = {});
    entt::entity AddMesh(const fs::path& MeshFilePath, MeshCreateInfo InMeshCreateInfo = {});
    entt::entity GetSelectedEntity() const;
    entt::entity GetParentEntity(entt::entity Entity) const;

    void SetEntityVisible(entt::entity Entity, bool bIsVisible);

    Camera CreateDefaultCamera() const;
    void Render();
    void RenderGizmos();

public:
    Camera Camera;

    glm::vec4 EdgeColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);        // Used for line mode.
    glm::vec4 MeshEdgeColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);  // Used for faces mode.
    
    entt::registry Registry;
    entt::entity SelectedEntity = entt::null;

    std::unique_ptr<Renderer> RenderPipeline;
    glm::vec4 BackgroundColor = glm::vec4(0.22f, 0.22f, 0.22f, 1.f);

    // std::unique_ptr<Gizmo> Gizmo;

    MeshElement SelectionMeshElement = MeshElement::Face;
    MeshElementIndex SelectedElement;
};