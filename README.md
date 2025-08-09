# EykNotify - Sistema de Notificações

Include de notificações para SA-MP que exibe notificações de itens adicionados/removidos.

## Video

https://youtu.be/ce0-eSJqPJU

## Características

- ✅ **Até 5 notificações simultâneas**
- ✅ **Layout horizontal** (da direita para esquerda)
- ✅ **Timer automático** de 5 segundos
- ✅ **Cores dinâmicas** (verde para adicionado, vermelho para removido)
- ✅ **Modelos 3D** dos itens
- ✅ **Limpeza automática** na desconexão

## Como Usar

### Função Principal
```pawn
CreateNotification(playerid, model, bool:isGreen, bool:isAdded, amount)
```

**Parâmetros:**
- `playerid` - ID do jogador
- `model` - ID do modelo 3D do item
- `isGreen` - true = verde, false = vermelho
- `isAdded` - true = "Adicionado", false = "Removido"
- `amount` - Quantidade do item

### Exemplos

```pawn
// Item adicionado (verde)
CreateNotification(playerid, 1579, true, true, 5); // +5 AK-47

// Item removido (vermelho)
CreateNotification(playerid, 1579, false, false, 2); // -2 AK-47
```

### Funções Auxiliares

```pawn
// Limpar todas as notificações de um jogador
DestroyAllNotifications(playerid);

// Destruir notificação específica
DestroyNotification(playerid, slot);
```

## Configuração

Constantes configuráveis em `EykNotify.inc`:

```pawn
#define MAX_NOTIFICATIONS 5        // Máximo de notificações

static const NOTIFICATION_WIDTH = 50.0;    // Espaçamento horizontal
static const  NOTIFICATION_START_X = 350.0; // Posição X inicial
static const  NOTIFICATION_START_Y = 313.0; // Posição Y
```

## Compatibilidade

- **SA-MP 0.3.7+**
- **Compatível com outros includes** (usa ALS)
- **Otimizado para performance**

---

**Desenvolvido para SA-MP** | Sistema simples e eficiente
