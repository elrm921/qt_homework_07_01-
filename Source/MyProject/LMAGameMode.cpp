// LeaveMeAlone Game by Netologiya. All RightsReserved.


#include "LMAGameMode.h"
#include "LeaveMeAlone/Public/Player/LMADefaultCharacter.h"
#include "LeaveMeAlone/Public/Player/LMAPlayerController.h"

ALMAGameMode::ALMAGameMode()
{
    DefaultPawnClass = ALMADefaultCharacter::StaticClass();
    PlayerControllerClass = ALMAPlayerController::StaticClass();
}