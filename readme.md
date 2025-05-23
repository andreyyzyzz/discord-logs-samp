# SAMP Discord Logs System

Um sistema completo de logs via Discord para servidores SA-MP, fornecendo funções para enviar logs formatados com embeds para canais específicos do Discord.

## Características

- Sistema de logs gerais para diversas ações no servidor
- Sistema específico para logs de punições (ban, kick, cadeia, etc.)
- Sistema para logs de agendamentos (itens, dinheiro, etc.)
- Embeds personalizados com informações detalhadas
- Formatação com timestamps automáticos

## Requisitos

- [SA-MP Server](https://www.sa-mp.com/)
- [discord-connector](https://github.com/maddinat0r/samp-discord-connector)
- [YSI Library (Caso for usar como modulo)](https://github.com/pawn-lang/YSI-Includes)

## Instalação

1. Certifique-se de ter o plugin discord-connector instalado e configurado no seu servidor
2. Copie os arquivos para a pasta `pawno/includes` do seu servidor
3. Inclua o arquivo principal usando `#include <discord_logs>` no seu script
4. Configure os IDs dos canais Discord nas definições

## Imagens

![Discord Banner](./screens/logs-gerais.png)


![Discord Banner](./screens/punicoes.png)


![Discord Banner](./screens/item.png)


![Discord Banner](./screens/money.png)

## Uso

### Log Geral

```pawn
SendDiscordLog("Título Personalizado", CANAL_LOGS, "NomeJogador", "Compra", "Comprou um veículo %s por %s", NomeVeiculo, ValorFormatado);
```

### Log de Punição

```pawn
SendPunishmentLog(CANAL_PUNICOES, "Admin", "Jogador", "Ban", "Comportamento inadequado", 60, 2);
```

### Log de Agendamento

```pawn
SendScheduleLog(CANAL_AGENDAMENTOS, "Admin", "Jogador", "Item", 45, 10, "Compensação por bug");
```

## Configuração

Edite as definições dos canais no início do arquivo para corresponder aos IDs dos seus canais Discord:

```pawn
#define CANAL_LOGS           "1234567890123456789" // ID do canal para logs gerais
#define CANAL_PUNICOES       "1234567890123456789" // ID do canal para punições
#define CANAL_AGENDAMENTOS   "1234567890123456789" // ID do canal para agendamentos
```

## Créditos

- Desenvolvido por Andrey (quiksilveR) 842x (Discord User)
- Contribuições de Claude (@anthropic)

## Licença

MIT