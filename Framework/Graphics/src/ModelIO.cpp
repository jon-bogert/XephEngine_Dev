#include "Pch.h"
#include "ModelIO.h"

#include "Model.h"

void xe::Graphics::ModelIO::SaveModel(std::filesystem::path filePath, const Model& model)
{
	if (model.meshData.empty())
	{
		LOG("SaveModel -> No model data found");
		return;
	}

	FILE* file = nullptr;
	fopen_s(&file, filePath.u8string().c_str(), "w");
	if (!file)
	{
		return;
	}

	const uint32_t meshCount = static_cast<uint32_t>(model.meshData.size());
	fprintf_s(file, "MeshCount: %d\n", meshCount);
	for (uint32_t i = 0; i < meshCount; ++i)
	{
		const Model::MeshData& meshData = model.meshData[i];
		fprintf_s(file, "Material Index: %d\n", meshData.materialIndex);

		const Mesh& mesh = meshData.mesh;
		const uint32_t vertexCount = static_cast<uint32_t>(mesh.vertices.size());
		fprintf_s(file, "VertexCount: %d\n", vertexCount);

		for (const Vertex& v : mesh.vertices)
		{
			fprintf_s(file, "%f %f %f %f %f %f %f %f %f %f %f\n",
				v.position.x, v.position.y, v.position.z,
				v.normal.x, v.normal.y, v.normal.z,
				v.tangent.x, v.tangent.y, v.tangent.z,
				v.uvCoord.x, v.uvCoord.y);
		}

		const uint32_t indexCount = static_cast<uint32_t>(mesh.indices.size());
		fprintf_s(file, "Index Count: %d\n", indexCount);
		for (uint32_t n = 2; n < indexCount; ++n)
		{
			fprintf_s(file, "%d %d %d\n", mesh.indices[n - 2], mesh.indices[n - 1], mesh.indices[n]);
		}
	}

	fclose(file);
}

void xe::Graphics::ModelIO::LoadModel(std::filesystem::path filePath, Model& model)
{
	FILE* file = nullptr;
	fopen_s(&file, filePath.u8string().c_str(), "r");
	if (!file)
	{
		return;
	}

	uint32_t meshCount = 0;
	fscanf_s(file, "MeshCount: %d\n", &meshCount);
	model.meshData.resize(meshCount);

	for (uint32_t i = 0; i < meshCount; ++i)
	{
		Model::MeshData& meshData = model.meshData[i];
		fscanf_s(file, "Material Index: %d\n", &meshData.materialIndex);

		Mesh& mesh = meshData.mesh;
		uint32_t vertexCount = static_cast<uint32_t>(mesh.vertices.size());
		fscanf_s(file, "VertexCount: %d\n", &vertexCount);
		mesh.vertices.resize(vertexCount);

		for (Vertex& v : mesh.vertices)
		{
			fscanf_s(file, "%f %f %f %f %f %f %f %f %f %f %f\n",
				&v.position.x, &v.position.y, &v.position.z,
				&v.normal.x, &v.normal.y, &v.normal.z,
				&v.tangent.x, &v.tangent.y, &v.tangent.z,
				&v.uvCoord.x, &v.uvCoord.y);
		}

		uint32_t indexCount = static_cast<uint32_t>(mesh.indices.size());
		fscanf_s(file, "Index Count: %d\n", &indexCount);
		mesh.indices.resize(indexCount);

		for (uint32_t n = 2; n < indexCount; ++n)
		{
			fscanf_s(file, "%d %d %d\n", &mesh.indices[n - 2], &mesh.indices[n - 1], &mesh.indices[n]);
		}
	}

	fclose(file);
}

void xe::Graphics::ModelIO::SaveMaterial(std::filesystem::path filePath, const Model& model)
{
	if (model.materialData.empty())
		return;

	filePath.replace_extension("material");

	FILE* file = nullptr;

	fopen_s(&file, filePath.u8string().c_str(), "w");
	if (file == nullptr)
		return;

	uint32_t materialCount = static_cast<uint32_t>(model.materialData.size());
	fprintf_s(file, "Material Count: %d\n", materialCount);
	for (const Model::MaterialData& materialData : model.materialData)
	{
		const Material& m = materialData.material;
		fprintf_s(file, "%f %f %f %f\n", m.ambient.r, m.ambient.g, m.ambient.b, m.ambient.a);
		fprintf_s(file, "%f %f %f %f\n", m.diffuse.r, m.diffuse.g, m.diffuse.b, m.diffuse.a);
		fprintf_s(file, "%f %f %f %f\n", m.specular.r, m.specular.g, m.specular.b, m.specular.a);
		fprintf_s(file, "%f %f %f %f\n", m.emissive.r, m.emissive.g, m.emissive.b, m.emissive.a);
		fprintf_s(file, "Power; %f\n", m.power);

		fprintf_s(file, "%s\n", materialData.diffuseMapName.empty() ? "<none>" : materialData.diffuseMapName.c_str());
		fprintf_s(file, "%s\n", materialData.specularMapName.empty() ? "<none>" : materialData.specularMapName.c_str());
		fprintf_s(file, "%s\n", materialData.displMapName.empty() ? "<none>" : materialData.displMapName.c_str());
		fprintf_s(file, "%s\n", materialData.normalMapName.empty() ? "<none>" : materialData.normalMapName.c_str());

	}
	fclose(file);
}

void xe::Graphics::ModelIO::LoadMaterial(std::filesystem::path filePath, Model& model)
{
	filePath.replace_extension("material");

	FILE* file = nullptr;

	fopen_s(&file, filePath.u8string().c_str(), "r");
	if (file == nullptr)
		return;

	auto TryReadTextureName = [&](auto& filename)
	{
		char buffer[MAX_PATH]{};
		fscanf_s(file, "%s\n", &buffer, (uint32_t)sizeof(buffer));
		if (strcmp(buffer, "<none>") != 0)
		{
			filename = filePath.replace_filename(buffer).string();
		}
	};

	uint32_t materialCount = 0;
	fscanf_s(file, "Material Count: %d\n", &materialCount);
	model.materialData.resize(materialCount);
	for (Model::MaterialData& materialData : model.materialData)
	{
		const Material& m = materialData.material;
		fscanf_s(file, "%f %f %f %f\n", &m.ambient.r, &m.ambient.g, &m.ambient.b, &m.ambient.a);
		fscanf_s(file, "%f %f %f %f\n", &m.diffuse.r, &m.diffuse.g, &m.diffuse.b, &m.diffuse.a);
		fscanf_s(file, "%f %f %f %f\n", &m.specular.r, &m.specular.g, &m.specular.b, &m.specular.a);
		fscanf_s(file, "%f %f %f %f\n", &m.emissive.r, &m.emissive.g, &m.emissive.b, &m.emissive.a);
		fscanf_s(file, "Power; %f\n", &m.power);

		TryReadTextureName(materialData.diffuseMapName);
		TryReadTextureName(materialData.specularMapName);
		TryReadTextureName(materialData.displMapName);
		TryReadTextureName(materialData.normalMapName);
	}
	fclose(file);
}
