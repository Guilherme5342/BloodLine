#pragma once

#ifdef _WIN32
#define BALL_PNG "assets/img/ball2.png"
#define STUB_ANIMATED_SPRITE "assets/img/packedSpriteSheet1.png"s
#define PLAYER_IDLE "assets/img/playerIdle.png"
#define PLAYER_RUNNING "assets/img/playerRunning.png"
#define PLAYER_ATTACK "assets/img/playerAttack.png"

/*TileSets FilePaths*/
#define TILESET_WATER_STUB "assets/map/imageRefs/03 water.png"
#define TILESET_ICE_STUB "assets/img/tileset.png"

/*TileMap FilePaths*/
#define MAP_STUB "assets/map/mapaStub2.csv"

#else
#define BALL_PNG "../assets/img/ball2.png"
#define STUB_ANIMATED_SPRITE "../assets/img/packedSpriteSheet1.png"
#define PLAYER_IDLE "../assets/img/playerIdle.png"
#define PLAYER_RUNNING "../assets/img/playerRunning.png"
#define PLAYER_ATTACK "../assets/img/playerAttack.png"

#define TILESET_WATER_STUB "../assets/map/imageRefs/03 water.png"
#define TILESET_ICE_STUB "../assets/img/tileset.png"

#define MAP_STUB "../assets/map/mapaStub2.csv"
#endif
