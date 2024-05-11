#pragma once

class BaseObject
{
public:
	BaseObject(){}
	virtual ~BaseObject(){}

	//オブジェクトの種類
	enum class ObjectType
	{
		Player,
		Enemy,
		Bullet,
	};

	//仮想関数
	virtual void Update();
	virtual void Draw();
	virtual void Init();
	virtual void Release();

	void SetTexture(std::string _fileName);

	//HIT時の処理
	virtual void OnHit();

	ObjectType GetObjectType() { return m_objType; }

	Math::Vector3 GetPos() { return m_pos; }

	bool GeAliveFlg() { return m_aliveFlg; }

protected:
	KdTexture		m_Tex;
	Math::Vector3	m_pos;
	Math::Matrix	m_mat;
	bool			m_bFlg;

	bool            m_aliveFlg = true;

	ObjectType      m_objType;
};
