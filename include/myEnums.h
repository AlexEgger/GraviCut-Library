#ifndef MYENUMS_H
#define MYENUMS_H

// Enumeration for boards
enum Board
{
    BoardFuerAlles = 8,
    Roboter,
    NumberOfLastBoard
};

// Funktion, um den Enum-Wert in einen String umzuwandeln
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

// Enumeration for modules
enum Module
{
    MagazinModule = 0,
    SchereModule,
    SchieberModule,
    AnschlagModule,
    WechslerModule,
    NumberOfModules
};

// Funktion, um den Enum-Wert in einen String umzuwandeln
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
    default:
        return "Invalid Module";
    }
}

// Enumeration for module states
enum ModuleState
{
    RunningState = 0,
    CompletedState,
    ErrorState,
    InvalidState
};

// Funktion, um den Enum-Wert in einen String umzuwandeln
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

// Enumeration for response values
enum Response
{
    Running = 0,
    Completed,
    Magazin1Empty,
    Magazin2Empty,
    Magazin3Empty
};

// Funktion, um den Enum-Wert in einen String umzuwandeln
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

#endif // MYENUMS_H