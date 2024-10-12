#ifndef MYENUMS_H
#define MYENUMS_H

// Enumeration for modules
enum class Module {
    Magazin = 0,
    Schieber,
    Schere,
    Wechsler,
    Anschlag,
    NumberOfModules
};

// Enumeration for module states
enum class ModuleState {
    Running = 0,
    Completed,
    Error
};

#endif // MYENUMS_H