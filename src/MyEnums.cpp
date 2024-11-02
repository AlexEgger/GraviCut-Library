#include "MyEnums.h"

// Function definitions
const char *boardToString(Board board)
{
    switch (board)
    {
    case BoardFuerAlles:
        return "BoardFuerAlles";
    case Roboter:
        return "Roboter";
    default:
        return "Invalid Board";
    }
}

const char *moduleToString(Module module)
{
    switch (module)
    {
    case MagazinModule:
        return "MagazinModule";
    case SchereModule:
        return "SchereModule";
    case SchieberModule:
        return "SchieberModule";
    case AnschlagModule:
        return "AnschlagModule";
    case WechslerModule:
        return "WechslerModule";
    case RoboterModule:
        return "RoboterModule";
    default:
        return "Invalid Module";
    }
}

const char *moduleStateToString(ModuleState moduleState)
{
    switch (moduleState)
    {
    case RunningState:
        return "RunningState";
    case CompletedState:
        return "CompletedState";
    case ErrorState:
        return "ErrorState";
    default:
        return "InvalidState";
    }
}

const char *responseToString(Response response)
{
    switch (response)
    {
    case Running:
        return "Running";
    case Completed:
        return "Completed";
    case Magazin1Empty:
        return "Magazin1Empty";
    case Magazin2Empty:
        return "Magazin2Empty";
    case Magazin3Empty:
        return "Magazin3Empty";
    default:
        return "Invalid Response";
    }
}
