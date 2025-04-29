/*
    Exemplo de uso do sistema de logs Discord
    
    Este arquivo demonstra como utilizar as funções do sistema de logs
*/

#include <a_samp>
#include <discord-connector>
#include <discord_logs>

// Funções externas necessárias para o exemplo
forward NomeItemInv(itemid);
forward ConvertMoney(value);

// Exemplo: Funções de placeholder para testes
stock NomeItemInv(itemid)
{
    new nome[32];
    switch(itemid)
    {
        case 1: format(nome, sizeof(nome), "Celular");
        case 2: format(nome, sizeof(nome), "GPS");
        case 3: format(nome, sizeof(nome), "Pistola");
        default: format(nome, sizeof(nome), "Item Desconhecido");
    }
    return nome;
}

stock ConvertMoney(value)
{
    new string[32];
    format(string, sizeof(string), "R$ %d,00", value);
    return string;
}

// Exemplo de comando que utiliza o sistema de logs
CMD:ban(playerid, params[])
{
    new targetid, reason[128], duration;
    if(sscanf(params, "uis", targetid, duration, reason))
        return SendClientMessage(playerid, -1, "USO: /ban [playerid] [duração em minutos] [motivo]");
        
    new admin_name[MAX_PLAYER_NAME], target_name[MAX_PLAYER_NAME];
    GetPlayerName(playerid, admin_name, sizeof(admin_name));
    GetPlayerName(targetid, target_name, sizeof(target_name));
    
    // Log da punição no Discord
    SendPunishmentLog(CANAL_PUNICOES, admin_name, target_name, "Ban", reason, duration, 0);
    
    // Aplicar a punição...
    
    return 1;
}

// Exemplo de comando de doação que utiliza o sistema de logs
CMD:doar(playerid, params[])
{
    new targetid, quantidade;
    if(sscanf(params, "ii", targetid, quantidade))
        return SendClientMessage(playerid, -1, "USO: /doar [playerid] [quantidade]");
        
    new player_name[MAX_PLAYER_NAME], target_name[MAX_PLAYER_NAME];
    GetPlayerName(playerid, player_name, sizeof(player_name));
    GetPlayerName(targetid, target_name, sizeof(target_name));
    
    // Log da doação no Discord
    SendDiscordLog("Doação de Dinheiro", CANAL_LOGS, player_name, "Doação", 
        "**%s** doou **%s** para **%s**", player_name, ConvertMoney(quantidade), target_name);
    
    // Aplicar a transferência...
    
    return 1;
}

// Exemplo de comando administrativo para agendar item
CMD:agendaritem(playerid, params[])
{
    new targetid, itemid, quantidade, reason[128];
    if(sscanf(params, "iiis", targetid, itemid, quantidade, reason))
        return SendClientMessage(playerid, -1, "USO: /agendaritem [playerid] [itemid] [quantidade] [motivo]");
        
    new admin_name[MAX_PLAYER_NAME], target_name[MAX_PLAYER_NAME];
    GetPlayerName(playerid, admin_name, sizeof(admin_name));
    GetPlayerName(targetid, target_name, sizeof(target_name));
    
    // Log do agendamento no Discord
    SendScheduleLog(CANAL_AGENDAMENTOS, admin_name, target_name, "Item", itemid, quantidade, reason);
    
    // Realizar o agendamento...
    
    return 1;
}