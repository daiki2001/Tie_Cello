#pragma once
#include "primitiveScene.h"

class playScene
	:public primitiveScene
{
public:
	//�R���X�g���N�^
	playScene();
	~playScene();

	//���\�[�X�̓ǂݍ���
	void loadResources() override;

	//������
	void initialize() override;

	//�p�����[�^�̃��Z�b�g
	void setParameter() override;

	//�X�V
	void updata() override;

	//�w�i�`��
	void drawBack() override;

	//�`��(3D)
	void draw3D() override;

	//�`��(2D)
	void draw2D() override;

private:
	//�`���[�g���A��
	void tutorial();

private:
	//���o�p�J����
	std::unique_ptr<Camera> stagingCamera;
};