#ifndef MYENUMS_H
#define MYENUMS_H

// Enumeration for modules
enum Module {
    Magazin = 0,
    Schieber,
    Schere,
    Anschlag,
    Wechsler,
    NumberOfModules
};

// Enumeration for module states
enum ModuleState {
    Running = 0,
    Completed,
    Error
};

#endif // MYENUMS_H