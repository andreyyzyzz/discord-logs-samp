/*
    SA-MP Discord Logs System
    
    Um sistema completo para enviar logs formatados ao Discord via discord-connector
    
    Autor: Andrey (quiksilveR) (842x)
    Contribuição: Claude (@anthropic)
    
    Versão: 1.0.0
    Data: 29/04/2025
*/

#include <YSI_Coding\y_hooks>
#include <discord-connector>
#include <discord-cmd>

//==========================================================================
// CONFIGURACAO DO SERVIDOR
//==========================================================================
// Identificacao do Servidor
#define NAME                        "quiksilveR" // Nome curto do Servidor

// IDs de Canais no Discord
#define CANAL_LOGS                  "1365791603737759866"   // Canal de Logs
#define CANAL_PUNICOES       "1234567890123456789" // ID do canal para punições
#define CANAL_AGENDAMENTOS   "1234567890123456789" // ID do canal para agendamentos


/**
 * Funcao para enviar logs formatados para um canal do Discord.
 * 
 * @param title        Titulo do embed (opcional, use "" para padrao).
 * @param channelId    ID do canal Discord onde o log sera enviado.
 * @param username     Nome do usuario que acionou a acao.
 * @param action       Nome da acao/comando executada.
 * @param description  Descricao da acao (formato de mensagem).
 * @param ...          Parâmetros adicionais para formatacao da descricao.
 *
 * @return             1 se o log foi enviado com sucesso, 0 em caso de falha.
 */
stock SendDiscordLog(const title[] = "", const channelId[], const username[], const action[], const description[], ...)
{
    // Verifica se o ID do canal é valido
    new DCC_Channel:channel = DCC_FindChannelById(channelId);
    if(channel == DCC_INVALID_CHANNEL)
        return 0;
    
    // Cria o embed
    new DCC_Embed:embed = DCC_CreateEmbed();
    
    // Define o titulo (usando padrao se vazio)
    if(strlen(title) > 0) {
        DCC_SetEmbedTitle(embed, title);
    } else {
        DCC_SetEmbedTitle(embed, ""NAME" - Sistema de Logs");
    }
    
    // Formata a descricao principal com os argumentos variaveis
    new formatted_desc[512];
    
    // Acessamos os argumentos variáveis diretamente usando getarg()
    if(numargs() > 5) {
        // No máximo 8 argumentos variáveis (ajuste conforme necessário)
        new arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7;
        new num_var_args = numargs() - 5;
        
        if(num_var_args > 0) arg0 = getarg(5);
        if(num_var_args > 1) arg1 = getarg(6);
        if(num_var_args > 2) arg2 = getarg(7);
        if(num_var_args > 3) arg3 = getarg(8);
        if(num_var_args > 4) arg4 = getarg(9);
        if(num_var_args > 5) arg5 = getarg(10);
        if(num_var_args > 6) arg6 = getarg(11);
        if(num_var_args > 7) arg7 = getarg(12);
        
        format(formatted_desc, sizeof(formatted_desc), description, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    } else {
        format(formatted_desc, sizeof(formatted_desc), description);
    }
    
    // Define a descricao do embed
    DCC_SetEmbedDescription(embed, formatted_desc);
    
    // Adiciona informacoes como campos do embed
    new string_temp[128];
    
    // Campo de Usuario
    format(string_temp, sizeof(string_temp), "%s", username);
    DCC_AddEmbedField(embed, "Usuario", string_temp, true);
    
    // Campo de Acao
    format(string_temp, sizeof(string_temp), "%s", action);
    DCC_AddEmbedField(embed, "Acao", string_temp, true);
    
    // Adiciona timestamp (data e hora atual)
    new year, month, day, hour, minute, second;
    getdate(year, month, day);
    gettime(hour, minute, second);
    format(string_temp, sizeof(string_temp), "%02d/%02d/%04d as %02d:%02d:%02d", day, month, year, hour, minute, second);
    DCC_AddEmbedField(embed, "Data/Hora", string_temp, false);
    
    // Define cor do embed
    DCC_SetEmbedColor(embed, 0xFF9900); // Laranja
    
    // Envia o embed para o canal
    DCC_SendChannelEmbedMessage(channel, embed);
    
    return 1;
}

/**
 * Funcao simplificada para enviar logs de punicoes para o Discord.
 * 
 * @param channelId     ID do canal Discord onde o log sera enviado.
 * @param adminName     Nome do administrador que aplicou a punicao.
 * @param targetName    Nome do jogador punido.
 * @param punishType    Tipo de punicao (ex: "Cadeia", "Ban", "Kick").
 * @param reason        Motivo da punicao.
 * @param duration      Duracao da punicao (em minutos, 0 para permanente).
 * @param warnings      Número de avisos aplicados (0 se nao aplicavel).
 *
 * @return              1 se o log foi enviado com sucesso, 0 em caso de falha.
 */
stock SendPunishmentLog(const channelId[], const adminName[], const targetName[], const punishType[], const reason[], duration = 0, warnings = 0)
{
    // Cria o embed
    new DCC_Embed:embed = DCC_CreateEmbed();
    DCC_SetEmbedTitle(embed, ""NAME" - Sistema de Punicoes");
    
    // Descricao principal
    new desc[256];
    format(desc, sizeof(desc), "-# **%s** aplicou uma punicao do tipo **%s** com as seguintes informacoes:", adminName, punishType);
    DCC_SetEmbedDescription(embed, desc);
    
    // String temporaria para formatacao
    new string_temp[128];
    
    // Campos do embed
    format(string_temp, sizeof(string_temp), "%s", targetName);
    DCC_AddEmbedField(embed, "Jogador Punido", string_temp, true);
    
    format(string_temp, sizeof(string_temp), "%s", adminName);
    DCC_AddEmbedField(embed, "Administrador", string_temp, true);
    
    // Adiciona duracao se aplicavel
    if(duration > 0) {
        format(string_temp, sizeof(string_temp), "%d minutos", duration);
        DCC_AddEmbedField(embed, "Duracao", string_temp, true);
    }
    
    // Adiciona avisos se aplicavel
    if(warnings > 0) {
        format(string_temp, sizeof(string_temp), "%d", warnings);
        DCC_AddEmbedField(embed, "Avisos", string_temp, true);
    }
    
    // Adiciona motivo
    format(string_temp, sizeof(string_temp), "%s", reason);
    DCC_AddEmbedField(embed, "Motivo", string_temp, false);
    
    // Adiciona timestamp
    new year, month, day, hour, minute, second;
    getdate(year, month, day);
    gettime(hour, minute, second);
    format(string_temp, sizeof(string_temp), "%02d/%02d/%04d as %02d:%02d:%02d", day, month, year, hour, minute, second);
    DCC_AddEmbedField(embed, "Data/Hora", string_temp, false);
    
    // Define cor do embed (vermelho para punicoes)
    DCC_SetEmbedColor(embed, 0xFF0000);
    
    // Envia o embed para o canal
    new DCC_Channel:channel = DCC_FindChannelById(channelId);
    if(channel == DCC_INVALID_CHANNEL)
        return 0;
        
    DCC_SendChannelEmbedMessage(channel, embed);
    
    return 1;
}

/**
 * Funcao para enviar logs de agendamento de itens/dinheiro para o Discord.
 * 
 * @param channelId    ID do canal Discord onde o log sera enviado.
 * @param adminName    Nome de quem agendou o item/dinheiro.
 * @param targetName   Nome do jogador que recebera o item/dinheiro.
 * @param scheduleType Tipo de agendamento ("Item", "Dinheiro", "Cadeia", etc).
 * @param itemId       ID do item (0 se for dinheiro).
 * @param quantity     Quantidade de itens ou valor do dinheiro.
 * @param reason       Motivo do agendamento (opcional).
 *
 * @return             1 se o log foi enviado com sucesso, 0 em caso de falha.
 */
stock SendScheduleLog(const channelId[], const adminName[], const targetName[], const scheduleType[], itemId = 0, quantity = 0, const reason[] = "")
{
    // Cria o embed
    new DCC_Embed:embed = DCC_CreateEmbed();
    DCC_SetEmbedTitle(embed, ""NAME" - Sistema de Agendamento");
    
    // Descricao principal
    new desc[256];
    format(desc, sizeof(desc), "-# **%s** agendou um **%s** com as seguintes informacoes:", adminName, scheduleType);
    DCC_SetEmbedDescription(embed, desc);
    
    // String temporaria para formatacao
    new string_temp[128];
    
    // Campos do embed
    format(string_temp, sizeof(string_temp), "%s", targetName);
    DCC_AddEmbedField(embed, "Jogador Alvo", string_temp, true);
    
    format(string_temp, sizeof(string_temp), "%s", adminName);
    DCC_AddEmbedField(embed, "Administrador", string_temp, true);
    
    // Adiciona informacoes sobre o item se aplicavel
    if(strcmp(scheduleType, "Item", true) == 0 && itemId > 0) {
        format(string_temp, sizeof(string_temp), "%s (ID: %d)", NomeItemInv(itemId), itemId);
        DCC_AddEmbedField(embed, "Item", string_temp, true);
    }
    
    // Adiciona quantidade/valor
    format(string_temp, sizeof(string_temp), "%d", quantity);
    if(strcmp(scheduleType, "Dinheiro", true) == 0) {
        format(string_temp, sizeof(string_temp), "%s", ConvertMoney(quantity));
    }
    DCC_AddEmbedField(embed, "Quantidade", string_temp, true);
    
    // Adiciona motivo se fornecido
    if(strlen(reason) > 0) {
        format(string_temp, sizeof(string_temp), "%s", reason);
        DCC_AddEmbedField(embed, "Motivo", string_temp, false);
    }
    
    // Adiciona timestamp
    new year, month, day, hour, minute, second;
    getdate(year, month, day);
    gettime(hour, minute, second);
    format(string_temp, sizeof(string_temp), "%02d/%02d/%04d as %02d:%02d:%02d", day, month, year, hour, minute, second);
    DCC_AddEmbedField(embed, "Data/Hora", string_temp, false);
    
    // Define cor do embed (azul para agendamentos)
    DCC_SetEmbedColor(embed, 0x3498DB);
    
    // Envia o embed para o canal
    new DCC_Channel:channel = DCC_FindChannelById(channelId);
    if(channel == DCC_INVALID_CHANNEL)
        return 0;
        
    DCC_SendChannelEmbedMessage(channel, embed);
    
    return 1;
}

//==========================================================================
// COMANDOS DO DISCORD
//==========================================================================

DCMD:testarlogs1(user, canal, params[])
{
    new msg[256];
    format(msg, sizeof(msg), "O admin usou o comando %s para fazer %s", "/rg", "para abrir o rg");

    SendDiscordLog(
    "Logs Gerais", // Titulo do embed (opcional)
    CANAL_LOGS,  // ID do canal
    "quiksilveR",          // Nome do usuario que executou a acao
    "Comandos",             // Tipo de acao
    msg
    /*"O admin usou o comando %s para fazer %s", // Formato da descricao
    "/rg",          // Parâmetro 1 para formatacao
    "para abrir o rg"     // Parâmetro 2 para formatacao*/
    );

    SendPunishmentLog(
    CANAL_PUNICOES, // ID do canal
    "quiksilveR",         // Nome do admin
    "Jogador_Punido",      // Nome do jogador punido
    "Cadeia",              // Tipo de punicao
    "Desobedeceu regras",  // Motivo
    30,                    // Duracao em minutos
    2                      // Quantidade de avisos
    );

    SendScheduleLog(
    CANAL_AGENDAMENTOS, // ID do canal
    "quiksilveR",         // Nome do admin
    "Jogador_Alvo",        // Nome do jogador alvo
    "Item",                // Tipo de agendamento
    522,                   // ID do item
    5,                     // Quantidade
    "Compensacao por bug"  // Motivo (opcional)
    );

    SendScheduleLog(
    CANAL_AGENDAMENTOS, // ID do canal
    "quiksilveR",         // Nome do admin
    "Jogador_Alvo",        // Nome do jogador alvo
    "Dinheiro",            // Tipo de agendamento
    0,                     // ID do item (0 para dinheiro)
    50000,                 // Valor do dinheiro
    "Prêmio por evento"    // Motivo (opcional)
    );
    return 1;
}