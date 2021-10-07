#include "calculations.h"

void LoadPlayerList(std::vector<Player*>& players, KernelInterface& Driver, const ULONG ProcessId, bool verbose = false)
{
    int i = 0;
    const uint32_t EntityListBaseAddress = Driver.ReadVirtualMemory<uint32_t>(ProcessId, EntityBase, sizeof(uint32_t));

    while (Driver.ReadVirtualMemory<uint32_t>(ProcessId, EntityListBaseAddress + i, sizeof(uint32_t)) > 0xC00000)
    {
        players.push_back(new Player(Driver.ReadVirtualMemory<uint32_t>(ProcessId, EntityListBaseAddress + i, sizeof(uint32_t)), Driver, ProcessId));
        if (verbose)
        {
            std::cout << "Retrieved player in entity list : \n Value : " << std::hex << Driver.ReadVirtualMemory<uint32_t>(ProcessId, EntityListBaseAddress + i, sizeof(uint32_t)) <<
                std::dec << "    Address : " << std::hex << EntityListBaseAddress + i << std::dec << std::endl;
        }

        i += 4;
    }

    if (verbose)
        std::cout << "\n Loaded " << (i / 4) << " players.\n" << std::endl;
}

int main()
{
    KernelInterface Driver = KernelInterface("\\\\.\\AcAimbot");
    ULONG processid = Driver.GetProcessId();
    std::vector<Player*> PlayerList;
    Player UserPlayer(Driver.ReadVirtualMemory<uint32_t>(processid, 0x50F4F4, sizeof(uint32_t)), Driver, processid);

    std::cout << "Process ID : " << processid << std::endl;

    LoadPlayerList(PlayerList, Driver, processid, false);

    Player ClosestPlayer(getClosestPlayer(UserPlayer, PlayerList), Driver, processid);

    system("pause");

    while (1)
    {
        UserPlayer.update();
        ClosestPlayer.update();

        if (ClosestPlayer.getHealth() > 0)
            UserPlayer.aimAt(getAngleX(UserPlayer, ClosestPlayer), getAngleY(UserPlayer, ClosestPlayer));
    }

    for (unsigned int i = 0; i < PlayerList.size(); i++)
        delete PlayerList[i];

    return 0;

}