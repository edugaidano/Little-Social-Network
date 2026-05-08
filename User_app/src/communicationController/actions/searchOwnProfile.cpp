#include "../communication_controller.h"

PROFILE_S* CommunicationController::searchOwnProfile() {
    return searchProfile(username);
}