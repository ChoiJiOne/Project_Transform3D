#pragma once

#include <vector>

#include "IResource.h"
#include "Vertex3D.h"
#include "VertexBuffer.h"


/**
 * @brief ���� �޽� ���ҽ��Դϴ�.
 */
template <typename VertexType>
class StaticMesh : public IResource
{
public:
	/**
	 * @brief �޽� ���ҽ��� �����մϴ�.
	 *
	 * @param vertices �޽��� ���� ����Դϴ�.
	 * @param indices �޽��� �ε��� ����Դϴ�.
	 */
	explicit StaticMesh(const std::vector<VertexType>& vertices, const std::vector<uint32_t>& indices);


	/**
	 * @brief �޽��� ���� �Ҹ����Դϴ�.
	 *
	 * @note �޽� ���ο��� �Ҵ�� ��Ҹ� �����ϱ� ���ؼ��� �ݵ�� Release�� ȣ���ؾ� �մϴ�.
	 */
	virtual ~StaticMesh();


	/**
	 * @brief �޽��� ���� �����ڿ� ���� �����ڸ� ���������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(StaticMesh);


	/**
	 * @brief �޽��� ���� ���ҽ��� �Ҵ� �����մϴ�.
	 */
	virtual void Release() override;


	/**
	 * @brief �޽� ���ҽ��� ���������ο� ���ε��մϴ�.
	 */
	void Bind();


	/**
	 * @brief ���ε��� �޽� ���ҽ��� ���ε� �����մϴ�.
	 */
	void Unbind();


	/**
	 * @brief �޽��� �ε��� ���� ����ϴ�.
	 *
	 * @return �޽��� �ε��� ���� ��ȯ�մϴ�.
	 */
	uint32_t GetIndexCount() const { return static_cast<uint32_t>(indices_.size()); }


	/**
	 * @brief �޽��� ���� �迭 ������Ʈ�� ����ϴ�.
	 *
	 * @return �޽��� ���� �迭 ������Ʈ�� ��ȯ�մϴ�.
	 */
	uint32_t GetVertexArrayObject() const { return vertexArrayObject_; }


	/**
	 * @brief �޽��� ���� ����� ����ϴ�.
	 *
	 * @return �޽��� ���� ��� ��� �����ڸ� ��ȯ�մϴ�.
	 */
	const std::vector<VertexType>& GetVertices() const { return vertices_; }


private:
	/**
	 * @brief ���� ����Դϴ�.
	 */
	std::vector<VertexType> vertices_;


	/**
	 * @brief ���� ��Ͽ� �����ϴ� �ε��� ����Դϴ�.
	 */
	std::vector<uint32_t> indices_;


	/**
	 * @brief ���� �����͸� �����ϴ� �� �ʿ��� ��� �����Դϴ�.
	 *
	 * @see
	 * - https://www.khronos.org/opengl/wiki/Vertex_Specification#:~:text=has%20the%20details.-,Vertex%20Array%20Object,-Vertex%20Array%20Object
	 * - https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGenVertexArrays.xhtml
	 */
	uint32_t vertexArrayObject_ = 0;


	/**
	 * @brief GPU ���� ���� ���� ������Ʈ�Դϴ�.
	 */
	VertexBuffer vertexBuffer_;


	/**
	 * @brief GPU ���� �ε��� ���� ������Ʈ�� ID ���Դϴ�.
	 */
	uint32_t indexBufferID_ = 0;
};