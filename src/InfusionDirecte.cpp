#include "InfusionDirecte.h"

#include "Machine.h"

void InfusionDirecte::executerEtapes(Machine& machine) const
{
    const ParametresInfusion& p = parametres();
    machine.chaufferEau(p.temperature);
    machine.verserEau(p.volumeService);
    machine.doserThe(p.the, p.quantiteThe);
    infuserEtServir(machine);
}
