#pragma once
#include<memory>
#include<list>
#include"../3D/Collision.h"
#include"../2D/Sprite.h"
#include"../Input/dxInput.h"
#include"../FbxLoder/Object3d_FBX.h"
#include"../camera/FollowCamera.h"
#include"BulletManager.h"
#include"PlayerHitPointManager.h"
#include"../3D/Object3DSingleLine.h"


const int MaxPlayerMissileNum = 8;

class Player
{
public:
	Player();
	~Player();

	void init(dxinput* input, directX* directx);

	void loadUISprite();

	void move();

	void outArea();

	void boostMove();

	void quaternionMove();

	void playerClearMove();

	void playerDeathMove();

	void setStaging(bool isclear);

	void updata();

	void targetUpdata();

	void addMissile(Enemy* enemy, int& targetnum);

	void reset();

	void draw3D(directX* directx);

	void draw2D(directX* directx, int targetnum);

	/// <summary>
	/// �~�j�}�b�v�`��
	/// </summary>
	/// <param name="directx">directX_Bace</param>
	void drawMiniMapIcon(directX* directx);

	//�v���C���[�̈ʒu���擾
	XMFLOAT3 getPlayerPos() { return playerObject->getPosition(); }

	//�v���C���[�̐��ʃx�N�g�����擾
	XMFLOAT3 getPlayerFront() { return followCamera->getFrontVec(); }

	//�^�[�Q�b�g�A�C�R���̍��W���擾
	XMFLOAT3 getTargetPosition() { return targetFirst.position; }

private:
	static std::unique_ptr<Model> playerModel;

	//�N�H�[�^�j�I����]�s��
	Quaternion qLocal = quaternion(XMFLOAT3(0, 0, 1), 0);
	Quaternion qLocalCamera = quaternion(XMFLOAT3(0, 0, 1), 0);

	//�N�H�[�^�j�I����]�p�x
	float roll = 0.0f;
	float pitch = 0.0f;
	float yow = 0.0f;

	//roll��]����
	float totalRoll = 0.0f;

	//�ړ��X�s�[�h
	float moveSpeed = 0.0f;
	const float defaultMoveSpeed = 0.4f;
	const float boostMoveSpeed = 2.5f;

	SingleSprite remainingMissileNum[9];

	float yowRotateSpeedPositive = 0.0f;//���[��](������)
	float yowRotateSpeedNegative = 0.0f;//���[��](������)
	float pitchRotateSpeedPositive = 0.0f;//�s�b�`��](������)
	float pitchRotateSpeedNegative = 0.0f;//�s�b�`��](������)
	float addRotateSpeed = 0.002f;//���Z��
	float subRotateSpeed = -0.002f;//���Z��
	float limitRotateSpeed = 0.02f;//�ő��]���x

	//�}�E�X�J�[�\���Œ�l
	const int mouseOffsetX = 640;
	const int mouseOffsetY = 360;

	//���]��
	const XMFLOAT3 unitX = { 1,0,0 };
	const XMFLOAT3 unitY = { 0,1,0 };
	const XMFLOAT3 unitZ = { 0,0,1 };

public:
	//3d�I�u�W�F�N�g
	object3dFBX* playerObject = nullptr;

	//�Ǐ]�J����
	FollowCamera* followCamera = nullptr;

	//��O����p�ϐ�
	const XMFLOAT3 groundPosition = { 0,-180,0 };		//�n�ʂ̍��W(�����蔻��p)
	float lengthForPlayerPosition;						//���_����̋���
	bool isOutArea = false;								//�G���A�O�ɂ��邩�ǂ���
	int outAreaCount = 0;								//�G���A�O�ɂ��鎞��(�߂�ƃ��Z�b�g)
	bool isCautionDraw = false;							//�G���A�O�x���̕`��t���O
	SingleSprite outAreaCaution;						//�G���A�O�x��

	//�^�[�Q�b�g�X�v���C�g
	SingleSprite targetFirst;
	int targetCount = 0;
	int rockOnCount = 0;
	bool isRockOn = false;
	SingleSprite targetSecond;
	SingleSprite targetThird;

	//���b�N�I�����[�h�̃Q�[�W
	SingleSprite rockonGauge[2];

	//�Q�[�WUI
	SingleSprite boostGaugeBar;
	SingleSprite gaugeFrame;

	/// <summary>
	/// �~�j�}�b�v��̃A�C�R��
	/// </summary>
	SingleSprite miniMapPlayer;

	//�W�F�b�g�G���W���G�t�F�N�g
	int moveParticlesCount = 0;

	//�e
	std::unique_ptr<BulletManager> bulletManager;

	//����
	static dxinput* input;

	//�����蔻��
	Sphere playerCollision;

	//HP�}�l�[�W���[
	PlayerHitPointManager hitPointManager;

	//�u�[�X�g
	bool isBoost = false;
	float boostGauge = 0;
	const float maxBoostGauge = 300;

	//�`�悵�Ȃ��t���O
	int isInvisible = -1;

	//��~�t���O
	bool isStop = false;

	//���o�Z�b�g�t���O
	bool isStagingSet = false;

	//�N���A���o����
	bool isClearStaging = false;
	int clearTime = 0;
	const int maxClearTime = 200;

	//�Q�[���I�[�o�[���o
	bool isOverStaging = false;
	int fallCount = 0;
	const int maxFallCount = 360;
	XMFLOAT3 fallRot = { 0,0,0 };
	XMFLOAT3 fallScale = { 0,0,0 };

	//�~�T�C���̔��˃��[�g
	bool isShotMissile = false;
	const int nextMissileTime = 15;
	int waitMissileTime = nextMissileTime;

	//�`���[�g���A���p�ϐ�
	//�t���O
	bool isBoostTutorial = false;
	bool isNormalShot = false;
	bool isHomingMissile = false;
	//�J�E���g
	int cameraMoveCount = 0;//�J����������������
	int normalShotCount = 0;//�ʏ�e����������
	int missileCount = 0;	//�~�T�C������������
	int boostCount = 0;		//����������

	//-------------------���ؗp------------------------------

	
};