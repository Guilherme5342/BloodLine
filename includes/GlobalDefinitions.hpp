#pragma once

#ifdef _WIN32
#define BALL_PNG "assets/img/ball2.png"
#define STUB_ANIMATED_SPRITE "assets/img/packedSpriteSheet1.png"s

#define PLAYER_IDLE "assets/img/player/idle.png"
#define PLAYER_RUNNING "assets/img/player/running.png"
#define PLAYER_ATTACK "assets/img/player/jump.png"


#define PAWN_ENEMY_IDLE "assets/img/enemies/knight/_Idle.png"
#define PAWN_ENEMY_MOVE "assets/img/enemies/knight/_Run.png"
#define PAWN_ENEMY_ATTACK "assets/img/enemies/knight/_Attack.png"
#define PAWN_ENEMY_SPECIAL_ATTACK "assets/img/enemies/knight/_AttackCombo.png"


/*TileSets FilePaths*/
#define TILESET_WATER_STUB "assets/map/imageRefs/03 water.png"
#define TILESET_ICE_STUB "assets/img/tileset.png"

/*TileMap FilePaths*/
#define MAP_STUB "assets/map/mapaStub2.csv"

#else
#define BALL_PNG "../assets/img/ball2.png"
#define STUB_ANIMATED_SPRITE "../assets/img/packedSpriteSheet1.png"

#define PLAYER_IDLE "../assets/img/player/idle.png"
#define PLAYER_RUNNING "../assets/img/player/running.png"
#define PLAYER_ATTACK "../assets/img/player/jump.png"


#define PAWN_ENEMY_IDLE "../assets/img/enemies/knight/_Idle.png"
#define PAWN_ENEMY_MOVE "../assets/img/enemies/knight/_Run.png"
#define PAWN_ENEMY_ATTACK "../assets/img/enemies/knight/_Attack.png"
#define PAWN_ENEMY_SPECIAL_ATTACK "../assets/img/enemies/knight/_AttackCombo.png"

#define TILESET_WATER_STUB "../assets/map/imageRefs/03 water.png"
#define TILESET_ICE_STUB "../assets/img/tileset.png"

#define MAP_STUB "../assets/map/mapaStub2.csv"
#endif

enum Action {
	IDLE = 0,
	MOVE = 1,
	ATTACK = 2,
	MAGIC_SPELL = 3
};

enum EnemyTypePhysics { // A Física que define os tipos de inimigos
	GROUND = (1),   
	FLY = (1,0),
};
