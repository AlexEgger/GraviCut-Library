#ifndef MYENUMS_H
#define MYENUMS_H

// Enumeration for modules
enum Module
{
    MagazinModule = 0,
    SchieberModule,
    SchereModule,
    AnschlagModule,
    WechslerModule,
    NumberOfModules
};

// Enumeration for module states
enum ModuleState
{
    RunningState = 0,
    CompletedState,
    ErrorState
};

// Enumeration for response values
enum Response
{
    Running = 0,
    Completed,
    Magazin1Empty,
    Magazin2Empty,
    Magazin3Empty
};

#endif // MYENUMS_H