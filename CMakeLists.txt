cmake_minimum_required(VERSION 3.16)

project(PSIOSpaceDungeon LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(SFML_ROOT ${PROJECT_SOURCE_DIR}/SFML-2.5.1/)
include_directories(${SFML_ROOT}/include)
link_directories(${SFML_ROOT}/lib)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(PSIOSpaceDungeon
    include/engine/core/Debuger.h
    include/engine/core/Engine.h
    include/engine/core/Scene.h
    include/engine/core/Vector2.h
    source/engine/core/Vector2.cpp
    source/engine/core/Engine.cpp
    source/engine/core/Scene.cpp
    include/engine/core/Input.h
    source/engine/core/Input.cpp
    include/engine/object/Object.h
    source/engine/object/Object.cpp
    include/engine/component/Component.h
    source/engine/component/Component.cpp
    include/engine/component/Transform.h
    source/engine/component/Transform.cpp
    include/engine/object/Camera.h
    source/engine/object/Camera.cpp
    include/engine/core/CollisionManager.h
    source/engine/core/CollisionManager.cpp
    include/engine/component/Collider.h
    source/engine/component/Collider.cpp
    include/engine/core/VMath.h
    include/game/core/Game.h
    source/game/core/Game.cpp
    source/game/main.cpp
    include/game/scenes/MainScene.h
    include/game/scenes/GameScene.h
    include/game/scenes/StoreScene.h
    source/game/scenes/MainScene.cpp
    source/game/scenes/GameScene.cpp
    source/game/scenes/StoreScene.cpp
    include/engine/object/Button.h
    source/engine/object/Button.cpp
    include/game/core/Asset.h
    include/game/ui/BasicButtons.h
    source/game/ui/BasicButtons.cpp
    include/engine/component/Renderable.h
    source/engine/component/Renderable.cpp
    include/engine/core/Event.h
    source/engine/core/Event.cpp
    include/game/player/PlayerCore.h
    source/game/player/PlayerCore.cpp
    include/game/player/PlayerMove.h
    source/game/player/PlayerMove.cpp
    include/game/core/Parameter.h
    source/game/core/Parameter.cpp
    include/engine/component/AnimationController.h
    source/engine/component/AnimationController.cpp
    source/engine/core/VMath.cpp
    include/game/player/PlayerAnim.h
    source/game/player/PlayerAnim.cpp
    include/game/level/Tilemap.h
    source/game/level/Tilemap.cpp
    include/game/level/LevelGenerator.h
    source/game/level/LevelGenerator.cpp
    include/game/level/LevelManager.h
    source/game/level/LevelManager.cpp
    include/game/core/DataBlock.h
    source/game/core/DataBlock.cpp
    include/game/player/TrackingCamera.h
    source/game/player/TrackingCamera.cpp
    include/game/physics/Rigidbody.h
    source/game/physics/Rigidbody.cpp
    include/game/entity/Entity.h
    source/game/entity/Entity.cpp
    include/game/entity/Weapon.h
    source/game/entity/Weapon.cpp
    include/game/player/PlayerAttack.h
    source/game/player/PlayerAttack.cpp
    include/game/physics/Rycast.h
    source/game/physics/Rycast.cpp
    include/game/entity/BasicEntity.h
    source/game/entity/BasicEntity.cpp
    include/game/core/Tag.h
)

set_target_properties(
    PSIOSpaceDungeon PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/bin/debug"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/bin/release"
)

include(GNUInstallDirs)
install(TARGETS PSIOSpaceDungeon
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

target_link_libraries(PSIOSpaceDungeon
    sfml-graphics
    sfml-window
    sfml-system
)
