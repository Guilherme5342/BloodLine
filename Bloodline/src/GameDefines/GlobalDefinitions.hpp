#pragma once

#ifdef _WIN32
#define BALL_PNG "res/img/ball2.png"
#define STUB_ANIMATED_SPRITE "res/img/packedSpriteSheet1.png"s

#define PLAYER_IDLE "res/img/player/run.png"//"res/img/player/idle.png"
#define PLAYER_JUMP "res/img/player/run.png" //"res/img/player/jump.png"
#define PLAYER_RUNNING "res/img/player/run.png"
#define PLAYER_ATTACK "res/img/player/run.png"//"res/img/player/jump.png"


#define PAWN_ENEMY_IDLE "res/img/enemies/knight/_Idle.png"
#define PAWN_ENEMY_MOVE "res/img/enemies/knight/_Run.png"
#define PAWN_ENEMY_ATTACK "res/img/enemies/knight/_Attack.png"
#define PAWN_ENEMY_SPECIAL_ATTACK "res/img/enemies/knight/_SpecialAttack.png"


/*TileSets FilePaths*/
#define TILESET_WATER_STUB "res/map/imageRefs/03 water.png"
#define TILESET_ICE_STUB "res/img/tileset.png"

/*TileMap FilePaths*/
#define MAP_STUB "res/map/mapaStub2.csv"

#else
#define BALL_PNG "../res/img/ball2.png"
#define STUB_ANIMATED_SPRITE "../res/img/packedSpriteSheet1.png"

#define PLAYER_IDLE "../res/img/player/idle.png"
#define PLAYER_JUMP "../res/img/player/jump.png"
#define PLAYER_RUNNING "../res/img/player/run.png"
#define PLAYER_ATTACK "../res/img/player/jump.png"


#define PAWN_ENEMY_IDLE "../res/img/enemies/knight/_Idle.png"
#define PAWN_ENEMY_MOVE "../res/img/enemies/knight/_Run.png"
#define PAWN_ENEMY_ATTACK "../res/img/enemies/knight/_Attack.png"
#define PAWN_ENEMY_SPECIAL_ATTACK "../res/img/enemies/knight/_AttackCombo.png"

#define TILESET_WATER_STUB "../res/map/imageRefs/03 water.png"
#define TILESET_ICE_STUB "../res/img/tileset.png"

#define MAP_STUB "../res/map/mapaStub2.csv"
#endif

enum class Action {
	IDLE = 0,
	MOVE = 1,
	ATTACK = 2,
	MAGIC_SPELL = 3
};

enum class EnemyTypePhysics { // A F�sica que define os tipos de inimigos
	GROUND = (1),   
	FLY = (1,0),
};
