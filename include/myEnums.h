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

#endif // MYENUMS_H