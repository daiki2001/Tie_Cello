#include"CheckHItManager.h"

// �v���C���[�{�̂ƓG�{�̂̓����蔻��(�P��)
void checkHitManager::checkPlayerEnemy(Player* player, Enemy* enemy)
{
	if (enemy->isAlive == false || player->hitPointManager.getIsAlive() == false)
	{
		return;
	}

	if (player->hitPointManager.getisArmor())
	{
		return;
	}

	if (Collision::checkSphere2Sphere(player->playerCollision, enemy->enemyCollision))
	{
		player->hitPointManager.Damage(1);

		if (!enemy->isThisBoss)
		{
			enemy->HP--;
		}
	}
}

// �v���C���[�{�̂ƓG�{�̂̓����蔻��(�Q��)
void checkHitManager::checkPlayerEnemys(Player* player, list<unique_ptr<Enemy>>* enemys)
{
	for (std::unique_ptr<Enemy>& newenemy : *enemys)
	{
		checkPlayerEnemy(player, newenemy.get());
	}
}

// �v���C���[�̒ʏ�e�ƓG�{�̂̓����蔻��(�P��)
void checkHitManager::checkBulletEnemy(NormalBullet* bullet, Enemy* enemy)
{
	if (enemy->isAlive == false || bullet->isAlive == false)
	{
		return;
	}

	if (enemy->isArmor)
	{
		return;
	}

	if (Collision::checkSphere2Sphere(bullet->bulletCollision, enemy->enemyCollision))
	{
		bullet->bulletCount = 0;
		bullet->isAlive = false;

		enemy->HP--;
	}
}

// �v���C���[�̒ʏ�e�ƓG�{�̂̓����蔻��(�{�X)
void checkHitManager::checkBulletsEnemy(list<unique_ptr<NormalBullet>>* bulletsList, Enemy* enemy)
{
	if (enemy->isAlive == false)
	{
		return;
	}

	if (enemy->isArmor)
	{
		return;
	}

	for (std::unique_ptr<NormalBullet>& newbullet : *bulletsList)
	{
		checkBulletEnemy(newbullet.get(), enemy);
	}
}

// �v���C���[�̒ʏ�e�ƓG�{�̂̓����蔻��(�Q��)
void checkHitManager::checkBulletsEnemys(list<unique_ptr<NormalBullet>>* bulletsList, list<unique_ptr<Enemy>>* enemys)
{
	for (std::unique_ptr<NormalBullet>& newbullet : *bulletsList)
	{
		for (std::unique_ptr<Enemy>& newenemy : *enemys)
		{
			checkBulletEnemy(newbullet.get(), newenemy.get());
		}
	}
}

// �v���C���[�̃~�T�C���ƓG�{�̂̓����蔻��(�P��)
void checkHitManager::checkMissilesEnemy(list<unique_ptr<Missile>>* missilesList)
{
	for (std::unique_ptr<Missile>& newmissile : *missilesList)
	{
		if (newmissile->enemyPointer == nullptr)
		{
			return;
		}

		if (newmissile->enemyPointer->isAlive == true && newmissile->isAlive == true)
		{
			if (Collision::checkSphere2Sphere(newmissile->bulletCollision, newmissile->enemyPointer->enemyCollision))
			{
				if (newmissile->enemyPointer->isThisBoss)
				{
					if (!newmissile->enemyPointer->isArmor)
					{
						newmissile->enemyPointer->HP--;
					}
				}
				else
				{
					if (!newmissile->enemyPointer->isArmor)
					{
						newmissile->enemyPointer->HP = 0;
					}
				}
				newmissile->isTargetSet = false;
				newmissile->enemyPointer->isTargetSet = false;
				newmissile->enemyPointer->isSetMissile = false;
				newmissile->enemyPointer = nullptr;

			}
		}
	}
}

// �v���C���[�̒ʏ�e�ƓG�̗��˒e�̓����蔻��(�P�̓��m)
void checkHitManager::checkBulletEnemyRampage(NormalBullet* playerbullet, NormalBullet* rampagebullet)
{
	if (rampagebullet == nullptr)
	{
		return;
	}

	if (rampagebullet->isAlive == false)
	{
		return;
	}

	if (playerbullet->isAlive == false)
	{
		return;
	}

	if (Collision::checkSphere2Sphere(playerbullet->bulletCollision, rampagebullet->bulletCollision))
	{
		playerbullet->bulletCount = 0;
		playerbullet->isAlive = false;

		rampagebullet->isAlive = false;
		rampagebullet->bulletCount = 0;
	}
}

// �v���C���[�̒ʏ�e�ƓG�̗��˒e�̓����蔻��(list���m)
void checkHitManager::checkBulletsEnemyRampage(list<unique_ptr<NormalBullet>>* bulletsList, Enemy* enemy)
{
	for (std::unique_ptr<NormalBullet>& newbullet : *bulletsList)
	{
		for (std::unique_ptr<NormalBullet>& enemybullet : enemy->normalBullets)
		{
			checkBulletEnemyRampage(newbullet.get(), enemybullet.get());
		}
	}
}

// �v���C���[�{�̂ƓG�̗��˒e�̓����蔻��(�P��)
void checkHitManager::checkPlayerEnemyRampage(Player* player, NormalBullet* rampagebullet)
{
	if (rampagebullet == nullptr)
	{
		return;
	}

	if (rampagebullet->isAlive == false)
	{
		return;
	}

	if (player->hitPointManager.getisArmor() || player->hitPointManager.getIsAlive() == false)
	{
		return;
	}

	if (Collision::checkSphere2Sphere(player->playerCollision, rampagebullet->bulletCollision))
	{
		player->hitPointManager.Damage(1);
		rampagebullet->isAlive = false;
		rampagebullet->bulletCount = 0;
	}
}

// �v���C���[�{�̂ƓG�̗��˒e�̓����蔻��(���X�g)
void checkHitManager::checkPlayerEnemyRampages(Player* player, Enemy* enemy)
{
	for (std::unique_ptr<NormalBullet>& bullet : enemy->normalBullets)
	{
		checkPlayerEnemyRampage(player, bullet.get());
	}
}

// �v���C���[�J�[�\���ƓG�{�̂̃��b�N�I������(�P��)
void checkHitManager::checkRockonEnemy(Player* player, Enemy* enemy, int& targetnum)
{
	if (!player->isRockOn || player->isShotMissile)
	{
		return;
	}

	if (enemy->isAlive == false)
	{
		return;
	}

	if (enemy->isArmor)
	{
		return;
	}

	if (player->hitPointManager.getIsAlive() == false)
	{
		return;
	}

	if (enemy->isArmor)
	{
		return;
	}

	//���b�N�I��������Ԃŗ��ꂷ����Ɖ���
	if (enemy->isFar == true && enemy->isTargetSet)
	{
		enemy->isTargetSet = false;

		if (targetnum > 0)
		{
			targetnum--;
		}
		return;
	}

	if (enemy->toPlayerAngle > 85)
	{
		if (enemy->isTargetSet)
		{
			enemy->isTargetSet = false;

			if (targetnum > 0)
			{
				targetnum--;
			}
		}
		return;
	}

	XMFLOAT2 screenPos = enemy->enemyObject->worldToScleen();

	float dis = sqrtf(powf(player->targetFirst.position.x - screenPos.x, 2) + powf(player->targetFirst.position.y - screenPos.y, 2));

	if (dis < 56.5685f && enemy->isTargetSet == false && targetnum < MaxPlayerMissileNum)
	{
		enemy->isTargetSet = true;
		enemy->rockTarget->size = Enemy::setRockIconSize;

		targetnum++;
	}
}

// �v���C���[�J�[�\���ƓG�{�̂̃��b�N�I������(�Q��)
void checkHitManager::checkRockonEnemys(Player* player, list<unique_ptr<Enemy>>* enemys, int& targetnum)
{
	for (std::unique_ptr<Enemy>& newenemy : *enemys)
	{
		checkRockonEnemy(player, newenemy.get(), targetnum);
	}
}